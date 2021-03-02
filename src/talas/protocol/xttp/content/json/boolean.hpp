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
///   File: boolean.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_XTTP_CONTENT_JSON_BOOLEAN_HPP
#define TALAS_PROTOCOL_XTTP_CONTENT_JSON_BOOLEAN_HPP

#include "talas/protocol/xttp/content/json/node_type.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace content {
namespace json {

/// class booleant
template <class TExtends = message::part, class TImplements = typename TExtends::implements>
class exported booleant: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef booleant derives;
    
    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    booleant(const string_t& chars): extends(chars), true_(false) {
        this->separate();
    }
    booleant(const char_t* chars, size_t length): extends(chars, length), true_(false) {
        this->separate();
    }
    booleant(const char_t* chars): extends(chars), true_(false) {
        this->separate();
    }
    booleant(const bool& is): true_(is) {
        this->combine();
    }
    booleant(const booleant& copy): extends(copy), true_(copy.true_) {
    }
    booleant(): true_(false) {
        this->combine();
    }
    virtual ~booleant() {
    }

    /// set
    virtual bool set(const bool& to) {
        set_is_true(to);
        combine();
        return is_true();
    }

    /// read / write
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;
        // success = this->read_this(count, c, reader);
        return success;
    }
    virtual bool write(ssize_t& count, writer_t& writer) {
        bool success = this->write_this(count, writer);
        return success;
    }

    /// combine / separate
    virtual bool combine() {
        bool success = true;
        this->assign((true_)?(true_chars()):(false_chars()));
        return success;
    }
    virtual bool separate() {
        bool success = true;
        set_is_true(0 == (this->uncased_compare(true_chars())));
        return success;
    }

    /// set_default...
    virtual derives& set_default() {
        this->clear();
        set_defaults();
        return *this;
    }
    virtual derives& set_defaults() {
        true_ = false;
        return *this;
    }

    /// ...is_true
    virtual bool set_is_true(const bool to = true) {
        true_ = to;
        return true_;
    }
    virtual bool is_true() const {
        return true_;
    }

    /// true... / false...
    const char_t* true_chars() const {
        return "true";
    }
    const char_t* false_chars() const {
        return "false";
    }

protected:
    bool true_;
}; /// class booleant
typedef booleant<> boolean;

} /// namespace json
} /// namespace content
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_CONTENT_JSON_BOOLEAN_HPP 
