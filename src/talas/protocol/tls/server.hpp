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
#ifndef _TALAS_PROTOCOL_TLS_SERVER_HPP
#define _TALAS_PROTOCOL_TLS_SERVER_HPP

#include "talas/protocol/tls/context.hpp"

namespace talas {
namespace protocol {
namespace tls {

typedef implement_base servert_implements;
///////////////////////////////////////////////////////////////////////
///  Class: servert
///////////////////////////////////////////////////////////////////////
template <class TImplements = servert_implements>
class _EXPORT_CLASS servert: virtual public TImplements {
public:
    typedef TImplements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef servert<> server;

} // namespace tls 
} // namespace protocol 
} // namespace talas 

#endif // _TALAS_PROTOCOL_TLS_SERVER_HPP 
