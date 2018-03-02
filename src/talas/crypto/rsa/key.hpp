///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2015 $organization$
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
///   Date: 5/8/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RSA_KEY_HPP
#define _TALAS_CRYPTO_RSA_KEY_HPP

#include "talas/crypto/base.hpp"
#include "talas/io/logger.hpp"

namespace talas {
namespace crypto {
namespace rsa {

typedef xos::base::creatort<crypto::implement_base> key_implement_base;
///////////////////////////////////////////////////////////////////////
///  Class: key_implementt
///////////////////////////////////////////////////////////////////////
template <class TImplements = key_implement_base>

class _EXPORT_CLASS key_implementt: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create_msb
    (const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if ((modulus) && (modbytes) && (exponent) && (expbytes)) {
            if ((this->create(modbytes, expbytes))) {
                if ((this->set_msb(modulus, modbytes, exponent, expbytes))) {
                    return true;
                }
                this->destroy();
            }
        }
        return false;
    }
    virtual bool create(size_t modbytes, size_t expbytes) {
        return false;
    }
    virtual bool create(size_t pbytes) {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_msb
    (const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        return false;
    }
    virtual bool get_msb
    (size_t& modlen, size_t& explen,
     byte_t* modulus, size_t modbytes,
     byte_t* exponent, size_t expbytes) const {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_modulus_msb
    (const byte_t* modulus, size_t modbytes) {
        return 0;
    }
    virtual ssize_t get_modulus_msb
    (byte_t* modulus, size_t modbytes) const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_exponent_msb
    (const byte_t* exponent, size_t expbytes) {
        return 0;
    }
    virtual ssize_t get_exponent_msb
    (byte_t* exponent, size_t expbytes) const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t operator()
    (void* out, size_t outsize, const void* in, size_t inlen) {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_modbytes(size_t to) {
        return 0;
    }
    virtual size_t modbytes() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_expbytes(size_t to) {
        return 0;
    }
    virtual size_t expbytes() const {
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

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool CreateMSB
    (const BYTE* modulus, size_t modbytes,
     const BYTE* exponent, size_t expbytes) {
        return create_msb(modulus, modbytes, exponent, expbytes);
    }
    virtual bool Create(size_t modbytes, size_t expbytes) {
        return create(modbytes, expbytes);
    }
    virtual bool Create(size_t pbytes) {
        return create(pbytes);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetMSB
    (const BYTE* modulus, size_t modbytes,
     const BYTE* exponent, size_t expbytes) {
        return set_msb(modulus, modbytes, exponent, expbytes);
    }
    virtual bool GetMSB
    (size_t& modlen, size_t& explen,
     BYTE* modulus, size_t modbytes,
     BYTE* exponent, size_t expbytes) const {
        return get_msb(modlen, explen, modulus, modbytes, exponent, expbytes);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t SetModBytes(size_t to) {
        return set_modbytes(to);
    }
    virtual size_t ModBytes() const {
        return modbytes();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t SetExpBytes(size_t to) {
        return set_expbytes(to);
    }
    virtual size_t ExpBytes() const {
        return expbytes();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t SetPBytes(size_t to) {
        return set_pbytes(to);
    }
    virtual size_t PBytes() const {
        return pbytes();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef key_implementt<> key_implements;
typedef xos::base::creator_extendt<key_implements, crypto::base> key_extends;
///////////////////////////////////////////////////////////////////////
///  Class: keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = key_implements, class TExtends = key_extends>

class _EXPORT_CLASS keyt: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    keyt
    (const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes)
    : m_modbytes(0), m_expbytes(0), m_pbytes(0) {
        if (!(this->create_msb(modulus, modbytes, exponent, expbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create_msb(modulus, modbytes, exponent, expbytes) throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    keyt(size_t modbytes, size_t expbytes)
    : m_modbytes(0), m_expbytes(0), m_pbytes(0) {
        if (!(this->create(modbytes, expbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create(modbytes, expbytes) throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    keyt(size_t pbytes)
    : m_modbytes(0), m_expbytes(0), m_pbytes(0) {
        if (!(this->create(pbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create(pbytes) throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    keyt(const keyt& copy): m_modbytes(0), m_expbytes(0), m_pbytes(0) {
        xos::base::creator_exception e = xos::base::failed_to_create;
        TALAS_LOG_ERROR("...throwing creator_exception failed_to_create...");
        throw (e);
    }
    keyt(): m_modbytes(0), m_expbytes(0), m_pbytes(0) {
    }
    virtual ~keyt() {
        if (!(this->destroyed())) {
            xos::base::creator_exception e = xos::base::failed_to_destroy;
            TALAS_LOG_ERROR("...failed on destroyed() throwing creator_exception failed_to_destroy...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create(size_t modbytes, size_t expbytes) {
        if ((this->destroyed())) {
            if ((modbytes) && (!(modbytes & 1)) && (expbytes)) {
                this->m_pbytes = (modbytes >> 1);
                this->m_modbytes = modbytes;
                this->m_expbytes = expbytes;
                this->set_is_created();
                return true;
            }
        }
        return false;
    }
    virtual bool create(size_t pbytes) {
        if ((this->destroyed())) {
            if ((pbytes)) {
                this->m_pbytes = pbytes;
                this->m_modbytes = (pbytes << 1);
                this->m_expbytes = this->m_modbytes;
                this->set_is_created();
                return true;
            }
        }
        return false;
    }
    virtual bool destroy() {
        if ((this->is_created())) {
            this->set_is_created(false);
            this->m_modbytes = (this->m_expbytes = (this->m_pbytes = 0));
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_modbytes(size_t to) {
        m_modbytes = to;
        return m_modbytes;
    }
    virtual size_t modbytes() const {
        return m_modbytes;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_expbytes(size_t to) {
        m_expbytes = to;
        return m_expbytes;
    }
    virtual size_t expbytes() const {
        return m_expbytes;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t set_pbytes(size_t to) {
        m_pbytes = to;
        return m_pbytes;
    }
    virtual size_t pbytes() const {
        return m_pbytes;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t m_modbytes, m_expbytes, m_pbytes;
};
typedef keyt<> key;

} // namespace rsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RSA_KEY_HPP 
