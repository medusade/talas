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
///   File: client.hpp
///
/// Author: $author$
///   Date: 2/15/2017
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_PROTOCOL_TLS_OPENSSL_CLIENT_HPP
#define _TALAS_PROTOCOL_TLS_OPENSSL_CLIENT_HPP

#include "talas/protocol/tls/openssl/context.hpp"
#include "talas/protocol/tls/openssl/connection.hpp"
#include "talas/protocol/tls/client.hpp"

namespace talas {
namespace protocol {
namespace tls {
namespace openssl {

typedef SSL* client_attached_t;

typedef nadir::creatort<tls::client> client_creator;
typedef nadir::attachert
<client_attached_t, int, 0, client_creator> client_attacher;
typedef nadir::attachedt
<client_attached_t, int, 0, client_attacher> client_attached;
typedef nadir::createdt
<client_attached_t, int, 0, client_attacher, client_attached> client_created;

typedef client_attacher clientt_implements;
typedef client_created clientt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: clientt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = clientt_implements, class TExtends = clientt_extends>

class _EXPORT_CLASS clientt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef typename Extends::attached_t attached_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    clientt
    (client_context& context,
     attached_t attached = 0, bool is_created = false)
    : Extends(attached, is_created), context_(context) {
    }
    clientt(clientt& copy)
    : Extends(copy.atttached_to()), context_(copy.context()) {
    }
    virtual ~clientt() {
        if (!(this->destroyed())) {
            create_exception e(destroy_failed);
            TALAS_LOG_ERROR("...throwing create_exception e(destroy_failed)...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool connect(openssl::connection& connection) {
        protocol::tls::openssl::BIO_RW& rw = connection.rw();
        SSL* ssl = 0;
        if ((ssl = this->attached_to())) {
            BIO *rw_bio = 0;
            long verify = 0;
            unsigned long error = 0;
            char* error_string = 0;

            TALAS_LOG_DEBUG("protocol::tls::openssl::BIO_new_rw(&rw)...");
            if ((rw_bio = protocol::tls::openssl::BIO_new_rw(&rw))) {
                TALAS_LOG_DEBUG("...protocol::tls::openssl::BIO_new_rw(&rw)");

                TALAS_LOG_DEBUG("...SSL_set_bio(ssl, rw_bio, rw_bio)");
                SSL_set_bio(ssl, rw_bio, rw_bio);
                rw_bio = 0;

                TALAS_LOG_DEBUG("SSL_connect(ssl)...");
                if (1 == (SSL_connect(ssl))) {
                    TALAS_LOG_DEBUG("...SSL_connect(ssl)");

                    TALAS_LOG_DEBUG("X509_V_OK == (SSL_get_verify_result(ssl))...");
                    if (X509_V_OK == (verify = SSL_get_verify_result(ssl))) {
                        TALAS_LOG_DEBUG("...X509_V_OK == (SSL_get_verify_result(ssl))");

                        connection.attach(ssl);
                        return true;
                    } else {
                        TALAS_LOG_ERROR("...failed X509_V_OK != (" << verify << " = SSL_get_verify_result(ssl))");
                    }
                } else {
                    error_string = ERR_error_string(error = ERR_get_error(), NULL);
                    TALAS_LOG_ERROR
                    ("failed (" << error << ") \"" << error_string << "\" on " <<
                     "SSL_connect(ssl)");
                }
            } else {
                TALAS_LOG_ERROR("...failed on protocol::tls::openssl::BIO_new_rw(&rw)");
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t create_detached() const {
        client_context::attached_t ctx = 0;
        if ((ctx = context_.attached_to())) {
            attached_t ssl = 0;
            TALAS_LOG_DEBUG("ssl = SSL_new(ctx)...");
            if ((ssl = SSL_new(ctx))) {
                TALAS_LOG_DEBUG("...ssl = SSL_new(ctx))");
                return ssl;
            } else {
                TALAS_LOG_ERROR("...failed on SSL_new(ctx)");
            }
        }
        return 0;
    }
    virtual bool destroy_detached(attached_t detached) const {
        if ((detached)) {
            TALAS_LOG_DEBUG("...SSL_free(detached)");
            SSL_free(detached);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual client_context& context() const {
        return ((client_context&)context_);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    client_context& context_;
};
typedef clientt<> client;

} // namespace openssl 
} // namespace tls 
} // namespace protocol 
} // namespace talas 

#endif // _TALAS_PROTOCOL_TLS_OPENSSL_CLIENT_HPP 
