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
///   File: private_key.hpp
///
/// Author: $author$
///   Date: 2/11/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DH_MP_PRIVATE_KEY_HPP
#define _TALAS_CRYPTO_DH_MP_PRIVATE_KEY_HPP

#include "talas/crypto/dh/mp/public_key.hpp"
#include "talas/crypto/dh/private_key.hpp"

namespace talas {
namespace crypto {
namespace dh {
namespace mp {

///////////////////////////////////////////////////////////////////////
///  Class: private_keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = dh::private_key_implements, 
 class TExtends = dh::private_keyt<dh::private_key_implements, key> >

class _EXPORT_CLASS private_keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    private_keyt
    (const dh::public_key_implements& public_key,
     const byte_t* exponent, size_t expbytes) {
        if (!(this->create(public_key, exponent, expbytes))) {
            const creator_exception e = failed_to_create;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_create)...")
            throw(e);
        }
    }
    private_keyt() {
    }
    virtual ~private_keyt() {
        if (!(this->destroyed())) {
            const creator_exception e = failed_to_destroy;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_destroy)...")
            throw(e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create
    (const dh::public_key_implements& public_key,
     const byte_t* exponent, size_t expbytes) {
        if ((exponent) && (expbytes)) {
            public_key_implemented* pub = 0;

            if ((pub = public_key.mp_key_implemented())) {
                size_t genbytes = 0, modbytes = 0;
                MP_INT *g = 0, *n = 0;

                if ((g = pub->g()) && (genbytes = pub->genbytes()) 
                    && (n = pub->n()) && (modbytes = pub->modbytes())) {

                    if ((Implements::create(genbytes, modbytes, expbytes))) {
                        
                        TALAS_LOG_DEBUG("::mpz_set(&this->g_, g)...");
                        ::mpz_set(&this->g_, g);
                        
                        TALAS_LOG_DEBUG("::mpz_set(&this->n_, n)...");
                        ::mpz_set(&this->n_, n);
                        
                        if ((pub->create_secret_msb(&this->x_, exponent, expbytes))) {
                            return true;
                        }
                        Implements::destroy();
                    }
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef private_keyt<> private_key;
typedef private_key::Implements private_key_implements;

} // namespace mp 
} // namespace dh 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DH_MP_PRIVATE_KEY_HPP 
