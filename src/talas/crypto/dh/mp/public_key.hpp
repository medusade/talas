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
///   File: public_key.hpp
///
/// Author: $author$
///   Date: 2/11/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DH_MP_PUBLIC_KEY_HPP
#define _TALAS_CRYPTO_DH_MP_PUBLIC_KEY_HPP

#include "talas/crypto/dh/public_key.hpp"
#include "talas/crypto/dh/mp/key.hpp"

namespace talas {
namespace crypto {
namespace dh {
namespace mp {

typedef dh::public_key_implements public_key_implements;
///////////////////////////////////////////////////////////////////////
///  Class: public_key_implemented
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS public_key_implemented: virtual public public_key_implements {
public:
    typedef public_key_implements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create_secret_msb
    (MP_INT *X, const byte_t* exponent, size_t expbytes) {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual MP_INT* g() const {
        return 0;
    }
    virtual MP_INT* n() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///  Class: public_keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = public_key_implemented, 
 class TExtends = dh::public_keyt<public_key_implemented, key> >

class _EXPORT_CLASS public_keyt: virtual public TImplements,public TExtends {
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
    virtual ssize_t create_secret_msb
    (byte_t* secret, size_t secbytes, const byte_t* exponent, size_t expbytes) {
        ssize_t size = 0;
        
        if ((secret) && (secbytes) && (secbytes >= this->modbytes_) 
             && (exponent) && (expbytes) && (this->genbytes_) && (this->expbytes_)) {
            MP_INT X;
            
            TALAS_LOG_DEBUG("::mpz_init_set_ui(&X, 0)...");
            ::mpz_init_set_ui(&X, 0);
            
            if ((create_secret_msb(&X, exponent, expbytes))) {
                
                TALAS_LOG_DEBUG("::mpz_get_msb(secret, this->modbytes_, &X)...");
                ::mpz_get_msb(secret, this->modbytes_, &X);
                size = this->modbytes_;
            }
            
            TALAS_LOG_DEBUG("::mpz_clear(&X)...");
            ::mpz_clear(&X);
        }
        return size;
    }
    virtual bool create_secret_msb
    (MP_INT *X, const byte_t* exponent, size_t expbytes) {
        bool success = false;
        
        if ((X) && (exponent) && (expbytes)) {
            MP_INT x;
            
            TALAS_LOG_DEBUG("::mpz_init_set_msb(&x, exponent = " << x_to_string(exponent, expbytes) << ", expbytes = " << expbytes << ")...");
            ::mpz_init_set_msb(&x, exponent, expbytes);
            
            success = create_secret(X, &x);
            
            TALAS_LOG_DEBUG("::mpz_clear(&x)...");
            ::mpz_clear(&x);
        }
        return success;
    }
    virtual bool create_secret(MP_INT *X, MP_INT *x) {
        bool success = false;

        if ((X) && (x) && (this->expbytes_) && (this->modbytes_)) {
            
            TALAS_LOG_DEBUG("::mpz_powm(X, &this->x_, x, &this->n_)...");
            ::mpz_powm(X, &this->x_, x, &this->n_);
            success = true;
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual mp::public_key_implemented* mp_key_implemented() const {
        return (mp::public_key_implemented*)this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual MP_INT* g() const {
        return (MP_INT*)(&this->g_);
    }
    virtual MP_INT* n() const {
        return (MP_INT*)(&this->n_);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_exponent_msb
    (const byte_t* exponent, size_t expbytes) {
        ssize_t size = 0;

        if ((Extends::set_exponent_msb(exponent, expbytes))) {
            size = set_exponent_modulus_msb(exponent, expbytes);
        }
        return size;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_exponent_modulus_msb
    (const byte_t* exponent, size_t expbytes) {
        ssize_t size = 0;
        
        if ((this->genbytes_) && (this->modbytes_)
            && (exponent) && (expbytes) && (expbytes <= this->expbytes_)) {
            MP_INT x;
            
            TALAS_LOG_DEBUG("::mpz_init_set_msb(&x, exponent = " << x_to_string(exponent, expbytes) << ", expbytes = " << expbytes << ")...");
            ::mpz_init_set_msb(&x, exponent, expbytes);
            
            TALAS_LOG_DEBUG("::mpz_powm(&this->x_, &this->g_, &x, &this->n_)...");
            ::mpz_powm(&this->x_, &this->g_, &x, &this->n_);
            size = this->modbytes_;
            
            TALAS_LOG_DEBUG("::mpz_clear(&x)...");
            ::mpz_clear(&x);
        }
        return size;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef public_keyt<> public_key;

} // namespace mp 
} // namespace dh 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DH_MP_PUBLIC_KEY_HPP 
