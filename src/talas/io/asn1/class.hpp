///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2019 $organization$
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
///   File: class.hpp
///
/// Author: $author$
///   Date: 3/29/2019
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_IO_ASN1_CLASS_HPP
#define _TALAS_IO_ASN1_CLASS_HPP

#include "talas/io/asn1/base.hpp"

namespace talas {
namespace io {
namespace asn1 {

typedef base_t::Implements classt_implements;
typedef base_t classt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: classt
///////////////////////////////////////////////////////////////////////
template <class TImplements = classt_implements, class TExtends = classt_extends>
class _EXPORT_CLASS classt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef classt Derives;

    typedef int value_t;
    enum {
        Bit         = (6),
        Undefined   = (-1),
        Universal   = (0),
        Application = (1 << Bit),
        Context     = (2 << Bit),
        Private     = (3 << Bit),    
        Mask        = (3 << Bit)
    };
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    classt(const classt& copy): m_value(copy.value()), m_name(copy.name()) {
    }
    classt(value_t value = Universal): m_value(value), m_name(name_of(value)) {
    }
    virtual ~classt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual value_t set_value(value_t to) {
        set_name(name_of(to));
        return m_value = to;
    }
    virtual value_t value() const {
        return m_value;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* set_name(const char* to) {
        return m_name = to;
    }
    virtual const char* name() const {
        return m_name;
    }
    static const char* name_of(value_t ofValue) {
        static const char* name = "undefined";
        switch(ofValue) {
        case Universal:
            return "Universal";

        case Application:
            return "Application";

        case Context:
            return "Context";

        case Private:
            return "Private";
        }
        return name;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    value_t m_value;
    const char* m_name;
}; /// class _EXPORT_CLASS classt

typedef classt<> class_t;

} /// namespace asn1
} /// namespace io
} /// namespace talas

#endif /// ndef _TALAS_IO_ASN1_CLASS_HPP
