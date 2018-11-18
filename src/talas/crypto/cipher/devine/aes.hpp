///////////////////////////////////////////////////////////////////////
/// FIPS-197 compliant AES implementation
///
/// Copyright (C) 2006-2007  Christophe Devine
///
/// This program is free software; you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation; either version 2 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program; if not, write to the Free Software Foundation, Inc.,
/// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
///
/// The AES block cipher was designed by Vincent Rijmen and Joan Daemen.
///
/// http://csrc.nist.gov/encryption/aes/rijndael/Rijndael.pdf
/// http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf
///
///   File: aes.hpp
///
/// Author: $author$
///   Date: 4/30/2015
///
/// Christophe Devine's implementation of AES modified to be a C++ class
/// implementation.
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_CIPHER_DEVINE_AES_HPP
#define _TALAS_CRYPTO_CIPHER_DEVINE_AES_HPP

#include "talas/crypto/cipher/aes.hpp"
#include "talas/io/logger.hpp"

namespace talas {
namespace crypto {
namespace cipher {
namespace devine {

typedef cipher::aes_implements aes_implements;
typedef cipher::aes aes_base_extends;
///////////////////////////////////////////////////////////////////////
///  Class: aes_base
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS aes_base: virtual public aes_implements, public aes_base_extends {
friend class aes;
public:
    typedef aes_implements Implements;
    typedef aes_base_extends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
private:
    aes_base(const aes_base& copy) {}
protected:
    aes_base() {
        ClearKeySchedule();
    }
    virtual ~aes_base() {
        ClearKeySchedule();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void clear() {
        ClearKeySchedule();
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void ClearKeySchedule();
    virtual ssize_t InitEncryptKeySchedule(const uint8_t* key, unsigned keysize);
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    unsigned nr;
    uint32_t* rk;
    uint32_t buf[68];
};

typedef aes_base aes_extends;
///////////////////////////////////////////////////////////////////////
///  Class: aes
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS aes: virtual public aes_implements, public aes_extends {
public:
    typedef aes_implements Implements;
    typedef aes_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
private:
    aes(const aes& copy) {}
public:
    aes
    (const void* key, size_t keylen,
     const void* iv, size_t ivlen,
     const void* padd = 0, size_t paddlen = 0) {
        ClearKey();
        if (0 > (initialize(key, keylen, iv, ivlen, padd, paddlen))) {
            TALAS_LOG_ERROR("...failed on initialize() throw (error_failed)...");
            throw (error_failed);
        }
    }
    aes
    (const void* key,
     const void* iv,
     const void* padd = 0) {
        ClearKey();
        if (0 > (initialize(key, iv, padd))) {
            TALAS_LOG_ERROR("...failed on initialize() throw (error_failed)...");
            throw (error_failed);
        }
    }
    aes() {
        ClearKey();
    }
    virtual ~aes() {
        ClearKey();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::initialize;
    virtual ssize_t initialize
    (const void* key, size_t keylen,
     const void* iv, size_t ivlen,
     const void* padd = 0, size_t paddlen = 0);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t encrypt
    (void* out, size_t outsize, const void* in, size_t inlen);
    virtual ssize_t decrypt
    (void* out, size_t outsize, const void* in, size_t inlen);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void clear() {
        ClearKey();
        ClearKeySchedule();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef uint8_t tBlock[BLOCKSIZE];
    typedef uint8_t tKey[KEYMAX];

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void ClearKey();
    virtual ssize_t InitDecryptKeySchedule(const uint8_t* key, unsigned keysize);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void EncryptBlock(tBlock output, const tBlock input);
    virtual void DecryptBlock(tBlock output, const tBlock input);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void EncodeBlock(tBlock output, const tBlock input);
    virtual void DecodeBlock(tBlock output, const tBlock input);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    unsigned m_keysize;
    tKey m_key;
    tBlock m_iv;
    tBlock m_padd;
};

} // namespace devine 
} // namespace cipher 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_CIPHER_DEVINE_AES_HPP 
