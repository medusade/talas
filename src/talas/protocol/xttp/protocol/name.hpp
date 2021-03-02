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
#ifndef TALAS_PROTOCOL_XTTP_PROTOCOL_NAME_HPP
#define TALAS_PROTOCOL_XTTP_PROTOCOL_NAME_HPP

#include "talas/protocol/xttp/message/part.hpp"
#include "talas/protocol/http/protocol/which.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace protocol {

namespace extended {
/// class namet
template 
<class THttpWhich = http::protocol::which,
 class TExtends = message::part, class TImplements = typename TExtends::implements>
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
    namet(const string_t &copy): extends(copy) {
    }
    namet(const char_t* chars, size_t length): extends(chars, length) {
    }
    namet(const char_t* chars): extends(chars) {
    }
    namet(const namet& copy): extends(copy) {
    }
    namet() {
    }
    virtual ~namet() {
    }

    /// read / write
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;
        ssize_t amount = 0;
        string_t chars;
        
        this->set_default();
        do {
            if (0 < (amount = reader.read(&c, 1))) {
                count += amount;
                if (('/' != c) && (' ' != c) && ('\r' != c) && ('\n' != c)) {
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
            success = true;
        }
        return success;
    }
    virtual bool write(ssize_t& count, writer_t& writer) {
        bool success = this->write_this(count, writer);
        return success;
    }

    /// set
    using extends::set;
    virtual derives& set(const namet& to) {
        this->assign(to);
        return *this;
    }

    /// set_default...
    virtual derives& set_default() {
        this->clear();
        set_defaults();
        return *this;
    }
    virtual derives& set_defaults() {
        this->assign(default_name_chars());
        return *this;
    }

    /// ...name_chars
    virtual const char_t* default_name_chars() const {
        return THttpWhich::name_of();
    }
}; /// class namet
typedef namet<> name;
} /// namespace extended

/// class namet
template <class TExtends = protocol::extended::name, class TImplements = typename TExtends::implements>
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
    namet(const string_t &copy): extends(copy) {
    }
    namet(const char_t* chars, size_t length): extends(chars, length) {
    }
    namet(const char_t* chars): extends(chars) {
    }
    namet(const namet& copy): extends(copy) {
    }
    namet() {
        this->set_default();
    }
    virtual ~namet() {
    }
}; /// class namet
typedef namet<> name;

} /// namespace protocol
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_PROTOCOL_NAME_HPP 
