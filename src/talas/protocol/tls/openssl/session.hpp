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
///   File: session.hpp
///
/// Author: $author$
///   Date: 2/22/2017
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_PROTOCOL_TLS_OPENSSL_SESSION_HPP
#define _TALAS_PROTOCOL_TLS_OPENSSL_SESSION_HPP

#include "talas/protocol/tls/openssl/context.hpp"
#include "talas/protocol/tls/openssl/openssl.hpp"

namespace talas {
namespace protocol {
namespace tls {
namespace openssl {

typedef SSL* session_attached_t;

///////////////////////////////////////////////////////////////////////
///  Class: session_implementt
///////////////////////////////////////////////////////////////////////
template
<class TSession,
 class TCreator = xos::base::creatort<TSession>,
 class TImplements = xos::base::attachert
 <session_attached_t, int, 0, TCreator> >

class _EXPORT_CLASS session_implementt: virtual public TImplements {
public:
    typedef TImplements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///  Class: sessiont
///////////////////////////////////////////////////////////////////////
template
<class TSession,
 class TImplements = session_implementt<TSession>,
 class TExtends = xos::base::createdt
 <session_attached_t, int, 0, TImplements,
  xos::base::attachedt<session_attached_t, int, 0, TImplements> > >

class _EXPORT_CLASS sessiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef typename Extends::attached_t attached_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    sessiont
    (attached_t attached = 0, bool is_created = false)
    : Extends(attached, is_created) {
    }
    sessiont(const sessiont& copy): Extends(copy) {
    }
    virtual ~sessiont() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual attached_t create_detached(context::attached_t ctx) const {
        if ((ctx)) {
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
};

} // namespace openssl 
} // namespace tls 
} // namespace protocol 
} // namespace talas 

#endif // _TALAS_PROTOCOL_TLS_OPENSSL_SESSION_HPP 
