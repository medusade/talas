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
///   File: public_key.hpp
///
/// Author: $author$
///   Date: 2/20/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DSA_PUBLIC_KEY_HPP
#define _TALAS_CRYPTO_DSA_PUBLIC_KEY_HPP

#include "talas/crypto/dsa/key.hpp"

namespace talas {
namespace crypto {
namespace dsa {

class _EXPORT_CLASS public_key_implemented;

namespace bn {
class _EXPORT_CLASS public_key_implemented;
} // namespace bn
namespace mp {
class _EXPORT_CLASS public_key_implemented;
} // namespace mp
namespace mbu {
class _EXPORT_CLASS public_key_implemented;
} // namespace mbu

///////////////////////////////////////////////////////////////////////
///  Class: public_key_implementst
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = key_implements>

class _EXPORT_CLASS public_key_implementst: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create_msb
    (const byte_t* p, size_t pbytes,
     const byte_t* q, size_t qbytes,
     const byte_t* g, size_t gbytes,
     const byte_t* y, size_t ybytes) {
        if ((p) && (pbytes) && (q) && (qbytes) 
            && (g) && (gbytes) && (y) && (ybytes)) {
            if ((this->create(pbytes, qbytes, gbytes, ybytes))) {
                if ((this->set_msb(p, pbytes, q, qbytes, g, gbytes, y, ybytes))) {
                    return true;
                }
                this->destroy();
            }
        }
        return false;
    }
    virtual bool create
    (size_t pbytes, size_t qbytes, size_t gbytes, size_t ybytes) {
        if ((Implements::create(pbytes, qbytes, gbytes))) {
            if ((this->set_ybytes(ybytes))) {
                return true;
            }
            Implements::destroy();
        }
        return false;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_msb
    (const byte_t* p, size_t pbytes,
     const byte_t* q, size_t qbytes,
     const byte_t* g, size_t gbytes,
     const byte_t* y, size_t ybytes) {
        if ((p) && (pbytes) && (pbytes <= this->pbytes())
            && (q) && (qbytes) && (qbytes <= this->qbytes())
            && (g) && (gbytes) && (gbytes <= this->gbytes())
            && (y) && (ybytes) && (ybytes <= this->ybytes())) {

            if ((Implements::set_msb(p, pbytes, q, qbytes, g, gbytes))) {
                if ((set_y_msb(y, ybytes))) {
                    return true;
                }
            }
        }
        return false;
    }
    virtual bool get_msb
    (size_t& plen, size_t& qlen, size_t& glen, size_t& ylen,
     byte_t* p, size_t pbytes,
     byte_t* q, size_t qbytes,
     byte_t* g, size_t gbytes,
     byte_t* y, size_t ybytes) const {
        if ((p) && (pbytes) && (pbytes >= this->pbytes())
            && (q) && (qbytes) && (qbytes >= this->qbytes())
            && (g) && (gbytes) && (gbytes >= this->gbytes())
            && (y) && (ybytes) && (ybytes >= this->ybytes())) {

            if ((Implements::get_msb
                 (plen, qlen, glen, p, pbytes, q, qbytes, g, gbytes))) {
                if ((ylen = get_y_msb(y, ybytes))) {
                    return true;
                }
            }
        }
        return false;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t verify_msb
    (byte_t* v, size_t vbytes, const byte_t* h, size_t hbytes, 
     const byte_t* r, size_t rbytes, const byte_t* s, size_t sbytes) {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_y_msb(const byte_t* y, size_t ybytes) {
        return 0;
    }
    virtual ssize_t get_y_msb(byte_t* y, size_t ybytes) const {
        return 0;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_ybytes(size_t to) {
        return 0;
    }
    virtual size_t ybytes() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef public_key_implementst<> public_key_implements;
typedef public_key_implements public_key;

///////////////////////////////////////////////////////////////////////
///  Class: public_keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = public_key_implements, class TExtends = key_extend>

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
    virtual void clear() {
        TALAS_LOG_DEBUG("ybytes_ = 0...");
        ybytes_ = 0;
        Extends::clear();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_ybytes(size_t to) {
        TALAS_LOG_DEBUG("ybytes_ = " << to << "...");
        ybytes_ = to;
        return ybytes_;
    }
    virtual size_t ybytes() const {
        return ybytes_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t ybytes_;
};
typedef public_keyt<> public_key_extend;

namespace null {

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
        if ((this->pbytes_) && (this->qbytes_) && (this->gbytes_) 
            && (v) && (vbytes) && (vbytes >= this->qbytes_)
            && (h) && (hbytes) && (hbytes <= this->qbytes_)
            && (r) && (rbytes) && (rbytes == this->qbytes_)
            && (s) && (sbytes) && (sbytes == this->qbytes_)) {

            TALAS_LOG_DEBUG("::memset(v, 0, this->qbytes_)...");
            ::memset(v, 0, this->qbytes_);
            return this->qbytes_;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_y_msb(const byte_t* y, size_t ybytes) {
        if ((this->ybytes_) && (y) && (ybytes <= this->ybytes_)) {
            return this->ybytes_;
        }
        return 0;
    }
    virtual ssize_t get_y_msb(byte_t* y, size_t ybytes) const {
        if ((this->ybytes_) && (y) && (ybytes >= this->ybytes_)) {
            
            TALAS_LOG_DEBUG("::memset(v, 0, this->ybytes_)...");
            ::memset(y, 0, this->ybytes_);
            return this->ybytes_;
        }
        return 0;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef public_keyt<> public_key;

} // namespace null

} // namespace dsa 
} // namespace crypto 
} // namespace talas 


#endif // _TALAS_CRYPTO_DSA_PUBLIC_KEY_HPP 

        

