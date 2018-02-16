///////////////////////////////////////////////////////////////////////
/// Copyright (C) 1991, 1993, 1994, 1995, 1996 Free Software Foundation, Inc.
/// 
/// This file is part of the GNU MP Library.
/// 
/// The GNU MP Library is free software; you can redistribute it and/or modify
/// it under the terms of the GNU Library General Public License as published by
/// the Free Software Foundation; either version 2 of the License, or (at your
/// option) any later version.
/// 
/// The GNU MP Library is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
/// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
/// License for more details.
/// 
/// You should have received a copy of the GNU Library General Public License
/// along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
/// the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
/// MA 02111-1307, USA.
///
///   File: key.hpp
///
/// Author: $author$
///   Date: 2/11/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DH_MP_KEY_HPP
#define _TALAS_CRYPTO_DH_MP_KEY_HPP

#include "talas/crypto/dh/key.hpp"
#include "mpz_msb.h"

namespace talas {
namespace crypto {
namespace dh {
namespace mp {

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
        init();
        if (!(this->create_msb
             (generator, genbytes, modulus, modbytes, exponent, expbytes))) {
            const creator_exception e = failed_to_create;
            fini();
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_create)...")
            throw(e);
        }
    }
    keyt
    (const byte_t* generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        init();
        if (!(this->create_msb
             (generator, genbytes, modulus, modbytes, exponent, expbytes))) {
            const creator_exception e = failed_to_create;
            fini();
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_create)...")
            throw(e);
        }
    }
    keyt() {
        init();
    }
    virtual ~keyt() {
        if (!(this->destroyed())) {
            const creator_exception e = failed_to_destroy;
            fini();
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_destroy)...")
            throw(e);
        }
        fini();
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void clear() {
        TALAS_LOG_DEBUG("mpz_set_ui(&g_, 0)...");
        mpz_set_ui(&g_, 0);
        
        TALAS_LOG_DEBUG("mpz_set_ui(&n_, 0)...");
        mpz_set_ui(&n_, 0);
        
        TALAS_LOG_DEBUG("mpz_set_ui(&x_, 0)...");
        mpz_set_ui(&x_, 0);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_generator_msb
    (const byte_t* generator, size_t genbytes) {
        if ((generator) && (genbytes)  && (genbytes == this->genbytes())) {

            TALAS_LOG_DEBUG(":mpz_set_msb(&g_, generator = " << x_to_string(generator, genbytes) << ", genbytes = " << genbytes << ")...");
            ::mpz_set_msb(&g_, generator, genbytes);
            return genbytes;
        }
        return 0;
    }
    virtual ssize_t get_generator_msb
    (byte_t* generator, size_t genbytes) const {
        if ((generator) && (genbytes)  && (genbytes >= this->genbytes())) {

            TALAS_LOG_DEBUG("::mpz_get_msb(generator, genbytes, &g_)...");
            ::mpz_get_msb(generator, genbytes, &g_);
            return genbytes;
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_modulus_msb
    (const byte_t* modulus, size_t modbytes) {
        if ((modulus) && (modbytes)  && (modbytes == this->modbytes())) {

            TALAS_LOG_DEBUG(":mpz_set_msb(&n_, modulus = " << x_to_string(modulus, modbytes) << ", modbytes = " << modbytes << ")...");
            ::mpz_set_msb(&n_, modulus, modbytes);
            return modbytes;
        }
        return 0;
    }
    virtual ssize_t get_modulus_msb
    (byte_t* modulus, size_t modbytes) const {
        if ((modulus) && (modbytes)  && (modbytes >= this->modbytes())) {

            TALAS_LOG_DEBUG("::mpz_get_msb(modulus, modbytes, &n_)...");
            ::mpz_get_msb(modulus, modbytes, &n_);
            return modbytes;
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_exponent_msb
    (const byte_t* exponent, size_t expbytes) {
        if ((exponent) && (expbytes)  && (expbytes == this->expbytes())) {

            TALAS_LOG_DEBUG(":mpz_set_msb(&x_, exponent = " << x_to_string(exponent, expbytes) << ", expbytes = " << expbytes << ")...");
            ::mpz_set_msb(&x_, exponent, expbytes);
            return expbytes;
        }
        return 0;
    }
    virtual ssize_t get_exponent_msb
    (byte_t* exponent, size_t expbytes) const {
        if ((exponent) && (expbytes)  && (expbytes >= this->expbytes())) {

            TALAS_LOG_DEBUG("::mpz_get_msb(exponent, expbytes, &x_)...");
            ::mpz_get_msb(exponent, expbytes, &x_);
            return expbytes;
        }
        return 0;
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

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void init() {
        TALAS_LOG_DEBUG("::mpz_init_set_ui(&g_, 0)...");
        ::mpz_init_set_ui(&g_, 0);
        
        TALAS_LOG_DEBUG("::mpz_init_set_ui(&n_, 0)...");
        ::mpz_init_set_ui(&n_, 0);
        
        TALAS_LOG_DEBUG("::mpz_init_set_ui(&x_, 0)...");
        ::mpz_init_set_ui(&x_, 0);
    }
    virtual void fini() {
        TALAS_LOG_DEBUG("::mpz_clear(&x_)...");
        ::mpz_clear(&x_);

        TALAS_LOG_DEBUG("::mpz_clear(&n_)...");
        ::mpz_clear(&n_);

        TALAS_LOG_DEBUG("::mpz_clear(&g_)...");
        ::mpz_clear(&g_);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    MP_INT g_, n_, x_;
};
typedef keyt<> key;
typedef key::Implements key_implements;

} // namespace mp 
} // namespace dh 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DH_MP_KEY_HPP 
