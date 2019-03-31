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
///   File: type.hpp
///
/// Author: $author$
///   Date: 3/29/2019
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_IO_ASN1_TYPE_HPP
#define _TALAS_IO_ASN1_TYPE_HPP

#include "talas/io/asn1/form.hpp"
#include "talas/io/asn1/class.hpp"
#include "talas/io/asn1/base.hpp"

namespace talas {
namespace io {
namespace asn1 {

typedef base_t::Implements typet_implements;
typedef base_t typet_extends;
///////////////////////////////////////////////////////////////////////
///  Class: typet
///////////////////////////////////////////////////////////////////////
template <class TImplements = typet_implements, class TExtends = typet_extends>
class _EXPORT_CLASS typet: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef typet Derives;

    typedef int value_t;
    enum {
        Bit             = (0),
        Undefined       = (-1),
        Any             = (0),
        Boolean         = (1),
        Integer         = (2),
        BitString       = (3),
        OctetString     = (4),
        Null            = (5),
        ObjectID        = (6),
        Object          = (7),
        External        = (8),
        Real            = (9),
        Enum            = (10),
        Sequence        = (16),
        Set             = (17),
        NumericString   = (18),
        PrintableString = (19),
        TeletexString   = (20),
        VideotexString  = (21),
        IA5String       = (22),
        UTCTime         = (23),
        GeneralizedTime = (24),
        GraphicString   = (25),
        VisibleString   = (26),
        GeneralString   = (27),
        Mask            = (31)
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    typet(const typet& copy)
    : m_value(copy.value()), m_name(copy.name()), 
      m_form(copy.form_value()), m_class(copy.class_value()) {
    }
    typet
    (value_t value = Any, 
     form_t::value_t formValue = form_t::Primative,
     class_t::value_t classValue = class_t::Universal)
    : m_value(value), m_name(name_of(value)), 
      m_form(formValue), m_class(classValue) {
    }
    virtual ~typet() {
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(io::byte_reader& reader) {
        ssize_t count = 0;
        byte_t byte = 0;
        if (0 < (count = reader.read(&byte, 1))) {
            m_form.set_value(byte & form_t::Mask);
            m_class.set_value(byte & class_t::Mask);
            set_value(byte & Mask);
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual typet& copy(const typet& copy) {
        set(copy.value(), copy.form_value(), copy.class_value());
        *this;
    }
    virtual value_t set
    (value_t toValue, form_t::value_t toFormValue, class_t::value_t toClassValue) {
        m_class.set_value(toClassValue);
        m_form.set_value(toFormValue);
        return set_value(toValue);
    }
    virtual class_t::value_t class_value() const {
        return m_class.value();
    }
    virtual form_t::value_t form_value() const {
        return m_form.value();
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
        static const char* name0[] = {
            "Any",
            "Boolean",
            "Integer",
            "BitString",
            "OctetString",
            "Null",
            "ObjectID",
            "Object",
            "External",
            "Real",
            "Enum"
         };
        static const char* name1[] = {
            "Sequence",
            "Set",
            "NumericString",
            "PrintableString",
            "TeletexString",
            "VideotexString",
            "IA5String",
            "UTCTime",
            "GeneralizedTime",
            "GraphicString",
            "VisibleString",
            "GeneralString"
         };
        static const char* name = "undefined";

        if ((ofValue >= Any) && (ofValue <= Enum)) {
            name = name0[ofValue - Any];
        } else {
            if ((ofValue >= Sequence) && (ofValue <= GeneralString)) {
                name = name1[ofValue - Sequence];
            }
        }
        return name;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    value_t m_value;
    const char* m_name;
    asn1::form_t m_form;
    asn1::class_t m_class;
}; /// class _EXPORT_CLASS typet

typedef typet<> type_t;

} /// namespace asn1
} /// namespace io
} /// namespace talas

#endif /// ndef _TALAS_IO_ASN1_TYPE_HPP
