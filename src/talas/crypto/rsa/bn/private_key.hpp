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
///   File: private_key.hpp
///
/// Author: $author$
///   Date: 5/11/2015
///
/// Tatu Ylonen's RSA private key implementation modified to be a C++
/// class that uses Eric Young's big number library instead of gmp used
/// in the original C version.
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RSA_BN_PRIVATE_KEY_HPP
#define _TALAS_CRYPTO_RSA_BN_PRIVATE_KEY_HPP

#include "talas/crypto/rsa/bn/key.hpp"
#include "talas/crypto/rsa/private_key.hpp"

namespace talas {
namespace crypto {
namespace rsa {
namespace bn {

///////////////////////////////////////////////////////////////////////
///  Class: private_key_implements
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS private_key_implements
: virtual public rsa::private_key_implements, virtual public bn::key_implements {
public:
};
typedef bn::key private_key_extends;
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
    (const BYTE *p, const BYTE *q,
     const BYTE *dmp1, const BYTE *dmq1,
     const BYTE *iqmp, size_t pbytes)
    : m_p(0), m_q(0),
      m_dmp1(0), m_dmq1(0),
      m_iqmp(0), m_ptemp(0), m_qtemp(0) {
        if (!(this->create_msb(p, q, dmp1, dmq1, iqmp, pbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create() throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    private_key
    (const mpint_t *p, const mpint_t *q,
     const mpint_t *dmp1, const mpint_t *dmq1,
     const mpint_t *iqmp, size_t pbytes)
    : m_p(0), m_q(0),
      m_dmp1(0), m_dmq1(0),
      m_iqmp(0), m_ptemp(0), m_qtemp(0) {
        if (!(this->create(p, q, dmp1, dmq1, iqmp, pbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create() throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    private_key(size_t pbytes)
    : m_p(0), m_q(0),
      m_dmp1(0), m_dmq1(0),
      m_iqmp(0), m_ptemp(0), m_qtemp(0) {
        if (!(this->create(pbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create() throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    private_key(const private_key& copy)
    : m_p(0), m_q(0),
      m_dmp1(0), m_dmq1(0),
      m_iqmp(0), m_ptemp(0), m_qtemp(0) {
        if (!(this->create(copy.m_p, copy.m_q, copy.m_dmp1, copy.m_dmq1, copy.m_iqmp, copy.m_pbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create() throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    private_key()
    : m_p(0), m_q(0),
      m_dmp1(0), m_dmq1(0),
      m_iqmp(0), m_ptemp(0), m_qtemp(0) {
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
                
            TALAS_LOG_DEBUG("m_p=BN_new()...");
            if ((m_p=BN_new())) {
                
            TALAS_LOG_DEBUG("m_q=BN_new()...");
            if ((m_q=BN_new())) {
                
            TALAS_LOG_DEBUG("m_dmp1=BN_new()...");
            if ((m_dmp1=BN_new())) {
                
            TALAS_LOG_DEBUG("m_dmq1=BN_new()...");
            if ((m_dmq1=BN_new())) {
                
            TALAS_LOG_DEBUG("m_iqmp=BN_new()...");
            if ((m_iqmp=BN_new())) {
                
            TALAS_LOG_DEBUG("m_ptemp=BN_new()...");
            if ((m_ptemp=BN_new())) {
                
            TALAS_LOG_DEBUG("m_qtemp=BN_new()...");
            if ((m_qtemp=BN_new())) {
                return true;
                
            TALAS_LOG_DEBUG("BN_free(m_qtemp)...");
            BN_free(m_qtemp); }

            TALAS_LOG_DEBUG("BN_free(m_ptemp)...");
            BN_free(m_ptemp); }

            TALAS_LOG_DEBUG("BN_free(m_iqmp)...");
            BN_free(m_iqmp); }

            TALAS_LOG_DEBUG("BN_free(m_dmq1)...");
            BN_free(m_dmq1); }

            TALAS_LOG_DEBUG("BN_free(m_dmp1)...");
            BN_free(m_dmp1); }

            TALAS_LOG_DEBUG("BN_free(m_q)...");
            BN_free(m_q); }

            TALAS_LOG_DEBUG("BN_free(m_p)...");
            BN_free(m_p); }
            Extends::destroy(); }
        }
        return false;
    }
    virtual bool destroy() {
        if ((this->is_created())) {
            bool success = true;

            TALAS_LOG_DEBUG("BN_free(m_p)...");
            if (!(BN_free(m_p))) {
                success = false; }

            TALAS_LOG_DEBUG("BN_free(m_q)...");
            if (!(BN_free(m_q))) {
                success = false; }

            TALAS_LOG_DEBUG("BN_free(m_dmp1)...");
            if (!(BN_free(m_dmp1))) {
                success = false; }

            TALAS_LOG_DEBUG("BN_free(m_dmq1)...");
            if (!(BN_free(m_dmq1))) {
                success = false; }

            TALAS_LOG_DEBUG("BN_free(m_iqmp)...");
            if (!(BN_free(m_iqmp))) {
                success = false; }

            TALAS_LOG_DEBUG("BN_free(m_ptemp)...");
            if (!(BN_free(m_ptemp))) {
                success = false; }

            TALAS_LOG_DEBUG("BN_free(m_qtemp)...");
            if (!(BN_free(m_qtemp))) {
                success = false; }
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
            if ((m_p) && (m_q) && (m_dmp1) && (m_dmq1) && (m_iqmp)) {

                TALAS_LOG_DEBUG("BN_set_msb(m_p,p,pbytes)...");
                BN_set_msb(m_p,p,pbytes);

                TALAS_LOG_DEBUG("BN_set_msb(m_q,q,pbytes)...");
                BN_set_msb(m_q,q,pbytes);

                TALAS_LOG_DEBUG("N_set_msb(m_dmp1,dmp1,pbytes)...");
                BN_set_msb(m_dmp1,dmp1,pbytes);

                TALAS_LOG_DEBUG("BN_set_msb(m_dmq1,dmq1,pbytes)...");
                BN_set_msb(m_dmq1,dmq1,pbytes);

                TALAS_LOG_DEBUG("BN_set_msb(m_iqmp,iqmp,pbytes)...");
                BN_set_msb(m_iqmp,iqmp,pbytes);
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
            if ((m_p) && (m_q) && (m_dmp1) && (m_dmq1) && (m_iqmp)) {

                TALAS_LOG_DEBUG("BN_get_msb(m_p,p,pbytes)...");
                BN_get_msb(m_p,p,pbytes);

                TALAS_LOG_DEBUG("BN_get_msb(m_q,q,pbytes)...");
                BN_get_msb(m_q,q,pbytes);

                TALAS_LOG_DEBUG("BN_get_msb(m_dmp1,dmp1,pbytes)...");
                BN_get_msb(m_dmp1,dmp1,pbytes);

                TALAS_LOG_DEBUG("BN_get_msb(m_dmq1,dmq1,pbytes)...");
                BN_get_msb(m_dmq1,dmq1,pbytes);

                TALAS_LOG_DEBUG("BN_get_msb(m_iqmp,iqmp,pbytes)...");
                BN_get_msb(m_iqmp,iqmp,pbytes);
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
        if ((m_p) && (p) && (pbytes >= m_pbytes)) {

            TALAS_LOG_DEBUG("BN_get_msb(m_p,p,pbytes)...");
            BN_get_msb(m_p,p,pbytes);
            return m_pbytes;
        }
        return 0;
    }
    virtual ssize_t get_q_msb
    (byte_t* p, size_t pbytes) const {
        if ((m_q) && (p) && (pbytes >= m_pbytes)) {

            TALAS_LOG_DEBUG("BN_get_msb(m_q,p,pbytes)...");
            BN_get_msb(m_q,p,pbytes);
            return m_pbytes;
        }
        return 0;
    }
    virtual ssize_t get_dmp1_msb
    (byte_t* p, size_t pbytes) const {
        if ((m_dmp1) && (p) && (pbytes >= m_pbytes)) {

            TALAS_LOG_DEBUG("BN_get_msb(m_dmp1,p,pbytes)...");
            BN_get_msb(m_dmp1,p,pbytes);
            return m_pbytes;
        }
        return 0;
    }
    virtual ssize_t get_dmq1_msb
    (byte_t* p, size_t pbytes) const {
        if ((m_dmq1) && (p) && (pbytes >= m_pbytes)) {

            TALAS_LOG_DEBUG("BN_get_msb(m_dmq1,p,pbytes)...");
            BN_get_msb(m_dmq1,p,pbytes);
            return m_pbytes;
        }
        return 0;
    }
    virtual ssize_t get_iqmp_msb
    (byte_t* p, size_t pbytes) const {
        if ((m_iqmp) && (p) && (pbytes >= m_pbytes)) {

            TALAS_LOG_DEBUG("BN_get_msb(m_iqmp,p,pbytes)...");
            BN_get_msb(m_iqmp,p,pbytes);
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
            if ((m_p) && (m_q) && (m_dmp1) && (m_dmq1) && (m_iqmp)) {

                TALAS_LOG_DEBUG("BN_copy(m_p,(BIGNUM*)(p))...");
                BN_copy(m_p,(BIGNUM*)(p));

                TALAS_LOG_DEBUG("BN_copy(m_q,(BIGNUM*)(q))...");
                BN_copy(m_q,(BIGNUM*)(q));

                TALAS_LOG_DEBUG("BN_copy(m_dmp1,(BIGNUM*)(dmp1))...");
                BN_copy(m_dmp1,(BIGNUM*)(dmp1));

                TALAS_LOG_DEBUG("BN_copy(m_dmq1,(BIGNUM*)(dmq1))...");
                BN_copy(m_dmq1,(BIGNUM*)(dmq1));

                TALAS_LOG_DEBUG("BN_copy(m_iqmp,(BIGNUM*)(iqmp))...");
                BN_copy(m_iqmp,(BIGNUM*)(iqmp));
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
            if ((m_p) && (m_q) && (m_dmp1) && (m_dmq1) && (m_iqmp) && (m_pbytes)) {

                TALAS_LOG_DEBUG("BN_copy(p,m_p)...");
                BN_copy(p,m_p);

                TALAS_LOG_DEBUG("BN_copy(q,m_q)...");
                BN_copy(q,m_q);

                TALAS_LOG_DEBUG("BN_copy(dmp1,m_dmp1)...");
                BN_copy(dmp1,m_dmp1);

                TALAS_LOG_DEBUG("BN_copy(dmq1,m_dmq1)...");
                BN_copy(dmq1,m_dmq1);

                TALAS_LOG_DEBUG("BN_copy(iqmp,m_iqmp)...");
                BN_copy(iqmp,m_iqmp);
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
        if ((m_p) && (m_q) && (m_dmp1) && (m_dmq1)
            && (m_iqmp) && (m_pbytes) && (m_temp) && (m_ctx) && (m_modbytes)) {
            const byte_t* inb = 0;
            byte_t* outb = 0;

            if ((inb = ((const byte_t*)in)) && (inlen == m_modbytes)
                && (outb = ((byte_t*)out)) && (outsize >= m_modbytes)) {
                bool subp = false;

                TALAS_LOG_DEBUG("BN_set_msb(m_temp,inb,m_modbytes)...");
                BN_set_msb(m_temp,inb,m_modbytes);

                // Compute q2 = (value mod q) ^ dmq1 mod q.
                //
                TALAS_LOG_DEBUG("BN_mod(m_qtemp,m_temp,m_q,m_ctx)...");
                BN_mod(m_qtemp,m_temp,m_q,m_ctx);

                TALAS_LOG_DEBUG("BN_mod_exp(m_qtemp,m_qtemp,m_dmq1,m_q,m_ctx)...");
                BN_mod_exp(m_qtemp,m_qtemp,m_dmq1,m_q,m_ctx);

                // Compute p2 = (value mod p) ^ dmp1 mod p.
                //
                TALAS_LOG_DEBUG("BN_mod(m_ptemp,m_temp,m_p,m_ctx)...");
                BN_mod(m_ptemp,m_temp,m_p,m_ctx);

                TALAS_LOG_DEBUG("BN_mod_exp(m_ptemp,m_ptemp,m_dmp1,m_p,m_ctx)...");
                BN_mod_exp(m_ptemp,m_ptemp,m_dmp1,m_p,m_ctx);

                // if q2 > p then q2 = q2 - p
                //
                if ((subp=(BN_cmp(m_qtemp,m_p)>0))!=0) {
                    TALAS_LOG_DEBUG("BN_sub(m_qtemp,m_qtemp,m_p)...");
                    BN_sub(m_qtemp,m_qtemp,m_p);
                }
                // Compute k = (((p2 + p) - q2) mod p) * iqmp mod p.
                //
                TALAS_LOG_DEBUG("BN_add(m_temp,m_ptemp,m_p)...");
                BN_add(m_temp,m_ptemp,m_p);

                TALAS_LOG_DEBUG("BN_sub(m_temp,m_temp,m_qtemp)...");
                BN_sub(m_temp,m_temp,m_qtemp);

                TALAS_LOG_DEBUG("BN_mul(m_ptemp,m_temp,m_iqmp)...");
                BN_mul(m_ptemp,m_temp,m_iqmp);

                TALAS_LOG_DEBUG("BN_mod(m_temp,m_ptemp,m_p,m_ctx)...");
                BN_mod(m_temp,m_ptemp,m_p,m_ctx);

                // Compute value = q2 + q * k.
                //
                TALAS_LOG_DEBUG("BN_mul(m_ptemp,m_temp,m_q)...");
                BN_mul(m_ptemp,m_temp,m_q);

                TALAS_LOG_DEBUG("BN_add(m_temp,m_ptemp,m_qtemp)...");
                BN_add(m_temp,m_ptemp,m_qtemp);

                // if we subtracted p before the add it back here
                //
                if (subp) {
                    TALAS_LOG_DEBUG("BN_add(m_temp,m_temp,m_p)...");
                    BN_add(m_temp,m_temp,m_p);
                }
                TALAS_LOG_DEBUG("BN_get_msb(m_temp,outb,m_modbytes)...");
                BN_get_msb(m_temp,outb,m_modbytes);
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
    BIGNUM *m_p, *m_q, 
           *m_dmp1, *m_dmq1, 
           *m_iqmp, *m_ptemp, *m_qtemp;
};

} // namespace bn 
} // namespace rsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RSA_BN_PRIVATE_KEY_HPP 
