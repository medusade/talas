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
///   File: md5.hpp
///
/// Author: $author$
///   Date: 11/14/2014
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_HASH_MD5_HPP
#define _TALAS_CRYPTO_HASH_MD5_HPP

#include "talas/crypto/hash/base.hpp"

#define TALAS_CRYPTO_HASH_MD5_NAME "md5"

namespace talas {
namespace crypto {
namespace hash {

typedef base_implements md5_implements;
typedef base md5_extends;
///////////////////////////////////////////////////////////////////////
///  Class: md5t
///////////////////////////////////////////////////////////////////////
template
<class TImplements = md5_implements, class TExtends = md5_extends>

class _EXPORT_CLASS md5t: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    enum {
        HASHSIZE  = 16,
        BLOCKSIZE = 64,
        KEYMIN    = 1,
        KEYMAX    = BLOCKSIZE,
        KEYSIZE   = BLOCKSIZE
    };
    enum {
        HASH_SIZE = HASHSIZE,
        KEY_MIN = KEYMIN,
        KEY_MAX = KEYMAX,
        KEY_SIZE = KEYSIZE
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    md5t(void* out, size_t outsize, const void* in, size_t inlen)
    : Extends(HASHSIZE, BLOCKSIZE, KEYMIN, KEYMAX, m_key, m_mac, m_hash) {
        this->operator~();
        if (0 > (this->operator()(out, outsize, in, inlen))) {
            error e = error_failed;
            throw (e);
        }
    }
    md5t(const md5t& copy)
    : Extends(HASHSIZE, BLOCKSIZE, KEYMIN, KEYMAX, m_key, m_mac, m_hash) {
        this->operator=(copy);
    }
    md5t()
    : Extends(HASHSIZE, BLOCKSIZE, KEYMIN, KEYMAX, m_key, m_mac, m_hash) {
        this->operator~();
    }
    virtual ~md5t() {
        this->operator~();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual md5t& operator = (const md5t& copy) {
        m_A = copy.m_A; m_B = copy.m_B;
        m_C = copy.m_C; m_D = copy.m_D;
        m_L = copy.m_L; m_H = copy.m_H;
        memcpy(m_in, copy.m_in, sizeof(m_in));
        memcpy(m_key, copy.m_key, sizeof(m_key));
        memcpy(m_mac, copy.m_mac, sizeof(m_mac));
        memcpy(m_hash, copy.m_hash, sizeof(m_hash));
        return *this;
    }
    virtual md5t& operator ~ () {
        m_A = 0; m_B = 0;
        m_C = 0; m_D = 0;
        m_L = 0; m_H = 0;
        memset(m_in, 0, sizeof(m_in));
        memset(m_key, 0, sizeof(m_key));
        memset(m_mac, 0, sizeof(m_mac));
        memset(m_hash, 0, sizeof(m_hash));
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* name() const {
        return TALAS_CRYPTO_HASH_MD5_NAME;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    uint32_t m_A, m_B, m_C, m_D, m_L, m_H;
    uint8_t m_hash[HASHSIZE];
    uint8_t m_in[BLOCKSIZE];
    uint8_t m_key[BLOCKSIZE];
    uint8_t m_mac[HASHSIZE];
};
typedef md5t<> md5;

} // namespace hash
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_HASH_MD5_HPP 
