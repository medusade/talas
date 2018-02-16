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
///   File: key.hpp
///
/// Author: $author$
///   Date: 2/11/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DH_KEY_HPP
#define _TALAS_CRYPTO_DH_KEY_HPP

#include "talas/crypto/base.hpp"
#include "talas/io/logger.hpp"

namespace talas {
namespace crypto {
namespace dh {

///////////////////////////////////////////////////////////////////////
///  Class: key_implementst
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = ::xos::base::creatort<crypto::implement_base> >

class _EXPORT_CLASS key_implementst: virtual public TImplements {
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
                if ((this->set_msb(generator, genbytes, modulus, modbytes, exponent, expbytes))) {
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
        if ((generator) && (genbytes) && (modulus) && (modbytes)) {
            if ((this->create(genbytes, modbytes, expbytes))) {
                if ((this->set_msb(generator, genbytes, modulus, modbytes, exponent, expbytes))) {
                    return true;
                }
                this->destroy();
            }
        }
        return false;
    }
    virtual bool create(size_t genbytes, size_t modbytes, size_t expbytes) {
        if ((this->destroyed())) {
            if ((this->set_genbytes(genbytes))) {
                if ((this->set_modbytes(modbytes))) {
                    if ((this->set_expbytes(expbytes))) {
                        this->set_is_created();
                        return true;
                    }
                }
                clear();
            }
        }
        return false;
    }
    virtual bool destroy() {
        clear();
        this->set_is_created(false);
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void clear() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_msb
    (const unsigned& generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if ((genbytes > 0) && (genbytes <= sizeof(generator)) 
            && (genbytes <= this->genbytes())) {
            unsigned generator_msb = generator;
            byte_t generator_bytes[sizeof(generator)];

            for (unsigned b = genbytes; b > 0; --b) {
                generator_bytes[b-1] = (generator_msb & 255);
                generator_msb >>= 8;
            }
            if ((set_msb(generator_bytes, genbytes, modulus, modbytes, exponent, expbytes))) {
                return true;
            }
        }
        return false;
    }
    virtual bool get_msb
    (size_t& genlen, size_t& modlen, size_t& explen,
     const unsigned& generator, size_t genbytes,
     byte_t* modulus, size_t modbytes,
     byte_t* exponent, size_t expbytes) const {
        if ((genbytes > 0) && (genbytes <= sizeof(generator)) 
            && (genbytes <= this->genbytes())) {
            unsigned generator_msb = generator;
            byte_t generator_bytes[sizeof(generator)];

            for (unsigned b = genbytes; b > 0; --b) {
                generator_bytes[b-1] = (generator_msb & 255);
                generator_msb >>= 8;
            }
            if ((get_msb
                 (genlen, modlen, explen, generator_bytes, genbytes, 
                  modulus, modbytes, exponent, expbytes))) {
                return true;
            }
        }
        return false;
    }
    virtual bool set_msb
    (const byte_t* generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if ((generator) && (genbytes) && (genbytes <= this->genbytes())
            && (modulus) && (modbytes) && (modbytes <= this->modbytes())
            && (exponent) && (expbytes) && (expbytes <= this->expbytes())) {

            if ((set_generator_msb(generator, genbytes))) {
                if ((set_modulus_msb(modulus, modbytes))) {
                    if ((set_exponent_msb(exponent, expbytes))) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    virtual bool get_msb
    (size_t& genlen, size_t& modlen, size_t& explen,
     byte_t* generator, size_t genbytes,
     byte_t* modulus, size_t modbytes,
     byte_t* exponent, size_t expbytes) const {
        if ((generator) && (genbytes) && (genbytes >= this->genbytes())
            && (modulus) && (modbytes) && (modbytes >= this->modbytes())
            && (exponent) && (expbytes) && (expbytes >= this->expbytes())) {

            if ((genlen = get_generator_msb(generator, genbytes))) {
                if ((modlen = get_modulus_msb(modulus, modbytes))) {
                    if ((explen = get_exponent_msb(exponent, expbytes))) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_generator_msb
    (const unsigned& generator, size_t genbytes) {
        ssize_t size = 0;
        if ((genbytes > 0) && (genbytes <= sizeof(generator)) 
            && (genbytes <= this->genbytes())) {
            unsigned generator_msb = generator;
            byte_t generator_bytes[sizeof(generator)];

            for (unsigned b = genbytes; b > 0; --b) {
                generator_bytes[b-1] = (generator_msb & 255);
                generator_msb >>= 8;
            }
            if ((size = set_generator_msb(generator_bytes, genbytes))) {
                return size;
            }
        }
        return size;
    }
    virtual ssize_t get_generator_msb
    (unsigned& generator, size_t genbytes) const {
        ssize_t size = 0;
        if ((genbytes > 0) && (genbytes <= sizeof(generator)) 
            && (genbytes <= this->genbytes())) {
            byte_t generator_bytes[sizeof(generator)];

            if ((size = get_generator_msb(generator_bytes, genbytes))) {
                generator = 0;
                for (unsigned b = genbytes; b > 0; --b) {
                    generator <<= 8;
                    generator |= generator_bytes[b-1];
                }
                return size;
            }
        }
        return size;
    }
    virtual ssize_t set_generator_msb
    (const byte_t* generator, size_t genbytes) {
        return 0;
    }
    virtual ssize_t get_generator_msb
    (byte_t* generator, size_t genbytes) const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_modulus_msb
    (const byte_t* modulus, size_t modbytes) {
        return 0;
    }
    virtual ssize_t get_modulus_msb
    (byte_t* modulus, size_t modbytes) const {
        return 0;
    }
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
    virtual size_t set_genbytes(size_t to) {
        return 0;
    }
    virtual size_t genbytes() const {
        return 0;
    }
    virtual size_t genbytes_min() const {
        return 0;
    }
    virtual size_t genbytes_max() const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_modbytes(size_t to) {
        return 0;
    }
    virtual size_t modbytes() const {
        return 0;
    }
    virtual size_t modbytes_min() const {
        return 0;
    }
    virtual size_t modbytes_max() const {
        return 0;
    }
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
typedef key_implementst<> key_implements;
typedef key_implements key;

///////////////////////////////////////////////////////////////////////
///  Class: keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = key_implements, 
 class TExtends = ::xos::base::creator_extendt<TImplements, crypto::base> >

class _EXPORT_CLASS keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    keyt
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
    keyt
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
    keyt(const keyt& copy) {
        const creator_exception e = failed_to_create;
        TALAS_LOG_ERROR("...keyt(const keyt& copy) not allowed throw(const creator_exception e = failed_to_create)...")
        throw(e);
    }
    keyt() {
        clear();
    }
    virtual ~keyt() {
        if (!(this->destroyed())) {
            const creator_exception e = failed_to_destroy;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_destroy)...")
            throw(e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void clear() {
        TALAS_LOG_DEBUG("genbytes_ = modbytes_ = expbytes_ = 0...");
        genbytes_ = modbytes_ = expbytes_ = 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_genbytes(size_t to) {
        if ((to >= genbytes_min()) && (to <= genbytes_max())) {
            TALAS_LOG_DEBUG("genbytes_ = " << to << "...");
            genbytes_ = to;
            return genbytes_;
        }
        return 0;
    }
    virtual size_t genbytes() const {
        return genbytes_;
    }
    virtual size_t genbytes_min() const {
        return 0;
    }
    virtual size_t genbytes_max() const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_modbytes(size_t to) {
        if ((to >= modbytes_min()) && (to <= modbytes_max())) {
            TALAS_LOG_DEBUG("modbytes_ = " << to << "...");
            modbytes_ = to;
            return modbytes_;
        }
        return 0;
    }
    virtual size_t modbytes() const {
        return modbytes_;
    }
    virtual size_t modbytes_min() const {
        return 0;
    }
    virtual size_t modbytes_max() const {
        return 0;
    }
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
    virtual size_t expbytes_min() const {
        return 0;
    }
    virtual size_t expbytes_max() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t genbytes_, modbytes_, expbytes_;
};
typedef keyt<> key_extend;

} // namespace dh 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DH_KEY_HPP 
