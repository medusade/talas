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
///   File: reason.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_XTTP_RESPONSE_REASON_HPP
#define TALAS_PROTOCOL_XTTP_RESPONSE_REASON_HPP

#include "talas/protocol/xttp/message/part.hpp"
#include "talas/protocol/xttp/response/status.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace response {

namespace extended {
/// class reasont
template 
<typename TStatus = status,  typename TWhich = typename TStatus::which_t, TWhich VNone = TStatus::none, 
 class TExtends = message::part, class TImplements = typename TExtends::implements>
class exported reasont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef reasont derives;

    typedef TStatus status_t;
    typedef TWhich which_t;
    enum { none = VNone };
    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    reasont(const string_t& chars): extends(chars), which_(none) {
    }
    reasont(const char_t* chars, size_t length): extends(chars, length), which_(none) {
    }
    reasont(const char_t* chars): extends(chars), which_(none) {
    }
    reasont(const status_t& status): which_(status.which()) {
    }
    reasont(const which_t& which): which_(which) {
    }
    reasont(const reasont& copy): extends(copy), which_(copy.which_) {
    }
    reasont(): which_(none) {
    }
    virtual ~reasont() {
    }

    /// set
    using extends::set;
    virtual derives& set(const status_t& to) {
        set(to.which());
        return *this;
    }
    virtual derives& set(const which_t& to) {
        which_ = to;
        set_name();
        return *this;
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
    virtual const char_t* default_name_chars() const {
        return "OK";
    }
    virtual which_t default_which() const {
        return none;
    }

protected:
    which_t which_;
}; /// class reasont
typedef reasont<> reason;
} /// namespace extended

/// class reasont
template 
<class TExtends = extended::reason, class TImplements = typename TExtends::implements>
class exported reasont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef reasont derives;

    typedef typename extends::status_t status_t;
    typedef typename extends::which_t which_t;
    enum { none = extends::none };
    typedef typename extends::part_t part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    reasont(const string_t& chars): extends(chars) {
        this->set_which();
    }
    reasont(const char_t* chars, size_t length): extends(chars, length) {
        this->set_which();
    }
    reasont(const char_t* chars): extends(chars) {
        this->set_which();
    }
    reasont(status_t status): extends(status) {
        this->set_name();
    }
    reasont(which_t which): extends(which) {
        this->set_name();
    }
    reasont(const reasont& copy): extends(copy) {
    }
    reasont() {
        this->set_default();
    }
    virtual ~reasont() {
    }
}; /// class reasont
typedef reasont<> reason;

} /// namespace response
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_RESPONSE_REASON_HPP 
