///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2021 $organization$
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
///   File: field.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_HTTP_FORM_FIELD_HPP
#define TALAS_PROTOCOL_HTTP_FORM_FIELD_HPP

#include "talas/protocol/xttp/message/part.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace form {

/// class fieldt
template <class TExtends = xttp::message::part, class TImplements = typename TExtends::implements>
class exported fieldt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef fieldt derives;

    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    fieldt(const fieldt& copy): extends(copy) {
    }
    fieldt() {
    }
    virtual ~fieldt() {
    }

    /// read / write
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;
        ssize_t amount = 0;
        string_t chars;

        set_default();
        do {
            if (0 < (amount = reader.read(&c, 1))) {
                count += amount;
                if (('&' != c)) {
                    chars.append(&c, 1);
                } else {
                    success = this->is_set(chars);
                    break;
                }
            } else {
                if (0 > (amount)) {
                    count = amount;
                    break;
                } else {
                    success = this->is_set(chars);
                }
            }
        } while (0 < amount);
        return success;
    }
    virtual bool write(ssize_t& count, writer_t& writer) {
        bool success = false;
        success = this->write_this(count, writer);
        return success;
    }

    /// combine / separate
    virtual bool combine() {
        bool success = true;
        const char_t* chars = 0;
        size_t length = 0;

        this->clear();
        if ((chars = name_.has_chars(length))) {
            this->assign(chars, length);
            this->append("=");
            this->append(value_);
        }
        return success;
    }
    virtual bool separate() {
        bool success = true;
        const char_t* chars = 0;
        size_t length = 0;

        set_defaults();
        if ((chars = this->has_chars(length))) {
            char_t c = 0;
            const char_t* end = chars + length;
            string_t *part = 0, name, value;

            for (part = &name; chars != end; ++chars) {
                if ('=' != (c = *chars)) {
                    part->append(&c, 1);
                } else {
                    if (part != &name) {
                        part->append(&c, 1);
                    } else {
                        if (name.has_chars()) {
                            /// ?'='
                            part = &value;
                        } else {
                            /// '='
                            return false;
                        }
                    }
                }
            }
            if ((name.has_chars())) {
                name_.is_set(name);
                value_.is_set(value);
            } else {
                return false;
            }
        }
        return success;
    }

    /// set_default...
    virtual derives& set_default() {
        this->clear();
        set_defaults();
        return *this;
    }
    virtual derives& set_defaults() {
        name_.clear();
        value_.clear();
        return *this;
    }

    /// ...name
    virtual part_t& set_name(const string_t& to) {
        name_.is_set(to);
        return name_;
    }
    virtual part_t& set_name(const char_t* to, size_t length) {
        name_.is_set(to, length);
        return name_;
    }
    virtual part_t& set_name(const char_t* to) {
        name_.is_set(to);
        return name_;
    }
    virtual part_t& name() const {
        return (part_t&)name_;
    }
    
    /// ...value
    virtual part_t& set_value(const string_t& to) {
        value_.is_set(to);
        return value_;
    }
    virtual part_t& set_value(const char_t* to, size_t length) {
        value_.is_set(to, length);
        return value_;
    }
    virtual part_t& set_value(const char_t* to) {
        value_.is_set(to);
        return value_;
    }
    virtual part_t& value() const {
        return (part_t&)value_;
    }

protected:
    part_t name_, value_;
}; /// class fieldt
typedef fieldt<> field;

} /// namespace form
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_FORM_FIELD_HPP 
