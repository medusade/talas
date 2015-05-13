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
///   File: number.hpp
///
/// Author: $author$
///   Date: 5/2/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RANDOM_PRIME_BN_NUMBER_HPP
#define _TALAS_CRYPTO_RANDOM_PRIME_BN_NUMBER_HPP

#include "talas/crypto/base.hpp"
#include "xos/base/created.hpp"
#include "xos/base/creator.hpp"
#include "xos/base/attached.hpp"
#include "xos/base/attacher.hpp"
#include "bn_msb.h"

namespace talas {
namespace crypto {
namespace random {
namespace prime {
namespace bn {

typedef BIGNUM BIGPRIME;
typedef BIGNUM* BIGINT;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS number_implement: virtual public crypto::implement_base {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool BN_CTX_free(BN_CTX*& a) {
        if ((a)) {
            ::BN_CTX_free(a);
            a = 0;
            return true;
        }
        return false;
    }
    virtual bool BN_free(BIGNUM*& a) {
        if ((a)) {
            ::BN_free(a);
            a = 0;
            return true;
        }
        return false;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS number_extend
: virtual public number_implement, public crypto::base {
public:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    number_extend() {}
    virtual ~number_extend() {}
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

typedef BIGNUM* number_attached_t;

typedef xos::base::creatort<number_implement> number_creator;
typedef xos::base::attachert
<number_attached_t, int, 0, number_creator> number_attacher;
typedef xos::base::attachedt
<number_attached_t, int, 0, number_attacher, number_extend> number_attached;
typedef xos::base::createdt
<number_attached_t, int, 0, number_attacher, number_attached> number_created;
typedef number_attacher number_implements;
typedef number_created number_extends;
///////////////////////////////////////////////////////////////////////
///  Class: number
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS number
: virtual public number_implements, public number_extends {
public:
    typedef number_implements Implements;
    typedef number_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    number(unsigned initialValue = 0) {
        if (!(this->create(initialValue))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            XOS_LOG_ERROR("...failed on create(" << initialValue << ") throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    virtual ~number() {
        if (!(this->destroyed())) {
            xos::base::creator_exception e = xos::base::failed_to_destroy;
            XOS_LOG_ERROR("...failed on destroyed() throwing creator_exception failed_to_destroy...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t from_msb(const byte_t* from, unsigned bytes) {
        ssize_t size = 0;
        if ((from) && (bytes)) {
            BIGNUM* detached = 0;
            if ((detached = this->attached_to())) {
                BN_set_msb(detached, from, bytes);
                size = bytes;
            }
        }
        return size;
    }
    virtual ssize_t to_msb(byte_t* to, unsigned bytes) const {
        ssize_t size = 0;
        if ((to) && (bytes)) {
            BIGNUM* detached = 0;
            if ((detached = this->attached_to())) {
                BN_get_msb(detached, to, bytes);
                size = bytes;
            }
        }
        return size;
    }

    ///////////////////////////////////////////////////////////////////////
    /// deprecated
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t FromMSB(const byte_t* from, unsigned bytes) {
        ssize_t size = this->from_msb(from, bytes);
        return size;
    }
    virtual ssize_t ToMSB(byte_t* to, unsigned bytes) const {
        ssize_t size = this->to_msb(to, bytes);
        return size;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual operator BIGNUM* () const {
        return this->attached_to();
    }
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create(unsigned initialValue = 0) {
        BIGNUM* detached = 0;
        if ((detached = BN_new())) {
            this->attach_created(detached);
            ::BN_set_word(detached, initialValue);
            return true;
        }
        return true;
    }
    virtual bool destroy() {
        BIGNUM* detached = 0;
        if ((detached = this->detach())) {
            ::BN_free(detached);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace bn 
} // namespace prime
} // namespace random
} // namespace crypto
} // namespace talas 

#endif // _TALAS_CRYPTO_RANDOM_PRIME_BN_NUMBER_HPP
