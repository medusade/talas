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
///   File: public_key.hpp
///
/// Author: $author$
///   Date: 2/11/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DH_BN_PUBLIC_KEY_HPP
#define _TALAS_CRYPTO_DH_BN_PUBLIC_KEY_HPP

#include "talas/crypto/dh/public_key.hpp"
#include "talas/crypto/dh/bn/key.hpp"

namespace talas {
namespace crypto {
namespace dh {
namespace bn {

typedef dh::public_key_implements public_key_implements;
///////////////////////////////////////////////////////////////////////
///  Class: public_key_implemented
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS public_key_implemented: virtual public public_key_implements {
public:
    typedef public_key_implements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create_secret_msb
    (BIGNUM *X, const byte_t* exponent, size_t expbytes) {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual BIGNUM* g() const {
        return 0;
    }
    virtual BIGNUM* n() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///  Class: public_keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = public_key_implemented, 
 class TExtends = dh::public_keyt<public_key_implemented, key> >

class public_keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    public_keyt
    (const unsigned& generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if (!(this->create_msb
             (generator, genbytes, modulus, modbytes, exponent, expbytes))) {
            const creator_exception e = failed_to_create;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_create)...")
            throw(e);
        }
    }
    public_keyt
    (const byte_t* generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if (!(this->create_msb
             (generator, genbytes, modulus, modbytes, exponent, expbytes))) {
            const creator_exception e = failed_to_create;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_create)...")
            throw(e);
        }
    }
    public_keyt() {
    }
    virtual ~public_keyt() {
        if (!(this->destroyed())) {
            const creator_exception e = failed_to_destroy;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_destroy)...")
            throw(e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t create_secret_msb
    (byte_t* secret, size_t secbytes, const byte_t* exponent, size_t expbytes) {
        ssize_t size = 0;
        
        if ((secret) && (secbytes) && (exponent) && (expbytes) 
            && (this->g_) && (this->n_) && (this->x_)) {
            BIGNUM *X = 0;

            TALAS_LOG_DEBUG("X = BN_new()...");
            if ((X = BN_new())) {

                if ((create_secret_msb(X, exponent, expbytes))) {

                    TALAS_LOG_DEBUG("BN_get_msb(X, secret, secbytes = " << secbytes << ")...");
                    BN_get_msb(X, secret, secbytes);
                    size = secbytes;
                }
                TALAS_LOG_DEBUG("BN_clear_free(X)...");
                BN_clear_free(X);
            }
        }
        return size;
    }
    virtual bool create_secret_msb
    (BIGNUM *X, const byte_t* exponent, size_t expbytes) {
        bool success = false;
        
        if ((X) && (exponent) && (expbytes)) {
            BIGNUM *x = 0;
    
            TALAS_LOG_DEBUG("x = BN_new()...");
            if ((x = BN_new())) {
    
                TALAS_LOG_DEBUG("BN_set_msb(x, exponent, expbytes)...");
                BN_set_msb(x, exponent, expbytes);
                
                if ((create_secret(X, x))) {
                    success = true;
                }
                TALAS_LOG_DEBUG("BN_clear_free(x)...");
                BN_clear_free(x);
            }
        }
        return success;
    }
    virtual bool create_secret(BIGNUM *X, BIGNUM *x) {
        bool success = false;

        if ((X) && (x) && (this->x_) && (this->n_)) {
            BN_CTX *ctx = 0;

            TALAS_LOG_DEBUG("ctx = BN_CTX_new()...");
            if ((ctx = BN_CTX_new())) {

                TALAS_LOG_DEBUG("BN_mod_exp(X, x, this->x_, this->n_, ctx)...");
                BN_mod_exp(X, this->x_, x, this->n_, ctx);
                success = true;

                TALAS_LOG_DEBUG("BN_CTX_free(ctx)...");
                BN_CTX_free(ctx);
            }
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bn::public_key_implemented* bn_key_implemented() const {
        return (bn::public_key_implemented*)this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual BIGNUM* g() const {
        return (BIGNUM*)(this->g_);
    }
    virtual BIGNUM* n() const {
        return (BIGNUM*)(this->n_);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_exponent_msb
    (const byte_t* exponent, size_t expbytes) {
        ssize_t size = 0;

        if ((Extends::set_exponent_msb(exponent, expbytes))) {
            size = set_exponent_modulus_msb(exponent, expbytes);
        }
        return size;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_exponent_modulus_msb
    (const byte_t* exponent, size_t expbytes) {
        ssize_t size = 0;
        
        if ((this->g_) && (this->n_) && (this->x_) 
            && (exponent) && (expbytes) && (expbytes <= this->expbytes_)) {
            BIGNUM *x = 0;
    
            TALAS_LOG_DEBUG("x = BN_new()...");
            if ((x = BN_new())) {
                BN_CTX *ctx = 0;
                
                TALAS_LOG_DEBUG("BN_set_msb(x, exponent = " << x_to_string(exponent, expbytes) << ", expbytes = " << expbytes << ")...");
                BN_set_msb(x, exponent, expbytes);
    
                TALAS_LOG_DEBUG("ctx = BN_CTX_new()...");
                if ((ctx = BN_CTX_new())) {

                    TALAS_LOG_DEBUG("BN_mod_exp(this->x_, this->g_, x, this->n_, ctx)...");
                    BN_mod_exp(this->x_, this->g_, x, this->n_, ctx);
                    size = this->expbytes_;

                    TALAS_LOG_DEBUG("BN_CTX_free(ctx)...");
                    BN_CTX_free(ctx);
                }
                TALAS_LOG_DEBUG("BN_clear_free(x)...");
                BN_clear_free(x);
            }
        }
        return size;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef public_keyt<> public_key;

} // namespace bn 
} // namespace dh 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DH_BN_PUBLIC_KEY_HPP 
