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
///   File: setting.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_HTTP_CGI_CONFIGURE_SETTING_HPP
#define TALAS_PROTOCOL_HTTP_CGI_CONFIGURE_SETTING_HPP

#include "talas/protocol/http/cgi/configure/which.hpp"
#include "talas/protocol/http/cgi/configure/name.hpp"
#include "talas/protocol/http/cgi/configure/value.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace cgi {
namespace configure {

/// class settingt
template <class TExtends = xttp::message::part, class TImplements = typename TExtends::implements>
class exported settingt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef settingt derives;

    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef xos::charst<typename string_t::char_t> chars_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    settingt(configure::which_t which): name_(which), value_(which), which_(which) {
        combine();
    }
    settingt(configure::which_t which, const string_t& chars): name_(which), value_(which, chars), which_(which) {
        combine();
    }
    settingt(configure::which_t which, const char_t* chars, size_t length): name_(which), value_(which, chars, length), which_(which) {
        combine();
    }
    settingt(configure::which_t which, const char_t* chars): name_(which), value_(which, chars), which_(which) {
        combine();
    }
    settingt(const string_t& chars): extends(chars) {
    }
    settingt(const char_t* chars, size_t length): extends(chars, length) {
    }
    settingt(const char_t* chars): extends(chars) {
    }
    settingt(const settingt& copy): extends(copy) {
    }
    settingt() {
        set_default();
    }
    virtual ~settingt() {
    }

    /// read / write
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;
        if ((this->read_this(count, c, reader))) {
            if (!(success = separate())) {
                set_default();
            }
        }
        return success;
    }
    virtual bool write(ssize_t& count, writer_t& writer) {
        bool success = false;
        success = this->write_this(count, writer);
        return success;
    }

    /// combine / separate
    virtual bool combine() {
        bool success = false;
        const char* chars = 0;
        size_t length = 0;

        this->clear();
        if ((success = (chars = name_.has_chars(length)))) {
            this->append(chars, length);
            this->append("=", 1);
            if ((chars = value_.has_chars(length))) {
                this->append(chars, length);
            }
        }
        return success;
    }
    virtual bool separate() {
        bool success = false;
        const char_t* chars = 0;
        size_t length = 0;

        set_defaults();
        if ((chars = this->has_chars(length)) && (2 <= length)) {
            char_t c = 0;
            const char_t* end = chars + length;
            string_t *part = 0, name, value;
            
            for (part = &name; chars != end; ++chars) {
                if ('=' != (c = *chars)) {
                    part->append(&c, 1);
                } else {
                    if (part != &value) {
                        if (name.has_chars()) {
                            /// ?'='
                            part = &value;
                        } else {
                            /// '='
                            return false;
                        }
                    } else {
                        /// ?'='*'='
                        part->append(&c, 1);
                    }
                }
            }
            if ((chars = name.has_chars(length))) {
                /// ?'='
                name_.is_set(name);
                value_.is_set(name_.which());
                if ((chars = value.has_chars(length))) {
                    /// ?'='?
                    value_.is_set(value);
                }
                success = true;
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
        name_.is_set(configure::none);
        value_.is_set(configure::none);
        which_ = configure::none;
        return *this;
    }

    /// ...name / ...value / ...which
    virtual configure::name& name() const {
        return (configure::name&)name_;
    }
    virtual configure::value& value() const {
        return (configure::value&)value_;
    }
    virtual configure::which_t set_which(configure::which_t to) {
        which_ = to;
        name_.is_set(to);
        value_.is_set(to);
        return (configure::which_t)which_;
    }
    virtual configure::which_t which() const {
        return (configure::which_t)which_;
    }

protected:
    configure::name name_;
    configure::value value_;
    configure::which which_;
}; /// class settingt
typedef settingt<> setting;

} /// namespace configure
} /// namespace cgi
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_CGI_CONFIGURE_SETTING_HPP 
