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
///   Date: 2/24/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DSA_MP_KEY_HPP
#define _TALAS_CRYPTO_DSA_MP_KEY_HPP

#include "talas/crypto/dsa/key.hpp"
#include "mpz_msb.h"

namespace talas {
namespace crypto {
namespace dsa {
namespace mp {

///////////////////////////////////////////////////////////////////////
///  Class: keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = key_implements, 
 class TExtends = key_extend>

class _EXPORT_CLASS keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    keyt
    (const byte_t* p, size_t pbytes,
     const byte_t* q, size_t qbytes,
     const byte_t* g, size_t gbytes) {
        this->init();
        if (!(this->create_msb
             (p, pbytes, q, qbytes, g, gbytes))) {
            const creator_exception e = failed_to_create;
            this->fini();
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
        this->init();
        this->clear();
    }
    virtual ~keyt() {
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
    virtual ssize_t set_p_msb(const byte_t* p, size_t pbytes) {
        if ((this->pbytes_) && (p) && (pbytes) && (pbytes <= this->pbytes_)) {

            TALAS_LOG_DEBUG("::mpz_set_msb(&p_, p = " << x_to_string(p, pbytes) << ", pbytes = " << pbytes << ")...");
            ::mpz_set_msb(&p_, p, pbytes);
            return pbytes;
        }
        return 0;
    }
    virtual ssize_t get_p_msb(byte_t* p, size_t pbytes) const {
        if ((this->pbytes_) && (p) && (pbytes) && (pbytes >= this->pbytes_)) {

            TALAS_LOG_DEBUG("::mpz_get_msb(p, pbytes, &p_)...");
            ::mpz_get_msb(p, pbytes, &p_);
            return this->pbytes_;
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_q_msb(const byte_t* q, size_t qbytes) {
        if ((this->qbytes_) && (q) && (qbytes) && (qbytes <= this->qbytes_)) {

            TALAS_LOG_DEBUG(":mpz_set_msb(&q_, q = " << x_to_string(q, qbytes) << ", qbytes = " << qbytes << ")...");
            ::mpz_set_msb(&q_, q, qbytes);
            return qbytes;
        }
        return 0;
    }
    virtual ssize_t get_q_msb(byte_t* q, size_t qbytes) const {
        if ((this->qbytes_) && (q) && (qbytes) && (qbytes >= this->qbytes_)) {

            TALAS_LOG_DEBUG("::mpz_get_msb(q, qbytes, &q_)...");
            ::mpz_get_msb(q, qbytes, &q_);
            return this->qbytes_;
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_g_msb(const byte_t* g, size_t gbytes) {
        if ((this->gbytes_) && (g) && (gbytes) && (gbytes <= this->gbytes_)) {

            TALAS_LOG_DEBUG("::mpz_set_msb(&g_, g = " << x_to_string(g, gbytes) << ", gbytes = " << gbytes << ")...");
            ::mpz_set_msb(&g_, g, gbytes);
            return gbytes;
        }
        return 0;
    }
    virtual ssize_t get_g_msb(byte_t* g, size_t gbytes) const {
        if ((this->gbytes_) && (g) && (gbytes) && (gbytes >= this->gbytes_)) {

            TALAS_LOG_DEBUG("::mpz_get_msb(g, gbytes, &g_)...");
            ::mpz_get_msb(g, gbytes, &g_);
            return this->gbytes_;
        }
        return 0;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void init() {
        TALAS_LOG_DEBUG("::mpz_init_set_ui(&p_, 0)...");
        ::mpz_init_set_ui(&p_, 0);
        fp_ = true;

        TALAS_LOG_DEBUG("::mpz_init_set_ui(&q_, 0)...");
        ::mpz_init_set_ui(&q_, 0);
        fq_ = true;

        TALAS_LOG_DEBUG("::mpz_init_set_ui(&g_, 0)...");
        ::mpz_init_set_ui(&g_, 0);
        fg_ = true;
    }
    virtual void fini() {
        if (fp_) {
            TALAS_LOG_DEBUG("::mpz_clear(&p_)...");
            ::mpz_clear(&p_);
            fp_ = false;
        }
        if (fq_) {
            TALAS_LOG_DEBUG("::mpz_clear(&q_)...");
            ::mpz_clear(&q_);
            fq_ = false;
        }
        if (fg_) {
            TALAS_LOG_DEBUG("::mpz_clear(&g_)...");
            ::mpz_clear(&g_);
            fg_ = false;
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual MP_INT &p() const {
        return (MP_INT &)p_;
    }
    virtual MP_INT &q() const {
        return (MP_INT &)q_;
    }
    virtual MP_INT &g() const {
        return (MP_INT &)g_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool fp_, fq_, fg_; 
    MP_INT p_, q_, g_;
};
typedef keyt<> key;

} // namespace mp 
} // namespace dsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DSA_MP_KEY_HPP 
