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
///   Date: 4/27/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_ECC_CURVE25519_PUBLIC_KEY_HPP
#define _TALAS_CRYPTO_ECC_CURVE25519_PUBLIC_KEY_HPP

#include "talas/crypto/ecc/curve25519/private_key.hpp"
#include "talas/crypto/ecc/curve25519/base_point.hpp"

namespace talas {
namespace crypto {
namespace ecc {
namespace curve25519 {

typedef key_implements public_key_implements;
typedef key public_key_extends;
///////////////////////////////////////////////////////////////////////
///  Class: public_keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = public_key_implements, class TExtends = public_key_extends>

class _EXPORT_CLASS public_keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    public_keyt(const private_key& from_private, const base_point& from_base) {
        if (!(this->generate(from_private, from_base))) {
            error e = error_failed;
            TALAS_LOG_ERROR("...failed on generate() throwing error " << e);
            throw (e);
        }
    }
    public_keyt() {
    }
    public_keyt(const public_keyt& copy): Extends(copy) {
    }
    virtual ~public_keyt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool generate
    (const private_key& from_private, const base_point& from_base) {
        return generate(*this, from_private, from_base);
    }
    virtual bool generate
    (key& to, const private_key& from_private, const key& from_public) const {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef public_keyt<> public_key;

} // namespace curve25519 
} // namespace ecc 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_ECC_CURVE25519_PUBLIC_KEY_HPP 
