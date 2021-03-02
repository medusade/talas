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
#ifndef TALAS_PROTOCOL_HTTP_CONTENT_MEDIA_TYPE_NAME_HPP
#define TALAS_PROTOCOL_HTTP_CONTENT_MEDIA_TYPE_NAME_HPP

#include "talas/protocol/http/content/media/type/which.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace content {
namespace media {
namespace type {

/// class namet
template <class TExtends = message::part, class TImplements = typename TExtends::implements>
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
    namet(const string_t &copy): extends(copy), which_(none) {
        separate();
    }
    namet(const char_t* chars, size_t length): extends(chars, length), which_(none) {
        separate();
    }
    namet(const char_t* chars): extends(chars), which_(none) {
        separate();
    }
    namet(which_t which): which_(which) {
        combine();
    }
    namet(const namet& copy): extends(copy), which_(copy.which_) {
    }
    namet(): which_(none) {
        combine();
    }
    virtual ~namet() {
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
        bool success = this->write_this(count, writer);
        return success;
    }

    /// set
    using extends::set;
    virtual derives& set(which_t which) {
        this->assign(name_of_chars(which));
        return *this;
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

    /// set_default...
    virtual derives& set_default() {
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
        return which::of_name(name);
    }
    virtual string_t name_of(which_t which) const {
        string name(name_of_chars(which));
        return name;
    }
    virtual const char_t* name_of_chars(which_t which) const {
        return which::name_of(which);
    }

    /// ...name_chars / ...which
    virtual const char_t* default_name_chars() const {
        return which::name_of_none();
    }
    virtual which_t default_which() const {
        return which::of_name_none();
    }

protected:
    which_t which_;
}; /// class namet
typedef namet<> name;

} /// namespace type
} /// namespace media
} /// namespace content
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_CONTENT_MEDIA_TYPE_NAME_HPP 
