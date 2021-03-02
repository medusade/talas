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
#ifndef TALAS_PROTOCOL_HTTP_CONTENT_TYPE_NAME_HPP
#define TALAS_PROTOCOL_HTTP_CONTENT_TYPE_NAME_HPP

#include "talas/protocol/http/content/type/which.hpp"
#include "talas/protocol/http/content/media/type/name.hpp"
#include "talas/protocol/http/content/media/subtype/name.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace content {
namespace type {

/// class namet
template <class TExtends = message::part, class TImplements = typename TExtends::implements>
class exported namet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef namet derives;

    typedef media::type::which type_which_t;
    typedef media::type::name type_name_t;
    typedef media::subtype::which subtype_which_t;
    typedef media::subtype::name subtype_name_t;
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
        set_name();
        separate();
    }
    namet(const namet& copy): extends(copy), which_(copy.which_) {
    }
    namet(): which_(none) {
        set_name();
        separate();
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

    /// combine / separate
    virtual bool combine() {
        bool success = false;
        const char_t *type_name = 0, *subtype_name = 0;

        this->clear();
        if ((type_name = type_name_.has_chars())
            && (subtype_name = subtype_name_.has_chars())) {
            this->assign(type_name);
            this->append("/");
            this->append(subtype_name);
            return true;
        }
        return success;
    }
    virtual bool separate() {
        bool success = false;
        const char_t* chars = 0;
        size_t length = 0;

        set_defaults();
        if ((chars = this->has_chars(length))) {
            char_t c = 0;
            const char_t* end = chars + length;
            string_t *part = 0, type_name, subtype_name;

            for (part = &type_name; chars != end; ++chars) {
                if ('/' != (c = *chars)) {
                    part->append(&c, 1);
                } else {
                    if (part != &subtype_name) {
                        if (type_name.has_chars()) {
                            // ?'/'
                            part = &subtype_name;
                        } else {
                            // '/'
                            return false;
                        }
                    } else {
                        // ?'/'*'/'
                        return false;
                    }
                }
            }
            if ((type_name.has_chars()) && (subtype_name.has_chars())) {
                // ?'/'?
                type_name_.set(type_name);
                subtype_name_.set(subtype_name);
                success = true;
            }
        }
        return success;
    }

    /// set_default...
    virtual derives& set_default() {
        this->clear();
        set_defaults();
        this->assign(name_of_chars(which_ = default_which()));
        return *this;
    }
    virtual derives& set_defaults() {
        type_name_.set_default();
        subtype_name_.set_default();
        return *this;
    }

    /// ...name / ...which
    virtual string_t set_name() {
        const char_t* chars = name_of_chars(which_);
        string_t name(chars);
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

    /// ...type_name / ...type_which
    virtual type_name_t& type_name() const {
        return (type_name_t&)type_name_;
    }
    virtual type_which_t type_which() const {
        type_name_t& type_name = this->type_name();
        return type_name.which();
    }
    virtual subtype_name_t& subtype_name() const {
        return (subtype_name_t&)subtype_name_;
    }
    virtual subtype_which_t subtype_which() const {
        subtype_name_t& subtype_name = this->subtype_name();
        return subtype_name.which();
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
    type_name_t type_name_;
    subtype_name_t subtype_name_;
}; /// class namet
typedef namet<> name;

} /// namespace type
} /// namespace content
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_CONTENT_TYPE_NAME_HPP 
