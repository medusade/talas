///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
/// All rights reserved
/// Copyright (C) 1991, 1993, 1994, 1995, 1996 Free Software Foundation, Inc.
/// 
/// This file is part of the GNU MP Library.
/// 
/// The GNU MP Library is free software; you can redistribute it and/or modify
/// it under the terms of the GNU Library General Public License as published by
/// the Free Software Foundation; either version 2 of the License, or (at your
/// option) any later version.
/// 
/// The GNU MP Library is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
/// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
/// License for more details.
/// 
/// You should have received a copy of the GNU Library General Public License
/// along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
/// the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
/// MA 02111-1307, USA.
///
///   File: generator.hpp
///
/// Author: $author$
///   Date: 5/7/2015
///
/// Tatu Ylonen's prime generation modified to be a C++ class that
/// uses the gmp used in the original C version.
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RANDOM_PRIME_MP_GENERATOR_HPP
#define _TALAS_CRYPTO_RANDOM_PRIME_MP_GENERATOR_HPP

#include "talas/crypto/random/prime/generator.hpp"
#include "talas/crypto/random/prime/mp/number.hpp"
#include "talas/crypto/random/prime/mp/reader.hpp"
#include "xos/base/creator.hpp"

#if !defined(_RSA_NO_MILLER_RABIN_TEST)
#include "talas/crypto/random/prime/mp/miller_rabin.hpp"
#endif // !defined(_CRSA_NO_MILLER_RABIN_TEST)

namespace talas {
namespace crypto {
namespace random {
namespace prime {
namespace mp {

typedef xos::base::creatort
<random::prime::mp::reader_implements> generator_implements;

typedef xos::base::creator_extendt
<generator_implements, random::prime::generatort
 <BIGPRIME, generator_implements, random::prime::mp::reader> > generator_extends;
///////////////////////////////////////////////////////////////////////
///  Class: generator
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS generator
: virtual public generator_implements, public generator_extends {
public:
    typedef generator_implements Implements;
    typedef generator_extends Extends;
    typedef reader_observer reader_observer_t;
    typedef reader_random random_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    generator(reader_observer_t* reader_observer = 0)
    : m_reader_observer(reader_observer)
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
            mpz_init_set_ui(&m_temp1, 0);
            mpz_init_set_ui(&m_temp2, 0);
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
            if ((m_miller_rabin.create())) {
#endif // !defined(_CRSA_NO_MILLER_RABIN_TEST)
                this->set_is_created();
                return true;
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
            }
#endif // !defined(_CRSA_NO_MILLER_RABIN_TEST)
            mpz_clear(&m_temp2);
            mpz_clear(&m_temp1);
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
            mpz_clear(&m_temp2);
            mpz_clear(&m_temp1);
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
            mpz_set_ui(&m_temp1, 1);
            mpz_ior(prime, prime, &m_temp1);

            /* Set the highest bit to make it n bits.
             */
            mpz_mul_2exp(&m_temp1, &m_temp1, (bits-1));
            mpz_ior(prime, prime, &m_temp1);

#if defined(_RSA_SET_TWO_HIGHEST_BITS)
            /* Set the second highest bit.
             */
            mpz_tdiv_q_2exp(&m_temp1, &m_temp1,1);
            mpz_ior(prime, prime, &m_temp1);
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
                    mpz_mod_ui(&m_temp1, prime, m_small_primes[num_primes]);
                    m_moduli[num_primes] = mpz_get_ui(&m_temp1);
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
                mpz_add_ui(prime, prime, difference);
#endif // !defined(_RSA_NO_SMALL_PRIME_TEST)

                /* Perform the fermat test for witness. This means
                 * it is not prime if 2^n mod n != 2.
                 */
                mpz_set_ui(&m_temp1, 2);
                mpz_powm(&m_temp2, &m_temp1, prime, prime);
                if (mpz_cmp(&m_temp1, &m_temp2)) {
                    /* Failed the fermat test for witness.
                     */
                    continue;
                }
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
                /* Perform the Miller Rabin primality test.
                 */
                if (!(m_miller_rabin.ProbablyPrime
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
                mpz_tdiv_q_2exp(&m_temp1, prime, bits-1);
                if (mpz_get_ui(&m_temp1)) {
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
    MP_INT m_temp1, m_temp2;
#if !defined(_RSA_NO_MILLER_RABIN_TEST)
    miller_rabin m_miller_rabin;
#endif // !defined(_CRSA_NO_MILLER_RABIN_TEST)
};

} // namespace mp 
} // namespace prime 
} // namespace random 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RANDOM_PRIME_MP_GENERATOR_HPP 
