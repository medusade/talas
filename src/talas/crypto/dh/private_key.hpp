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
///   File: private_key.hpp
///
/// Author: $author$
///   Date: 2/11/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DH_PRIVATE_KEY_HPP
#define _TALAS_CRYPTO_DH_PRIVATE_KEY_HPP

#include "talas/crypto/dh/public_key.hpp"

namespace talas {
namespace crypto {
namespace dh {

///////////////////////////////////////////////////////////////////////
///  Class: private_key_implementst
///////////////////////////////////////////////////////////////////////
template <class TImplements = key_implements>

class _EXPORT_CLASS private_key_implementst: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Implements::create;
    virtual bool create
    (const public_key_implements& public_key,
     const byte_t* exponent, size_t expbytes) {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef private_key_implementst<> private_key_implements;
typedef private_key_implements private_key;

///////////////////////////////////////////////////////////////////////
///  Class: private_keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = private_key_implements, class TExtends = key_extend>

class _EXPORT_CLASS private_keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    private_keyt
    (const public_key_implements& public_key,
     const byte_t* exponent, size_t expbytes) {
        if (!(this->create(public_key, exponent, expbytes))) {
            const creator_exception e = failed_to_create;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_create)...")
            throw(e);
        }
    }
    private_keyt(const private_keyt& copy) {
        const creator_exception e = failed_to_create;
        TALAS_LOG_ERROR("...private_keyt(const private_keyt& copy) not allowed throw(const creator_exception e = failed_to_create)...")
        throw(e);
    }
    private_keyt() {
    }
    virtual ~private_keyt() {
        if (!(this->destroyed())) {
            const creator_exception e = failed_to_destroy;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_destroy)...")
            throw(e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef private_keyt<> private_key_extend;

} // namespace dh 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DH_PRIVATE_KEY_HPP 
