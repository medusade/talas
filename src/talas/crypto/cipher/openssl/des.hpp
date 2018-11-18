///////////////////////////////////////////////////////////////////////
/// Copyright (C) 1995-1997 Eric Young (eay@cryptsoft.com)
/// All rights reserved.
///
/// This package is an SSL implementation written
/// by Eric Young (eay@cryptsoft.com).
/// The implementation was written so as to conform with Netscapes SSL.
///
/// This library is free for commercial and non-commercial use as long as
/// the following conditions are aheared to.  The following conditions
/// apply to all code found in this distribution, be it the RC4, RSA,
/// lhash, DES, etc., code; not just the SSL code.  The SSL documentation
/// included with this distribution is covered by the same copyright terms
/// except that the holder is Tim Hudson (tjh@cryptsoft.com).
///
/// Copyright remains Eric Young's, and as such any Copyright notices in
/// the code are not to be removed.
/// If this package is used in a product, Eric Young should be given attribution
/// as the author of the parts of the library used.
/// This can be in the form of a textual message at program startup or
/// in documentation (online or textual) provided with the package.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions
/// are met:
/// 1. Redistributions of source code must retain the copyright
///    notice, this list of conditions and the following disclaimer.
/// 2. Redistributions in binary form must reproduce the above copyright
///    notice, this list of conditions and the following disclaimer in the
///    documentation and/or other materials provided with the distribution.
/// 3. All advertising materials mentioning features or use of this software
///    must display the following acknowledgement:
///    "This product includes cryptographic software written by
///     Eric Young (eay@cryptsoft.com)"
///    The word 'cryptographic' can be left out if the rouines from the library
///    being used are not cryptographic related :-).
/// 4. If you include any Windows specific code (or a derivative thereof) from
///    the apps directory (application code) you must include an acknowledgement:
///    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
///
/// THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
/// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
/// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
/// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
/// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
/// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
/// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
/// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
/// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
/// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
/// SUCH DAMAGE.
///
/// The licence and distribution terms for any publically available version or
/// derivative of this code cannot be changed.  i.e. this code cannot simply be
/// copied and put under another distribution licence
/// [including the GNU Public Licence.]
///
///   File: des.hpp
///
/// Author: $author$
///   Date: 5/16/2015
///
/// Eric Young's implementation of DES and 3DES modified to be C++ class
/// implementations.
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_CIPHER_OPENSSL_DES_HPP
#define _TALAS_CRYPTO_CIPHER_OPENSSL_DES_HPP

#include "talas/crypto/cipher/des3.hpp"
#include "talas/io/logger.hpp"

namespace talas {
namespace crypto {
namespace cipher {
namespace openssl {

typedef cipher::des des_implements;
typedef cipher::base des_extends;
///////////////////////////////////////////////////////////////////////
///  Class: des
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS des: virtual public des_implements, public des_extends {
public:
    typedef des_implements Implements;
    typedef des_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    des() {
        clear();
    }
    virtual ~des() {
        clear();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Implements::initialize;
    virtual ssize_t initialize
    (const void* key, size_t keylen,
     const void* iv, size_t ivlen,
     const void* padd = 0, size_t paddlen = 0);
    virtual void clear();

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t encrypt
    (void* out, size_t outsize, const void* in, size_t inlen);
    virtual ssize_t decrypt
    (void* out, size_t outsize, const void* in, size_t inlen);

protected:
    typedef uint8_t tBlock[BLOCKSIZE];
    typedef uint8_t tKey[BLOCKSIZE*3];
    typedef uint32_t tSchedule[32];

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    void InitSchedule(tSchedule schedule, const tBlock key);
    void Encode(uint32_t data[2], tSchedule schedule);
    void Decode(uint32_t data[2], tSchedule schedule);
    virtual void EncryptBlock(tBlock out, const tBlock in);
    virtual void DecryptBlock(tBlock out, const tBlock in);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    static const uint32_t m_setkey[8][64];
    static const uint32_t m_encrypt[8][64];

    tKey m_key;
    tBlock m_iv;
    tBlock m_padd;
    tSchedule m_schedule[3];
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef cipher::des3 des3_implements;
typedef des des3_extends;
///////////////////////////////////////////////////////////////////////
///  Class: des3
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS des3: virtual public des3_implements, public des3_extends {
public:
    typedef des3_implements Implements;
    typedef des3_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    des3
    (const void* key, size_t keylen,
     const void* iv, size_t ivlen,
     const void* padd = 0, size_t paddlen = 0) {
        if (0 > (initialize(key, keylen, iv, ivlen, padd, paddlen))) {
            TALAS_LOG_ERROR("...failed on initialize() throw (error_failed)...");
            throw (error_failed);
        }
    }
    des3
    (const void* key,
     const void* iv,
     const void* padd = 0) {
        if (0 > (initialize(key, iv, padd))) {
            TALAS_LOG_ERROR("...failed on initialize() throw (error_failed)...");
            throw (error_failed);
        }
    }
    des3() {
    }
    virtual ~des3() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Implements::initialize;
    virtual ssize_t initialize
    (const void* key, size_t keylen,
     const void* iv, size_t ivlen,
     const void* padd = 0, size_t paddlen = 0);

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void EncryptBlock(tBlock out, const tBlock in);
    virtual void DecryptBlock(tBlock out, const tBlock in);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace openssl
} // namespace cipher 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_CIPHER_OPENSSL_DES_HPP 
