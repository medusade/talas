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
///   File: block.hpp
///
/// Author: $author$
///   Date: 3/29/2019
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_IO_ASN1_BLOCK_HPP
#define _TALAS_IO_ASN1_BLOCK_HPP

#include "talas/io/asn1/length.hpp"
#include "talas/io/asn1/type.hpp"
#include "talas/io/asn1/form.hpp"
#include "talas/io/asn1/class.hpp"
#include "talas/io/asn1/base.hpp"

namespace talas {
namespace io {
namespace asn1 {

typedef base_t::Implements blockt_implements;
typedef base_t blockt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: blockt
///////////////////////////////////////////////////////////////////////
template <class TImplements = blockt_implements, class TExtends = blockt_extends>
class _EXPORT_CLASS blockt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef blockt Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    blockt(const blockt& copy) {
    }
    blockt() {
    }
    virtual ~blockt() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(io::byte_reader& reader) {
        ssize_t count = 0, amount = 0;
        if (0 < (count = m_type.read(reader))) {
            if (0 >= (amount = m_length.read(reader))) {
                return amount;
            } else {
                count += amount;
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual class_t::value_t class_value() const {
        return (m_type.class_value());
    }
    virtual form_t::value_t form_value() const {
        return (m_type.form_value());
    }
    virtual type_t::value_t type_value() const {
        return (m_type.value());
    }
    virtual const char* type_name() const {
        return (m_type.name());
    }
    virtual size_t length() const {
        return (m_length.value());
    }
    virtual size_t size() const {
        return (m_length.value()+m_length.size()+m_type.size());
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    asn1::type_t m_type;
    asn1::length_t m_length;
}; /// class _EXPORT_CLASS blockt

typedef blockt<> block_t;

} /// namespace asn1
} /// namespace io
} /// namespace talas

#endif /// ndef _TALAS_IO_ASN1_BLOCK_HPP
