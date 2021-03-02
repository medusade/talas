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
///   File: identifier.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_HTTP_REQUEST_RESOURCE_IDENTIFIER_HPP
#define TALAS_PROTOCOL_HTTP_REQUEST_RESOURCE_IDENTIFIER_HPP

#include "talas/protocol/http/request/resource/which.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace request {
namespace resource {

namespace extended { 
/// class identifiert
template <class TExtends = message::part, class TImplements = typename TExtends::implements>
class exported identifiert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef identifiert derives;
    
    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    identifiert(which_t which, const string_t& chars): extends(chars), which_(which) {
    }
    identifiert(which_t which, const char_t* chars, size_t length): extends(chars, length), which_(which) {
    }
    identifiert(which_t which, const char_t* chars): extends(chars), which_(which) {
    }
    identifiert(which_t which): which_(which) {
    }
    identifiert(const string_t& chars): extends(chars), which_(absolute_path) {
    }
    identifiert(const char_t* chars, size_t length): extends(chars, length), which_(absolute_path) {
    }
    identifiert(const char_t* chars): extends(chars), which_(absolute_path) {
    }
    identifiert(const identifiert& copy): extends(copy), which_(copy.which_) {
    }
    identifiert(): which_(absolute_path) {
    }
    virtual ~identifiert() {
    }

    /// read / write
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;
        // success = this->read_this(count, c, reader);
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
        return success;
    }
    virtual bool separate() {
        bool success = true;
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

    /// ..which
    virtual which_t set_which(which_t to) {
        which_ = to;
        return which_;
    }
    virtual which_t which() const {
        return which_;
    }

    /// ...name... / ...which
    virtual const char_t* name_of_chars(which_t which) const {
        return resource::which::name_of(which);
    }
    virtual const char_t* default_name_chars() const {
        return resource::which::name_of(default_which());
    }
    virtual which_t default_which() const {
        return asterisk;
    }

protected:
    which_t which_;
}; /// class identifiert
typedef identifiert<> identifier;
} /// namespace extended

/// class identifiert
template <class TExtends = extended::identifier, class TImplements = typename TExtends::implements>
class exported identifiert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef identifiert derives;
    
    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    identifiert(const string_t& chars): extends(chars) {
        this->separate();
    }
    identifiert(const char_t* chars, size_t length): extends(chars, length) {
        this->separate();
    }
    identifiert(const char_t* chars): extends(chars) {
        this->separate();
    }
    identifiert(const identifiert& copy): extends(copy) {
    }
    identifiert() {
        this->set_default();
    }
    virtual ~identifiert() {
    }
}; /// class identifiert
typedef identifiert<> identifier;

namespace absolute {

/// class patht
template <class TExtends = extended::identifier, class TImplements = typename TExtends::implements>
class exported patht: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef patht derives;
    
    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    patht(const string_t& chars): extends(absolute_path, chars) {
        this->separate();
    }
    patht(const char_t* chars, size_t length): extends(absolute_path, chars, length) {
        this->separate();
    }
    patht(const char_t* chars): extends(absolute_path, chars) {
        this->separate();
    }
    patht(const patht& copy): extends(copy) {
    }
    patht(): extends(absolute_path) {
        this->set_default();
    }
    virtual ~patht() {
    }

    /// ...which
    virtual which_t default_which() const {
        return absolute_path;
    }
}; /// class patht
typedef patht<> path;

/// class identifiert
template <class TExtends = extended::identifier, class TImplements = typename TExtends::implements>
class exported identifiert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef identifiert derives;
    
    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    identifiert(const string_t& chars): extends(absolute_identifier, chars) {
        this->separate();
    }
    identifiert(const char_t* chars, size_t length): extends(absolute_identifier, chars, length) {
        this->separate();
    }
    identifiert(const char_t* chars): extends(absolute_identifier, chars) {
        this->separate();
    }
    identifiert(const identifiert& copy): extends(copy) {
    }
    identifiert(): extends(absolute_identifier) {
        this->set_default();
    }
    virtual ~identifiert() {
    }

    /// ...which
    virtual which_t default_which() const {
        return absolute_identifier;
    }
}; /// class identifiert
typedef identifiert<> identifier;

} /// namespace absolute

} /// namespace resource
} /// namespace request
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_REQUEST_RESOURCE_IDENTIFIER_HPP 
