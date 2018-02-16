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
///   Date: 2/12/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DH_MBU_KEY_HPP
#define _TALAS_CRYPTO_DH_MBU_KEY_HPP

#include "talas/crypto/dh/key.hpp"
#include "mbuint.h"

namespace talas {
namespace crypto {
namespace dh {
namespace mbu {

///////////////////////////////////////////////////////////////////////
///  Class: keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = dh::key_implements, class TExtends = dh::key_extend>

class _EXPORT_CLASS keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    enum {key_min = 1, key_max = 256};
    
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
    using Implements::set_msb;
    virtual bool set_msb
    (const unsigned& generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if ((generator) && (genbytes > 0) && (genbytes <= sizeof(generator))
            && (modulus) && (modbytes) && (modbytes == this->modbytes())
            && (exponent) && (expbytes) && (expbytes == this->modbytes())) {

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
    virtual bool set_msb
    (const byte_t* generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if ((generator) && (genbytes) && (genbytes == this->modbytes())
            && (modulus) && (modbytes) && (modbytes == this->modbytes())
            && (exponent) && (expbytes) && (expbytes == this->modbytes())) {

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

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_generator_msb
    (const unsigned& generator, size_t genbytes) {
        size_t modbytes = this->modbytes();
        if ((generator) && (genbytes) 
            && (genbytes <= sizeof(generator)) && (modbytes)) {
            
            TALAS_LOG_DEBUG("::mbu_set_u(g_, generator = " << generator << ", modbytes = " << modbytes << ")...");
            ::mbu_set_u(g_, generator_ = generator, modbytes);
            return modbytes;
        }
        return 0;
    }
    virtual ssize_t set_generator_msb
    (const byte_t* generator, size_t genbytes) {
        return 0;
        if ((generator) && (genbytes) && (genbytes == this->modbytes())) {

            TALAS_LOG_DEBUG(":mbu_set(g_, generator = " << x_to_string(generator, genbytes) << ", genbytes = " << genbytes << ")...");
            ::mbu_set(g_, generator, genbytes);
            return genbytes;
        }
    }
    virtual ssize_t get_generator_msb
    (byte_t* generator, size_t genbytes) const {
        size_t modbytes = this->modbytes();
        if ((generator) && (genbytes) && (genbytes >= modbytes)) {

            TALAS_LOG_DEBUG(":mbu_set(generator, g_ = " << x_to_string(g_, modbytes) << ", modbytes = " << modbytes << ")...");
            ::mbu_set(generator, g_, modbytes);
            return modbytes;
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_modulus_msb
    (const byte_t* modulus, size_t modbytes) {
        if ((modulus) && (modbytes) && (modbytes == this->modbytes())) {

            TALAS_LOG_DEBUG("::mbu_set(m_, modulus = " << x_to_string(modulus, modbytes) << ", modbytes = " << modbytes << ")...");
            ::mbu_set(n_, modulus, modbytes);
            return modbytes;
        }
        return 0;
    }
    virtual ssize_t get_modulus_msb
    (byte_t* modulus, size_t modbytes) const {
        size_t nbytes = this->modbytes();
        if ((modulus) && (modbytes) && (modbytes >= nbytes)) {

            TALAS_LOG_DEBUG(":mbu_set(modulus, n_ = " << x_to_string(n_, nbytes) << ", nbytes = " << nbytes << ")...");
            ::mbu_set(modulus, n_, nbytes);
            return nbytes;
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_exponent_msb
    (const byte_t* exponent, size_t expbytes) {
        if ((exponent) && (expbytes) && (expbytes == this->modbytes())) {

            TALAS_LOG_DEBUG("::mbu_set(x_, exponent = " << x_to_string(exponent, expbytes) << ", expbytes = " << expbytes << ")...");
            ::mbu_set(x_, exponent, expbytes);
            return expbytes;
        }
        return 0;
    }
    virtual ssize_t get_exponent_msb
    (byte_t* exponent, size_t expbytes) const {
        size_t modbytes = this->modbytes();
        if ((exponent) && (expbytes) && (expbytes >= modbytes)) {

            TALAS_LOG_DEBUG(":mbu_set(exponent, x_ = " << x_to_string(x_, modbytes) << ", modbytes = " << modbytes << ")...");
            ::mbu_set(exponent, x_, modbytes);
            return modbytes;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void clear() {

        TALAS_LOG_DEBUG("generator_ = 0...");
        generator_ = 0;
        
        TALAS_LOG_DEBUG("::mbu_set_u(g_, 0, key_max = " << key_max << ")...");
        ::mbu_set_u(g_, 0, key_max);

        TALAS_LOG_DEBUG("::mbu_set_u(n_, 0, key_max = " << key_max << ")...");
        ::mbu_set_u(n_, 0, key_max);
        
        TALAS_LOG_DEBUG("::mbu_set_u(x_, 0, key_max = " << key_max << ")...");
        ::mbu_set_u(x_, 0, key_max);
        Extends::clear();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t genbytes_min() const {
        return key_min;
    }
    virtual size_t genbytes_max() const {
        return key_max;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual size_t modbytes_min() const {
        return key_min;
    }
    virtual size_t modbytes_max() const {
        return key_max;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual size_t expbytes_min() const {
        return key_min;
    }
    virtual size_t expbytes_max() const {
        return key_max;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    unsigned generator_;
    unsigned char g_[key_max], n_[key_max], x_[key_max];
};
typedef keyt<> key;
typedef key::Implements key_implements;

} // namespace mbu 
} // namespace dh 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DH_MBU_KEY_HPP 
