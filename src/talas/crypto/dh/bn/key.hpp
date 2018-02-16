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
///   File: key.hpp
///
/// Author: $author$
///   Date: 2/11/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DH_BN_KEY_HPP
#define _TALAS_CRYPTO_DH_BN_KEY_HPP

#include "talas/crypto/dh/key.hpp"
#include "bn_msb.h"

namespace talas {
namespace crypto {
namespace dh {
namespace bn {

///////////////////////////////////////////////////////////////////////
///  Class: keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = dh::key_implements, class TExtends = dh::key_extend>

class keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    enum {key_min = 1, key_max = 256};

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    keyt
    (const unsigned& generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes): g_(0), n_(0), x_(0) {
        if (!(this->create_msb
             (generator, genbytes, modulus, modbytes, exponent, expbytes))) {
            const creator_exception e = failed_to_create;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_create)...")
            throw(e);
        }
    }
    keyt
    (const byte_t* generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes): g_(0), n_(0), x_(0) {
        if (!(this->create_msb
             (generator, genbytes, modulus, modbytes, exponent, expbytes))) {
            const creator_exception e = failed_to_create;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_create)...")
            throw(e);
        }
    }
    keyt(): g_(0), n_(0), x_(0) {
    }
    virtual ~keyt() {
        if (!(this->destroyed())) {
            const creator_exception e = failed_to_destroy;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_destroy)...")
            throw(e);
        }
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create(size_t genbytes, size_t modbytes, size_t expbytes) {
        if ((Implements::create(genbytes, modbytes, expbytes))) {

            TALAS_LOG_DEBUG("g_ = BN_new()...");
            if ((g_ = BN_new())) {

                TALAS_LOG_DEBUG("n_ = BN_new()...");
                if ((n_ = BN_new())) {

                    TALAS_LOG_DEBUG("x_ = BN_new()...");
                    if ((x_ = BN_new())) {
                        return true;
                    }
                    BN_clear_free(n_);
                }
                BN_clear_free(g_);
            }
            Implements::destroy();
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void clear() {
        if ((g_)) {
            TALAS_LOG_DEBUG("BN_clear_free(g_)...");
            BN_clear_free(g_);
            g_ = 0;
        }
        if ((n_)) {
            TALAS_LOG_DEBUG("BN_clear_free(n_)...");
            BN_clear_free(n_);
            n_ = 0;
        }
        if ((g_)) {
            TALAS_LOG_DEBUG("BN_clear_free(g_)...");
            BN_clear_free(g_);
            g_ = 0;
        }
        Extends::clear();
    }
        
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Implements::set_msb;
    virtual bool set_msb
    (const byte_t* generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if ((generator) && (genbytes) && (genbytes <= this->genbytes())
            && (modulus) && (modbytes) && (modbytes <= this->modbytes())
            && (exponent) && (expbytes) && (expbytes <= this->expbytes())
            && (g_) && (n_) && (x_)) {

            if ((set_generator_msb(generator, genbytes))) {
                if ((set_modulus_msb(modulus, modbytes))) {
                    if ((set_exponent_msb(exponent, expbytes))) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_generator_msb
    (const byte_t* generator, size_t genbytes) {
        if ((generator) && (genbytes) && (genbytes <= this->genbytes()) && (g_)) {

            TALAS_LOG_DEBUG("BN_set_msb(g_, generator = " << x_to_string(generator, genbytes) << ", genbytes = " << genbytes << ")...");
            BN_set_msb(g_, generator, genbytes);
            return genbytes;
        }
        return 0;
    }
    virtual ssize_t get_generator_msb
    (byte_t* generator, size_t genbytes) const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_modulus_msb
    (const byte_t* modulus, size_t modbytes) {
        if ((modulus) && (modbytes) && (modbytes <= this->modbytes()) && (n_)) {

            TALAS_LOG_DEBUG("BN_set_msb(n_, modulus = " << x_to_string(modulus, modbytes) << ", modbytes = " << modbytes << ")...");
            BN_set_msb(n_, modulus, modbytes);
            return modbytes;
        }
        return 0;
    }
    virtual ssize_t get_modulus_msb
    (byte_t* modulus, size_t modbytes) const {
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_exponent_msb
    (const byte_t* exponent, size_t expbytes) {
        if ((exponent) && (expbytes) && (expbytes <= this->expbytes()) && (x_)) {

            TALAS_LOG_DEBUG("BN_set_msb(x_, exponent = " << x_to_string(exponent, expbytes) << ", expbytes = " << expbytes << ")...");
            BN_set_msb(x_, exponent, expbytes);
            return expbytes;
        }
        return 0;
    }
    virtual ssize_t get_exponent_msb
    (byte_t* exponent, size_t expbytes) const {
        if ((exponent) && (expbytes) && (expbytes >= this->expbytes_) && (x_)) {

            TALAS_LOG_DEBUG("BN_get_msb(x_, exponent, this->expbytes_ = " << this->expbytes_ << ")...");
            BN_get_msb(x_, exponent, this->expbytes_);
            return expbytes;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t genbytes_min() const {
        return key_min;
    }
    virtual size_t genbytes_max() const {
        return key_max;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual size_t modbytes_min() const {
        return key_min;
    }
    virtual size_t modbytes_max() const {
        return key_max;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual size_t expbytes_min() const {
        return key_min;
    }
    virtual size_t expbytes_max() const {
        return key_max;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    BIGNUM *g_, *n_, *x_;
};
typedef keyt<> key;
typedef key::Implements key_implements;

} // namespace bn 
} // namespace dh 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DH_BN_KEY_HPP 
