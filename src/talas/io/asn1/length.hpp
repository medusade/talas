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
///   File: length.hpp
///
/// Author: $author$
///   Date: 3/29/2019
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_IO_ASN1_LENGTH_HPP
#define _TALAS_IO_ASN1_LENGTH_HPP

#include "talas/io/asn1/base.hpp"

namespace talas {
namespace io {
namespace asn1 {

typedef base_t::Implements lengtht_implements;
typedef base_t lengtht_extends;
///////////////////////////////////////////////////////////////////////
///  Class: lengtht
///////////////////////////////////////////////////////////////////////
template <class TImplements = lengtht_implements, class TExtends = lengtht_extends>
class _EXPORT_CLASS lengtht: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef lengtht Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    lengtht(const lengtht& copy)
    : m_value(copy.m_value), m_size(copy.m_size), m_isIndefinite(copy.m_isIndefinite) {
    }
    lengtht(size_t value = 0, byte_t size = 0, bool isIndefinite = false)
    : m_value(value), m_size(size), m_isIndefinite(isIndefinite) {
    }
    virtual ~lengtht() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t read(io::byte_reader& reader) {
        ssize_t count = 0, amount = 0;
        byte_t bytes = 0, byte = 0;

        if (0 < (count = reader.read(&byte, 1))) {
            m_isIndefinite = false;
            m_size = 1;

            if (byte < 128) {
                m_value = byte;
             } else {
                m_value = 0;

                if (byte > 128) {
                    for (bytes = (byte & 127); (bytes > 0); --bytes, ++m_size, ++count) {
                        if  (0 >= (amount = reader.read(&byte, 1))) {
                            return amount;
                        }
                        m_value = (m_value << 8) | byte;
                    }
                } else {
                    m_isIndefinite = true;
                }
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual lengtht& copy(const lengtht& copy) {
        m_value = copy.value();
        m_size = copy.size();
        m_isIndefinite = copy.isIndefinite();
        *this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool isIndefinite() const {
        return m_isIndefinite;
    }
    virtual size_t value() const {
        return m_value;
    }
    virtual size_t size() const {
        return m_size;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    bool m_isIndefinite;
    size_t m_value;
    size_t m_size;
}; /// class _EXPORT_CLASS lengtht

typedef lengtht<> length_t;

} /// namespace asn1
} /// namespace io
} /// namespace talas

#endif /// ndef _TALAS_IO_ASN1_LENGTH_HPP
