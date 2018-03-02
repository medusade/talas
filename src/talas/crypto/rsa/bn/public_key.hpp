///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
/// All rights reserved
/// Copyright (C) 1995-1997 Eric Young (eay@cryptsoft.com)
/// All rights reserved.
/// 
/// This package is an SSL implementation written
/// by Eric Young (eay@cryptsoft.com).
/// The implementation was written so as to conform with Netscapes SSL.
/// 
/// This library is free for commercial and non-commercial use as long as
/// the following conditions are aheared to.  The following conditions
/// apply to all code found in this distribution, be it the RC4, RSA,
/// lhash, DES, etc., code; not just the SSL code.  The SSL documentation
/// included with this distribution is covered by the same copyright terms
/// except that the holder is Tim Hudson (tjh@cryptsoft.com).
/// 
/// Copyright remains Eric Young's, and as such any Copyright notices in
/// the code are not to be removed.
/// If this package is used in a product, Eric Young should be given attribution
/// as the author of the parts of the library used.
/// This can be in the form of a textual message at program startup or
/// in documentation (online or textual) provided with the package.
/// 
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions
/// are met:
/// 1. Redistributions of source code must retain the copyright
///    notice, this list of conditions and the following disclaimer.
/// 2. Redistributions in binary form must reproduce the above copyright
///    notice, this list of conditions and the following disclaimer in the
///    documentation and/or other materials provided with the distribution.
/// 3. All advertising materials mentioning features or use of this software
///    must display the following acknowledgement:
///    "This product includes cryptographic software written by
///     Eric Young (eay@cryptsoft.com)"
///    The word 'cryptographic' can be left out if the rouines from the library
///    being used are not cryptographic related :-).
/// 4. If you include any Windows specific code (or a derivative thereof) from
///    the apps directory (application code) you must include an acknowledgement:
///    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
/// 
/// THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
/// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
/// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
/// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
/// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
/// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
/// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
/// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
/// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
/// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
/// SUCH DAMAGE.
/// 
/// The licence and distribution terms for any publically available version or
/// derivative of this code cannot be changed.  i.e. this code cannot simply be
/// copied and put under another distribution licence
/// [including the GNU Public Licence.]
///
///   File: public_key.hpp
///
/// Author: $author$
///   Date: 5/10/2015
///
/// Tatu Ylonen's RSA public key implementation modified to be a C++
/// class that uses Eric Young's big number library instead of gmp used
/// in the original C version.
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RSA_BN_PUBLIC_KEY_HPP
#define _TALAS_CRYPTO_RSA_BN_PUBLIC_KEY_HPP

#include "talas/crypto/rsa/bn/key.hpp"
#include "talas/crypto/rsa/public_key.hpp"

