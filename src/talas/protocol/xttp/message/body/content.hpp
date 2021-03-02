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
///   File: content.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_XTTP_MESSAGE_BODY_CONTENT_HPP
#define TALAS_PROTOCOL_XTTP_MESSAGE_BODY_CONTENT_HPP

#include "talas/protocol/xttp/message/part.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace message {
namespace body {

/// class contentt
template <class TExtends = message::part, class TImplements = typename TExtends::implements>
class exported contentt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef contentt derives;

    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    contentt(const string_t& chars): extends(chars) {
    }
    contentt(const char_t* chars, size_t length): extends(chars, length) {
    }
    contentt(const char_t* chars): extends(chars) {
    }
    contentt(const contentt& copy): extends(copy) {
    }
    contentt() {
    }
    virtual ~contentt() {
    }

    /// read / write
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader, size_t length) {
        bool success = true;
        set_default();
        for (ssize_t amount = 0; 0 < length; --length, count += amount) {
            if (0 < (amount = reader.read(&c, 1))) {
                this->append(&c, 1);
            } else {
                success = false;
                break;
            }
        }
        return success;
    }
    virtual bool write(ssize_t& count, writer_t& writer) {
        return ((const derives*)this)->write(count, writer);
    }
    virtual bool write(ssize_t& count, writer_t& writer) const {
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
        return *this;
    }
}; /// class contentt
typedef contentt<> content;

} /// namespace body
} /// namespace message
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_MESSAGE_BODY_CONTENT_HPP 
