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

#include "talas/crypto/dh/key.hpp"

namespace talas {
namespace crypto {
namespace dh {

typedef key_implements private_key_implementst_implements;
///////////////////////////////////////////////////////////////////////
///  Class: private_key_implementst
///////////////////////////////////////////////////////////////////////
template
<class TImplements = private_key_implementst_implements>

class _EXPORT_CLASS private_key_implementst: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create_msb
    (const unsigned& generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if ((generator) && (genbytes) && (modulus) && (modbytes) && (exponent) && (expbytes)) {
            if ((this->create(genbytes, modbytes, expbytes))) {
                if ((this->set_msb
                     (generator, genbytes, modulus, modbytes, exponent, expbytes))) {
                    return true;
                }
                this->destroy();
            }
        }
        return false;
    }
    virtual bool create_msb
    (const byte_t* generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if ((generator) && (genbytes) && (modulus) && (modbytes) && (exponent) && (expbytes)) {
            if ((this->create(genbytes, modbytes, expbytes))) {
                if ((this->set_msb
                     (generator, genbytes, modulus, modbytes, exponent, expbytes))) {
                    return true;
                }
                this->destroy();
            }
        }
        return false;
    }
    virtual bool create(size_t genbytes, size_t modbytes, size_t expbytes) {
        if ((Implements::create(genbytes, modbytes))) {
            if ((set_expbytes(expbytes))) {
                return true;
            }
            Implements::destroy();
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_msb
    (const unsigned& generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if ((Implements::set_msb(generator, genbytes, modulus, modbytes))) {
            if ((set_exponent_msb(exponent, expbytes))) {
                return true;
            }
            Implements::clear();
        }
        return false;
    }
    virtual bool set_msb
    (const byte_t* generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if ((Implements::set_msb(generator, genbytes, modulus, modbytes))) {
            if ((set_exponent_msb(exponent, expbytes))) {
                return true;
            }
            Implements::clear();
        }
        return false;
    }
    virtual bool get_msb
    (size_t& genlen, size_t& modlen, size_t& explen,
     unsigned& generator, size_t genbytes,
     byte_t* modulus, size_t modbytes,
     byte_t* exponent, size_t expbytes) const {
        return false;
    }
    virtual bool get_msb
    (size_t& genlen, size_t& modlen, size_t& explen,
     byte_t* generator, size_t genbytes,
     byte_t* modulus, size_t modbytes,
     byte_t* exponent, size_t expbytes) const {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_exponent_msb
    (const byte_t* exponent, size_t expbytes) {
        return 0;
    }
    virtual ssize_t get_exponent_msb
    (byte_t* exponent, size_t expbytes) const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_expbytes(size_t to) {
        return 0;
    }
    virtual size_t expbytes() const {
        return 0;
    }
    virtual size_t expbytes_min() const {
        return 0;
    }
    virtual size_t expbytes_max() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef private_key_implementst<> private_key_implements;

typedef private_key_implements private_keyt_implements;
typedef key private_keyt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: private_keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = private_keyt_implements, class TExtends = private_keyt_extends>

class _EXPORT_CLASS private_keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
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
    virtual void clear() {

        TALAS_LOG_DEBUG("expbytes_ = 0...");
        expbytes_ = 0;
        Extends::clear();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_expbytes(size_t to) {
        if ((to >= this->expbytes_min()) && (to <= this->expbytes_max())) {
            TALAS_LOG_DEBUG("expbytes_ = " << to << "...");
            expbytes_ = to;
            return expbytes_;
        }
        return 0;
    }
    virtual size_t expbytes() const {
        return expbytes_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t expbytes_;
};
typedef private_keyt<> private_key;

} // namespace dh 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DH_PRIVATE_KEY_HPP 
