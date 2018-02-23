///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: private_key.hpp
///
/// Author: $author$
///   Date: 2/20/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DSA_BN_PRIVATE_KEY_HPP
#define _TALAS_CRYPTO_DSA_BN_PRIVATE_KEY_HPP

#include "talas/crypto/dsa/private_key.hpp"
#include "talas/crypto/dsa/bn/key.hpp"

namespace talas {
namespace crypto {
namespace dsa {
namespace bn {

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
        ssize_t result = 0;
        
        if ((this->p_) && (this->pbytes_) 
            && (this->q_) && (this->qbytes_) 
            && (this->g_) && (this->gbytes_) 
            && (this->x_) && (this->xbytes_) && (this->ctx_) 
            && (r) && (rbytes) && (rbytes >= this->qbytes_)
            && (s) && (sbytes) && (sbytes >= this->qbytes_)
            && (h) && (hbytes) && (k) && (kbytes)) {
            BIGNUM *r_, *s_, *h_, *k_ = 0, *ik_ = 0, *t1_ = 0, *t2_ = 0;

            TALAS_LOG_DEBUG("r_ = BN_new()...");
            if ((r_ = BN_new())) {

                TALAS_LOG_DEBUG("s_ = BN_new())...");
                if ((s_ = BN_new())) {

                    TALAS_LOG_DEBUG("h_ = BN_new()...");
                    if ((h_ = BN_new())) {

                        TALAS_LOG_DEBUG("BN_set_msb(h_, h, hbytes)...");
                        BN_set_msb(h_, h, hbytes);

                        TALAS_LOG_DEBUG("k_ = BN_new()...");
                        if ((k_ = BN_new())) {

                            TALAS_LOG_DEBUG("BN_set_msb(k_, k, kbytes)...");
                            BN_set_msb(k_, k, kbytes);

                            TALAS_LOG_DEBUG("t1_ = BN_new()...");
                            if ((t1_ = BN_new())) {

                                TALAS_LOG_DEBUG("t2_ = BN_new()...");
                                if ((t2_ = BN_new())) {
                                    // ik = k^-1 mod q
                                    //
                                    if ((ik_ = BN_mod_inverse(k_, this->q_, this->ctx_))) {
                                        // r = (g^k mod p) mod q
                                        //
                                        BN_mod_exp(t1_, this->g_, k_, this->p_, this->ctx_);
                                        BN_mod(r_, t1_, this->q_, this->ctx_);
                                        BN_get_msb(r_, r, this->qbytes_);
    
                                        // s = k^-1*(h+x*r) mod q
                                        //
                                        BN_mul(t1_, r_, this->x_);
                                        BN_add(t2_, h_, t1_);
                                        BN_mul(t1_, t2_, ik_);
                                        BN_mod(s_, t1_, this->q_, this->ctx_);
                                        BN_get_msb(s_, s, this->qbytes_);
                                        result = this->qbytes_;

                                        TALAS_LOG_DEBUG("BN_clear_free(ik_)...");
                                        BN_clear_free(ik_);
                                    }
                                    TALAS_LOG_DEBUG("BN_clear_free(t2_)...");
                                    BN_clear_free(t2_);
                                }
                                TALAS_LOG_DEBUG("BN_clear_free(t1_)...");
                                BN_clear_free(t1_);
                            }
                            TALAS_LOG_DEBUG("BN_clear_free(k_)...");
                            BN_clear_free(k_);
                        }
                        TALAS_LOG_DEBUG("BN_clear_free(h_)...");
                        BN_clear_free(h_);
                    }
                    TALAS_LOG_DEBUG("BN_clear_free(s_)...");
                    ;
                }
                TALAS_LOG_DEBUG("BN_clear_free(r_)...");
                BN_clear_free(r_);
            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t get_y_msb(byte_t* y, size_t ybytes) const {
        ssize_t result = 0;

        if ((this->p_) && (this->pbytes_) && (this->q_) && (this->qbytes_) 
            && (this->g_) && (this->gbytes_) && (this->x_) && (this->xbytes_) 
            && (this->ctx_) && (y) && (ybytes) && (ybytes >= this->pbytes_)) {
            BIGNUM *y_ = 0;
            
            TALAS_LOG_DEBUG("y_ = BN_new()...");
            if ((y_ = BN_new())) {
                TALAS_LOG_DEBUG("y = g^x mod p...");
                
                TALAS_LOG_DEBUG("BN_mod_exp(y_, this->g_, this->x_, this->p_, this->ctx_)...");
                BN_mod_exp(y_, this->g_, this->x_, this->p_, this->ctx_);

                TALAS_LOG_DEBUG("BN_get_msb(y_, y, this->pbytes_)...");
                BN_get_msb(y_, y, this->pbytes_);
                result = this->pbytes_;
                
                TALAS_LOG_DEBUG("BN_clear_free(y_)...");
                BN_clear_free(y_);
            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_x_msb(const byte_t* x, size_t xbytes) {
        if ((this->x_) && (this->xbytes_) 
            && (x) && (xbytes) && (xbytes <= this->xbytes_)) {

            TALAS_LOG_DEBUG("BN_set_msb(this->x_, x, xbytes)...");
            BN_set_msb(this->x_, x, xbytes);
            return this->xbytes_;
        }
        return 0;
    }
    virtual ssize_t get_x_msb(byte_t* x, size_t xbytes) const {
        if ((this->x_) && (this->xbytes_) 
            && (x) && (xbytes) && (xbytes >= this->xbytes_)) {

            TALAS_LOG_DEBUG("BN_get_msb(this->x_, x, this->xbytes_)...");
            BN_get_msb(this->x_, x, this->xbytes_);
            return this->xbytes_;
        }
        return 0;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void init() {
        TALAS_LOG_DEBUG("x_ = 0; ctx_ = 0...");
        x_ = 0; ctx_ = 0;
        
        TALAS_LOG_DEBUG("x_ = BN_new()...");
        if ((x_ = BN_new())) {
            
            TALAS_LOG_DEBUG("ctx_ = BN_CTX_new()...");
            if ((ctx_ = BN_CTX_new())) {
                
                return;
                TALAS_LOG_DEBUG("BN_CTX_free(ctx_)...");
                BN_CTX_free(ctx_);
                ctx_ = 0;
            }
            TALAS_LOG_DEBUG("BN_free(x_)...");
            BN_free(x_);
            x_ = 0;
        }
        const creator_exception e = failed_to_create;
        TALAS_LOG_ERROR("...keyt(const keyt& copy) not allowed throw(const creator_exception e = failed_to_create)...")
        throw(e);
    }
    virtual void fini() {
        if ((x_)) {
            TALAS_LOG_DEBUG("BN_clear_free(x_)...");
            BN_clear_free(x_);
            x_ = 0;
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
        if ((x_)) {
            TALAS_LOG_DEBUG("BN_clear(x_)...");
            BN_clear(x_);
        }
        Extends::clear();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual BIGNUM *x() const {
        return (BIGNUM *)x_;
    }
    virtual BN_CTX *ctx() const {
        return (BN_CTX *)ctx_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    BIGNUM *x_;
    BN_CTX *ctx_;
};
typedef private_keyt<> private_key;

} // namespace bn 
} // namespace dsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DSA_BN_PRIVATE_KEY_HPP 
