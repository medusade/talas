///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
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
///   Date: 2/11/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DH_PUBLIC_KEY_HPP
#define _TALAS_CRYPTO_DH_PUBLIC_KEY_HPP

#include "talas/crypto/dh/key.hpp"

namespace talas {
namespace crypto {
namespace dh {

class _EXPORT_CLASS public_key_implemented;

namespace bn {
class _EXPORT_CLASS public_key_implemented;
} // namespace bn
namespace mp {
class _EXPORT_CLASS public_key_implemented;
} // namespace mp
namespace mbu {
class _EXPORT_CLASS public_key_implemented;
} // namespace mbu

///////////////////////////////////////////////////////////////////////
///  Class: public_key_implementst
///////////////////////////////////////////////////////////////////////
template <class TImplements = key_implements>

class _EXPORT_CLASS public_key_implementst: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t create_secret_msb
    (byte_t* secret, size_t secbytes, const byte_t* exponent, size_t expbytes) {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual public_key_implemented* key_implemented() const {
        return 0;
    }
    virtual bn::public_key_implemented* bn_key_implemented() const {
        return 0;
    }
    virtual mp::public_key_implemented* mp_key_implemented() const {
        return 0;
    }
    virtual mbu::public_key_implemented* mbu_key_implemented() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef public_key_implementst<> public_key_implements;
typedef public_key_implements public_key;

///////////////////////////////////////////////////////////////////////
///  Class: public_keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = public_key_implements, class TExtends = key_extend>

class _EXPORT_CLASS public_keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    public_keyt
    (const unsigned& generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if (!(this->create_msb
             (generator, genbytes, modulus, modbytes, exponent, expbytes))) {
            const creator_exception e = failed_to_create;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_create)...")
            throw(e);
        }
    }
    public_keyt
    (const byte_t* generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if (!(this->create_msb
             (generator, genbytes, modulus, modbytes, exponent, expbytes))) {
            const creator_exception e = failed_to_create;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_create)...")
            throw(e);
        }
    }
    public_keyt(const public_keyt& copy) {
        const creator_exception e = failed_to_create;
        TALAS_LOG_ERROR("...public_keyt(const public_keyt& copy) not allowed throw(const creator_exception e = failed_to_create)...")
        throw(e);
    }
    public_keyt() {
    }
    virtual ~public_keyt() {
        if (!(this->destroyed())) {
            const creator_exception e = failed_to_destroy;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_destroy)...")
            throw(e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef public_keyt<> public_key_extend;

} // namespace dh 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DH_PUBLIC_KEY_HPP 
