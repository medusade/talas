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
///   File: private_key.hpp
///
/// Author: $author$
///   Date: 2/11/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DH_BN_PRIVATE_KEY_HPP
#define _TALAS_CRYPTO_DH_BN_PRIVATE_KEY_HPP

#include "talas/crypto/dh/bn/public_key.hpp"
#include "talas/crypto/dh/private_key.hpp"

namespace talas {
namespace crypto {
namespace dh {
namespace bn {

///////////////////////////////////////////////////////////////////////
///  Class: private_keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = dh::private_key_implements, 
 class TExtends = dh::private_keyt<dh::private_key_implements, key> >

class private_keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    private_keyt
    (const dh::public_key_implements& public_key,
     const byte_t* exponent, size_t expbytes) {
        if (!(this->create(public_key, exponent, expbytes))) {
            const creator_exception e = failed_to_create;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_create)...")
            throw(e);
        }
    }
    private_keyt() {
    }
    virtual ~private_keyt() {
        if (!(this->destroyed())) {
            const creator_exception e = failed_to_destroy;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_destroy)...")
            throw(e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create
    (const dh::public_key_implements& public_key,
     const byte_t* exponent, size_t expbytes) {
        if ((exponent) && (expbytes)) {
            public_key_implemented* pub = 0;
            if ((pub = public_key.bn_key_implemented())) {
                size_t genbytes = 0, modbytes = 0;
                BIGNUM *g = 0, *n = 0;
                if ((g = pub->g()) && (genbytes = pub->genbytes()) 
                    && (n = pub->n()) && (modbytes = pub->modbytes())) {
                    if ((Implements::create(genbytes, modbytes, expbytes))) {
                        
                        TALAS_LOG_DEBUG("this->g_ = BN_new()...");
                        if ((this->g_ = BN_new())) {
                            
                            TALAS_LOG_DEBUG("BN_copy(this->g_, g)...");
                            BN_copy(this->g_, g);
                            
                            TALAS_LOG_DEBUG("this->n_ = BN_new()...");
                            if ((this->n_ = BN_new())) {
                                
                                TALAS_LOG_DEBUG("BN_copy(this->n_, n)...");
                                BN_copy(this->n_, n);
                                
                                TALAS_LOG_DEBUG("this->x_ = BN_new()...");
                                if ((this->x_ = BN_new())) {
                                    
                                    if ((pub->create_secret_msb(this->x_, exponent, expbytes))) {
                                        return true;
                                    }
                                    TALAS_LOG_DEBUG("BN_clear_free(this->x_)...");
                                    BN_clear_free(this->x_);
                                    this->x_ = 0;
                                }
                                TALAS_LOG_DEBUG("BN_clear_free(this->n_)...");
                                BN_clear_free(this->n_);
                                this->n_ = 0;
                            }
                            TALAS_LOG_DEBUG("BN_clear_free(this->g_)...");
                            BN_clear_free(this->g_);
                            this->g_ = 0;
                        }
                        Implements::destroy();
                    }
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef private_keyt<> private_key;
typedef private_key::Implements private_key_implements;

} // namespace bn 
} // namespace dh 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DH_BN_PRIVATE_KEY_HPP 
