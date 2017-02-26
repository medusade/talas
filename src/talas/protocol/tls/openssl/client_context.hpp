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
///   File: client_context.hpp
///
/// Author: $author$
///   Date: 2/22/2017
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_PROTOCOL_TLS_OPENSSL_CLIENT_CONTEXT_HPP
#define _TALAS_PROTOCOL_TLS_OPENSSL_CLIENT_CONTEXT_HPP

#include "talas/protocol/tls/openssl/context.hpp"

namespace talas {
namespace protocol {
namespace tls {
namespace openssl {

typedef contextt_implements client_contextt_implements;
typedef context client_contextt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: client_contextt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = client_contextt_implements,
 class TExtends = client_contextt_extends>

class _EXPORT_CLASS client_contextt: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef typename Extends::attached_t attached_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    client_contextt(const tls::versions& versions) {
        if (!(this->create(versions))) {
            create_exception e(create_failed);
            TALAS_LOG_ERROR("...throwing create_exception e(create_failed)...");
            throw (e);
        }
    }
    client_contextt(attached_t attached = 0, bool is_created = false)
    : Extends(attached, is_created) {
    }
    client_contextt(const client_contextt& copy): Extends(copy) {
    }
    virtual ~client_contextt() {
        if (!(this->destroyed())) {
            create_exception e(destroy_failed);
            TALAS_LOG_ERROR("...throwing create_exception e(destroy_failed)...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual SSL_METHOD* method() const {
        return TLSv1_client_method();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef client_contextt<> client_context;

} // namespace openssl
} // namespace tls 
} // namespace protocol 
} // namespace talas 

#endif // _TALAS_PROTOCOL_TLS_OPENSSL_CLIENT_CONTEXT_HPP 
