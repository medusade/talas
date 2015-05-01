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
///   File: base.hpp
///
/// Author: $author$
///   Date: 4/29/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_CIPHER_BASE_HPP
#define _TALAS_CRYPTO_CIPHER_BASE_HPP

#include "talas/crypto/base.hpp"

namespace talas {
namespace crypto {
namespace cipher {

typedef crypto::implement_base base_implements;
///////////////////////////////////////////////////////////////////////
///  Class: implement_baset
///////////////////////////////////////////////////////////////////////
template
<class TImplements = base_implements>

class _EXPORT_CLASS implement_baset: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t initialize
    (const void* key, size_t keylen,
     const void* iv, size_t ivlen,
     const void* padd, size_t paddlen) {
        return -error_not_implemented;
    }
    virtual ssize_t initialize
    (const void* key, const void* iv, const void* padd) {
        if ((key)) {
            size_t keylen = 0;
            if ((keylen = bytes_t::count((const byte_t*)key))) {
                if ((iv)) {
                    size_t ivlen = 0;
                    if ((ivlen = bytes_t::count((const byte_t*)iv))) {
                        if ((padd)) {
                            size_t paddlen = 0;
                            if ((paddlen = bytes_t::count((const byte_t*)padd))) {
                                return this->initialize
                                (key, keylen, iv, ivlen, padd, paddlen);
                            }
                        } else {
                            return this->initialize
                            (key, keylen, iv, ivlen, 0, 0);
                        }
                    }
                }
            }
        }
        return -error_failed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t encrypt
    (void* out, size_t outsize, const void* in, size_t inlen) {
        return -error_not_implemented;
    }
    virtual ssize_t encrypt(void* out, size_t outsize, const void* in) {
        if ((in)) {
            size_t inlen = 0;
            if ((inlen = bytes_t::count((const byte_t*)in))) {
                return this->encrypt(out, outsize, in, inlen);
            }
        }
        return -error_failed;
    }
    virtual ssize_t decrypt
    (void* out, size_t outsize, const void* in, size_t inlen) {
        return -error_not_implemented;
    }
    virtual ssize_t decrypt(void* out, size_t outsize, const void* in) {
        if ((in)) {
            size_t inlen = 0;
            if ((inlen = bytes_t::count((const byte_t*)in))) {
                return this->decrypt(out, outsize, in, inlen);
            }
        }
        return -error_failed;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t key_size_min() const {
        return 0;
    }
    virtual ssize_t key_size_max() const {
        return 0;
    }
    virtual ssize_t key_size_inc() const {
        return 0;
    }
    virtual ssize_t key_size() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t iv_size_min() const {
        return 0;
    }
    virtual ssize_t iv_size_max() const {
        return 0;
    }
    virtual ssize_t iv_size_inc() const {
        return 0;
    }
    virtual ssize_t iv_size() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t block_size() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool is_block() const {
        return (1 > block_size());
    }
    virtual bool is_stream() const {
        return (1 == block_size());
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef implement_baset<> implement_base;

typedef crypto::base base_extends;
///////////////////////////////////////////////////////////////////////
///  Class: baset
///////////////////////////////////////////////////////////////////////
template
<class TImplements = base_implements, class TExtends = base_extends>

class _EXPORT_CLASS baset: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    baset() {
    }
    virtual ~baset() {
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef baset<> base;

} // namespace cipher
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_CIPHER_BASE_HPP 
