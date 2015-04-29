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
///   File: key.hpp
///
/// Author: $author$
///   Date: 4/27/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_ECC_CURVE25519_KEY_HPP
#define _TALAS_CRYPTO_ECC_CURVE25519_KEY_HPP

#include "talas/crypto/ecc/curve25519/array.hpp"

namespace talas {
namespace crypto {
namespace ecc {
namespace curve25519 {

typedef array_implements key_implements;
typedef array key_extends;
///////////////////////////////////////////////////////////////////////
///  Class: keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = key_implements, class TExtends = key_extends>

class _EXPORT_CLASS keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    keyt() {
    }
    keyt(const keyt& copy): Extends(copy) {
    }
    virtual ~keyt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef keyt<> key;

} // namespace curve25519 
} // namespace ecc 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_ECC_CURVE25519_KEY_HPP 
