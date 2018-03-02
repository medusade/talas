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
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef public_key_implementt<> public_key_implements;

typedef public_key_implements public_key_implements;
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
    public_keyt
    (const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if (!(this->create_msb(modulus, modbytes, exponent, expbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create_msb(modulus, modbytes, exponent, expbytes) throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    public_keyt(size_t modbytes, size_t expbytes) {
        if (!(this->create(modbytes, expbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create(modbytes, expbytes) throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    public_keyt(const public_keyt& copy) {
        xos::base::creator_exception e = xos::base::failed_to_create;
        TALAS_LOG_ERROR("...throwing creator_exception failed_to_create...");
        throw (e);
    }
    public_keyt() {
    }
    virtual ~public_keyt() {
        if (!(this->destroyed())) {
            xos::base::creator_exception e = xos::base::failed_to_destroy;
            TALAS_LOG_ERROR("...failed on destroyed() throwing creator_exception failed_to_destroy...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef public_keyt<> public_key;

} // namespace rsa
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RSA_PUBLIC_KEY_HPP 
