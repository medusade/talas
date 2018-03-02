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
///   File: private_key.hpp
///
/// Author: $author$
///   Date: 5/10/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RSA_PRIVATE_KEY_HPP
#define _TALAS_CRYPTO_RSA_PRIVATE_KEY_HPP

#include "talas/crypto/rsa/key.hpp"

namespace talas {
namespace crypto {
namespace rsa {

typedef key_implements private_key_implement_base;
///////////////////////////////////////////////////////////////////////
///  Class: private_key_implementt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = private_key_implement_base>

class _EXPORT_CLASS private_key_implementt: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create_msb
    (const byte_t *p, const byte_t *q,
     const byte_t *dmp1, const byte_t *dmq1,
     const byte_t *iqmp, size_t pbytes) {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool set_msb
    (const byte_t *p, const byte_t *q,
     const byte_t *dmp1, const byte_t *dmq1,
     const byte_t *iqmp, size_t pbytes) {
        return false;
    }
    virtual bool get_msb
    (size_t& plen, byte_t *p, byte_t *q,
     byte_t *dmp1, byte_t *dmq1,
     byte_t *iqmp, size_t pbytes) {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t get_p_msb
    (byte_t* p, size_t pbytes) const {
        return 0;
    }
    virtual ssize_t get_q_msb
    (byte_t* p, size_t pbytes) const {
        return 0;
    }
    virtual ssize_t get_dmp1_msb
    (byte_t* p, size_t pbytes) const {
        return 0;
    }
    virtual ssize_t get_dmq1_msb
    (byte_t* p, size_t pbytes) const {
        return 0;
    }
    virtual ssize_t get_iqmp_msb
    (byte_t* p, size_t pbytes) const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool CreateMSB
    (const BYTE *p, const BYTE *q,
     const BYTE *dmp1, const BYTE *dmq1,
     const BYTE *iqmp, size_t pbytes) {
        return create_msb(p,q, dmp1,dmq1, iqmp, pbytes);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool SetMSB
    (const BYTE *p, const BYTE *q,
     const BYTE *dmp1, const BYTE *dmq1,
     const BYTE *iqmp, size_t pbytes) {
        return set_msb(p,q, dmp1,dmq1, iqmp, pbytes);
    }
    virtual bool GetMSB
    (size_t& plen, BYTE *p, BYTE *q,
     BYTE *dmp1, BYTE *dmq1,
     BYTE *iqmp, size_t pbytes) {
        return get_msb(plen, p,q, dmp1,dmq1, iqmp, pbytes);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef private_key_implementt<> private_key_implements;

typedef key private_key_extends;
///////////////////////////////////////////////////////////////////////
///  Class: private_keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = private_key_implements, 
 class TExtends = private_key_extends>

class _EXPORT_CLASS private_keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    private_keyt
    (const byte_t *p, const byte_t *q,
     const byte_t *dmp1, const byte_t *dmq1,
     const byte_t *iqmp, size_t pbytes) {
        if (!(this->create_msb(p, q, dmp1, dmq1, iqmp, pbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create_msb(p, q, dmp1, dmq1, iqmp, pbytes) throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    private_keyt(size_t pbytes) {
        if (!(this->create(pbytes))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create(pbytes) throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    private_keyt(const private_keyt& copy) {
        xos::base::creator_exception e = xos::base::failed_to_create;
        TALAS_LOG_ERROR("...throwing creator_exception failed_to_create...");
        throw (e);
    }
    private_keyt() {
    }
    virtual ~private_keyt() {
        if (!(this->destroyed())) {
            xos::base::creator_exception e = xos::base::failed_to_destroy;
            TALAS_LOG_ERROR("...failed on destroyed() throwing creator_exception failed_to_destroy...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef private_keyt<> private_key;

} // namespace rsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RSA_PRIVATE_KEY_HPP 
