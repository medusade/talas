///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2015 $organization$
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
///   File: public_key.hpp
///
/// Author: $author$
///   Date: 5/8/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RSA_PUBLIC_KEY_HPP
#define _TALAS_CRYPTO_RSA_PUBLIC_KEY_HPP

#include "talas/crypto/rsa/key.hpp"

namespace talas {
namespace crypto {
namespace rsa {

typedef key_implements public_key_implement_base;
///////////////////////////////////////////////////////////////////////
///  Class: public_key_implementt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = public_key_implement_base>
class _EXPORT_CLASS public_key_implementt: virtual public TImplements {
public:
    typedef TImplements Implements;
};
typedef public_key_implementt<> public_key_implements;

} // namespace rsa
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RSA_PUBLIC_KEY_HPP 