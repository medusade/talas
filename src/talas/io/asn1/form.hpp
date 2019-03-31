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
///   File: form.hpp
///
/// Author: $author$
///   Date: 3/29/2019
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_IO_ASN1_FORM_HPP
#define _TALAS_IO_ASN1_FORM_HPP

#include "talas/io/asn1/base.hpp"

namespace talas {
namespace io {
namespace asn1 {

typedef base_t::Implements formt_implements;
typedef base_t formt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: formt
///////////////////////////////////////////////////////////////////////
template <class TImplements = formt_implements, class TExtends = formt_extends>
class _EXPORT_CLASS formt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef formt Derives;

    typedef int value_t;
    enum {
        Bit       = (5),
        Undefined = (-1),
        Primative = (0),
        Construct = (1 << Bit),
        Mask      = (1 << Bit)
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    formt(const formt& copy): m_value(copy.value()), m_name(copy.name()) {
    }
    formt(value_t value = Primative): m_value(value), m_name(name_of(value)) {
    }
    virtual ~formt() {
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
        case Primative:
            return "Primative";

        case Construct:
            return "Construct";
        }
        return name;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    value_t m_value;
    const char* m_name;
}; /// class _EXPORT_CLASS formt

typedef formt<> form_t;

} /// namespace asn1
} /// namespace io
} /// namespace talas

#endif /// ndef _TALAS_IO_ASN1_FORM_HPP
