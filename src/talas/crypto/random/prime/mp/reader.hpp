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
///   File: reader.hpp
///
/// Author: $author$
///   Date: 5/7/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RANDOM_PRIME_MP_READER_HPP
#define _TALAS_CRYPTO_RANDOM_PRIME_MP_READER_HPP

#include "talas/crypto/random/prime/reader.hpp"
#include "talas/crypto/random/prime/mp/number.hpp"
#include "talas/crypto/base.hpp"

namespace talas {
namespace crypto {
namespace random {
namespace prime {
namespace mp {

typedef crypto::random::prime::readert<BIGPRIME> reader_implements;
typedef reader_implements::observer reader_observer;
typedef crypto::base reader_extends;
///////////////////////////////////////////////////////////////////////
///  Class: reader
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS reader
: virtual public reader_observer, virtual public reader_implements, public reader_extends {
public:
    typedef reader_implements Implements;
    typedef reader_extends Extends;
    typedef reader_observer observer_t;
    typedef reader_random random_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    reader(observer_t* observer = 0): m_observer(observer) {
    }
    virtual ~reader() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read_msb(number& n, size_t bytes, random_t& random) {
        BIGPRIME* detached = 0;
        if ((detached = n.attached_to())) {
            return read_msb(detached, bytes, random);
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read_msb(BIGPRIME* n, size_t bytes, random_t& random) {
        byte_t byte = 0;
        mpz_set_ui(n, 0);
        for (size_t i=0; i<bytes; i++) {
            if (0 >= (this->get(byte, random)))
                return 0;
            mpz_mul_2exp(n, n, 8);
            mpz_add_ui(n, n, byte);
        }
        bytes = this->on_read(n, bytes);
        return bytes;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual observer_t* observer_delegated(BIGPRIME* n) const {
        return m_observer;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    observer_t* m_observer;
};

} // namespace mp 
} // namespace prime 
} // namespace random 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RANDOM_PRIME_MP_READER_HPP 
