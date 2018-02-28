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
///   File: unsigned_integer.hpp
///
/// Author: $author$
///   Date: 2/27/2018
///////////////////////////////////////////////////////////////////////
#ifndef _NUMERA_MP_MP_UNSIGNED_INTEGER_HPP
#define _NUMERA_MP_MP_UNSIGNED_INTEGER_HPP

#include "numera/mp/unsigned_integer.hpp"
#include "mpz_msb.h"

namespace numera {
namespace mp {
namespace mp {

///////////////////////////////////////////////////////////////////////
///  Class: unsigned_integert
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = numera::mp::unsigned_integer_implement, 
 class TExtends = numera::mp::unsigned_integert<MP_INT*> >

class _EXPORT_CLASS unsigned_integert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef unsigned_integert unsigned_integer;
    typedef typename Extends::attached_t attached_t;
    typedef typename Extends::unattached_t unattached_t;
    enum { unattached = Extends::unattached };
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    unsigned_integert(const byte_t* msb, size_t msbsize) {
        this->init();
        if (!(this->create_msb(msb, msbsize))) {
            const creator_exception e = failed_to_create;
            this->fini();
            LOG_ERROR("...this->create(value = " << x_to_string(msb, msbsize) << ") failed throw(const creator_exception e = failed_to_create)...");
            throw(e);
        }
    }
    unsigned_integert(const unsigned& value) {
        this->init();
        if (!(this->create(value))) {
            const creator_exception e = failed_to_create;
            this->fini();
            LOG_ERROR("...this->create(value = " << value << ") failed throw(const creator_exception e = failed_to_create)...");
            throw(e);
        }
    }
    unsigned_integert(const unsigned_integert& copy) {
        this->init();
        if (!(this->create(copy))) {
            const creator_exception e = failed_to_create;
            this->fini();
            LOG_ERROR("...failed throw(const creator_exception e = failed_to_create)...");
            throw(e);
        }        
    }
    unsigned_integert() {
        this->init();
        if (!(this->create())) {
            const creator_exception e = failed_to_create;
            this->fini();
            LOG_ERROR("...failed throw(const creator_exception e = failed_to_create)...");
            throw(e);
        }        
    }
    virtual ~unsigned_integert() {
        if (!(this->destroyed())) {
            const creator_exception e = failed_to_destroy;
            this->fini();
            LOG_ERROR("...this->destroyed() failed throw(const creator_exception e = failed_to_destroy)...");
            throw(e);
        }
        this->fini();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create_msb(const byte_t* msb, size_t msbsize) {
        if ((msb) && (msbsize)) {
            if ((this->create())) {
                MP_INT* detached = 0;
                if ((detached = this->attached_to())) {
                    LOG_DEBUG("::mpz_set_msb(detached, msb = " << x_to_string(msb, msbsize) << ", msbsize = " << msbsize << ")...");
                    ::mpz_set_msb(detached, msb, msbsize);
                    return true;
                }
                this->destroy();
            }
        }
        return false;
    }
    virtual bool create(const unsigned& value) {
        if ((this->create())) {
            MP_INT* detached = 0;
            if ((detached = this->attached_to())) {
                LOG_DEBUG("::mpz_set_ui(detached, value = " << value << ")...");
                ::mpz_set_ui(detached, value);
                return true;
            }
            this->destroy();
        }
        return false;
    }
    virtual bool create(const unsigned_integert& copy) {
        return false;
    }
    virtual bool create() {
        if ((this->destroyed())) {
            MP_INT* detached = 0;
            LOG_DEBUG("detached = this->i()...");
            if ((detached = this->i())) {
                this->attach_created(detached);
                return true;
            } else {
                LOG_ERROR("...failed on detached = this->i()");
            }
        }
        return false;
    }
    virtual bool destroy() {
        bool success = true;
        MP_INT* detached = 0;
        if ((detached = this->detach())) {
            LOG_DEBUG("::mpz_set_ui(detached, 0)...");
            ::mpz_set_ui(detached, 0);
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    unsigned_integer& add
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        MP_INT* detached = 0, *c_ = 0, *b_ = 0, *a_ = 0;
        if ((detached = this->attached_to()) 
            && (c_ = c.attached_to())  && (b_ = b.attached_to()) && (a_ = a.attached_to())) {
            LOG_DEBUG("::mpz_add(c_, a_, b_)...");
            ::mpz_add(c_, a_, b_);
        }
        return (unsigned_integer&)(*this);
    }
    unsigned_integer& sub
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        MP_INT* detached = 0, *c_ = 0, *b_ = 0, *a_ = 0;
        if ((detached = this->attached_to()) 
            && (c_ = c.attached_to())  && (b_ = b.attached_to()) && (a_ = a.attached_to())) {
            LOG_DEBUG("::mpz_sub(c_, a_, b_)...");
            ::mpz_sub(c_, a_, b_);
        }
        return (unsigned_integer&)(*this);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    unsigned_integer& mul
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        MP_INT* detached = 0, *c_ = 0, *b_ = 0, *a_ = 0;
        if ((detached = this->attached_to()) 
            && (c_ = c.attached_to())  && (b_ = b.attached_to()) && (a_ = a.attached_to())) {
            LOG_DEBUG("::mpz_mul(c_, a_, b_)...");
            ::mpz_mul(c_, a_, b_);
        }
        return (unsigned_integer&)(*this);
    }
    unsigned_integer& div
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        MP_INT* detached = 0, *c_ = 0, *b_ = 0, *a_ = 0;
        if ((detached = this->attached_to())
            && (c_ = c.attached_to()) && (b_ = b.attached_to()) && (a_ = a.attached_to())) {
            LOG_DEBUG("::mpz_div(c_, a_, b_)...");
            ::mpz_div(c_, a_, b_);
        }
        return (unsigned_integer&)(*this);
    }
    unsigned_integer& mod
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        MP_INT* detached = 0, *c_ = 0, *b_ = 0, *a_ = 0;
        if ((detached = this->attached_to())
            && (c_ = c.attached_to())  && (b_ = b.attached_to()) && (a_ = a.attached_to())) {
            LOG_DEBUG("::mpz_mod(c_, a_, b_)...");
            ::mpz_mod(c_, a_, b_);
        }
        return (unsigned_integer&)(*this);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    unsigned_integer& mod_inv
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        MP_INT* detached = 0, *c_ = 0, *b_ = 0, *a_ = 0;
        if ((detached = this->attached_to())
            && (c_ = c.attached_to())  && (b_ = b.attached_to()) && (a_ = a.attached_to())) {
            LOG_DEBUG("::mpz_mod_inverse(c_, a_, b_)...");
            ::mpz_mod_inverse(c_, a_, b_);
        }
        return (unsigned_integer&)(*this);
    }
    unsigned_integer& mod_exp
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& e, const unsigned_integer& b) {
        MP_INT* detached = 0, *e_ = 0, *c_ = 0, *b_ = 0, *a_ = 0;
        if ((detached = this->attached_to())
            && (e_ = e.attached_to()) && (c_ = c.attached_to()) && (b_ = b.attached_to()) && (a_ = a.attached_to())) {
            LOG_DEBUG("::mpz_powm(c_, a_, e_, b_)...");
            ::mpz_powm(c_, a_, e_, b_);
        }
        return (unsigned_integer&)(*this);
    }
    unsigned_integer& exp
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        MP_INT* detached = 0, *c_ = 0, *b_ = 0, *a_ = 0;
        if ((detached = this->attached_to())
            && (c_ = c.attached_to())  && (b_ = b.attached_to()) && (a_ = a.attached_to())) {
        }
        return (unsigned_integer&)(*this);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_msb(const byte_t* msb, size_t msbsize) {
        if ((msb) && (msbsize)) {
            MP_INT* detached = 0;
            if ((detached = this->attached_to())) {
                LOG_DEBUG("::mpz_set_msb(detached, msb = " << x_to_string(msb, msbsize) << ", msbsize = " << msbsize << ")...");
                ::mpz_set_msb(detached, msb, msbsize);
                return msbsize;
            }
        }
        return 0;
    }
    virtual ssize_t get_msb(byte_t* msb, size_t msbsize) {
        if ((msb) && (msbsize)) {
            MP_INT* detached = 0;
            if ((detached = this->attached_to())) {
                ::mpz_get_msb(msb, msbsize, detached);
                LOG_DEBUG("...::mpz_get_msb(msb = " << x_to_string(msb, msbsize) << ", msbsize = " << msbsize << ", detached)");
                return msbsize;
            }
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void init() {
        LOG_DEBUG("::mpz_init(&i_)...");
        ::mpz_init(&i_);
        this->fini_ = true;
    }
    virtual void fini() {
        if ((this->fini_)) {
            LOG_DEBUG("::mpz_clear(&i_)...");
            ::mpz_clear(&i_);
            this->fini_ = false;
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual MP_INT* i() const {
        return (MP_INT*)&i_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool fini_;
    MP_INT i_;
};
typedef unsigned_integert<> unsigned_integer;

} // namespace mp 
} // namespace mp 
} // namespace numera 

#endif // _NUMERA_MP_MP_UNSIGNED_INTEGER_HPP 
