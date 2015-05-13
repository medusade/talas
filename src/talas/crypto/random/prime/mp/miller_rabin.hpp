///////////////////////////////////////////////////////////////////////
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
///   File: miller_rabin.hpp
///
/// Author: $author$
///   Date: 5/7/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RANDOM_PRIME_MP_MILLER_RABIN_HPP
#define _TALAS_CRYPTO_RANDOM_PRIME_MP_MILLER_RABIN_HPP

#include "talas/crypto/random/prime/miller_rabin.hpp"
#include "talas/crypto/random/prime/mp/reader.hpp"
#include "talas/io/logger.hpp"
#include "xos/base/creator.hpp"

namespace talas {
namespace crypto {
namespace random {
namespace prime {
namespace mp {

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
    : m_reader_observer(observer) {
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
            mpz_init_set_ui(&m_n_minus_1,0);
            mpz_init_set_ui(&m_x,0);
            mpz_init_set_ui(&m_one,1);
            mpz_init_set_ui(&m_z,0);
            mpz_init_set_ui(&m_q,0);
            this->set_is_created();
            return true;
        }
        return false;
    }
    virtual bool destroy() {
        if ((this->is_created())) {
            set_is_created(false);
            mpz_clear(&m_q);
            mpz_clear(&m_z);
            mpz_clear(&m_one);
            mpz_clear(&m_x);
            mpz_clear(&m_n_minus_1);
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

            mpz_sub(&m_n_minus_1, n, &m_one);

            /* find q and k, such that n = 1 + 2^k * q
             * ie q = (n-1)/2^k
             */
            mpz_set(&m_q, &m_n_minus_1);

            for (k=0; (mpz_get_ui(&m_q)&1)==0; k++)
                mpz_tdiv_q_2exp(&m_q, &m_q, 1);

            for (i = 0; i < reps ; i++) {
                /* find random x such that 1 < x < n
                 */
                do {
                    if (0 >= (ReadMSB(&m_x, bytes, random)))
                        return false;

                    /* make x < n
                     */
                    mpz_clrbit(&m_x, bits-1);
                } while (mpz_cmp(&m_x, &m_one) <= 0);

                /* z = x^q mod n
                 */
                mpz_powm(&m_z, &m_x, &m_q, n);

                /* if z == 0 or z == n-1 then possibly prime
                 */
                if ((mpz_cmp(&m_z, &m_one) == 0)
                    || (mpz_cmp(&m_z, &m_n_minus_1) == 0))
                    continue;

                for (j = 1; j < k; j++) {
                    /* z = z^2 mod n
                     */
                    mpz_powm_ui(&m_z, &m_z, 2, n);

                    /* if z == n-1 then possibly prime
                     */
                    if (mpz_cmp(&m_z, &m_n_minus_1) == 0)
                        break;

                    /* if z == 1 then not prime
                     */
                    if (mpz_cmp(&m_z, &m_one) == 0)
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
    MP_INT m_n_minus_1;
    MP_INT m_x;
    MP_INT m_one;
    MP_INT m_z;
    MP_INT m_q;
};

} // namespace mp 
} // namespace prime 
} // namespace random 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RANDOM_PRIME_MP_MILLER_RABIN_HPP 
