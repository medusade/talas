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
///   Date: 2/24/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DSA_MP_PUBLIC_KEY_HPP
#define _TALAS_CRYPTO_DSA_MP_PUBLIC_KEY_HPP

#include "talas/crypto/dsa/public_key.hpp"
#include "talas/crypto/dsa/mp/key.hpp"

namespace talas {
namespace crypto {
namespace dsa {
namespace mp {

///////////////////////////////////////////////////////////////////////
///  Class: public_keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = public_key_implements, 
 class TExtends = dsa::public_keyt<public_key_implements, key> >

class _EXPORT_CLASS public_keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    public_keyt
    (const byte_t* p, size_t pbytes,
     const byte_t* q, size_t qbytes,
     const byte_t* g, size_t gbytes,
     const byte_t* y, size_t ybytes) {
        this->init();
        if (!(this->create_msb
             (p, pbytes, q, qbytes, g, gbytes, y, ybytes))) {
            const creator_exception e = failed_to_create;
            this->fini();
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_create)...")
            throw(e);
        }
    }
    public_keyt(const public_keyt& copy) {
        const creator_exception e = failed_to_create;
        TALAS_LOG_ERROR("...keyt(const keyt& copy) not allowed throw(const creator_exception e = failed_to_create)...")
        throw(e);
    }
    public_keyt() {
        this->init();
        this->clear();
    }
    virtual ~public_keyt() {
        if (!(this->destroyed())) {
            const creator_exception e = failed_to_destroy;
            this->fini();
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_destroy)...")
            throw(e);
        }
        this->fini();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t verify_msb
    (byte_t* v, size_t vbytes, const byte_t* h, size_t hbytes, 
     const byte_t* r, size_t rbytes, const byte_t* s, size_t sbytes) {
        if ((this->pbytes_) && (this->qbytes_) && (this->gbytes_) 
            && (v) && (vbytes) && (vbytes >= this->qbytes_)
            && (h) && (hbytes) && (hbytes <= this->qbytes_)
            && (r) && (rbytes) && (rbytes == this->qbytes_)
            && (s) && (sbytes) && (sbytes == this->qbytes_)) {
            MP_INT v_, h_, r_, s_, u1_, u2_, si_;

            TALAS_LOG_DEBUG("::mpz_init(&v_)...");
            ::mpz_init(&v_);

            TALAS_LOG_DEBUG("::mpz_init_set_msb(&h_, h, hbytes)...");
            ::mpz_init_set_msb(&h_, h, hbytes);
            
            TALAS_LOG_DEBUG("::mpz_init_set_msb(&r_, r, rbytes)...");
            ::mpz_init_set_msb(&r_, r, rbytes);
            
            TALAS_LOG_DEBUG("::mpz_init_set_msb(&s_, s, sbytes)...");
            ::mpz_init_set_msb(&s_, s, sbytes);
            
            TALAS_LOG_DEBUG("::mpz_init(&u1_)...");
            ::mpz_init(&u1_);

            TALAS_LOG_DEBUG("::mpz_init(&u2_)...");
            ::mpz_init(&u2_);

            TALAS_LOG_DEBUG("::mpz_init(&si_)...");
            ::mpz_init(&si_);
            {
                MP_INT &t1_ = v_, &t2_ = r_;
                
                // si = s^-1 mod q
                //
                ::mpz_mod_inverse(&si_, &s_, &this->q_);
                // u2 = r*si mod q
                //
                ::mpz_mul(&t1_, &r_, &si_);
                ::mpz_mod(&u2_, &t1_, &this->q_);
                // u1 = h*si mod q
                //
                ::mpz_mul(&t1_, &h_, &si_);
                ::mpz_mod(&u1_, &t1_, &this->q_);
                // t1 = g^u1 mod p
                //
                ::mpz_powm(&t1_, &this->g_, &u1_, &this->p_);
                // t2 = y^u2 mod p
                //
                ::mpz_powm(&t2_, &this->y_, &u2_, &this->p_);
                // u2 = t1*t2 mod p
                //
                ::mpz_mul(&u1_, &t1_, &t2_);
                ::mpz_mod(&u2_, &u1_, &this->p_);
                // v = u2 mod q
                //
                ::mpz_mod(&v_, &u2_, &this->q_);
                ::mpz_get_msb(v, this->qbytes_, &v_);
            }
            TALAS_LOG_DEBUG("::mpz_clear(&si_)...");
            ::mpz_clear(&si_);

            TALAS_LOG_DEBUG("::mpz_clear(&u2_)...");
            ::mpz_clear(&u2_);

            TALAS_LOG_DEBUG("::mpz_clear(&u1_)...");
            ::mpz_clear(&u1_);

            TALAS_LOG_DEBUG("::mpz_clear(&s_)...");
            ::mpz_clear(&s_);

            TALAS_LOG_DEBUG("::mpz_clear(&r_)...");
            ::mpz_clear(&r_);

            TALAS_LOG_DEBUG("::mpz_clear(&h_)...");
            ::mpz_clear(&h_);

            TALAS_LOG_DEBUG("::mpz_clear(&v_)...");
            ::mpz_clear(&v_);

            return this->qbytes_;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_y_msb(const byte_t* y, size_t ybytes) {
        if ((this->ybytes_) && (y) && (ybytes <= this->ybytes_)) {

            TALAS_LOG_DEBUG("::mpz_set_msb(&y_, y = " << x_to_string(y, ybytes) << ", ybytes = " << ybytes << ")...");
            ::mpz_set_msb(&y_, y, ybytes);
            return ybytes;
        }
        return 0;
    }
    virtual ssize_t get_y_msb(byte_t* y, size_t ybytes) const {
        if ((this->ybytes_) && (y) && (ybytes >= this->ybytes_)) {
            
            TALAS_LOG_DEBUG("::mpz_get_msb(y, ybytes, &y_)...");
            ::mpz_get_msb(y, ybytes, &y_);
            return this->ybytes_;
        }
        return 0;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void init() {
        TALAS_LOG_DEBUG("::mpz_init_set_ui(&y_, 0)...");
        ::mpz_init_set_ui(&y_, 0);
        fy_ = true;
    }
    virtual void fini() {
        if (fy_) {
            TALAS_LOG_DEBUG("::mpz_clear(&y_)...");
            ::mpz_clear(&y_);
            fy_ = false;
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual MP_INT &y() const {
        return (MP_INT &)y_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool fy_;
    MP_INT y_;
};
typedef public_keyt<> public_key;

} // namespace mp 
} // namespace dsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DSA_MP_PUBLIC_KEY_HPP 
