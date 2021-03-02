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
#ifndef TALAS_PROTOCOL_XTTP_MESSAGE_HEADER_FIELD_HPP
#define TALAS_PROTOCOL_XTTP_MESSAGE_HEADER_FIELD_HPP

#include "talas/protocol/xttp/message/part.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace message {
namespace header {

namespace extended {
/// class fieldt
template <class TExtends = part, class TImplements = typename TExtends::implements>
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
    fieldt(const string_t& name, const string_t& value) {
    }
    fieldt(const string_t& chars): extends(chars) {
    }
    fieldt(const char_t* chars, size_t length): extends(chars, length) {
    }
    fieldt(const char_t* chars): extends(chars) {
    }
    fieldt(const fieldt& copy): extends(copy) {
    }
    fieldt() {
    }
    virtual ~fieldt() {
    }

    /// read / write
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;
        char_t cr = 0;
        ssize_t amount = 0;
        string_t chars;

        this->set_default();
        do {
            if (0 < (amount = reader.read(&c, 1))) {
                count += amount;
                if (('\r' != c)) {
                    if (('\n' != c)) {
                        chars.append(&c, 1);
                    } else {
                        success = this->is_set(chars);
                        break;
                    }
                } else {
                    if (cr != c) {
                        cr = c;
                    } else {
                        chars.append(&cr, 1);
                    }
                }
            } else {
                count = amount;
                break;
            }
        } while (0 < amount);
        return success;
    }
    virtual bool write(ssize_t& count, writer_t& writer) {
        bool success = false;
        const char_t* chars = 0;
        size_t length = 0;
        
        if ((chars = this->has_chars(length))) {
            ssize_t amount = 0;

            if (length <= (amount = writer.write(chars, length))) {
                count = amount;
                success = true;
            }
        }
        return success;
    }

    /// set
    using extends::set;
    virtual bool set(const string_t& name, const string_t& value) {
        bool success = true;
        const char_t* chars = 0;
        size_t length = 0;
        if ((chars = name.has_chars(length))) {
            name_.assign(chars, length);
            value_.assign(value);
            success = this->combine();
        }
        return success;
    }

    /// combine / separate
    virtual bool combine() {
        bool success = true;
        this->clear();
        if ((name_.has_chars())) {
            this->assign(name_);
            this->append(":");
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
                if (':' != (c = *chars)) {
                    if (' ' != (c)) {
                        part->append(&c, 1);
                    } else {
                        if ((part->has_chars())) {
                            part->append(&c, 1);
                        }
                    }
                } else {
                    if (part != &name) {
                        part->append(&c, 1);
                    } else {
                        if (name.has_chars()) {
                            // ?':'
                            part = &value;
                        } else {
                            // ':'
                            return false;
                        }
                    }
                }
            }
            if ((name.has_chars())) {
                name_.set(name);
                value_.set(value);
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
    virtual part_t& set_name(const string_t& s) {
        const char* chars = 0;
        size_t length = 0;
        if ((chars = s.has_chars(length))) {
            name_.assign(chars, length);
            this->combine();
        }
        return name_;
    }
    virtual part_t& set_name(const char_t* chars, size_t length) {
        if ((chars) && (0 < length)) {
            name_.assign(chars, length);
            this->combine();
        }
        return name_;
    }
    virtual part_t& set_name(const char_t* chars) {
        if ((chars) && (chars[0])) {
            name_.assign(chars);
            this->combine();
        }
        return name_;
    }
    virtual const part_t& name() const {
        return name_;
    }

    /// ...value
    virtual part_t& set_value(const string_t& s) {
        value_.assign(s);
        this->combine();
        return value_;
    }
    virtual part_t& set_value(const char_t* chars, size_t length) {
        value_.assign(chars, length);
        this->combine();
        return value_;
    }
    virtual part_t& set_value(const char_t* chars) {
        value_.assign(chars);
        this->combine();
        return value_;
    }
    virtual part_t& set_value() {
        value_.clear();
        this->combine();
        return value_;
    }
    virtual const message::part& value() const {
        return value_;
    }

protected:
    part_t name_, value_;
}; /// class fieldt
typedef fieldt<> field;
} /// namespace extended

/// class fieldt
template <class TExtends = extended::field, class TImplements = typename TExtends::implements>
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
    fieldt(const string_t& name, const string_t& value) {
        this->set(name, value);
    }
    fieldt(const string_t& chars): extends(chars) {
        this->separate();
    }
    fieldt(const char_t* chars, size_t length): extends(chars, length) {
        this->separate();
    }
    fieldt(const char_t* chars): extends(chars) {
        this->separate();
    }
    fieldt(const fieldt& copy): extends(copy) {
    }
    fieldt() {
        this->set_default();
    }
    virtual ~fieldt() {
    }
}; /// class fieldt
typedef fieldt<> field;

} /// namespace header
} /// namespace message
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_MESSAGE_HEADER_FIELD_HPP 
