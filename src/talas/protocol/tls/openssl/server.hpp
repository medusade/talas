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
///   File: server.hpp
///
/// Author: $author$
///   Date: 2/23/2017
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_PROTOCOL_TLS_OPENSSL_SERVER_HPP
#define _TALAS_PROTOCOL_TLS_OPENSSL_SERVER_HPP

#include "talas/protocol/tls/openssl/server_context.hpp"
#include "talas/protocol/tls/openssl/session.hpp"
#include "talas/protocol/tls/openssl/context.hpp"
#include "talas/protocol/tls/openssl/connection.hpp"
#include "talas/protocol/tls/server.hpp"

namespace talas {
namespace protocol {
namespace tls {
namespace openssl {

typedef session_implementt<tls::server> servert_implements;
typedef sessiont<tls::server> servert_extends;
///////////////////////////////////////////////////////////////////////
///  Class: servert
///////////////////////////////////////////////////////////////////////
template
<class TImplements = servert_implements, class TExtends = servert_extends>
class _EXPORT_CLASS servert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef typename Extends::attached_t attached_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    servert
    (server_context& context,
     attached_t attached = 0, bool is_created = false)
    : Extends(attached, is_created), context_(context) {
    }
    servert(servert& copy)
    : Extends(copy), context_(copy.context()) {
    }
    virtual ~servert() {
        if (!(this->destroyed())) {
            create_exception e(destroy_failed);
            TALAS_LOG_ERROR("...throwing create_exception e(destroy_failed)...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool accept(openssl::connection& connection) {
        protocol::tls::openssl::BIO_RW& rw = connection.rw();
        SSL* ssl = 0;
        if ((ssl = this->attached_to())) {
            bool success = false;
            BIO *rw_bio = 0;
            int did_accept = 0;

            TALAS_LOG_DEBUG("protocol::tls::openssl::BIO_new_rw(&rw)...");
            if ((rw_bio = protocol::tls::openssl::BIO_new_rw(&rw))) {
                TALAS_LOG_DEBUG("...protocol::tls::openssl::BIO_new_rw(&rw)");

                TALAS_LOG_DEBUG("...SSL_set_bio(ssl, rw_bio, rw_bio)");
                SSL_set_bio(ssl, rw_bio, rw_bio);
                rw_bio = 0;

                TALAS_LOG_DEBUG("SSL_accept(ssl)...");
                if (1 == (did_accept = SSL_accept(ssl))) {
                    TALAS_LOG_DEBUG("...SSL_accept(ssl)");
                    success = true;
                } else {
                    unsigned long error = 0;
                    const char* error_string = ERR_error_string(error = ERR_get_error(), NULL);
                    TALAS_LOG_MESSAGE_DEBUG
                    ("...failed (" << error << ") \"" << error_string << "\" on " <<
                     "SSL_accept(ssl)");
                }
                if ((rw_bio)) {
                    TALAS_LOG_DEBUG("...BIO_free_all(rw_bio)");
                    BIO_free_all(rw_bio);
                    rw_bio = 0;
                }
            } else {
                TALAS_LOG_ERROR("...failed on protocol::tls::openssl::BIO_new_rw(&rw)");
            }
            return success;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::create_detached;
    virtual attached_t create_detached() const {
        server_context::attached_t ctx = 0;
        if ((ctx = context_.attached_to())) {
            return this->create_detached(ctx);
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual server_context& context() const {
        return ((server_context&)context_);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    server_context& context_;
};
typedef servert<> server;

} // namespace openssl 
} // namespace tls 
} // namespace protocol 
} // namespace talas 

#endif // _TALAS_PROTOCOL_TLS_OPENSSL_SERVER_HPP 
