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
#ifndef _TALAS_CRYPTO_DSA_KEY_HPP
#define _TALAS_CRYPTO_DSA_KEY_HPP

#include "talas/crypto/base.hpp"
#include "talas/io/logger.hpp"

namespace talas {
namespace crypto {
namespace dsa {

class _EXPORT_CLASS key_implemented;

namespace bn {
class _EXPORT_CLASS key_implemented;
} // namespace bn
namespace mp {
class _EXPORT_CLASS key_implemented;
} // namespace mp
namespace mbu {
class _EXPORT_CLASS key_implemented;
} // namespace mbu

///////////////////////////////////////////////////////////////////////
///  Class: key_implementst
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = ::xos::base::creatort<crypto::implement_base> >

class _EXPORT_CLASS key_implementst: virtual public TImplements {
public:
    typedef TImplements Implements;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create_msb
    (const byte_t* p, size_t pbytes,
     const byte_t* q, size_t qbytes,
     const byte_t* g, size_t gbytes) {
        if ((p) && (pbytes) && (q) && (qbytes) && (g) && (gbytes)) {
            if ((this->create(pbytes, qbytes, gbytes))) {
                if ((this->set_msb(p, pbytes, q, qbytes, g, gbytes))) {
                    return true;
                }
                this->destroy();
            }
        }
        return false;
    }
    virtual bool create(size_t pbytes, size_t qbytes, size_t gbytes) {
        if ((this->destroyed())) {
            if ((this->set_pbytes(pbytes))) {
                if ((this->set_qbytes(qbytes))) {
                    if ((this->set_gbytes(gbytes))) {
                        this->set_is_created();
                        return true;
                    }
                }
                clear();
            }
        }
        return false;
    }
    virtual bool destroy() {
        clear();
        this->set_is_created(false);
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void clear() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_msb
    (const byte_t* p, size_t pbytes,
     const byte_t* q, size_t qbytes,
     const byte_t* g, size_t gbytes) {
        if ((p) && (pbytes) && (pbytes <= this->pbytes())
            && (q) && (qbytes) && (qbytes <= this->qbytes())
            && (g) && (gbytes) && (gbytes <= this->gbytes())) {

            if ((set_p_msb(p, pbytes))) {
                if ((set_q_msb(q, qbytes))) {
                    if ((set_g_msb(g, gbytes))) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    virtual bool get_msb
    (size_t& plen, size_t& qlen, size_t& glen,
     byte_t* p, size_t pbytes,
     byte_t* q, size_t qbytes,
     byte_t* g, size_t gbytes) const {
        if ((p) && (pbytes) && (pbytes >= this->pbytes())
            && (q) && (qbytes) && (qbytes >= this->qbytes())
            && (g) && (gbytes) && (gbytes >= this->gbytes())) {

            if ((plen = get_p_msb(p, pbytes))) {
                if ((qlen = get_q_msb(q, qbytes))) {
                    if ((glen = get_g_msb(g, gbytes))) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_p_msb(const byte_t* p, size_t pbytes) {
        return 0;
    }
    virtual ssize_t get_p_msb(byte_t* p, size_t pbytes) const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_q_msb(const byte_t* q, size_t qbytes) {
        return 0;
    }
    virtual ssize_t get_q_msb(byte_t* q, size_t qbytes) const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_g_msb(const byte_t* g, size_t gbytes) {
        return 0;
    }
    virtual ssize_t get_g_msb(byte_t* g, size_t gbytes) const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_pbytes(size_t to) {
        return 0;
    }
    virtual size_t pbytes() const {
        return 0;
    }
    virtual size_t pbytes_inc() const {
        return 0;
    }
    virtual size_t pbytes_min() const {
        return 0;
    }
    virtual size_t pbytes_max() const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_qbytes(size_t to) {
        return 0;
    }
    virtual size_t qbytes() const {
        return 0;
    }
    virtual size_t qbytes_inc() const {
        return 0;
    }
    virtual size_t qbytes_min() const {
        return 0;
    }
    virtual size_t qbytes_max() const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_gbytes(size_t to) {
        return 0;
    }
    virtual size_t gbytes() const {
        return 0;
    }
    virtual size_t gbytes_inc() const {
        return 0;
    }
    virtual size_t gbytes_min() const {
        return 0;
    }
    virtual size_t gbytes_max() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void init() {
    }
    virtual void fini() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef key_implementst<> key_implements;
typedef key_implements key;

///////////////////////////////////////////////////////////////////////
///  Class: keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = key_implements, 
 class TExtends = ::xos::base::creator_extendt<TImplements, crypto::base> >

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
    virtual void clear() {
        TALAS_LOG_DEBUG("pbytes_ = qbytes_ = gbytes_ = 0...");
        pbytes_ = qbytes_ = gbytes_ = 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_pbytes(size_t to) {
        TALAS_LOG_DEBUG("pbytes_ = " << to << "...");
        pbytes_ = to;
        return pbytes_;
    }
    virtual size_t pbytes() const {
        return pbytes_;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_qbytes(size_t to) {
        TALAS_LOG_DEBUG("qbytes_ = " << to << "...");
        qbytes_ = to;
        return qbytes_;
    }
    virtual size_t qbytes() const {
        return qbytes_;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_gbytes(size_t to) {
        TALAS_LOG_DEBUG("gbytes_ = " << to << "...");
        gbytes_ = to;
        return gbytes_;
    }
    virtual size_t gbytes() const {
        return gbytes_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void init() {
    }
    virtual void fini() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t pbytes_, qbytes_, gbytes_;
};
typedef keyt<> key_extend;

namespace null {

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
            return pbytes;
        }
        return 0;
    }
    virtual ssize_t get_p_msb(byte_t* p, size_t pbytes) const {
        if ((this->pbytes_) && (p) && (pbytes) && (pbytes >= this->pbytes_)) {

            TALAS_LOG_DEBUG("::memset(p, 0, this->pbytes_)...");
            ::memset(p, 0, this->pbytes_);
            return this->pbytes_;
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_q_msb(const byte_t* q, size_t qbytes) {
        if ((this->qbytes_) && (q) && (qbytes) && (qbytes <= this->qbytes_)) {
            return qbytes;
        }
        return 0;
    }
    virtual ssize_t get_q_msb(byte_t* q, size_t qbytes) const {
        if ((this->qbytes_) && (q) && (qbytes) && (qbytes >= this->qbytes_)) {

            TALAS_LOG_DEBUG("::memset(q, 0, this->qbytes_)...");
            ::memset(q, 0, this->qbytes_);
            return this->qbytes_;
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_g_msb(const byte_t* g, size_t gbytes) {
        if ((this->gbytes_) && (g) && (gbytes) && (gbytes <= this->gbytes_)) {
            return gbytes;
        }
        return 0;
    }
    virtual ssize_t get_g_msb(byte_t* g, size_t gbytes) const {
        if ((this->gbytes_) && (g) && (gbytes) && (gbytes >= this->gbytes_)) {

            TALAS_LOG_DEBUG("::memset(g, 0, this->gbytes_)...");
            ::memset(g, 0, this->gbytes_);
            return this->gbytes_;
        }
        return 0;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef keyt<> key;

} // namespace null

} // namespace dsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DSA_KEY_HPP 

