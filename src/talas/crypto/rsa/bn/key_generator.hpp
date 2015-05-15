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
///   File: key_generator.hpp
///
/// Author: $author$
///   Date: 5/13/2015
///
/// Tatu Ylonen's RSA key generation function modified to be a C++
/// class that uses Eric Young's big number library instead of gmp used
/// in the original C version.
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RSA_BN_KEY_GENERATOR_HPP
#define _TALAS_CRYPTO_RSA_BN_KEY_GENERATOR_HPP

#include "talas/crypto/rsa/bn/private_key.hpp"
#include "talas/crypto/rsa/bn/public_key.hpp"
#include "talas/crypto/rsa/bn/key.hpp"
#include "talas/crypto/random/prime/bn/generator.hpp"

namespace talas {
namespace crypto {
namespace rsa {
namespace bn {

typedef random::prime::bn::generator::random_t random_reader_t;
typedef random::prime::bn::generator::reader_observer_t reader_observer_t;
typedef random::prime::bn::generator prime_generator_t;

typedef random::prime::bn::number_implement key_generator_implements;
typedef random::prime::bn::number_extend key_generator_extends;
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
                    BIGPRIME* pp = p;
                    BIGPRIME* qp = q;
                    BN_CTX* ctx = 0;

                    if ((ctx = privatekey.ctx())) {
                    if ((p_minus_1 = BN_new())) {
                    if ((q_minus_1 = BN_new())) {
                    if ((phi = BN_new())) {
                    if ((G = BN_new())) {
                    if ((F = BN_new())) {
                    if ((one = BN_new())) {
                    if ((temp = BN_new())) {
                        BN_set_word(one,1);

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
                                BN_mul(n,p,q);

                                /* Make sure that p*q will be modbits in size.
                                 */
                                if (BN_num_bits(n)!=(int)modbits) {
                                    /* Not big enough so we will try again.
                                     */
                                    retryp = true;
                                    continue;
                                }

                                /* See if q < p.
                                 */
                                cmp = BN_cmp(p,q);
                                if (!cmp) {
                                    /* q == p
                                     */
                                    retryq = true;
                                    continue;
                                } else if (cmp<0) {
                                    /* p < q
                                     */
                                    BN_copy(p_minus_1,q);
                                    BN_copy(q_minus_1,p);
                                    /* swap p and q
                                     */
                                    BN_copy(q,p);
                                    BN_copy(p,q_minus_1);
                                } else {
                                    /* p > q
                                     */
                                    BN_copy(p_minus_1,p);
                                    BN_copy(q_minus_1,q);
                                }

                                /* Make sure that p and q are not too close together
                                 */
                                BN_sub(temp,p_minus_1,q_minus_1);
                                BN_rshift(p_minus_1,p_minus_1,10);

                                if (BN_cmp(temp,p_minus_1)<0) {
                                    /* p-q < p>>10 (they are too close)
                                     */
                                    retryq = true;
                                    continue;
                                }

                                /* Make certain p and q are relatively prime
                                 * (in case one or both were false positives...
                                 * Though this is quite improbable).
                                 */
                                BN_gcd(temp,p,q,ctx);

                                if (BN_cmp(temp,one)) {
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
                                BN_sub(p_minus_1,p,one);
                                BN_sub(q_minus_1,q,one);

                                /* phi = (p - 1) * (q - 1); the number of positive integers less than p*q
                                 * that are relatively prime to p*q.
                                 */
                                BN_mul(phi,p_minus_1,q_minus_1);

                                /* G is the number of "spare key sets" for a given modulus n.  The smaller
                                 * G is, the better.  The smallest G can get is 2.
                                 * F = phi / G; the number of relative prime numbers per spare key set.
                                 */
                                BN_gcd(G,p_minus_1,q_minus_1,ctx);
                                BN_div(F,temp,phi,G,ctx);

                                if (exponent) {
                                    BN_set_msb(e,exponent,expbytes);
                                } else {
                                    /* Find a suitable e (the public exponent).
                                     */
                                    BN_set_word(e,1);
                                    BN_lshift(e,e,ebits);
                                    BN_add_word(e,1);

                                    /* make lowest bit 1
                                    /* Keep adding 2 until it is relatively prime to (p-1)(q-1).
                                     */
                                    do {
                                        BN_gcd(temp,e,phi,ctx);
                                        if ((cmp = BN_cmp(temp,one))>0)
                                            BN_add_word(e,2);
                                    } while (cmp>0);
                                }

                                /* d is the multiplicative inverse of e, mod F.  Could also be mod
                                 * (p-1)(q-1); however, we try to choose the smallest possible d.
                                 */
                                d = BN_mod_inverse(e,F,ctx);
                                if (d) {
                                    /* Compute dmp1 = d mod p-1.
                                     */
                                    BN_mod(dmp1,d,p_minus_1,ctx);

                                    /* Compute dmq1 = d mod q-1.
                                     */
                                    BN_mod(dmq1,d,q_minus_1,ctx);
                                    BN_free(d);
                                }

                                /* iqmp is the multiplicative inverse of q, mod p, if q < p.  It is used
                                 * when doing private key RSA operations using the chinese remainder
                                 * theorem method.
                                 */
                                d = BN_mod_inverse(q,p,ctx);
                                if (d) {
                                    BN_copy(iqmp,d);
                                    BN_free(d);
                                }

                            } while (retryq);

                        } while (retryp);

                    BN_free(temp); }
                    BN_free(one); }
                    BN_free(F); }
                    BN_free(G); }
                    BN_free(phi); }
                    BN_free(q_minus_1); }
                    BN_free(p_minus_1); }
                    (ctx = 0); }

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

} // namespace bn 
} // namespace rsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RSA_BN_KEY_GENERATOR_HPP 
