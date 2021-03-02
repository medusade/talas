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
///   File: method.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_XTTP_REQUEST_METHOD_HPP
#define TALAS_PROTOCOL_XTTP_REQUEST_METHOD_HPP

#include "talas/protocol/xttp/message/part.hpp"
#include "talas/protocol/http/request/method/which.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace request {

namespace extended {
/// class methodt
template 
<typename TWhich = int, TWhich VNone = 0, 
 TWhich VHttpGET = http::request::method::GET, class THttpWhich = http::request::method::which,
 class TExtends = message::part, class TImplements = typename TExtends::implements>
class exported methodt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef methodt derives;

    typedef TWhich which_t;
    enum { none = VNone };

    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    methodt(const string_t &copy): extends(copy), which_(none) {
    }
    methodt(const char_t* chars, size_t length): extends(chars, length), which_(none) {
    }
    methodt(const char_t* chars): extends(chars), which_(none) {
    }
    methodt(which_t which): which_(which) {
    }
    methodt(const methodt& copy): extends(copy), which_(copy.which_) {
    }
    methodt(): which_(none) {
    }
    virtual ~methodt() {
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
                if ((' ' != c) && ('\r' != c) && ('\n' != c)) {
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

    /// combine / separate
    virtual bool combine() {
        bool success = true;
        set_name();
        return success;
    }
    virtual bool separate() {
        bool success = true;
        set_which();
        return success;
    }

    /// set
    using extends::set;
    virtual derives& set(const methodt& to) {
        which_ = to.which_;
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
        this->assign(name_of_chars(which_ = default_which()));
        return *this;
    }

    /// ...name / ...which
    virtual string_t set_name() {
        string_t name(name_of_chars(which_));
        this->assign(name);
        return name;
    }
    virtual which_t set_which() {
        which_ = of_name(this->chars());
        return which_;
    }
    virtual which_t which() const {
        return which_;
    }

    /// ...of...
    virtual which_t of_name(const string_t& name) const {
        return of_name(name.chars());
    }
    virtual which_t of_name(const char_t* name) const {
        return none;
    }
    virtual string_t name_of(which_t which) const {
        string_t name(name_of_chars(which));
        return name;
    }
    virtual const char_t* name_of_chars(which_t which) const {
        return default_name_chars();
    }

    /// ...name_chars / ...which
    virtual const char_t* GET_name_chars() const {
        return THttpWhich::name_of(VHttpGET);
    }
    virtual const char_t* default_name_chars() const {
        return GET_name_chars();
    }
    virtual which_t default_which() const {
        return none;
    }

protected:
    which_t which_;
}; /// class methodt
typedef methodt<> method;
} /// namespace extended

/// class methodt
template <class TExtends = extended::method, class TImplements = typename TExtends::implements>
class exported methodt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef methodt derives;

    typedef typename extends::which_t which_t;
    enum { none = extends::none };

    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    methodt(const string_t &copy): extends(copy) {
        this->separate();
    }
    methodt(const char_t* chars, size_t length): extends(chars, length) {
        this->separate();
    }
    methodt(const char_t* chars): extends(chars) {
        this->separate();
    }
    methodt(which_t which): extends(which) {
        this->combine();
    }
    methodt(const extends& copy): extends(copy) {
    }
    methodt(const methodt& copy): extends(copy) {
    }
    methodt() {
        this->combine();
    }
    virtual ~methodt() {
    }
}; /// class methodt
typedef methodt<> method;
    
} /// namespace request
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_REQUEST_METHOD_HPP 
