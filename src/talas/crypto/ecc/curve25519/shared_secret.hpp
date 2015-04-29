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
///   File: shared_secret.hpp
///
/// Author: $author$
///   Date: 4/27/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_ECC_CURVE25519_SHARED_SECRET_HPP
#define _TALAS_CRYPTO_ECC_CURVE25519_SHARED_SECRET_HPP

#include "talas/crypto/ecc/curve25519/public_key.hpp"
#include "talas/crypto/ecc/curve25519/private_key.hpp"

namespace talas {
namespace crypto {
namespace ecc {
namespace curve25519 {

typedef public_key_implements shared_secret_implements;
typedef public_key shared_secret_extends;
///////////////////////////////////////////////////////////////////////
///  Class: shared_secrett
///////////////////////////////////////////////////////////////////////
template
<class TImplements = shared_secret_implements, class TExtends = shared_secret_extends>

class _EXPORT_CLASS shared_secrett: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    shared_secrett
    (const private_key& from_private, const public_key& from_public) {
        if (!(this->generate(from_private, from_public))) {
            error e = error_failed;
            TALAS_LOG_ERROR("...failed on generate() throwing error " << e);
            throw (e);
        }
    }
    shared_secrett() {
    }
    virtual ~shared_secrett() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool generate
    (const private_key& from_private, const public_key& from_public) {
        return from_public.generate(*this, from_private, from_public);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef shared_secrett<> shared_secret;

} // namespace curve25519 
} // namespace ecc 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_ECC_CURVE25519_SHARED_SECRET_HPP 
