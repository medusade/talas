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
///   Date: 5/9/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RSA_BN_KEY_HPP
#define _TALAS_CRYPTO_RSA_BN_KEY_HPP

#include "talas/crypto/rsa/key.hpp"
#include "bn_msb.h"

namespace talas {
namespace crypto {
namespace rsa {
namespace bn {

typedef BIGNUM mpint_t;
typedef BIGNUM BIGPRIME;
typedef BIGNUM* BIGINT;

typedef rsa::key_implements key_implements;
typedef rsa::key key_extends;
///////////////////////////////////////////////////////////////////////
///  Class: keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = key_implements, class TExtends = key_extends>

class _EXPORT_CLASS keyt: virtual public TImplements,public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    keyt(): m_temp(0), m_ctx(0) {
    }
    virtual ~keyt() {
        if (!(this->destroyed())) {
            xos::base::creator_exception e = xos::base::failed_to_destroy;
            TALAS_LOG_ERROR("...failed on destroyed() throwing creator_exception failed_to_destroy...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create(size_t modbytes, size_t expbytes) {
        if ((this->destroyed())) {
            if ((Extends::create(modbytes, expbytes))) {
                TALAS_LOG_DEBUG("m_temp = BN_new()...");
                if ((m_temp = BN_new())) {
                    TALAS_LOG_DEBUG("m_ctx = BN_CTX_new()...");
                    if ((m_ctx = BN_CTX_new())) {
                        return true;
                        TALAS_LOG_DEBUG("BN_CTX_free(m_ctx)...");
                        BN_CTX_free(m_ctx);
                    }
                    TALAS_LOG_DEBUG("BN_free(m_temp)...");
                    BN_free(m_temp);
                }
                Extends::destroy();
            }
        }
        return false;
    }
    virtual bool create(size_t pbytes) {
        if ((this->destroyed())) {
            if ((Extends::create(pbytes))) {
                TALAS_LOG_DEBUG("m_temp = BN_new()...");
                if ((m_temp = BN_new())) {
                    TALAS_LOG_DEBUG("m_ctx = BN_CTX_new()...");
                    if ((m_ctx = BN_CTX_new())) {
                        return true;
                        TALAS_LOG_DEBUG("BN_CTX_free(m_ctx)...");
                        BN_CTX_free(m_ctx);
                    }
                    TALAS_LOG_DEBUG("BN_free(m_temp)...");
                    BN_free(m_temp);
                }
                Extends::destroy();
            }
        }
        return false;
    }
    virtual bool destroy() {
        if ((this->is_created())) {
            bool success = true;
            TALAS_LOG_DEBUG("BN_CTX_free(m_ctx)...");
            if (!(BN_CTX_free(m_ctx))) {
                success = false;
            }
            TALAS_LOG_DEBUG("BN_free(m_temp)...");
            if (!(BN_free(m_temp))) {
                success = false;
            }
            if (!(Extends::destroy())) {
                success = false;
            }
            return success;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual BN_CTX*& ctx() const {
        return (BN_CTX*&)m_ctx;
    }
    virtual BIGNUM*& temp() const {
        return (BIGNUM*&)m_temp;
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool BN_CTX_free(BN_CTX*& a) {
        if ((a)) {
            //TALAS_LOG_DEBUG("::BN_CTX_free(a)...");
            ::BN_CTX_free(a);
            a = 0;
            return true;
        }
        return false;
    }
    virtual bool BN_free(BIGNUM*& a) {
        if ((a)) {
            //TALAS_LOG_DEBUG("::BN_free(a)...");
            ::BN_free(a);
            a = 0;
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    BIGNUM *m_temp;
    BN_CTX *m_ctx;
};
typedef keyt<> key;

} // namespace bn 
} // namespace rsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RSA_BN_KEY_HPP 
