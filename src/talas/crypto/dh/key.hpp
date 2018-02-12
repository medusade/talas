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
#include "xos/base/creator.hpp"

namespace talas {
namespace crypto {
namespace dh {

typedef ::xos::base::creatort<crypto::implement_base> key_implementst_implements;
///////////////////////////////////////////////////////////////////////
///  Class: key_implementst
///////////////////////////////////////////////////////////////////////
template
<class TImplements = key_implementst_implements>

class _EXPORT_CLASS key_implementst: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create_msb
    (const unsigned& generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes) {
        if ((generator) && (genbytes) && (modulus) && (modbytes)) {
            if ((this->create(genbytes, modbytes))) {
                if ((this->set_msb(generator, genbytes, modulus, modbytes))) {
                    return true;
                }
                this->destroy();
            }
        }
        return false;
    }
    virtual bool create_msb
    (const byte_t* generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes) {
        if ((generator) && (genbytes) && (modulus) && (modbytes)) {
            if ((this->create(genbytes, modbytes))) {
                if ((this->set_msb(generator, genbytes, modulus, modbytes))) {
                    return true;
                }
                this->destroy();
            }
        }
        return false;
    }
    virtual bool create(size_t genbytes, size_t modbytes) {
        if ((this->destroyed())) {
            if ((this->set_genbytes(genbytes))) {
                if ((this->set_modbytes(modbytes))) {
                    this->set_is_created();
                    return true;
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
     const byte_t* modulus, size_t modbytes) {
        if ((genbytes > 0) && (genbytes <= sizeof(generator)) 
            && (genbytes <= this->genbytes())) {
            unsigned generator_msb = generator;
            byte_t generator_bytes[sizeof(generator)];

            for (unsigned b = genbytes; b > 0; --b) {
                generator_bytes[b-1] = (generator_msb & 255);
                generator_msb >>= 8;
            }
            if ((set_msb(generator_bytes, genbytes, modulus, modbytes))) {
                return true;
            }
        }
        return false;
    }
    virtual bool set_msb
    (const byte_t* generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes) {
        return false;
    }
    virtual bool get_msb
    (size_t& genlen, size_t& modlen,
     const unsigned& generator, size_t genbytes,
     byte_t* modulus, size_t modbytes) const {
        return false;
    }
    virtual bool get_msb
    (size_t& genlen, size_t& modlen,
     byte_t* generator, size_t genbytes,
     byte_t* modulus, size_t modbytes) const {
        return false;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_generator_msb
    (const unsigned& generator, size_t genbytes) {
        return 0;
    }
    virtual ssize_t set_generator_msb
    (const byte_t* generator, size_t genbytes) {
        return 0;
    }
    virtual ssize_t get_generator_msb
    (const unsigned& generator, size_t genbytes) const {
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
    ///////////////////////////////////////////////////////////////////////
};
typedef key_implementst<> key_implements;

typedef key_implements keyt_implements;
typedef ::xos::base::creator_extendt<key_implements, crypto::base> keyt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = keyt_implements, class TExtends = keyt_extends>

class _EXPORT_CLASS keyt: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
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
        TALAS_LOG_DEBUG("genbytes_ = modbytes_ = 0...");
        genbytes_ = modbytes_ = 0;
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
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t genbytes_, modbytes_;
};
typedef keyt<> key;

} // namespace dh 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DH_KEY_HPP 
