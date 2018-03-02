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
///   File: public_key.hpp
///
/// Author: $author$
///   Date: 5/12/2015
///
/// Tatu Ylonen's RSA public key implementation modified to be a C++
/// class that uses the gmp used in the original C version.
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RSA_MP_PUBLIC_KEY_HPP
#define _TALAS_CRYPTO_RSA_MP_PUBLIC_KEY_HPP

#include "talas/crypto/rsa/mp/key.hpp"
#include "talas/crypto/rsa/public_key.hpp"

namespace talas {
namespace crypto {
namespace rsa {
namespace mp {

///////////////////////////////////////////////////////////////////////
///  Class: public_key_implements
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS public_key_implements
: virtual public rsa::public_key_implements, virtual public mp::key_implements {
public:
};
typedef mp::key public_key_extends;
///////////////////////////////////////////////////////////////////////
///  Class: public_key
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS public_key
: virtual public public_key_implements, public public_key_extends {
public:
    typedef public_key_implements Implements;
    typedef public_key_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    public_key
    (const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if (!(this->create_msb(modulus, modbytes, exponent, expbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create() throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    public_key
    (const mpint_t* modulus, size_t modbytes,
     const mpint_t* exponent, size_t expbytes) {
        if (!(this->create(modulus, modbytes, exponent, expbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create() throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    public_key(size_t modbytes, size_t expbytes) {
        if (!(this->create(modbytes, expbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create() throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    public_key(const public_key& copy) {
        if (!(this->create(&copy.m_modulus, copy.m_modbytes, &copy.m_exponent, copy.m_expbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create() throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    public_key() {
    }
    virtual ~public_key() {
        if (!(this->destroyed())) {
            xos::base::creator_exception e = xos::base::failed_to_destroy;
            TALAS_LOG_ERROR("...failed on destroyed() throwing creator_exception failed_to_destroy...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create
    (const mpint_t* modulus, size_t modbytes,
     const mpint_t* exponent, size_t expbytes) {
        if ((modulus) && (modbytes) && (exponent) && (expbytes)) {
            if ((this->create(modbytes, expbytes))) {
                if ((this->set(modulus, exponent))) {
                    return true;
                }
                this->destroy();
            }
        }
        return false;
    }
    virtual bool create(size_t modbytes, size_t expbytes) {
        if ((this->destroyed())) {
            if ((Extends::create(modbytes, expbytes))) {

                TALAS_LOG_DEBUG("mpz_init_set_ui(&m_modulus,0)...");
                mpz_init_set_ui(&m_modulus,0);

                TALAS_LOG_DEBUG("mpz_init_set_ui(&m_exponent,0)...");
                mpz_init_set_ui(&m_exponent,0);
                return true;
                Extends::destroy();
            }
        }
        return false;
    }
    virtual bool destroy() {
        if ((this->is_created())) {
            bool success = true;

            TALAS_LOG_DEBUG("mpz_clear(&m_modulus)...");
            mpz_clear(&m_modulus);

            TALAS_LOG_DEBUG("mpz_clear(&m_exponent)...");
            mpz_clear(&m_exponent);
            if (!(Extends::destroy())) {
                success = false;
            }
            return success;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_msb
    (const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if ((modulus) && (modbytes) && (exponent) && (expbytes)) {
            if ((m_modbytes) && (m_expbytes)) {

                TALAS_LOG_DEBUG("mpz_set_msb(&m_modulus, modulus, m_modbytes = modbytes)...");
                mpz_set_msb(&m_modulus, modulus, m_modbytes = modbytes);

                TALAS_LOG_DEBUG("mpz_set_msb(&m_exponent, exponent, m_expbytes = expbytes)...");
                mpz_set_msb(&m_exponent, exponent, m_expbytes = expbytes);
                m_pbytes = (m_modbytes >> 1);
                return true;
            }
        }
        return false;
    }
    virtual bool get_msb
    (size_t& modlen, size_t& explen,
     byte_t* modulus, size_t modbytes,
     byte_t* exponent, size_t expbytes) const {
        if ((modulus) && (modbytes) && (exponent) && (expbytes)) {
            if ((m_modbytes) && (modbytes >= m_modbytes)
                && (m_expbytes) && (expbytes >= m_expbytes)) {

                TALAS_LOG_DEBUG("mpz_get_msb(modulus, m_modbytes, &m_modulus)...");
                mpz_get_msb(modulus, m_modbytes, &m_modulus);

                TALAS_LOG_DEBUG("mpz_get_msb(exponent, m_expbytes, &m_exponent)...");
                mpz_get_msb(exponent, m_expbytes, &m_exponent);
                explen = m_expbytes;
                modlen = m_modbytes;
                return true;
            }
        }
        return false;
    }
    virtual ssize_t get_modulus_msb
    (byte_t* modulus, size_t modbytes) const {
        if ((modulus) && (modbytes)) {
            if ((m_modbytes) && (modbytes >= m_modbytes)) {

                TALAS_LOG_DEBUG("mpz_get_msb(modulus, m_modbytes, &m_modulus)...");
                mpz_get_msb(modulus, m_modbytes, &m_modulus);
                return m_modbytes;
            }
        }
        return 0;
    }
    virtual ssize_t get_exponent_msb
    (byte_t* exponent, size_t expbytes) const {
        if ((exponent) && (expbytes)) {
            if ((m_expbytes) && (expbytes >= m_expbytes)) {

                TALAS_LOG_DEBUG("mpz_get_msb(exponent, m_expbytes, &m_exponent)...");
                mpz_get_msb(exponent, m_expbytes, &m_exponent);
                return m_expbytes;
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set
    (const mpint_t* modulus, const mpint_t* exponent) {
        if ((modulus) && (exponent)) {
            if ((m_modbytes) && (m_expbytes)) {

                TALAS_LOG_DEBUG("mpz_set(&m_modulus, (modulus))...");
                mpz_set(&m_modulus, (modulus));

                TALAS_LOG_DEBUG("mpz_set(&m_exponent, (exponent))...");
                mpz_set(&m_exponent, (exponent));
                return true;
            }
        }
        return false;
    }
    virtual bool get
    (size_t& modlen, size_t& explen,
     mpint_t*& modulus, mpint_t*& exponent) const {
        if ((modulus) && (exponent)) {
            if ((m_modbytes) && (m_expbytes)) {

                TALAS_LOG_DEBUG("mpz_set(modulus, &m_modulus)...");
                mpz_set(modulus, &m_modulus);

                TALAS_LOG_DEBUG("mpz_set(exponent, &m_exponent)...");
                mpz_set(exponent, &m_exponent);
                explen = m_expbytes;
                modlen = m_modbytes;
                return true;
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t operator()
    (void* out, size_t outsize, const void* in, size_t inlen) {
        if ((m_modbytes) && (m_expbytes)) {
            const byte_t* inb;
            byte_t* outb;

            if ((inb = ((const byte_t*)in)) && (inlen == m_modbytes)
                && (outb = ((byte_t*)out)) && (outsize >= m_modbytes)) {

                TALAS_LOG_DEBUG("mpz_set_msb(&m_temp, inb, m_modbytes)...");
                mpz_set_msb(&m_temp, inb, m_modbytes);

                TALAS_LOG_DEBUG("mpz_powm(&m_temp, &m_temp, &m_exponent, &m_modulus)...");
                mpz_powm(&m_temp, &m_temp, &m_exponent, &m_modulus);

                TALAS_LOG_DEBUG("mpz_get_msb(outb, m_modbytes, &m_temp)...");
                mpz_get_msb(outb, m_modbytes, &m_temp);
                return m_modbytes;
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual BIGINT& modulus() const {
        return (BIGINT&)m_modulus;
    }
    virtual BIGINT& exponent() const {
        return (BIGINT&)m_exponent;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    MP_INT m_modulus, m_exponent;
};

} // namespace mp 
} // namespace rsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RSA_MP_PUBLIC_KEY_HPP 
