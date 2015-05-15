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
///   File: key_generator.hpp
///
/// Author: $author$
///   Date: 5/13/2015
///
/// Tatu Ylonen's RSA key generation modified to be a C++
/// class that uses the gmp used in the original C version.
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RSA_MP_KEY_GENERATOR_HPP
#define _TALAS_CRYPTO_RSA_MP_KEY_GENERATOR_HPP

#include "talas/crypto/rsa/mp/private_key.hpp"
#include "talas/crypto/rsa/mp/public_key.hpp"
#include "talas/crypto/rsa/mp/key.hpp"
#include "talas/crypto/random/prime/mp/generator.hpp"

namespace talas {
namespace crypto {
namespace rsa {
namespace mp {

typedef random::prime::mp::generator::random_t random_reader_t;
typedef random::prime::mp::generator::reader_observer_t reader_observer_t;
typedef random::prime::mp::generator prime_generator_t;

typedef random::prime::mp::number_implement key_generator_implements;
typedef random::prime::mp::number_extend key_generator_extends;
///////////////////////////////////////////////////////////////////////
///  Class: key_generator
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS key_generator
: virtual public key_generator_implements, public key_generator_extends {
public:
    typedef key_generator_implements Implements;
    typedef key_generator_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    key_generator(reader_observer_t* reader_observer = 0)
    : m_prime_generator(reader_observer) {
    }
    virtual ~key_generator() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool generate
    (private_key& privatekey, public_key& publickey,
     size_t modbytes, const byte_t* exponent, unsigned expbytes,
     random_reader_t& random, reader_observer_t* reader_observer = 0) {
        bool success = false;

        BIGINT& p = privatekey.p();
        BIGINT& q = privatekey.q();
        BIGINT& dmp1 = privatekey.dmp1();
        BIGINT& dmq1 = privatekey.dmq1();
        BIGINT& iqmp = privatekey.iqmp();
        BIGINT& e = publickey.exponent();
        BIGINT& n = publickey.modulus();
        BIGINT p_minus_1, q_minus_1, phi, F, G, d, one, temp;

        unsigned bytes, bits, ebits, modbits;
        bool retryp, retryq;
        int cmp;

        /* Compute the number of bits in each prime.
         */
        bytes = modbytes/2;
        bits = bytes*8;
        ebits = expbytes*8;
        modbits = bits*2;

        if ((m_prime_generator.create())) {
            if ((publickey.create(modbytes,expbytes))) {
                if ((privatekey.create(bytes))) {
                    BIGPRIME* pp = &p;
                    BIGPRIME* qp = &q;

                    mpz_init_set_ui(&p_minus_1,0);
                    mpz_init_set_ui(&q_minus_1,0);
                    mpz_init_set_ui(&phi,0);
                    mpz_init_set_ui(&G,0);
                    mpz_init_set_ui(&F,0);
                    mpz_init_set_ui(&d,0);
                    mpz_init_set_ui(&one,1);
                    mpz_init_set_ui(&temp,0);

                    success = true;
                    do {
                        retryp = false;

                        /* Generate random number p.
                         */
                        if (0 >= (m_prime_generator.generate(pp,bytes,random,reader_observer))) {
                            success = false;
                            break;
                        }
                        do {
                            retryq = false;

                            /* Generate random number q.
                             */
                            if (0 >= (m_prime_generator.generate(qp,bytes,random,reader_observer))) {
                                success = false;
                                break;
                            }

                            /* n = p * q (the public modulus).
                             */
                            mpz_mul(&n, &p, &q);

                            /* Make sure that p*q will be modbits in size.
                             */
                            mpz_tdiv_q_2exp(&temp, &n, modbits-1);
                            if ((!mpz_get_ui(&temp)) && (!mpz_getbit(&n, modbits-1))) {
                                /* Not big enough so we will try again.
                                 */
                                retryp = true;
                                continue;
                            }

                            /* See if q < p.
                             */
                            cmp = mpz_cmp(&p, &q);
                            if (!cmp) {
                                /* q == p
                                 */
                                retryq = true;
                                continue;
                            } else if (cmp<0) {
                                /* p < q
                                 */
                                mpz_set(&p_minus_1, &q);
                                mpz_set(&q_minus_1, &p);
                                /* swap p and q
                                 */
                                mpz_set(&q, &p);
                                mpz_set(&p, &q_minus_1);
                            } else {
                                /* p > q
                                 */
                                mpz_set(&p_minus_1, &p);
                                mpz_set(&q_minus_1, &q);
                            }

                            /* Make sure that p and q are not too close together
                             */
                            mpz_sub(&temp, &p_minus_1, &q_minus_1);
                            mpz_div_2exp(&p_minus_1, &p_minus_1, 10);

                            if (mpz_cmp(&temp, &p_minus_1)<0) {
                                /* p-q < p>>10 (they are too close)
                                 */
                                retryq = true;
                                continue;
                            }

                            /* Make certain p and q are relatively prime
                             * (in case one or both were false positives...
                             * Though this is quite improbable).
                             */
                            mpz_gcd(&temp, &p, &q);
                            if (mpz_cmp_ui(&temp, 1)) {
                                /* No, p and q are not relatively prime
                                 */
                                retryq = true;
                                continue;
                            }

                            /* Derive the RSA private key from the primes.
                             * Given mutual primes p and q, derive RSA key components n, e, d, and u.
                             * The exponent e will be at least ebits bits in size.
                             * p must be smaller than q.
                             */

                            /* Compute p-1 and q-1.
                             */
                            mpz_sub_ui(&p_minus_1, &p, 1);
                            mpz_sub_ui(&q_minus_1, &q, 1);

                            /* phi = (p - 1) * (q - 1); the number of positive integers less than p*q
                             * that are relatively prime to p*q.
                             */
                            mpz_mul(&phi, &p_minus_1, &q_minus_1);

                            /* G is the number of "spare key sets" for a given modulus n.  The smaller
                             * G is, the better.  The smallest G can get is 2.
                             * F = phi / G; the number of relative prime numbers per spare key set.
                             */
                            mpz_gcd(&G, &p_minus_1, &q_minus_1);
                            mpz_div(&F, &phi, &G);

                            if (exponent) {
                                mpz_set_msb(&e, exponent, expbytes);
                            } else {
                                /* Find a suitable e (the public exponent).
                                 */
                                mpz_set_ui(&e, 1);
                                mpz_mul_2exp(&e, &e, ebits);
                                mpz_add_ui(&e, &e, 1);

                                /* make lowest bit 1
                                /* Keep adding 2 until it is relatively prime to (p-1)(q-1).
                                 */
                                do {
                                    mpz_gcd(&temp, &e, &phi);
                                    if ((cmp = mpz_cmp_ui(&temp, 1))>0)
                                        mpz_add_ui(&e, &e, 2);
                                } while (cmp>0);
                            }

                            /* d is the multiplicative inverse of e, mod F.  Could also be mod
                             * (p-1)(q-1); however, we try to choose the smallest possible d.
                             */
                            mpz_mod_inverse(&d, &e, &F);

                            /* Compute dmp1 = d mod p-1.
                             */
                            mpz_mod(&dmp1, &d, &p_minus_1);

                            /* Compute dmq1 = d mod q-1.
                             */
                            mpz_mod(&dmq1, &d, &q_minus_1);

                            /* iqmp is the multiplicative inverse of q, mod p, if q < p.  It is used
                             * when doing private key RSA operations using the chinese remainder
                             * theorem method.
                             */
                            mpz_mod_inverse(&iqmp, &q, &p);

                        } while (retryq);

                    } while (retryp);

                    mpz_clear(&p_minus_1);
                    mpz_clear(&q_minus_1);
                    mpz_clear(&phi);
                    mpz_clear(&G);
                    mpz_clear(&F);
                    mpz_clear(&d);
                    mpz_clear(&one);
                    mpz_clear(&temp);

                    if (!success)
                        privatekey.destroy();
                }
                if (!success)
                    publickey.destroy();
            }
            m_prime_generator.destroy();
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    prime_generator_t m_prime_generator;
};

} // namespace mp 
} // namespace rsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RSA_MP_KEY_GENERATOR_HPP 
