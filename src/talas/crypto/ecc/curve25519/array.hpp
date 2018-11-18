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
///   File: array.hpp
///
/// Author: $author$
///   Date: 4/27/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_ECC_CURVE25519_ARRAY_HPP
#define _TALAS_CRYPTO_ECC_CURVE25519_ARRAY_HPP

#include "talas/crypto/base.hpp"
#include "talas/base/base.hpp"
#include "talas/io/logger.hpp"
#include "xos/base/array.hpp"

#define TALAS_CRYPTO_ECC_CURVE25519_KEY_SIZE 32

namespace talas {
namespace crypto {
namespace ecc {
namespace curve25519 {

typedef crypto::base_implements array_implements;
typedef xos::base::arrayt
<byte_t, size_t, TALAS_CRYPTO_ECC_CURVE25519_KEY_SIZE,
 crypto::base, array_implements> array_extends;
///////////////////////////////////////////////////////////////////////
///  Class: arrayt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = array_implements, class TExtends = array_extends>

class _EXPORT_CLASS arrayt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    arrayt(): Extends(TALAS_CRYPTO_ECC_CURVE25519_KEY_SIZE) {
        this->zero();
    }
    arrayt(const arrayt& copy): Extends(copy) {
    }
    virtual ~arrayt() {
        this->zero();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void zero() {
        byte_t& b = this->operator[](0);
        talas::bytes_t::set(&b, 0, TALAS_CRYPTO_ECC_CURVE25519_KEY_SIZE);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual byte_t& operator[](size_t index) const {
        byte_t* b = 0;
        if ((TALAS_CRYPTO_ECC_CURVE25519_KEY_SIZE != (this->size()))
            || (TALAS_CRYPTO_ECC_CURVE25519_KEY_SIZE != (this->length()))
            || (!(b = this->elements()))) {
            TALAS_LOG_ERROR("...unexpected condition throw (error_failed)...");
            throw (error_failed);
        } else {
            if (index >= TALAS_CRYPTO_ECC_CURVE25519_KEY_SIZE) {
                TALAS_LOG_ERROR("...index [" << index << "] out of range throw (error_failed)...");
                throw (error_failed);
            }
        }
        return b[index];
    }
};
typedef arrayt<> array;

} // namespace curve25519 
} // namespace ecc 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_ECC_CURVE25519_ARRAY_HPP 
