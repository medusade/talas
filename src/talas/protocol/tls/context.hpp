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
///   Date: 2/13/2017
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_PROTOCOL_TLS_CONTEXT_HPP
#define _TALAS_PROTOCOL_TLS_CONTEXT_HPP

#include "talas/protocol/tls/version.hpp"
#include "talas/base/base.hpp"

namespace talas {
namespace protocol {
namespace tls {

typedef implement_base contextt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: contextt
///////////////////////////////////////////////////////////////////////
template <class TImplements = contextt_implements>
class _EXPORT_CLASS contextt: virtual public TImplements {
public:
    typedef TImplements Implements;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_versions(const tls::versions& versions) {
        return false;
    }
    virtual const tls::versions& versions() const {
        static const tls::versions none;
        return none;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef contextt<> context;

} // namespace tls 
} // namespace protocol 
} // namespace talas 

#endif // _TALAS_PROTOCOL_TLS_CONTEXT_HPP 
