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
///   File: miller_rabin.hpp
///
/// Author: $author$
///   Date: 5/3/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RANDOM_PRIME_BN_MILLER_RABIN_HPP
#define _TALAS_CRYPTO_RANDOM_PRIME_BN_MILLER_RABIN_HPP

#include "talas/crypto/random/prime/miller_rabin.hpp"
#include "talas/crypto/random/prime/bn/reader.hpp"
#include "talas/io/logger.hpp"
#include "xos/base/creator.hpp"

namespace talas {
namespace crypto {
namespace random {
namespace prime {
namespace bn {

typedef reader_random random_t;
typedef reader reader_t;
typedef reader_observer reader_observer_t;

typedef xos::base::creatort<reader_t> miller_rabin_creator;
class _EXPORT_CLASS miller_rabin_implements
: virtual public miller_rabin_creator, virtual public number_implement {
};
typedef crypto::random::prime::miller_rabint
<BIGPRIME, reader_t, random_t, miller_rabin_implements>  miller_rabin_base;
typedef xos::base::creator_extendt
<miller_rabin_implements, miller_rabin_base> miller_rabin_extends;
///////////////////////////////////////////////////////////////////////
///  Class: miller_rabin
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS miller_rabin
: virtual public miller_rabin_implements, public miller_rabin_extends {
public:
    typedef miller_rabin_implements Implements;
    typedef miller_rabin_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    miller_rabin(reader_observer_t* observer = 0)
    : m_reader_observer(observer),
      m_n_minus_1(0),
      m_x(0),
      m_one(0),
      m_z(0),
      m_q(0),
      m_ctx(0) {
    }
    virtual ~miller_rabin() {
        if (!(this->destroyed())) {
            xos::base::creator_exception e = xos::base::failed_to_destroy;
            TALAS_LOG_ERROR("...failed on destroyed() throwing creator_exception failed_to_destroy...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create() {
        if ((this->destroyed())) {
            if ((m_n_minus_1 = BN_new())) {
            if ((m_x = BN_new())) {
            if ((m_one = BN_new())) {
            if ((m_z = BN_new())) {
            if ((m_q = BN_new())) {
            if ((m_ctx = BN_CTX_new())) {
                BN_set_word(m_one,1);
                this->set_is_created();
                return true;
            BN_CTX_free(m_ctx); }
            BN_free(m_q); }
            BN_free(m_z); }
            BN_free(m_one); }
            BN_free(m_x); }
            BN_free(m_n_minus_1); }
        }
        return false;
    }
    virtual bool destroy() {
        if ((this->is_created())) {
            set_is_created(false);
            BN_CTX_free(m_ctx);
            BN_free(m_q);
            BN_free(m_z);
            BN_free(m_one);
            BN_free(m_x);
            BN_free(m_n_minus_1);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::probably_prime;
    virtual bool probably_prime
    (BIGPRIME* n, size_t bytes, unsigned reps, random_t& random) {
        if ((this->is_created())) {
            unsigned bits = (bytes<<3);
            unsigned i,j,k;

            BN_sub(m_n_minus_1, n, m_one);

            /* find q and k, such that n = 1 + 2^k * q
             * ie q = (n-1)/2^k
             */
            for (k=0; !BN_is_bit_set(m_n_minus_1,k); k++);

            BN_rshift(m_q,m_n_minus_1,k);

            for (i = 0; i < reps ; i++) {
                /* find random x such that 1 < x < n
                 */
                do {
                    if (0 >= (ReadMSB(m_x, bytes, random)))
                        return false;

                    /* make x < n
                     */
                    BN_clear_bit(m_x,bits-1);
                } while (BN_cmp(m_x, m_one) <= 0);

                /* z = x^q mod n
                 */
                BN_mod_exp(m_z, m_x, m_q, n, m_ctx);

                /* if z == 0 or z == n-1 then possibly prime
                 */
                if ((BN_cmp(m_z, m_one) == 0)
                    || (BN_cmp(m_z, m_n_minus_1) == 0))
                    continue;

                for (j = 1; j < k; j++) {
                    /* z = z^2 mod n
                     */
                    BN_mod_mul(m_z, m_z, m_z, n, m_ctx);

                    /* if z == n-1 then possibly prime
                     */
                    if (BN_cmp(m_z, m_n_minus_1) == 0)
                        break;

                    /* if z == 1 then not prime
                     */
                    if (BN_cmp(m_z, m_one) == 0)
                        return false;
                }
                if (j>=k)
                    return false;
            }
            return true;
        }
        return false;
    }

    ////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual reader_observer_t* delegate_observer(reader_observer_t* to) {
        m_reader_observer = to;
        return m_reader_observer;
    }
    virtual reader_observer_t* observer_delegated(BIGPRIME* n) const {
        return m_reader_observer;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    reader_observer_t* m_reader_observer;
    BIGNUM* m_n_minus_1;
    BIGNUM* m_x;
    BIGNUM* m_one;
    BIGNUM* m_z;
    BIGNUM* m_q;
    BN_CTX* m_ctx;
};

} // namespace bn
} // namespace prime
} // namespace random 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RANDOM_PRIME_BN_MILLER_RABIN_HPP
