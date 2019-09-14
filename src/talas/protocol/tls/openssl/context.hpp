///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2017 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: context.hpp
///
/// Author: $author$
///   Date: 2/14/2017
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_PROTOCOL_TLS_OPENSSL_CONTEXT_HPP
#define _TALAS_PROTOCOL_TLS_OPENSSL_CONTEXT_HPP

#include "talas/protocol/tls/context.hpp"
#include "talas/protocol/tls/version.hpp"
#include "talas/protocol/tls/openssl/openssl.hpp"

namespace talas {
namespace protocol {
namespace tls {
namespace openssl {

typedef SSL_CTX* context_attached_t;

typedef xos::base::creatort<tls::context> context_creator;
typedef xos::base::attachert
<context_attached_t, int, 0, context_creator> context_attacher;
typedef xos::base::attachedt
<context_attached_t, int, 0, context_attacher> context_attached;
typedef xos::base::createdt
<context_attached_t, int, 0, context_attacher, context_attached> context_created;

typedef context_attacher contextt_implements;
typedef context_created contextt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: contextt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = contextt_implements, class TExtends = contextt_extends>

class _EXPORT_CLASS contextt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef typename Extends::attached_t attached_t;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    contextt(attached_t attached = 0, bool is_created = false)
    : Extends(attached, is_created) {
    }
    contextt(const contextt& copy)
    : Extends(copy.attached_to()) {
    }
    virtual ~contextt() {
        if (!(this->destroyed())) {
            create_exception e(destroy_failed);
            TALAS_LOG_ERROR("...throwing create_exception e(destroy_failed)...");
            throw (e);
        }
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create(const tls::versions& versions) {
        attached_t detacted = 0;
        if ((detacted = create_attached(versions))) {
            this->set_is_created();
            return true;
        }
        return false;
    }
    virtual attached_t create_attached(const tls::versions& versions) {
        if ((this->destroyed())) {
            attached_t detacted = 0;
            if ((detacted = create_detached(versions))) {
                this->attach(detacted);
                return detacted;
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_verify_certificate_file_locations(const string_t& trust, const string_t& certs) {
        return set_verify_certificate_file_locations(trust.chars(), certs.chars());
    }
    virtual bool set_verify_certificate_file_locations(const char* trust, const char* certs) {
        attached_t ctx = 0;
        if ((ctx = this->attached_to())) {
            TALAS_LOG_DEBUG("SSL_CTX_load_verify_locations(ctx, trust = \"" << trust << "\", certs = \"" << certs << "\")...");
            if ((SSL_CTX_load_verify_locations(ctx, trust, certs))) {
                TALAS_LOG_DEBUG("...SSL_CTX_load_verify_locations(ctx, trust = \"" << trust << "\", certs = \"" << certs << "\")");
                if ((this->is_server())) {
                    typedef int (*verify_callback_t)(int, X509_STORE_CTX*);
                    verify_callback_t verify_callback = NULL;
                    int verify_mode = SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT;
                    int verify_depth = this->verify_depth();

                    TALAS_LOG_DEBUG("SSL_CTX_set_verify(ctx, verify_mode, verify_callback)...");
                    SSL_CTX_set_verify(ctx, verify_mode, verify_callback);

                    TALAS_LOG_DEBUG("SSL_CTX_set_verify_depth(ctx, verify_depth)...");
                    SSL_CTX_set_verify_depth(ctx, verify_depth);
                }
                return true;
            } else {
                unsigned long error = 0;
                const char* error_string = 0;
                error_string = ERR_error_string(error = ERR_get_error(), NULL);
                TALAS_LOG_ERROR
                ("failed (" << error << ") \"" << error_string << "\" on " <<
                 "SSL_CTX_load_verify_locations(ctx, trust = \"" << trust << "\", certs = \"" << certs << "\")");
            }
        }
        return false;
    }
    virtual bool set_certificate_file(const string_t& cert) {
        return set_certificate_file(cert.chars());
    }
    virtual bool set_certificate_file(const char* cert) {
        int cert_type = SSL_FILETYPE_PEM;
        attached_t ctx = 0;
        if ((ctx = this->attached_to())) {
            TALAS_LOG_DEBUG("SSL_CTX_use_certificate_file(ctx, cert = \"" << cert << "\", cert_type)...");
            if ((SSL_CTX_use_certificate_file(ctx, cert, cert_type))) {
                TALAS_LOG_DEBUG("...SSL_CTX_use_certificate_file(ctx, cert = \"" << cert << "\", cert_type)");
                return true;
            } else {
                unsigned long error = 0;
                const char* error_string = 0;
                error_string = ERR_error_string(error = ERR_get_error(), NULL);
                TALAS_LOG_ERROR
                ("failed (" << error << ") \"" << error_string << "\" on " <<
                 "SSL_CTX_use_certificate_file(ctx, cert = \"" << cert << "\", cert_type)");
            }
        }
        return false;
    }
    virtual bool set_private_key_file(const string_t& key) {
        return set_private_key_file(key.chars());
    }
    virtual bool set_private_key_file(const char* key) {
        int key_type = SSL_FILETYPE_PEM;
        attached_t ctx = 0;
        if ((ctx = this->attached_to())) {
            TALAS_LOG_DEBUG("SSL_CTX_use_PrivateKey_file(ctx, key = \"" << key << "\", key_type)...");
            if ((SSL_CTX_use_PrivateKey_file(ctx, key, key_type))) {
                TALAS_LOG_DEBUG("...SSL_CTX_use_PrivateKey_file(ctx, key = \"" << key << "\", key_type)");
                if ((verify_private_key(key))) {
                    return true;
                }
            } else {
                unsigned long error = 0;
                const char* error_string = 0;
                error_string = ERR_error_string(error = ERR_get_error(), NULL);
                TALAS_LOG_ERROR
                ("failed (" << error << ") \"" << error_string << "\" on " <<
                 "SSL_CTX_use_PrivateKey_file(ctx, key = \"" << key << "\", key_type)");
            }
        }
        return false;
    }
    virtual bool verify_private_key(const char* key) {
        attached_t ctx = 0;
        if ((ctx = this->attached_to())) {
            TALAS_LOG_DEBUG("SSL_CTX_check_private_key(ctx) key = \"" << key << "\"...");
            if ((SSL_CTX_check_private_key(ctx))) {
                TALAS_LOG_DEBUG("...SSL_CTX_check_private_key(ctx) key = \"" << key << "\"");
                return true;
            } else {
                unsigned long error = 0;
                const char* error_string = 0;
                error_string = ERR_error_string(error = ERR_get_error(), NULL);
                TALAS_LOG_ERROR
                ("failed (" << error << ") \"" << error_string << "\" on " <<
                 "SSL_CTX_check_private_key(ctx) key = \"" << key << "\"");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t create_detached(const tls::versions& versions) const {
        SSL_METHOD* method = 0;
        if ((method = this->method())) {
            attached_t detached = 0;
            TALAS_LOG_DEBUG("SSL_CTX_new(method)...");
            if ((detached = SSL_CTX_new(method))) {
                return detached;
            } else {
                TALAS_LOG_ERROR("...failed on SSL_CTX_new(method)");
            }
        }
        return 0;
    }
    virtual bool destroy_detached(attached_t detached) const {
        if ((detached)) {
            TALAS_LOG_DEBUG("...SSL_CTX_free(detached)");
            SSL_CTX_free(detached);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual SSL_METHOD* method() const {
        return TLSv1_method();
    }
    virtual bool is_server() const {
        return false;
    }
    virtual int verify_depth() const {
        return 10;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef contextt<> context;

} // namespace openssl
} // namespace tls 
} // namespace protocol 
} // namespace talas 

#endif // _TALAS_PROTOCOL_TLS_OPENSSL_CONTEXT_HPP 
