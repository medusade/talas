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
#ifndef _TALAS_CRYPTO_DSA_PRIVATE_KEY_HPP
#define _TALAS_CRYPTO_DSA_PRIVATE_KEY_HPP

#include "talas/crypto/dsa/key.hpp"

namespace talas {
namespace crypto {
namespace dsa {

class _EXPORT_CLASS private_key_implemented;

namespace bn {
class _EXPORT_CLASS private_key_implemented;
} // namespace bn
namespace mp {
class _EXPORT_CLASS private_key_implemented;
} // namespace mp
namespace mbu {
class _EXPORT_CLASS private_key_implemented;
} // namespace mbu

///////////////////////////////////////////////////////////////////////
///  Class: private_key_implementst
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = key_implements>

class _EXPORT_CLASS private_key_implementst: virtual public TImplements {
public:
    typedef TImplements Implements;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create_msb
    (const byte_t* p, size_t pbytes,
     const byte_t* q, size_t qbytes,
     const byte_t* g, size_t gbytes,
     const byte_t* x, size_t xbytes) {
        if ((p) && (pbytes) && (q) && (qbytes) 
            && (g) && (gbytes) && (x) && (xbytes)) {
            if ((this->create(pbytes, qbytes, gbytes, xbytes))) {
                if ((this->set_msb(p, pbytes, q, qbytes, g, gbytes, x, xbytes))) {
                    return true;
                }
                this->destroy();
            }
        }
        return false;
    }
    virtual bool create
    (size_t pbytes, size_t qbytes, size_t gbytes, size_t xbytes) {
        if ((Implements::create(pbytes, qbytes, gbytes))) {
            if ((this->set_xbytes(xbytes))) {
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
     const byte_t* x, size_t xbytes) {
        if ((p) && (pbytes) && (pbytes <= this->pbytes())
            && (q) && (qbytes) && (qbytes <= this->qbytes())
            && (g) && (gbytes) && (gbytes <= this->gbytes())
            && (x) && (xbytes) && (xbytes <= this->xbytes())) {

            if ((Implements::set_msb(p, pbytes, q, qbytes, g, gbytes))) {
                if ((set_x_msb(x, xbytes))) {
                    return true;
                }
            }
        }
        return false;
    }
    virtual bool get_msb
    (size_t& plen, size_t& qlen, size_t& glen, size_t& xlen,
     byte_t* p, size_t pbytes,
     byte_t* q, size_t qbytes,
     byte_t* g, size_t gbytes,
     byte_t* x, size_t xbytes) const {
        if ((p) && (pbytes) && (pbytes >= this->pbytes())
            && (q) && (qbytes) && (qbytes >= this->qbytes())
            && (g) && (gbytes) && (gbytes >= this->gbytes())
            && (x) && (xbytes) && (xbytes >= this->xbytes())) {

            if ((Implements::get_msb
                 (plen, qlen, glen, p, pbytes, q, qbytes, g, gbytes))) {
                if ((xlen = get_x_msb(x, xbytes))) {
                    return true;
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t sign_msb
    (byte_t* r, size_t rbytes, byte_t* s, size_t sbytes, 
     const byte_t* h, size_t hbytes, const byte_t* k, size_t kbytes) {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t get_y_msb(byte_t* y, size_t ybytes) const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_x_msb(const byte_t* x, size_t xbytes) {
        return 0;
    }
    virtual ssize_t get_x_msb(byte_t* x, size_t xbytes) const {
        return 0;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_xbytes(size_t to) {
        return 0;
    }
    virtual size_t xbytes() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef private_key_implementst<> private_key_implements;
typedef private_key_implements private_key;

///////////////////////////////////////////////////////////////////////
///  Class: private_keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = private_key_implements, class TExtends = key_extend>

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
    virtual void clear() {
        TALAS_LOG_DEBUG("xbytes_ = 0...");
        xbytes_ = 0;
        Extends::clear();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_xbytes(size_t to) {
        TALAS_LOG_DEBUG("xbytes_ = " << to << "...");
        xbytes_ = to;
        return xbytes_;
    }
    virtual size_t xbytes() const {
        return xbytes_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t xbytes_;
};
typedef private_keyt<> private_key_extend;

namespace null {

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
        if ((this->pbytes_) && (this->qbytes_) && (this->gbytes_) 
            && (r) && (rbytes) && (rbytes >= this->qbytes_)
            && (s) && (sbytes) && (sbytes >= this->qbytes_)
            && (h) && (hbytes) && (k) && (kbytes)) {

            TALAS_LOG_DEBUG("r = (g^k mod p) mod q...");
            TALAS_LOG_DEBUG("::memset(r, 0, this->qbytes_)...");
            ::memset(r, 0, this->qbytes_);

            TALAS_LOG_DEBUG("s = k^-1*(h+x*r) mod q...");
            TALAS_LOG_DEBUG("::memset(s, 0, this->qbytes_)...");
            ::memset(s, 0, this->qbytes_);
            return this->qbytes_;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t get_y_msb(byte_t* y, size_t ybytes) const {
        if ((this->pbytes_) && (this->qbytes_) && (this->gbytes_) && (this->xbytes_)
            && (y) && (ybytes) && (ybytes >= this->pbytes_)) {

            TALAS_LOG_DEBUG("y = g^x mod p...");

            TALAS_LOG_DEBUG("::memset(y, 0, this->pbytes_)...");
            ::memset(y, 0, this->pbytes_);
            return this->pbytes_;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_x_msb(const byte_t* x, size_t xbytes) {
        if ((this->xbytes_) && (x) && (xbytes) && (xbytes <= this->xbytes_)) {
            return xbytes;
        }
        return 0;
    }
    virtual ssize_t get_x_msb(byte_t* x, size_t xbytes) const {
        if ((this->xbytes_) && (x) && (xbytes) && (xbytes >= this->xbytes_)) {

            TALAS_LOG_DEBUG("::memset(x, 0, this->xbytes_)...");
            ::memset(x, 0, this->xbytes_);
            return this->xbytes_;
        }
        return 0;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef private_keyt<> private_key;

} // namespace null

} // namespace dsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DSA_PRIVATE_KEY_HPP 
        

