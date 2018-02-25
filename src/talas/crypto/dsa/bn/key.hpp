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
///   File: key.hpp
///
/// Author: $author$
///   Date: 2/20/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DSA_BN_KEY_HPP
#define _TALAS_CRYPTO_DSA_BN_KEY_HPP

#include "talas/crypto/dsa/key.hpp"
#include "bn_msb.h"

namespace talas {
namespace crypto {
namespace dsa {
namespace bn {

///////////////////////////////////////////////////////////////////////
///  Class: keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = key_implements, 
 class TExtends = key_extend>

class _EXPORT_CLASS keyt: virtual public TImplements,public TExtends {
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
        if ((this->p_) && (this->pbytes_) 
             && (p) && (pbytes) && (pbytes <= this->pbytes_)) {

            TALAS_LOG_DEBUG("BN_set_msb(this->p_, p, pbytes)...");
            BN_set_msb(this->p_, p, pbytes);
            return pbytes;
        }
        return 0;
    }
    virtual ssize_t get_p_msb(byte_t* p, size_t pbytes) const {
        if ((this->p_) && (this->pbytes_) 
            && (p) && (pbytes) && (pbytes >= this->pbytes_)) {

            TALAS_LOG_DEBUG("BN_get_msb(this->p_, p, this->pbytes)...");
            BN_get_msb(this->p_, p, this->pbytes_);
            return this->pbytes_;
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_q_msb(const byte_t* q, size_t qbytes) {
        if ((this->q_) && (this->qbytes_) 
            && (q) && (qbytes) && (qbytes <= this->qbytes_)) {
            
            TALAS_LOG_DEBUG("BN_set_msb(this->q_, q, qbytes)...");
            BN_set_msb(this->q_, q, qbytes);
            return qbytes;
        }
        return 0;
    }
    virtual ssize_t get_q_msb(byte_t* q, size_t qbytes) const {
        if ((this->q_) && (this->qbytes_) 
            && (q) && (qbytes) && (qbytes >= this->qbytes_)) {

            TALAS_LOG_DEBUG("BN_get_msb(this->q_, q, this->qbytes_)...");
            BN_get_msb(this->q_, q, this->qbytes_);
            return this->qbytes_;
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_g_msb(const byte_t* g, size_t gbytes) {
        if ((this->g_) && (this->gbytes_) 
             && (g) && (gbytes) && (gbytes <= this->gbytes_)) {
            
            TALAS_LOG_DEBUG("BN_set_msb(this->g_, g, gbytes)...");
            BN_set_msb(this->g_, g, gbytes);
            return gbytes;
        }
        return 0;
    }
    virtual ssize_t get_g_msb(byte_t* g, size_t gbytes) const {
        if ((this->g_) && (this->gbytes_) 
             && (g) && (gbytes) && (gbytes >= this->gbytes_)) {

            TALAS_LOG_DEBUG("BN_get_msb(this->g_, g, this->gbytes_)...");
            BN_get_msb(this->g_, g, this->gbytes_);
            return this->gbytes_;
        }
        return 0;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void init() {
        TALAS_LOG_DEBUG("p_ = q_ = g_ = 0...");
        p_ = q_ = g_ = 0;
        
        TALAS_LOG_DEBUG("p_ = BN_new()...");
        if ((p_ = BN_new())) {
            
            TALAS_LOG_DEBUG("q_ = BN_new()...");
            if ((q_ = BN_new())) {
                
                TALAS_LOG_DEBUG("g_ = BN_new()...");
                if ((g_ = BN_new())) {
                    
                    return;
                    TALAS_LOG_DEBUG("BN_free(g_)...");
                    BN_free(g_);
                    g_ = 0;
                }
                TALAS_LOG_DEBUG("BN_free(q_)...");
                BN_free(q_);
                q_ = 0;
            }
            TALAS_LOG_DEBUG("BN_free(p_)...");
            BN_free(p_);
            p_ = 0;
        }
        const creator_exception e = failed_to_create;
        TALAS_LOG_ERROR("...keyt(const keyt& copy) not allowed throw(const creator_exception e = failed_to_create)...")
        throw(e);
    }
    virtual void fini() {
        if ((p_)) {
            TALAS_LOG_DEBUG("BN_clear_free(p_)...");
            BN_clear_free(p_);
            p_ = 0;
        }
        if ((q_)) {
            TALAS_LOG_DEBUG("BN_clear_free(q_)...");
            BN_clear_free(q_);
            q_ = 0;
        }
        if ((g_)) {
            TALAS_LOG_DEBUG("BN_clear_free(g_)...");
            BN_clear_free(g_);
            g_ = 0;
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void clear() {
        if ((p_)) {
            TALAS_LOG_DEBUG("BN_clear(p_)...");
            BN_clear(p_);
        }
        if ((q_)) {
            TALAS_LOG_DEBUG("BN_clear(q_)...");
            BN_clear(q_);
        }
        if ((g_)) {
            TALAS_LOG_DEBUG("BN_clear(g_)...");
            BN_clear(g_);
        }
        Extends::clear();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual BIGNUM *p() const {
        return (BIGNUM *)p_;
    }
    virtual BIGNUM *q() const {
        return (BIGNUM *)q_;
    }
    virtual BIGNUM *g() const {
        return (BIGNUM *)g_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    BIGNUM *p_, *q_, *g_;
};
typedef keyt<> key;

} // namespace bn 
} // namespace dsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DSA_BN_KEY_HPP 
