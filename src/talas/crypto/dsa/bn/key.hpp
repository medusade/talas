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
            return this->pbytes_;
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
            return this->qbytes_;
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
            return this->gbytes_;
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
