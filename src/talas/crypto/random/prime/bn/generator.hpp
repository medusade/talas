///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
/// All rights reserved
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
///   File: generator.hpp
///
/// Author: $author$
///   Date: 5/6/2015
///
/// Tatu Ylonen's prime generation modified to be a C++ class that
/// uses Eric Young's big number library instead of gmp used in the
/// original C version.
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RANDOM_PRIME_BN_GENERATOR_HPP
#define _TALAS_CRYPTO_RANDOM_PRIME_BN_GENERATOR_HPP

#include "talas/crypto/random/prime/generator.hpp"
#include "talas/crypto/random/prime/bn/number.hpp"
#include "talas/crypto/random/prime/bn/reader.hpp"
#include "xos/base/creator.hpp"

#if !defined(_RSA_NO_MILLER_RABIN_TEST)
#include "talas/crypto/random/prime/bn/miller_rabin.hpp"
#endif // !defined(_CRSA_NO_MILLER_RABIN_TEST)

namespace talas {
namespace crypto {
namespace random {
namespace prime {
namespace bn {

typedef xos::base::creatort
<random::prime::bn::reader_implements> generator_implements;

typedef xos::base::creator_extendt
<generator_implements, random::prime::generatort
 <BIGPRIME, generator_implements, random::prime::bn::reader> > generator_extends;
///////////////////////////////////////////////////////////////////////
///  Class: generator
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS generator
: virtual public number_implement,
  virtual public generator_implements, public generator_extends {
public:
    typedef generator_implements Implements;
    typedef generator_extends Extends;
    typedef reader_observer reader_observer_t;
    typedef reader_random random_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    generator(reader_observer_t* reader_observer = 0)
    : m_reader_observer(reader_observer),
      m_temp1(0), m_temp2(0), m_ctx(0)
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
      , m_miller_rabin(reader_observer)
#endif // !defined(_CRSA_NO_MILLER_RABIN_TEST)
    {
    }
    virtual ~generator() {
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
            if ((m_temp1 = BN_new())) {
            if ((m_temp2 = BN_new())) {
            if ((m_ctx = BN_CTX_new())) {
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
            if ((m_miller_rabin.create())) {
#endif // !defined(_CRSA_NO_MILLER_RABIN_TEST)
                return true;
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
                m_miller_rabin.destroy(); }
#endif // !defined(_CRSA_NO_MILLER_RABIN_TEST)
                BN_CTX_free(m_ctx); }
                BN_free(m_temp2); }
                BN_free(m_temp1); }
        }
        return false;
    }
    virtual bool destroy() {
        if ((this->is_created())) {
            bool is_true = true;
            set_is_created(false);
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
            is_true = m_miller_rabin.destroy();
#endif // !defined(_CRSA_NO_MILLER_RABIN_TEST)
            BN_CTX_free(m_ctx);
            BN_free(m_temp2);
            BN_free(m_temp1);
            return is_true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t generate
    (BIGPRIME* prime, size_t bytes, random_t& random,
     reader_observer_t* reader_observer = 0) {
        size_t count = 0;
        bool retry = true;
        unsigned bits = (bytes << 3);

#if !defined(_RSA_NO_SMALL_PRIME_TEST)
        long difference, small_prime;
        unsigned i, num_primes;
#endif // !defined(_RSA_NO_SMALL_PRIME_TEST)

        reader_observer_t* old_reader_observer = m_reader_observer;
        if ((reader_observer)) {
            m_reader_observer = reader_observer;
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
            m_miller_rabin.delegate_observer(reader_observer);
#endif // !defined(_CRSA_NO_MILLER_RABIN_TEST)
        }

        do {
            /* Pick a random integer of the appropriate size.
             */
            if (0 >= (count = ReadMSB(prime, bytes, random))) {
                return count;
            }

            /* Set the lowest bit to make it odd.
             */
            BN_set_bit(prime,0);

            /* Set the highest bit to make it n bits.
             */
            BN_set_bit(prime,(bits-1));

#if defined(_RSA_SET_TWO_HIGHEST_BITS)
            /* Set the second highest bit.
             */
            BN_set_bit(prime,(bits-2));
#endif // defined(_RSA_SET_TWO_HIGHEST_BITS)

#if !defined(_RSA_NO_SMALL_PRIME_TEST)
            /* Initialize moduli of the small primes with respect to the
             * random number.
             */
            if (bits < 16) {
                /* Don't use the table for very small numbers.
                 */
                num_primes = 0;
            } else {
                for (num_primes = 0; m_small_primes[num_primes] != 0; num_primes++) {
                    m_moduli[num_primes] = BN_mod_word(prime, m_small_primes[num_primes]);
                }
            }

            /* Look for numbers that are not evenly divisible
             * by any of the small primes.
             */
            for (difference = 0; difference <= m_small_prime_difference; difference += 2) {
                /* Check if it is a multiple of any small prime. Note that this
                 * updates the moduli into negative values as difference grows.
                 */
                for (i = 0; i < num_primes; i++) {
                    while ((m_moduli[i] + difference) >= (small_prime = (long)(m_small_primes[i]))) {
                        m_moduli[i] -= small_prime;
                    }
                    if ((m_moduli[i] + difference) == 0) {
                        break;
                    }
                }

                if (i < num_primes) {
                    /* Multiple of a known prime.
                     */
                    continue;
                }
                /* It passed the small prime test (not divisible by any of them).
                 * Compute the number in question.
                 */
                BN_add_word(prime,difference);
#endif // !defined(_RSA_NO_SMALL_PRIME_TEST)

                /* Perform the fermat test for witness 2. This means
                 * it is not prime if 2^n mod n != 2.
                 */
                BN_set_word(m_temp1,2);
                BN_mod_exp(m_temp2,m_temp1,prime,prime,m_ctx);
                if (BN_cmp(m_temp1,m_temp2)) {
                    /* Failed the fermat test for witness 2.
                     */
                    continue;
                }
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
                /* Perform the Miller Rabin primality test.
                 */
                if (!(m_miller_rabin.probably_prime
                    (prime, bytes, m_miller_rabin_reps, random))) {
                    /* Failed the Miller Rabin probable primality test.
                     */
                    continue;
                }
#endif // !defined(_CRSA_NO_MILLER_RABIN_TEST)

                /* Found a (probable) prime.
                 * Sanity check: does it still have the high bit set
                 * (we might have wrapped around)?
                 */
                if (BN_is_bit_set(prime,bits-1)) {
                    /* passed sanity check!
                     * it does still have the high bit set
                     */
                    retry = false;
                }
#if !defined(_RSA_NO_SMALL_PRIME_TEST)
                break;
            }
#endif // !defined(_RSA_NO_SMALL_PRIME_TEST)

        } while (retry);

        if ((reader_observer)) {
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
            m_miller_rabin.delegate_observer(old_reader_observer);
#endif // !defined(_CRSA_NO_MILLER_RABIN_TEST)
            m_reader_observer = old_reader_observer;
        }
        return bytes;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual reader_observer_t* observer_delegated(BIGPRIME* n) const {
        return m_reader_observer;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    reader_observer_t* m_reader_observer;
    BIGNUM *m_temp1,*m_temp2;
    BN_CTX *m_ctx;
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
    miller_rabin m_miller_rabin;
#endif // !defined(_CRSA_NO_MILLER_RABIN_TEST)
};

} // namespace bn 
} // namespace prime 
} // namespace random 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RANDOM_PRIME_BN_GENERATOR_HPP 
