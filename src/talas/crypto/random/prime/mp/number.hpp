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
///   File: number.hpp
///
/// Author: $author$
///   Date: 5/7/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RANDOM_PRIME_MP_NUMBER_HPP
#define _TALAS_CRYPTO_RANDOM_PRIME_MP_NUMBER_HPP

#include "talas/crypto/base.hpp"
#include "talas/io/logger.hpp"
#include "xos/base/created.hpp"
#include "xos/base/creator.hpp"
#include "xos/base/attached.hpp"
#include "xos/base/attacher.hpp"
#include "mpz_msb.h"

namespace talas {
namespace crypto {
namespace random {
namespace prime {
namespace mp {

typedef MP_INT BIGPRIME;
typedef MP_INT BIGINT;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS number_implement: virtual public crypto::implement_base {
public:
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

typedef MP_INT* number_attached_t;

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
class _EXPORT_CLASS number: virtual public number_implements, public number_extends {
public:
    typedef number_implements Implements;
    typedef number_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    number(unsigned initialValue = 0) {
        if (!(this->create(initialValue))) {
            xos::base::creator_exception e = xos::base::failed_to_create;
            TALAS_LOG_ERROR("...failed on create(" << initialValue << ") throwing creator_exception failed_to_create...");
            throw (e);
        }
    }
    virtual ~number() {
        if (!(this->destroyed())) {
            xos::base::creator_exception e = xos::base::failed_to_destroy;
            TALAS_LOG_ERROR("...failed on destroyed() throwing creator_exception failed_to_destroy...");
            throw (e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t from_msb(const byte_t* from, unsigned bytes) {
        ssize_t size = 0;
        if ((from) && (bytes)) {
            MP_INT* detached = 0;
            if ((detached = this->attached_to())) {
                mp_size_t mpsize = 0;
                if (bytes <= (mpsize = mpz_set_msb(detached, from, bytes))) {
                    size = mpsize;
                }
            }
        }
        return size;
    }
    virtual ssize_t to_msb(byte_t* to, unsigned bytes) const {
        ssize_t size = 0;
        if ((to) && (bytes)) {
            MP_INT* detached = 0;
            if ((detached = this->attached_to())) {
                mp_size_t mpsize = 0;
                if (bytes <= (mpsize = mpz_get_msb(to, bytes, detached))) {
                    size = mpsize;
                }
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
    virtual operator MP_INT* () const {
        return this->attached_to();
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create(unsigned initialValue = 0) {
        if ((this->destroyed())) {
            MP_INT* detached = 0;
            if ((detached = this->attach_created(&m_value))) {
                mpz_init_set_ui(detached, initialValue);
                return true;
            }
        }
        return false;
    }
    virtual bool destroy() {
        MP_INT* detached = 0;
        if ((detached = this->detach())) {
            mpz_clear(detached);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    MP_INT m_value;
};

} // namespace mp 
} // namespace prime 
} // namespace random 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RANDOM_PRIME_MP_NUMBER_HPP 
