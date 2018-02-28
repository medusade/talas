///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: unsigned_integer.hpp
///
/// Author: $author$
///   Date: 2/26/2018
///////////////////////////////////////////////////////////////////////
#ifndef _NUMERA_MP_UNSIGNED_INTEGER_HPP
#define _NUMERA_MP_UNSIGNED_INTEGER_HPP

#include "numera/base/base.hpp"

namespace numera {
namespace mp {

///////////////////////////////////////////////////////////////////////
///  Class: unsigned_integer_implementt
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = implement_base>

class _EXPORT_CLASS unsigned_integer_implementt: virtual public TImplements {
public:
    typedef TImplements Implements;
    typedef unsigned_integer_implementt unsigned_integer;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    unsigned_integer& add
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        return (unsigned_integer&)(*this);
    }
    unsigned_integer& sub
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        return (unsigned_integer&)(*this);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    unsigned_integer& mul
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        return (unsigned_integer&)(*this);
    }
    unsigned_integer& div
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        return (unsigned_integer&)(*this);
    }
    unsigned_integer& mod
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        return (unsigned_integer&)(*this);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    unsigned_integer& mod_inv
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        return (unsigned_integer&)(*this);
    }
    unsigned_integer& mod_exp
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& e, const unsigned_integer& b) {
        return (unsigned_integer&)(*this);
    }
    unsigned_integer& exp
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        return (unsigned_integer&)(*this);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef unsigned_integer_implementt<> unsigned_integer_implement;

///////////////////////////////////////////////////////////////////////
///  Class: unsigned_integert
///////////////////////////////////////////////////////////////////////
template
<typename TAttachedTo = unsigned_integer_implement*, 
 typename TUnattached = int, TUnattached VUnattached = 0,
 class TImplementBase = unsigned_integer_implement, class TBase = base,

 class TCreator = ::xos::base::creatort<TImplementBase>,

 class TAttacher = ::xos::base::attachert
 <TAttachedTo, TUnattached, VUnattached, TCreator>,

 class TAttached = ::xos::base::attachedt
 <TAttachedTo, TUnattached, VUnattached, TAttacher, TBase>,

 class TCreated = ::xos::base::createdt
 <TAttachedTo, TUnattached, VUnattached, TAttacher, TAttached>,

 class TImplements = TAttacher, class TExtends = TCreated>

class _EXPORT_CLASS unsigned_integert: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    typedef unsigned_integert unsigned_integer;
    typedef TAttachedTo attached_t;
    typedef TUnattached unattached_t;
    enum { unattached = VUnattached };
    
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
        return false;
    }
    virtual bool create(const unsigned& value) {
        return false;
    }
    virtual bool create(const unsigned_integert& copy) {
        return false;
    }
    virtual bool create() {
        return true;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    unsigned_integer& add
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        return (unsigned_integer&)(*this);
    }
    unsigned_integer& sub
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        return (unsigned_integer&)(*this);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    unsigned_integer& mul
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        return (unsigned_integer&)(*this);
    }
    unsigned_integer& div
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        return (unsigned_integer&)(*this);
    }
    unsigned_integer& mod
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        return (unsigned_integer&)(*this);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    unsigned_integer& mod_inv
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        return (unsigned_integer&)(*this);
    }
    unsigned_integer& mod_exp
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& e, const unsigned_integer& b) {
        return (unsigned_integer&)(*this);
    }
    unsigned_integer& exp
    (unsigned_integer& c, const unsigned_integer& a, const unsigned_integer& b) {
        return (unsigned_integer&)(*this);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_msb(const byte_t* msb, size_t msbsize) {
        return 0;
    }
    virtual ssize_t get_msb(byte_t* msb, size_t msbsize) {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void init() {
    }
    virtual void fini() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef unsigned_integert<> unsigned_integer;

} // namespace mp 
} // namespace numera 

#endif // _NUMERA_MP_UNSIGNED_INTEGER_HPP 
