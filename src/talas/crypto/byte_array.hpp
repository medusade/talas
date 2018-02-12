///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2015 $organization$
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
///   File: byte_array.hpp
///
/// Author: $author$
///   Date: 5/13/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_BYTE_ARRAY_HPP
#define _TALAS_CRYPTO_BYTE_ARRAY_HPP

#include "talas/crypto/base.hpp"
#include "xos/base/array.hpp"

namespace talas {
namespace crypto {

typedef uint64_t unsigned_value_t;
typedef xos::base::byte_array byte_array_extends;
///////////////////////////////////////////////////////////////////////
///  Class: byte_array
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS byte_array: public byte_array_extends {
public:
    typedef byte_array_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    byte_array(const byte_array_extends& value) {
        this->append(value.elements(), value.length());
    }
    byte_array(const string_t& value) {
        this->set_size(value.length());
        this->append(value);
    }
    byte_array(unsigned_value_t value, size_t size, size_t length) {
        this->set_size(size*length);
        this->append(value, size, length);
    }
    byte_array(unsigned_value_t value, size_t size) {
        this->set_size(size);
        this->append(value, size, 1);
    }
    byte_array(size_t size) {
        this->set_size(size);
    }
    byte_array() {
    }
    virtual ~byte_array() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::assign;
    virtual size_t assign(const byte_array_extends& value) {
        return this->assign(value.elements(), value.length());
    }
    virtual size_t assign(const string_t& value) {
        return this->assign((const byte_t*)value.chars(), value.length());
    }
    virtual size_t assign(unsigned_value_t value, size_t size, size_t length) {
        this->set_length(0);
        this->set_size(size*length);
        return this->append(value, size, length);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::append;
    virtual size_t append(const byte_array_extends& value) {
        return this->append(value.elements(), value.length());
    }
    virtual size_t append(const string_t& value) {
        return this->append((const byte_t*)value.chars(), value.length());
    }
    virtual size_t append(unsigned_value_t value, size_t size, size_t length) {
        size_t count = 0;
        for (size_t amount = 0; length; --length, count += amount) {
            amount = this->append_msb(value, size);
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t assign_lsb(unsigned_value_t value, size_t size) {
        this->set_length(0);
        this->set_size(size);
        return this->append_lsb(value, size);
    }
    virtual size_t assign_msb(unsigned_value_t value, size_t size) {
        this->set_length(0);
        this->set_size(size);
        return this->append_msb(value, size);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t append_lsb(unsigned_value_t value, size_t size) {
        size_t i = 0;
        byte_t b = 0;
        for (i = 0; i < size; ++i, value >>= 8) {
            b = (value & 255);
            this->append(&b, 1);
        }
        return size;
    }
    virtual size_t append_msb(unsigned_value_t value, size_t size) {
        unsigned_value_t msb = 0;
        size_t i = 0;
        byte_t b = 0;
        for (i = 0; i < size; ++i, value >>= 8) {
            (msb <<= 8) |= (value & 255);
        }
        return this->append_lsb(msb, size);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t appendx(const string_t& value) {
        return this->appendx(value.chars(), value.length());
    }
    virtual size_t appendx(const char* chars, size_t length) {
        if ((chars) && (length)) {
            size_t bytes = 0, nibbles = 0;
            byte_t byte = 0, nibble = 0;
            char x = 0;
            do {
                x = chars[nibbles];
                nibble = xtod(x);
                byte = ((byte << 4) | (nibble & 15));
                if ((nibbles++) & 1) {
                    this->append(&byte, 1);
                    byte = 0;
                }
            } while (--length);
            return bytes;
        }
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    inline byte_t xtod(char x) {
        byte_t d = 0;
        if (((char_t)('A') <= x) && ((char_t)('F') >= x)) {
            d = (byte_t)((x - (char_t)('A')) + 10);
        } else {
            if (((char_t)('a') <= x) && ((char_t)('f') >= x)) {
                d = (byte_t)((x - (char_t)('a')) + 10);
            } else {
                if (((char_t)('0') <= x) && ((char_t)('9') >= x)) {
                    d = (byte_t)((x - (char_t)('0')));
                }
            }
        }
        return d;
    }
};

typedef byte_array hex_to_byte_array_extends;
///////////////////////////////////////////////////////////////////////
///  Class: hex_to_byte_array
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS hex_to_byte_array: public hex_to_byte_array_extends {
public:
    typedef hex_to_byte_array_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    hex_to_byte_array(const string_t& value) {
        this->appendx(value);
    }
};

typedef byte_array lsbyte_array_extends;
///////////////////////////////////////////////////////////////////////
///  Class: lsbyte_array
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS lsbyte_array: public lsbyte_array_extends {
public:
    typedef lsbyte_array_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    lsbyte_array(const byte_array_extends& value) {
        this->append(value.elements(), value.length());
    }
    lsbyte_array(const string_t& value) {
        this->set_size(value.length());
        this->append(value);
    }
    lsbyte_array(unsigned_value_t value, size_t size, size_t length) {
        this->set_size(size*length);
        this->append(value, size, length);
    }
    lsbyte_array(unsigned_value_t value, size_t size) {
        this->set_size(size);
        this->append(value, size, 1);
    }
    lsbyte_array(size_t size) {
        this->set_size(size);
    }
    lsbyte_array() {
    }
    virtual ~lsbyte_array() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::append;
    virtual size_t append(unsigned_value_t value, size_t size, size_t length) {
        size_t count = 0;
        for (size_t amount = 0; length; --length, count += amount) {
            amount = this->append_lsb(value, size);
        }
        return count;
    }
};

typedef lsbyte_array hex_to_lsbyte_array_extends;
///////////////////////////////////////////////////////////////////////
///  Class: hex_to_lsbyte_array
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS hex_to_lsbyte_array: public hex_to_lsbyte_array_extends {
public:
    typedef hex_to_lsbyte_array_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    hex_to_lsbyte_array(const string_t& value) {
        this->appendx(value);
    }
};

} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_BYTE_ARRAY_HPP 
