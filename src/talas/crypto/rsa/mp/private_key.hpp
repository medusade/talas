///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
/// All rights reserved
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
///   Date: 5/12/2015
///
/// Tatu Ylonen's RSA private key implementation modified to be a C++
/// class that uses the gmp used in the original C version.
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RSA_MP_PRIVATE_KEY_HPP
#define _TALAS_CRYPTO_RSA_MP_PRIVATE_KEY_HPP

#include "talas/crypto/rsa/mp/key.hpp"
#include "talas/crypto/rsa/private_key.hpp"

namespace talas {
namespace crypto {
namespace rsa {
namespace mp {

///////////////////////////////////////////////////////////////////////
///  Class: private_key_implements
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS private_key_implements
: virtual public rsa::private_key_implements, virtual public mp::key_implements {
public:
};
typedef mp::key private_key_extends;
///////////////////////////////////////////////////////////////////////
///  Class: private_key
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS private_key
: virtual public private_key_implements, public private_key_extends {
public:
    typedef private_key_implements Implements;
    typedef private_key_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    private_key
    (const byte_t *p, const byte_t *q,
     const byte_t *dmp1, const byte_t *dmq1,
     const byte_t *iqmp, size_t pbytes) {
        if (!(this->create_msb(p, q, dmp1, dmq1, iqmp, pbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create() throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    private_key
    (const mpint_t *p, const mpint_t *q,
     const mpint_t *dmp1, const mpint_t *dmq1,
     const mpint_t *iqmp, size_t pbytes) {
        if (!(this->create(p, q, dmp1, dmq1, iqmp, pbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create() throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    private_key(size_t pbytes) {
        if (!(this->create(pbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create() throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    private_key(const private_key& copy) {
        if (!(this->create(&copy.m_p, &copy.m_q, &copy.m_dmp1, &copy.m_dmq1, &copy.m_iqmp, copy.m_pbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create() throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    private_key() {
    }
    virtual ~private_key() {
        if (!(this->destroyed())) {
            xos::base::creator_exception e = xos::base::failed_to_destroy;
            TALAS_LOG_ERROR("...failed on destroyed() throwing creator_exception failed_to_destroy...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create_msb
    (const byte_t *p, const byte_t *q,
     const byte_t *dmp1, const byte_t *dmq1,
     const byte_t *iqmp, size_t pbytes) {
        if ((this->create(pbytes))) {
            if ((this->set_msb(p,q,dmp1,dmq1,iqmp,pbytes))) {
                return true;
            }
            this->destroy();
        }
        return false;
    }
    virtual bool create
    (const mpint_t *p, const mpint_t *q,
     const mpint_t *dmp1, const mpint_t *dmq1,
     const mpint_t *iqmp, size_t pbytes) {
        if ((this->create(pbytes))) {
            if ((this->set(p,q,dmp1,dmq1,iqmp,pbytes))) {
                return true;
            }
            this->destroy();
        }
        return false;
    }
    virtual bool create(size_t pbytes) {
        if ((this->destroyed())) {
            if ((Extends::create(pbytes))) {
                TALAS_LOG_DEBUG("mpz_init_set_ui(&m_p,0)...");
                mpz_init_set_ui(&m_p,0);
                TALAS_LOG_DEBUG("mpz_init_set_ui(&m_q,0)...");
                mpz_init_set_ui(&m_q,0);
                TALAS_LOG_DEBUG("mpz_init_set_ui(&m_dmp1,0)...");
                mpz_init_set_ui(&m_dmp1,0);
                TALAS_LOG_DEBUG("mpz_init_set_ui(&m_dmq1,0)...");
                mpz_init_set_ui(&m_dmq1,0);
                TALAS_LOG_DEBUG("mpz_init_set_ui(&m_iqmp,0)...");
                mpz_init_set_ui(&m_iqmp,0);
                TALAS_LOG_DEBUG("mpz_init_set_ui(&m_ptemp,0)...");
                mpz_init_set_ui(&m_ptemp,0);

                TALAS_LOG_DEBUG("mpz_init_set_ui(&m_qtemp,0)...");
                mpz_init_set_ui(&m_qtemp,0);
                return true;
                Extends::destroy();
            }
        }
        return false;
    }
    virtual bool destroy() {
        if ((this->is_created())) {
            bool success = true;

            TALAS_LOG_DEBUG("mpz_clear(&m_p)...");
            mpz_clear(&m_p);

            TALAS_LOG_DEBUG("mpz_clear(&m_q)...");
            mpz_clear(&m_q);

            TALAS_LOG_DEBUG("mpz_clear(&m_dmp1)...");
            mpz_clear(&m_dmp1);

            TALAS_LOG_DEBUG("mpz_clear(&m_dmq1)...");
            mpz_clear(&m_dmq1);

            TALAS_LOG_DEBUG("mpz_clear(&m_iqmp)...");
            mpz_clear(&m_iqmp);

            TALAS_LOG_DEBUG("mpz_clear(&m_ptemp)...");
            mpz_clear(&m_ptemp);

            TALAS_LOG_DEBUG("mpz_clear(&m_qtemp)...");
            mpz_clear(&m_qtemp);
            if (!(Extends::destroy())) {
                success = false; }
            return success;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_msb
    (const byte_t *p, const byte_t *q,
     const byte_t *dmp1, const byte_t *dmq1,
     const byte_t *iqmp, size_t pbytes) {
        if ((p) && (q) && (dmp1) && (dmq1) && (iqmp)) {
            if ((m_pbytes)) {

                TALAS_LOG_DEBUG("mpz_set_msb(&m_p,p,pbytes)...");
                mpz_set_msb(&m_p,p,pbytes);

                TALAS_LOG_DEBUG("mpz_set_msb(&m_q,q,pbytes)...");
                mpz_set_msb(&m_q,q,pbytes);

                TALAS_LOG_DEBUG("mpz_set_msb(&m_dmp1,dmp1,pbytes)...");
                mpz_set_msb(&m_dmp1,dmp1,pbytes);

                TALAS_LOG_DEBUG("mpz_set_msb(&m_dmq1,dmq1,pbytes)...");
                mpz_set_msb(&m_dmq1,dmq1,pbytes);

                TALAS_LOG_DEBUG("mpz_set_msb(&m_iqmp,iqmp,pbytes)...");
                mpz_set_msb(&m_iqmp,iqmp,pbytes);
                m_expbytes = (m_modbytes = ((m_pbytes = pbytes) << 1));
                return true;
            }
        }
        return false;
    }
    virtual bool get_msb
    (size_t& plen, byte_t *p, byte_t *q,
     byte_t *dmp1, byte_t *dmq1,
     byte_t *iqmp, size_t pbytes) {
        if ((p) && (q) && (dmp1) && (dmq1) && (iqmp) && (pbytes >= m_pbytes)) {
            if ((m_pbytes)) {

                TALAS_LOG_DEBUG("mpz_get_msb(p,pbytes,&m_p)...");
                mpz_get_msb(p,pbytes,&m_p);

                TALAS_LOG_DEBUG("mpz_get_msb(q,pbytes,&m_q)...");
                mpz_get_msb(q,pbytes,&m_q);

                TALAS_LOG_DEBUG("mpz_get_msb(dmp1,pbytes,&m_dmp1)...");
                mpz_get_msb(dmp1,pbytes,&m_dmp1);

                TALAS_LOG_DEBUG("mpz_get_msb(dmq1,pbytes,&m_dmq1)...");
                mpz_get_msb(dmq1,pbytes,&m_dmq1);

                TALAS_LOG_DEBUG("mpz_get_msb(iqmp,pbytes,&m_iqmp)...");
                mpz_get_msb(iqmp,pbytes,&m_iqmp);
                plen = m_pbytes;
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t get_p_msb
    (byte_t* p, size_t pbytes) const {
        if ((p) && (pbytes >= m_pbytes) && (m_pbytes)) {

            TALAS_LOG_DEBUG("mpz_get_msb(p,pbytes,&m_p)...");
            mpz_get_msb(p,pbytes,&m_p);
            return m_pbytes;
        }
        return 0;
    }
    virtual ssize_t get_q_msb
    (byte_t* p, size_t pbytes) const {
        if ((p) && (pbytes >= m_pbytes) && (m_pbytes)) {

            TALAS_LOG_DEBUG("mpz_get_msb(p,pbytes,&m_q)...");
            mpz_get_msb(p,pbytes,&m_q);
            return m_pbytes;
        }
        return 0;
    }
    virtual ssize_t get_dmp1_msb
    (byte_t* p, size_t pbytes) const {
        if ((p) && (pbytes >= m_pbytes) && (m_pbytes)) {

            TALAS_LOG_DEBUG("mpz_get_msb(p,pbytes,&m_dmp1)...");
            mpz_get_msb(p,pbytes,&m_dmp1);
            return m_pbytes;
        }
        return 0;
    }
    virtual ssize_t get_dmq1_msb
    (byte_t* p, size_t pbytes) const {
        if ((p) && (pbytes >= m_pbytes) && (m_pbytes)) {

            TALAS_LOG_DEBUG("mpz_get_msb(p,pbytes,&m_dmq1)...");
            mpz_get_msb(p,pbytes,&m_dmq1);
            return m_pbytes;
        }
        return 0;
    }
    virtual ssize_t get_iqmp_msb
    (byte_t* p, size_t pbytes) const {
        if ((p) && (pbytes >= m_pbytes) && (m_pbytes)) {

            TALAS_LOG_DEBUG("mpz_get_msb(p,pbytes,&m_iqmp)...");
            mpz_get_msb(p,pbytes,&m_iqmp);
            return m_pbytes;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set
    (const mpint_t *p, const mpint_t *q,
     const mpint_t *dmp1, const mpint_t *dmq1,
     const mpint_t *iqmp, size_t pbytes) {
        if ((p) && (q) && (dmp1) && (dmq1) && (iqmp) && (pbytes)) {
            if ((m_pbytes)) {

                TALAS_LOG_DEBUG("mpz_set(&m_p,p)...");
                mpz_set(&m_p,p);

                TALAS_LOG_DEBUG("mpz_set(&m_q,q)...");
                mpz_set(&m_q,q);

                TALAS_LOG_DEBUG("mpz_set(&m_dmp1,dmp1)...");
                mpz_set(&m_dmp1,dmp1);

                TALAS_LOG_DEBUG("mpz_set(&m_dmq1,dmq1)...");
                mpz_set(&m_dmq1,dmq1);

                TALAS_LOG_DEBUG("mpz_set(&m_iqmp,iqmp)...");
                mpz_set(&m_iqmp,iqmp);
                m_expbytes = (m_modbytes = ((m_pbytes = pbytes) << 1));
                return true;
            }
        }
        return false;
    }
    virtual bool get
    (size_t& plen, mpint_t *p, mpint_t *q,
     mpint_t *dmp1, mpint_t *dmq1, mpint_t *iqmp) {
        if ((p) && (q) && (dmp1) && (dmq1) && (iqmp)) {
            if ((m_pbytes)) {

                TALAS_LOG_DEBUG("mpz_set(p,&m_p)...");
                mpz_set(p,&m_p);

                TALAS_LOG_DEBUG("mpz_set(q,&m_q)...");
                mpz_set(q,&m_q);

                TALAS_LOG_DEBUG("mpz_set(dmp1,&m_dmp1)...");
                mpz_set(dmp1,&m_dmp1);

                TALAS_LOG_DEBUG("mpz_set(dmq1,&m_dmq1)...");
                mpz_set(dmq1,&m_dmq1);

                TALAS_LOG_DEBUG("mpz_set(iqmp,&m_iqmp)...");
                mpz_set(iqmp,&m_iqmp);
                plen = m_pbytes;
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    /// Performs a private-key RSA operation (encrypt/decrypt). The computation
    /// is done using the Chinese Remainder Theorem, which is faster than
    /// direct modular exponentiation.
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t operator()
    (void* out, size_t outsize, const void* in, size_t inlen) {
        if ((m_modbytes)) {
            const byte_t* inb = 0;
            byte_t* outb = 0;

            if ((inb = ((const byte_t*)in)) && (inlen == m_modbytes)
                && (outb = ((byte_t*)out)) && (outsize >= m_modbytes)) {
                bool subp = 0;

                TALAS_LOG_DEBUG("mpz_set_msb(&m_temp,inb,m_modbytes)...");
                mpz_set_msb(&m_temp,inb,m_modbytes);

                // Compute q2 = (value mod q) ^ dmq1 mod q.
                //
                TALAS_LOG_DEBUG("mpz_mod(&m_qtemp,&m_temp,&m_q)...");
                mpz_mod(&m_qtemp,&m_temp,&m_q);

                TALAS_LOG_DEBUG("mpz_powm(&m_qtemp,&m_qtemp,&m_dmq1,&m_q)...");
                mpz_powm(&m_qtemp,&m_qtemp,&m_dmq1,&m_q);

                // Compute p2 = (value mod p) ^ dmp1 mod p.
                //
                TALAS_LOG_DEBUG("mpz_mod(&m_ptemp,&m_temp,&m_p)...");
                mpz_mod(&m_ptemp,&m_temp,&m_p);

                TALAS_LOG_DEBUG("mpz_powm(&m_ptemp,&m_ptemp,&m_dmp1,&m_p)...");
                mpz_powm(&m_ptemp,&m_ptemp,&m_dmp1,&m_p);

                // if q2 > p then q2 = q2 - p
                //
                if ((subp=(mpz_cmp(&m_qtemp,&m_p)>0))!=0) {
                    TALAS_LOG_DEBUG("mpz_sub(&m_qtemp,&m_qtemp,&m_p)...");
                    mpz_sub(&m_qtemp,&m_qtemp,&m_p);
                }
                // Compute k = (((p2 + p) - q2) mod p) * iqmp mod p.
                //
                TALAS_LOG_DEBUG("mpz_add(&m_temp,&m_ptemp,&m_p)...");
                mpz_add(&m_temp,&m_ptemp,&m_p);

                TALAS_LOG_DEBUG("mpz_sub(&m_temp,&m_temp,&m_qtemp)...");
                mpz_sub(&m_temp,&m_temp,&m_qtemp);

                TALAS_LOG_DEBUG("mpz_mul(&m_ptemp,&m_temp,&m_iqmp)...");
                mpz_mul(&m_ptemp,&m_temp,&m_iqmp);

                TALAS_LOG_DEBUG("mpz_mmod(&m_temp,&m_ptemp,&m_p)...");
                mpz_mmod(&m_temp,&m_ptemp,&m_p);

                // Compute value = q2 + q * k.
                //
                TALAS_LOG_DEBUG("mpz_mul(&m_ptemp,&m_temp,&m_q)...");
                mpz_mul(&m_ptemp,&m_temp,&m_q);

                TALAS_LOG_DEBUG("mpz_add(&m_temp,&m_ptemp,&m_qtemp)...");
                mpz_add(&m_temp,&m_ptemp,&m_qtemp);

                // if we subtracted p before then add it back here
                //
                if (subp) {
                    TALAS_LOG_DEBUG("mpz_add(&m_temp,&m_temp,&m_p)...");
                    mpz_add(&m_temp,&m_temp,&m_p);
                }
                TALAS_LOG_DEBUG("mpz_get_msb(outb,m_modbytes,&m_temp)...");
                mpz_get_msb(outb,m_modbytes,&m_temp);
                return m_modbytes;
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual BIGINT& p() const {
        return (BIGINT&)m_p;
    }
    virtual BIGINT& q() const {
        return (BIGINT&)m_q;
    }
    virtual BIGINT& dmp1() const {
        return (BIGINT&)m_dmp1;
    }
    virtual BIGINT& dmq1() const {
        return (BIGINT&)m_dmq1;
    }
    virtual BIGINT& iqmp() const {
        return (BIGINT&)m_iqmp;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    MP_INT m_p, m_q, m_dmp1, m_dmq1, m_iqmp, m_ptemp, m_qtemp;
};

} // namespace mp 
} // namespace rsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RSA_MP_PRIVATE_KEY_HPP 
