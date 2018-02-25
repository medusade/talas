///////////////////////////////////////////////////////////////////////
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
///   Date: 2/20/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DSA_BN_PUBLIC_KEY_HPP
#define _TALAS_CRYPTO_DSA_BN_PUBLIC_KEY_HPP

#include "talas/crypto/dsa/public_key.hpp"
#include "talas/crypto/dsa/bn/key.hpp"

namespace talas {
namespace crypto {
namespace dsa {
namespace bn {

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
        ssize_t result = 0;
        
        if ((this->p_) && (this->pbytes_) && (this->q_) && (this->qbytes_) 
            && (this->g_) && (this->gbytes_) && (this->y_) && (this->ybytes_) && (this->ctx_)
            && (v) && (vbytes) && (vbytes >= this->qbytes_)
            && (h) && (hbytes) && (hbytes <= this->qbytes_)
            && (r) && (rbytes) && (rbytes == this->qbytes_)
            && (s) && (sbytes) && (sbytes == this->qbytes_)) {
            BIGNUM *v_, *r_, *s_, *h_, *u1_ = 0, *u2_ = 0, *si_;

            TALAS_LOG_DEBUG("v_ = BN_new()...");
            if ((v_ = BN_new())) {

                TALAS_LOG_DEBUG("r_ = BN_new()...");
                if ((r_ = BN_new())) {

                    TALAS_LOG_DEBUG("BN_set_msb(r_, r, rbytes)...");
                    BN_set_msb(r_, r, rbytes);

                    TALAS_LOG_DEBUG("s_ = BN_new()...");
                    if ((s_ = BN_new())) {
                        
                        TALAS_LOG_DEBUG("BN_set_msb(s_, s, hbytes)...");
                        BN_set_msb(s_, s, hbytes);
                        
                        TALAS_LOG_DEBUG("h_ = BN_new()...");
                        if ((h_ = BN_new())) {
                            
                            TALAS_LOG_DEBUG("BN_set_msb(h_, h, hbytes)...");
                            BN_set_msb(h_, h, hbytes);
                            
                            TALAS_LOG_DEBUG("u1_ = BN_new()...");
                            if ((u1_ = BN_new())) {
                                
                                TALAS_LOG_DEBUG("u2_ = BN_new()...");
                                if ((u2_ = BN_new())) {
                                    BIGNUM *t1_ = v_, *t2_ = r_;
                                    
                                    // si = s^-1 mod q
                                    //
                                    TALAS_LOG_DEBUG("BN_mod_inverse(s_, this->q_, this->ctx_)...");
                                    if ((si_ = BN_mod_inverse(s_, this->q_, this->ctx_))) {
                                        // u2 = r*si mod q
                                        //
                                        TALAS_LOG_DEBUG("BN_mul(t1_, r_, si_)...");
                                        BN_mul(t1_, r_, si_);
                                        
                                        TALAS_LOG_DEBUG("BN_mod(u2_, t1_, this->q_, this->ctx_)...");
                                        BN_mod(u2_, t1_, this->q_, this->ctx_);
                                        // u1 = h*si mod q
                                        //
                                        TALAS_LOG_DEBUG("BN_mul(t1_, h_, si_)...");
                                        BN_mul(t1_, h_, si_);
                                        
                                        TALAS_LOG_DEBUG("BN_mod(u1_, t1_, this->q_, this->ctx_)...");
                                        BN_mod(u1_, t1_, this->q_, this->ctx_);
                                        // t1 = g^u1 mod p
                                        //
                                        TALAS_LOG_DEBUG("BN_mod_exp(t1_, this->g_, u1_, this->p_, this->ctx_)...");
                                        BN_mod_exp(t1_, this->g_, u1_, this->p_, this->ctx_);
                                        // t2 = y^u2 mod p
                                        //
                                        TALAS_LOG_DEBUG("BN_mod_exp(t2_, this->y_, u2_, this->p_, this->ctx_)...");
                                        BN_mod_exp(t2_, this->y_, u2_, this->p_, this->ctx_);
                                        // u2 = t1*t2 mod p
                                        //
                                        TALAS_LOG_DEBUG("BN_mul(u1_, t1_, t2_)...");
                                        BN_mul(u1_, t1_, t2_);
                                        
                                        TALAS_LOG_DEBUG("BN_mod(u2_, u1_, this->p_, this->ctx_)...");
                                        BN_mod(u2_, u1_, this->p_, this->ctx_);
                                        // v = u2 mod q
                                        //
                                        TALAS_LOG_DEBUG("BN_mod(v_, u2_, this->q_, this->ctx_)...");
                                        BN_mod(v_, u2_, this->q_, this->ctx_);
                                        
                                        TALAS_LOG_DEBUG("BN_get_msb(v_, v, this->qbytes_)...");
                                        BN_get_msb(v_, v, this->qbytes_);
                                        result = this->qbytes_;
                                        
                                        TALAS_LOG_DEBUG("BN_clear_free(si_)...");
                                        BN_clear_free(si_);
                                    }
                                    TALAS_LOG_DEBUG("BN_clear_free(u2_)...");
                                    BN_clear_free(u2_);
                                }
                                TALAS_LOG_DEBUG("BN_clear_free(u1_)...");
                                BN_clear_free(u1_);
                            }
                            TALAS_LOG_DEBUG("BN_clear_free(h_)...");
                            BN_clear_free(h_);
                        }
                        TALAS_LOG_DEBUG("BN_clear_free(s_)...");
                        BN_clear_free(s_);
                    }
                    TALAS_LOG_DEBUG("BN_clear_free(r_)...");
                    BN_clear_free(r_);
                }
                TALAS_LOG_DEBUG("BN_clear_free(v_)...");
                BN_clear_free(v_);
            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_y_msb(const byte_t* y, size_t ybytes) {
        if ((this->y_) && (this->ybytes_) && (y) && (ybytes <= this->ybytes_)) {

            TALAS_LOG_DEBUG("BN_set_msb(this->y_, y, this->ybytes_)...");
            BN_set_msb(this->y_, y, this->ybytes_);
            return this->ybytes_;
        }
        return 0;
    }
    virtual ssize_t get_y_msb(byte_t* y, size_t ybytes) const {
        if ((this->y_) && (this->ybytes_) && (y) && (ybytes >= this->ybytes_)) {
            
            TALAS_LOG_DEBUG("BN_get_msb(this->y_, y, this->ybytes_)...");
            BN_get_msb(this->y_, y, this->ybytes_);
            return this->ybytes_;
        }
        return 0;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void init() {
        TALAS_LOG_DEBUG("y_ = 0; ctx_ = 0...");
        y_ = 0; ctx_ = 0;
        
        TALAS_LOG_DEBUG("y_ = BN_new()...");
        if ((y_ = BN_new())) {
            
            TALAS_LOG_DEBUG("ctx_ = BN_CTX_new()...");
            if ((ctx_ = BN_CTX_new())) {
                
                return;
                TALAS_LOG_DEBUG("BN_CTX_free(ctx_)...");
                BN_CTX_free(ctx_);
                ctx_ = 0;
            }
            TALAS_LOG_DEBUG("BN_free(y_)...");
            BN_free(y_);
            y_ = 0;
        }
        const creator_exception e = failed_to_create;
        TALAS_LOG_ERROR("...keyt(const keyt& copy) not allowed throw(const creator_exception e = failed_to_create)...")
        throw(e);
    }
    virtual void fini() {
        if ((y_)) {
            TALAS_LOG_DEBUG("BN_clear_free(y_)...");
            BN_clear_free(y_);
            y_ = 0;
        }
        if ((ctx_)) {
            TALAS_LOG_DEBUG("BN_CTX_free(ctx_)...");
            BN_CTX_free(ctx_);
            ctx_ = 0;
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void clear() {
        if ((y_)) {
            TALAS_LOG_DEBUG("BN_clear(y_)...");
            BN_clear(y_);
        }
        Extends::clear();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual BIGNUM *y() const {
        return (BIGNUM *)y_;
    }
    virtual BN_CTX *ctx() const {
        return (BN_CTX *)ctx_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    BIGNUM *y_;
    BN_CTX *ctx_;
};
typedef public_keyt<> public_key;

} // namespace bn 
} // namespace dsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DSA_BN_PUBLIC_KEY_HPP 
