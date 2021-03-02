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
///   File: string.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_XTTP_CONTENT_JSON_STRING_HPP
#define TALAS_PROTOCOL_XTTP_CONTENT_JSON_STRING_HPP

#include "talas/protocol/xttp/content/json/node_type.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace content {
namespace json {

/// class stringt
template <class TExtends = message::part, class TImplements = typename TExtends::implements>
class exported stringt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef stringt derives;

    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    stringt(const string_t& chars): extends(chars) {
        this->separate();
    }
    stringt(const char_t* chars, size_t length): extends(chars, length) {
        this->separate();
    }
    stringt(const char_t* chars): extends(chars) {
        this->separate();
    }
    stringt(const stringt& copy): extends(copy) {
    }
    stringt() {
        this->set_default();
    }
    virtual ~stringt() {
    }

    /// to_literal
    virtual string_t& to_literal(string_t& to) const {
        const char_t quot = this->quot(), esc = this->esc();
        const char_t* chars = 0; size_t length = 0;
        to.assign(&quot, 1);
        if ((chars = this->has_chars(length))) {
            for (char_t c = 0; (0 < length); ++chars, --length) {
                switch (((char)(c = *chars))) {
                case '"':
                    to.append(&esc, 1);
                default:
                    to.append(&c, 1);
                    break;
                }
            }
        }
        to.append(&quot, 1);
        return to;
    }
    
    /// read / write
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;
        // success = this->read_this(count, c, reader);
        return success;
    }
    virtual bool write(ssize_t& count, writer_t& writer) {
        const char_t quot = this->quot(), esc = this->esc();
        const char_t* chars = 0; size_t length = 0; ssize_t amount = 0;
        bool success = false;

        if (0 < (amount = writer.write(&quot, 1))) {
            count += amount;
            if ((chars = this->has_chars(length))) {
                for (char_t c = 0; (0 < length); ++chars, --length) {
                    switch (((char)(c = *chars))) {
                    case '"':
                        if (0 >= (amount = writer.write(&esc, 1))) {
                            return false; }
                        count += amount;
                    default:
                        if (0 >= (amount = writer.write(&c, 1))) {
                            return false; }
                        count += amount;
                        break;
                    }
                }
            }
            if (0 < (amount = writer.write(&quot, 1))) {
                count += amount;
                success = true;
            }
        }        
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
        return *this;
    }

    /// ...
    virtual const char_t& esc() const {
        static const char_t c = '\\';
        return c;
    }
    virtual const char_t& quot() const {
        static const char_t c = '"';
        return c;
    }
}; /// class stringt
typedef stringt<> string;

} /// namespace json
} /// namespace content
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_CONTENT_JSON_STRING_HPP 
