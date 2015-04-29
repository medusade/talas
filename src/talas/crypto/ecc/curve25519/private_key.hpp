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
///   File: private_key.hpp
///
/// Author: $author$
///   Date: 4/27/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_ECC_CURVE25519_PRIVATE_KEY_HPP
#define _TALAS_CRYPTO_ECC_CURVE25519_PRIVATE_KEY_HPP

#include "talas/crypto/ecc/curve25519/key.hpp"
#include "talas/crypto/random/generator.hpp"

#define TALAS_CRYPTO_ECC_CURVE25519_PRIVATE_KEY_MASK_BEGIN 248
#define TALAS_CRYPTO_ECC_CURVE25519_PRIVATE_KEY_MASK_END 127
#define TALAS_CRYPTO_ECC_CURVE25519_PRIVATE_KEY_BITS_END 64

namespace talas {
namespace crypto {
namespace ecc {
namespace curve25519 {

typedef key_implements private_key_implemets;
typedef key private_key_extends;
///////////////////////////////////////////////////////////////////////
///  Class: private_keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = private_key_implemets, class TExtends = private_key_extends>

class _EXPORT_CLASS private_keyt: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    private_keyt(random::generator& r) {
        byte_t* b = &(this->operator[](0));
        size_t size = this->size();
        r.generate(b, size);
        b[0] &= TALAS_CRYPTO_ECC_CURVE25519_PRIVATE_KEY_MASK_BEGIN;
        b[size-1] &= TALAS_CRYPTO_ECC_CURVE25519_PRIVATE_KEY_MASK_END;
        b[size-1] |= TALAS_CRYPTO_ECC_CURVE25519_PRIVATE_KEY_BITS_END;
    }
    private_keyt() {
    }
    private_keyt(const private_keyt& copy): Extends(copy) {
    }
    virtual ~private_keyt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef private_keyt<> private_key;

} // namespace curve25519 
} // namespace ecc 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_ECC_CURVE25519_PRIVATE_KEY_HPP 
