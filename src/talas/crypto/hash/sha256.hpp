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
///   File: sha256.hpp
///
/// Author: $author$
///   Date: 11/11/2014
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_HASH_SHA256_HPP
#define _TALAS_CRYPTO_HASH_SHA256_HPP

#include "talas/crypto/hash/base.hpp"

#define TALAS_CRYPTO_HASH_SHA256_NAME "sha256"

namespace talas {
namespace crypto {
namespace hash {

typedef base_implements sha256_implements;
typedef base sha256_extends;
///////////////////////////////////////////////////////////////////////
///  Class: sha256t
///////////////////////////////////////////////////////////////////////
template
<class TImplements = sha256_implements, class TExtends = sha256_extends>

class _EXPORT_CLASS sha256t: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    enum {
        WORDSIZE    = 4,
        LENGTHSIZE  = 8
    };
    enum {
        HASHSIZE  = 32,
        KONSTSIZE = 64,
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
    sha256t(void* out, size_t outsize, const void* in, size_t inlen)
    : Extends(HASHSIZE, BLOCKSIZE, KEYMIN, KEYMAX, m_key, m_mac, m_hash) {
        this->operator~();
        if (0 > (this->operator()(out, outsize, in, inlen))) {
            error e = error_failed;
            throw (e);
        }
    }
    sha256t(const sha256t& copy)
    : Extends(HASHSIZE, BLOCKSIZE, KEYMIN, KEYMAX, m_key, m_mac, m_hash) {
        this->operator=(copy);
    }
    sha256t()
    : Extends(HASHSIZE, BLOCKSIZE, KEYMIN, KEYMAX, m_key, m_mac, m_hash) {
        this->operator~();
    }
    virtual ~sha256t() {
        this->operator~();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual sha256t& operator = (const sha256t& copy) {
        m_A = copy.m_A; m_B = copy.m_B;
        m_C = copy.m_C; m_D = copy.m_D;
        m_E = copy.m_E; m_F = copy.m_F;
        m_G = copy.m_G; m_H = copy.m_H;
        m_l = copy.m_l; m_h = copy.m_h;
        memcpy(m_in, copy.m_in, sizeof(m_in));
        memcpy(m_key, copy.m_key, sizeof(m_key));
        memcpy(m_mac, copy.m_mac, sizeof(m_mac));
        memcpy(m_hash, copy.m_hash, sizeof(m_hash));
        return *this;
    }
    virtual sha256t& operator ~ () {
        m_A = 0; m_B = 0;
        m_C = 0; m_D = 0;
        m_E = 0; m_F = 0;
        m_G = 0; m_H = 0;
        m_l = 0; m_h = 0;
        memset(m_in, 0, sizeof(m_in));
        memset(m_key, 0, sizeof(m_key));
        memset(m_mac, 0, sizeof(m_mac));
        memset(m_hash, 0, sizeof(m_hash));
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* name() const {
        return TALAS_CRYPTO_HASH_SHA256_NAME;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    uint32_t m_A, m_B, m_C, m_D, m_E, m_F, m_G, m_H, m_l, m_h;
    uint8_t m_hash[HASHSIZE];
    uint8_t m_mac[HASHSIZE];
    uint8_t m_in[BLOCKSIZE];
    uint8_t m_key[BLOCKSIZE];
};
typedef sha256t<> sha256;

} // namespace hash 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_HASH_SHA256_HPP 