namespace talas {
namespace crypto {
namespace rsa {
namespace bn {

///////////////////////////////////////////////////////////////////////
///  Class: public_key_implements
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS public_key_implements
: virtual public rsa::public_key_implements, virtual public bn::key_implements {
public:
};
typedef bn::key public_key_extends;
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
     const byte_t* exponent, size_t expbytes)
    : m_modulus(0), m_exponent(0) {
        if (!(this->create_msb(modulus, modbytes, exponent, expbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create() throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    public_key
    (const mpint_t* modulus, size_t modbytes,
     const mpint_t* exponent, size_t expbytes)
    : m_modulus(0), m_exponent(0) {
        if (!(this->create(modulus, modbytes, exponent, expbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create() throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    public_key(size_t modbytes, size_t expbytes): m_modulus(0), m_exponent(0) {
        if (!(this->create(modbytes, expbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create() throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    public_key(const public_key& copy): m_modulus(0), m_exponent(0) {
        if (!(this->create(copy.m_modulus, copy.m_modbytes, copy.m_exponent, copy.m_expbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create() throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    public_key(): m_modulus(0), m_exponent(0) {
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

                TALAS_LOG_DEBUG("m_modulus = BN_new()...");
                if ((m_modulus = BN_new())) {

                    TALAS_LOG_DEBUG("m_exponent = BN_new()...");
                    if ((m_exponent = BN_new())) {
                        return true;

                        TALAS_LOG_DEBUG("BN_free(m_exponent)...");
                        BN_free(m_exponent);
                    }
                    TALAS_LOG_DEBUG("BN_free(m_modulus)...");
                    BN_free(m_modulus);
                }
                Extends::destroy();
            }
        }
        return false;
    }
    virtual bool destroy() {
        if ((this->is_created())) {
            bool success = true;

            TALAS_LOG_DEBUG("BN_free(m_exponent)...");
            if (!(BN_free(m_exponent))) {
                success = false;
            }

            TALAS_LOG_DEBUG("BN_free(m_modulus)...");
            if (!(BN_free(m_modulus))) {
                success = false;
            }
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
            if ((m_modulus) && (m_exponent)) {

                TALAS_LOG_DEBUG("BN_set_msb(m_modulus, modulus, m_modbytes = modbytes)...");
                BN_set_msb(m_modulus, modulus, m_modbytes = modbytes);

                TALAS_LOG_DEBUG("BN_set_msb(m_exponent, exponent, m_expbytes = expbytes)...");
                BN_set_msb(m_exponent, exponent, m_expbytes = expbytes);
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
            if ((m_modulus) && (modbytes >= m_modbytes)
                && (m_exponent) && (expbytes >= m_expbytes)) {

                TALAS_LOG_DEBUG("BN_get_msb(m_modulus, modulus, m_modbytes)...");
                BN_get_msb(m_modulus, modulus, m_modbytes);

                TALAS_LOG_DEBUG("BN_get_msb(m_exponent, exponent, m_expbytes)...");
                BN_get_msb(m_exponent, exponent, m_expbytes);
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
            if ((m_modulus) && (modbytes >= m_modbytes)) {

                TALAS_LOG_DEBUG("BN_get_msb(m_modulus, modulus, m_modbytes)...");
                BN_get_msb(m_modulus, modulus, m_modbytes);
                return m_modbytes;
            }
        }
        return 0;
    }
    virtual ssize_t get_exponent_msb
    (byte_t* exponent, size_t expbytes) const {
        if ((exponent) && (expbytes)) {
            if ((m_exponent) && (expbytes >= m_expbytes)) {

                TALAS_LOG_DEBUG("BN_get_msb(m_exponent, exponent, m_expbytes)...");
                BN_get_msb(m_exponent, exponent, m_expbytes);
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
            if ((m_modulus) && (m_exponent)) {

                TALAS_LOG_DEBUG("BN_copy(m_modulus, (BIGNUM*)(modulus))...");
                BN_copy(m_modulus, (BIGNUM*)(modulus));

                TALAS_LOG_DEBUG("BN_copy(m_exponent, (BIGNUM*)(exponent))...");
                BN_copy(m_exponent, (BIGNUM*)(exponent));
                return true;
            }
        }
        return false;
    }
    virtual bool get
    (size_t& modlen, size_t& explen,
     mpint_t*& modulus, mpint_t*& exponent) const {
        if ((modulus) && (exponent)) {
            if ((m_modulus) && (m_exponent)) {

                TALAS_LOG_DEBUG("BN_copy(modulus, m_modulus)...");
                BN_copy(modulus, m_modulus);

                TALAS_LOG_DEBUG("BN_copy(exponent, m_exponent)...");
                BN_copy(exponent, m_exponent);
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
        if ((m_modulus) && (m_modbytes)
            && (m_exponent) && (m_expbytes) && (m_temp) && (m_ctx)) {
            const byte_t* inb;
            byte_t* outb;

            if ((inb = ((const byte_t*)in)) && (inlen == m_modbytes)
                && (outb = ((byte_t*)out)) && (outsize >= m_modbytes)) {

                TALAS_LOG_DEBUG("BN_set_msb(m_temp, inb, inlen)...");
                BN_set_msb(m_temp, inb, inlen);

                TALAS_LOG_DEBUG("BN_mod_exp(m_temp, m_temp, m_exponent, m_modulus, m_ctx)...");
                BN_mod_exp(m_temp, m_temp, m_exponent, m_modulus, m_ctx);

                TALAS_LOG_DEBUG("BN_get_msb(m_temp, outb, m_modbytes)...");
                BN_get_msb(m_temp, outb, m_modbytes);
                return m_modbytes;
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual BIGNUM* modulus(size_t& modlen) const {
        if ((m_modulus) && (m_modbytes)) {
            modlen = m_modbytes;
            return m_modulus;
        }
        return 0;
    }
    virtual BIGNUM* exponent(size_t& explen) const {
        if ((m_exponent) && (m_expbytes)) {
            explen = m_expbytes;
            return m_exponent;
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
    BIGNUM *m_modulus, *m_exponent;
};

} // namespace bn 
} // namespace rsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RSA_BN_PUBLIC_KEY_HPP 
