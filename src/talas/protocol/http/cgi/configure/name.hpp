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
///   File: name.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_HTTP_CGI_CONFIGURE_NAME_HPP
#define TALAS_PROTOCOL_HTTP_CGI_CONFIGURE_NAME_HPP

#include "talas/protocol/http/cgi/configure/which.hpp"
#include "talas/protocol/xttp/message/part.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace cgi {
namespace configure {

/// class namet
template <class TExtends = xttp::message::part, class TImplements = typename TExtends::implements>
class exported namet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef namet derives;

    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    namet(configure::which_t which): which_(which) {
        combine();
    }
    namet(const string_t& chars): extends(chars) {
        separate();
    }
    namet(const char_t* chars, size_t length): extends(chars, length) {
        separate();
    }
    namet(const char_t* chars): extends(chars) {
        separate();
    }
    namet(const namet& copy): extends(copy), which_(copy.which_) {
    }
    namet() {
    }
    virtual ~namet() {
    }

    /// set
    virtual bool is_set(configure::which_t to) {
        bool success = false;
        const char_t* chars = 0;
        this->clear();
        set_which(to);
        if ((chars = which_.name()) && (chars[0])) {
            this->assign(chars);
            success = true;
        }
        return success;
    }
    virtual bool is_set(const string_t& chars) {
        bool success = false;
        this->assign(chars);
        success = separate();
        return success;
    }
    virtual bool is_set(const char_t* chars, size_t length) {
        bool success = false;
        this->assign(chars, length);
        success = separate();
        return success;
    }
    virtual bool is_set(const char_t* chars) {
        bool success = false;
        this->assign(chars);
        success = separate();
        return success;
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
                if (('=' != c) && ('\r' != c) && ('\n' != c)) {
                    chars.append(&c, 1);
                } else {
                    break;
                }
            } else {
                count = amount;
                return false;
            }
        } while (0 < amount);
        if ((chars.has_chars())) {
            this->assign(chars);
            success = separate();
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
        const char_t* chars = 0;
        this->clear();
        if ((chars = which_.name()) && (chars[0])) {
            this->assign(chars);
            success = true;
        }
        return success;
    }
    virtual bool separate() {
        configure::which_t which = set_which();
        bool success = (configure::none != which);
        return success;
    }

    /// set_default...
    virtual derives& set_default() {
        this->clear();
        set_defaults();
        return *this;
    }
    virtual derives& set_defaults() {
        set_which(configure::none);
        return *this;
    }

    /// ...which
    virtual configure::which_t set_which() {
        which_ = this->chars();
        return (configure::which_t)which_;
    }
    virtual configure::which_t set_which(configure::which_t to) {
        which_ = to;
        return (configure::which_t)which_;
    }
    virtual configure::which_t which() const {
        return (configure::which_t)which_;
    }

protected:
    configure::which which_;
}; /// class namet
typedef namet<> name;

} /// namespace configure
} /// namespace cgi
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_CGI_CONFIGURE_NAME_HPP 
