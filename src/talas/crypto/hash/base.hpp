///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2014 $organization$
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
///   Date: 11/11/2014
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_HASH_BASE_HPP
#define _TALAS_CRYPTO_HASH_BASE_HPP

#include "talas/crypto/hash/mac.hpp"
#include "talas/crypto/base.hpp"

namespace talas {
namespace crypto {
namespace hash {

typedef crypto::base_implements base_implement_implements;
///////////////////////////////////////////////////////////////////////
///  Class: base_implementt
///////////////////////////////////////////////////////////////////////
template <class TImplements = base_implement_implements>

class _EXPORT_CLASS base_implementt: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t initialize(const void* key, size_t keylen) {
        return -error_not_implemented;
    }
    virtual ssize_t initialize(const void* key) {
        if ((key)) {
            size_t keylen = 0;
            if ((keylen = bytes_t::count((const byte_t*)key))) {
                return this->initialize(key, keylen);
            }
        }
        return -error_failed;
    }
    virtual ssize_t initialize() {
        return this->initialize(0, 0);
    }
    virtual ssize_t finalize(void* out, size_t outsize) {
        return -error_not_implemented;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t hash(const void* in, size_t inlen) {
        return -error_not_implemented;
    }
    virtual ssize_t hash(const void* in) {
        if ((in)) {
            size_t inlen = 0;
            if ((inlen = bytes_t::count((const byte_t*)in))) {
                return this->hash(in, inlen);
            }
        }
        return -error_failed;
    }
    virtual ssize_t hash() {
        return this->hash(0, 0);
    }
    virtual ssize_t hash_size() const {
        return -error_not_implemented;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t operator()
    (void* out, size_t outsize, const void* in, size_t inlen, const void* key, size_t keylen) {
        ssize_t count;
        if (0 <= (count = initialize(key, keylen))) {
            if (0 <= (count = hash(in, inlen))) {
                count = finalize(out, outsize);
            }
        }
        return count;
    }
    virtual ssize_t operator()
    (void* out, size_t outsize, const void* in, size_t inlen, const void* key) {
        ssize_t count;
        if (0 <= (count = initialize(key))) {
            if (0 <= (count = hash(in, inlen))) {
                count = finalize(out, outsize);
            }
        }
        return count;
    }
    virtual ssize_t operator()
    (void* out, size_t outsize, const void* in, const void* key) {
        ssize_t count;
        if (0 <= (count = initialize(key))) {
            if (0 <= (count = hash(in))) {
                count = finalize(out, outsize);
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t operator()
    (void* out, size_t outsize, const void* in, size_t inlen) {
        ssize_t count;
        if (0 <= (count = initialize())) {
            if (0 <= (count = hash(in, inlen))) {
                count = finalize(out, outsize);
            }
        }
        return count;
    }
    virtual ssize_t operator()
    (void* out, size_t outsize, const void* in) {
        ssize_t count;
        if (0 <= (count = initialize())) {
            if (0 <= (count = hash(in))) {
                count = finalize(out, outsize);
            }
        }
        return count;
    }
    virtual ssize_t operator()
    (void* out, size_t outsize) {
        ssize_t count;
        if (0 <= (count = initialize())) {
            if (0 <= (count = hash())) {
                count = finalize(out, outsize);
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* name() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef base_implementt<> base_implements;
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
    baset
    (size_t hashsize,
     size_t blocksize,
     size_t keymin,
     size_t keymax,
     uint8_t* keybuff,
     uint8_t* macbuff,
     uint8_t* hashbuff)
     : m_hashsize(hashsize),
       m_blocksize(blocksize),
       m_keymin(keymin),
       m_keymax(keymax),
       m_keylen(0),
       m_keysize(0),
       m_keybuff(keybuff),
       m_macbuff(macbuff),
       m_hashbuff(hashbuff) {
    }
    virtual ~baset() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Implements::initialize;
    virtual ssize_t initialize(const void* key, size_t keylen) {
        const uint8_t* keybytes;
        size_t i;

        if ((keybytes = ((const uint8_t*)key)) && (keylen)) {
            if (keylen < m_keymin)
                return -error_invalid_parameter_size;

            if (keylen > m_keymax)
                return -error_invalid_parameter_size;

            m_keylen = keylen;
            m_keysize = m_keymax;
            memcpy(m_keybuff, keybytes, keylen);
            memset(m_keybuff+keylen, 0, m_keymax-keylen);

            //
            // HMAC
            //
            for (i=0; i<m_keymax; i++)
                m_keybuff[i] ^= mac::OPAD;
        }
        else m_keysize = m_keylen = keylen = 0;

        initial();

        if (m_keysize) {
            //
            // HMAC
            //
            for (i=0; i<m_keysize; i++)
                m_keybuff[i] = (m_keybuff[i]^mac::OPAD)^mac::IPAD;

            update(m_keybuff, m_keysize);

            //
            // HMAC
            //
            for (i=0; i<m_keysize; i++)
                m_keybuff[i] = (m_keybuff[i]^mac::IPAD)^mac::OPAD;
        }
        return keylen;
    }
    virtual ssize_t finalize(void* out, size_t outsize) {
        size_t outlen = outsize;

        if (outlen > m_hashsize)
            outlen = m_hashsize;

        final();

        if (m_keysize) {
            //
            // HMAC
            //
            memcpy(m_macbuff, m_hashbuff, m_hashsize);
            initial();
            update(m_keybuff, m_keysize);
            update(m_macbuff, m_hashsize);
            final();
        }

        memcpy(out, m_hashbuff, outlen);
        return outlen;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Implements::hash;
    virtual ssize_t hash(const void* in, size_t inlen) {
        const uint8_t* inbytes;
        if ((inbytes = ((const uint8_t*)in)) && (inlen)) {
            update(inbytes, inlen);
            return inlen;
        }
        return 0;
    }
    virtual ssize_t hash_size() const {
        return m_hashsize;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void initial() = 0;
    virtual void final() = 0;
    virtual void transform() = 0;
    virtual void update(const uint8_t* in, size_t inlen) = 0;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    size_t m_hashsize;
    size_t m_blocksize;
    size_t m_keymin;
    size_t m_keymax;
    size_t m_keysize;
    size_t m_keylen;
    uint8_t* m_keybuff;
    uint8_t* m_macbuff;
    uint8_t* m_hashbuff;
};
typedef baset<> base;

} // namespace hash
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_HASH_BASE_HPP 
