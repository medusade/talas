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
///   File: private_key.hpp
///
/// Author: $author$
///   Date: 2/24/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DSA_MP_PRIVATE_KEY_HPP
#define _TALAS_CRYPTO_DSA_MP_PRIVATE_KEY_HPP

#include "talas/crypto/dsa/private_key.hpp"
#include "talas/crypto/dsa/mp/key.hpp"

namespace talas {
namespace crypto {
namespace dsa {
namespace mp {

///////////////////////////////////////////////////////////////////////
///  Class: private_keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = private_key_implements, 
 class TExtends = dsa::private_keyt<private_key_implements, key> >

class _EXPORT_CLASS private_keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    private_keyt
    (const byte_t* p, size_t pbytes,
     const byte_t* q, size_t qbytes,
     const byte_t* g, size_t gbytes,
     const byte_t* x, size_t xbytes) {
        this->init();
        if (!(this->create_msb
             (p, pbytes, q, qbytes, g, gbytes, x, xbytes))) {
            const creator_exception e = failed_to_create;
            this->fini();
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_create)...")
            throw(e);
        }
    }
    private_keyt(const private_keyt& copy) {
        const creator_exception e = failed_to_create;
        TALAS_LOG_ERROR("...keyt(const keyt& copy) not allowed throw(const creator_exception e = failed_to_create)...")
        throw(e);
    }
    private_keyt() {
        this->init();
        this->clear();
    }
    virtual ~private_keyt() {
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
    virtual ssize_t sign_msb
    (byte_t* r, size_t rbytes, byte_t* s, size_t sbytes, 
     const byte_t* h, size_t hbytes, const byte_t* k, size_t kbytes) {
        if ((this->pbytes_) && (this->qbytes_) && (this->gbytes_) 
            && (r) && (rbytes) && (rbytes >= this->qbytes_)
            && (s) && (sbytes) && (sbytes >= this->qbytes_)
            && (h) && (hbytes) && (k) && (kbytes)) {
            MP_INT r_, s_, h_, k_, ik_, t1_, t2_;
            
            TALAS_LOG_DEBUG("::mpz_init(&r_)...");
            ::mpz_init(&r_);
            
            TALAS_LOG_DEBUG("::mpz_init(&s_)...");
            ::mpz_init(&s_);
            
            TALAS_LOG_DEBUG("::mpz_init_set_msb(&h_, h, hbytes)...");
            ::mpz_init_set_msb(&h_, h, hbytes);
            
            TALAS_LOG_DEBUG("::mpz_init_set_msb(&k_, k, kbytes)...");
            ::mpz_init_set_msb(&k_, k, kbytes);
            
            TALAS_LOG_DEBUG("::mpz_init(&ik_)...");
            ::mpz_init(&ik_);
            
            TALAS_LOG_DEBUG("::mpz_init(&t1_)...");
            ::mpz_init(&t1_);
            
            TALAS_LOG_DEBUG("::mpz_init(&t2_)...");
            ::mpz_init(&t2_);

            // ik = k^-1 mod q
            //
            TALAS_LOG_DEBUG("::mpz_mod_inverse(&ik_, &k_, &this->q_)...");
            ::mpz_mod_inverse(&ik_, &k_, &this->q_);

            // r = (g^k mod p) mod q
            //
            TALAS_LOG_DEBUG("::mpz_powm(&t1_, &this->g_, &k_, &this->p_)...");
            ::mpz_powm(&t1_, &this->g_, &k_, &this->p_);
            
            TALAS_LOG_DEBUG("::mpz_mod(&r_, &t1_, &this->q_)...");
            ::mpz_mod(&r_, &t1_, &this->q_);
            
            TALAS_LOG_DEBUG("::mpz_get_msb(r, this->qbytes_, &r_)...");
            ::mpz_get_msb(r, this->qbytes_, &r_);

            // s = k^-1*(h+x*r) mod q
            //
            TALAS_LOG_DEBUG("::mpz_mul(&t1_, &this->x_, &r_)...");
            ::mpz_mul(&t1_, &this->x_, &r_);
            
            TALAS_LOG_DEBUG("::mpz_add(&t2_, &h_, &t1_)...");
            ::mpz_add(&t2_, &h_, &t1_);
            
            TALAS_LOG_DEBUG("::mpz_mul(&t1_, &t2_, &ik_)...");
            ::mpz_mul(&t1_, &t2_, &ik_);
            
            TALAS_LOG_DEBUG("::mpz_mod(&s_, &t1_, &this->q_)...");
            ::mpz_mod(&s_, &t1_, &this->q_);
            
            TALAS_LOG_DEBUG("::mpz_get_msb(s, this->qbytes_, &s_)...");
            ::mpz_get_msb(s, this->qbytes_, &s_);
                        
            TALAS_LOG_DEBUG("::mpz_clear(&t2_)...");
            ::mpz_clear(&t2_);
            
            TALAS_LOG_DEBUG("::mpz_clear(&t1_)...");
            ::mpz_clear(&t1_);
            
            TALAS_LOG_DEBUG("::mpz_clear(&ik_)...");
            ::mpz_clear(&ik_);
            
            TALAS_LOG_DEBUG("::mpz_clear(&k_)...");
            ::mpz_clear(&k_);
            
            TALAS_LOG_DEBUG("::mpz_clear(&h_)...");
            ::mpz_clear(&h_);
            
            TALAS_LOG_DEBUG("::mpz_clear(&s_)...");
            ::mpz_clear(&s_);
            
            TALAS_LOG_DEBUG("::mpz_clear(&r_)...");
            ::mpz_clear(&r_);            
            return this->qbytes_;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t get_y_msb(byte_t* y, size_t ybytes) const {
        if ((this->pbytes_) && (this->qbytes_) && (this->gbytes_) && (this->xbytes_)
            && (y) && (ybytes) && (ybytes >= this->pbytes_)) {
            MP_INT y_;

            TALAS_LOG_DEBUG("::mpz_init(&y_)...");
            ::mpz_init(&y_);
            
            TALAS_LOG_DEBUG("::mpz_powm(&y_, &this->g_, &this->x_, &this->p_)...");
            ::mpz_powm(&y_, &this->g_, &this->x_, &this->p_);

            TALAS_LOG_DEBUG("::mpz_get_msb(y, this->pbytes_, &y_)...");
            ::mpz_get_msb(y, this->pbytes_, &y_);
            
            TALAS_LOG_DEBUG("::mpz_clear(&y_)...");
            ::mpz_clear(&y_);
            return this->pbytes_;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_x_msb(const byte_t* x, size_t xbytes) {
        if ((this->xbytes_) && (x) && (xbytes) && (xbytes <= this->xbytes_)) {

            TALAS_LOG_DEBUG("::mpz_set_msb(&x_, x = " << x_to_string(x, xbytes) << ", xbytes = " << xbytes << ")...");
            ::mpz_set_msb(&x_, x, xbytes);
            return xbytes;
        }
        return 0;
    }
    virtual ssize_t get_x_msb(byte_t* x, size_t xbytes) const {
        if ((this->xbytes_) && (x) && (xbytes) && (xbytes >= this->xbytes_)) {

            TALAS_LOG_DEBUG("::mpz_get_msb(x, xbytes, &x_)...");
            ::mpz_get_msb(x, xbytes, &x_);
            return this->xbytes_;
        }
        return 0;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void init() {
        TALAS_LOG_DEBUG("::mpz_init_set_ui(&x_, 0)...");
        ::mpz_init_set_ui(&x_, 0);
        fx_ = true;
    }
    virtual void fini() {
        if (fx_) {
            TALAS_LOG_DEBUG("::mpz_clear(&x_)...");
            ::mpz_clear(&x_);
            fx_ = false;
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual MP_INT &x() const {
        return (MP_INT &)x_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool fx_;
    MP_INT x_;
};
typedef private_keyt<> private_key;

} // namespace mp 
} // namespace dsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DSA_MP_PRIVATE_KEY_HPP 
