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
///   File: server_context.hpp
///
/// Author: $author$
///   Date: 2/22/2017
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_PROTOCOL_TLS_OPENSSL_SERVER_CONTEXT_HPP
#define _TALAS_PROTOCOL_TLS_OPENSSL_SERVER_CONTEXT_HPP

#include "talas/protocol/tls/openssl/context.hpp"

namespace talas {
namespace protocol {
namespace tls {
namespace openssl {

typedef contextt_implements server_contextt_implements;
typedef context server_contextt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: server_contextt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = server_contextt_implements,
 class TExtends = server_contextt_extends>
class server_contextt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef typename Extends::attached_t attached_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    server_contextt(const tls::versions& versions) {
        if (!(this->create(versions))) {
            create_exception e(create_failed);
            TALAS_LOG_ERROR("...throwing create_exception e(create_failed)...");
            throw (e);
        }
    }
    server_contextt(attached_t attached = 0, bool is_created = false)
    : Extends(attached, is_created) {
    }
    server_contextt(const server_contextt& copy): Extends(copy) {
    }
    virtual ~server_contextt() {
        if (!(this->destroyed())) {
            create_exception e(destroy_failed);
            TALAS_LOG_ERROR("...throwing create_exception e(destroy_failed)...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual SSL_METHOD* method() const {
        return TLSv1_server_method();
    }
    virtual bool is_server() const {
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef server_contextt<> server_context;

} // namespace openssl 
} // namespace tls 
} // namespace protocol 
} // namespace talas 

#endif // _TALAS_PROTOCOL_TLS_OPENSSL_SERVER_CONTEXT_HPP 
