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
///   File: base_point.hpp
///
/// Author: $author$
///   Date: 4/27/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_ECC_CURVE25519_BASE_POINT_HPP
#define _TALAS_CRYPTO_ECC_CURVE25519_BASE_POINT_HPP

#include "talas/crypto/ecc/curve25519/key.hpp"

namespace talas {
namespace crypto {
namespace ecc {
namespace curve25519 {

#define TALAS_CRYPTO_ECC_CURVE25519_BASE_POINT_VALUE 9

typedef key_implements base_point_implements;
typedef key base_point_extends;
///////////////////////////////////////////////////////////////////////
///  Class: base_pointt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = base_point_implements, class TExtends = base_point_extends>

class _EXPORT_CLASS base_pointt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    base_pointt() {
        byte_t& b = this->operator[](0);
        b = TALAS_CRYPTO_ECC_CURVE25519_BASE_POINT_VALUE;
    }
    base_pointt(const base_pointt& copy): Extends(copy) {
    }
    virtual ~base_pointt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef base_pointt<> base_point;

} // namespace curve25519 
} // namespace ecc 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_ECC_CURVE25519_BASE_POINT_HPP 
