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
///   File: key.hpp
///
/// Author: $author$
///   Date: 5/12/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_RSA_MP_KEY_HPP
#define _TALAS_CRYPTO_RSA_MP_KEY_HPP

#include "talas/crypto/rsa/key.hpp"
#include "mpz_msb.h"

namespace talas {
namespace crypto {
namespace rsa {
namespace mp {

typedef MP_INT mpint_t;
typedef MP_INT BIGPRIME;
typedef MP_INT BIGINT;

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
    keyt() {
    }
    virtual ~keyt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create(size_t modbytes, size_t expbytes) {
        if ((this->destroyed())) {
            if ((Extends::create(modbytes, expbytes))) {

                TALAS_LOG_DEBUG("mpz_init_set_ui(&m_temp,0)...");
                mpz_init_set_ui(&m_temp,0);
                return true;
                Extends::destroy();
            }
        }
        return false;
    }
    virtual bool create(size_t pbytes) {
        if ((this->destroyed())) {
            if ((Extends::create(pbytes))) {

                TALAS_LOG_DEBUG("mpz_init_set_ui(&m_temp,0)...");
                mpz_init_set_ui(&m_temp,0);
                return true;
                Extends::destroy();
            }
        }
        return false;
    }
    virtual bool destroy() {
        if ((this->is_created())) {
            bool success = true;

            TALAS_LOG_DEBUG("mpz_clear(&m_temp)...");
            mpz_clear(&m_temp);
            if (!(Extends::destroy())) {
                success = false;
            }
            return success;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    MP_INT m_temp;
};
typedef keyt<> key;

} // namespace mp 
} // namespace rsa 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_RSA_MP_KEY_HPP 
