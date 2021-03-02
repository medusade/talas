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
///   File: line.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_XTTP_MESSAGE_LINE_HPP
#define TALAS_PROTOCOL_XTTP_MESSAGE_LINE_HPP

#include "talas/protocol/xttp/message/part.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace message {

/// class linet
template <class TExtends = part, class TImplements = typename TExtends::implements>
class exported linet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef linet derives;

    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    linet(const string_t& chars): extends(chars) {
    }
    linet(const char_t* chars, size_t length): extends(chars, length) {
    }
    linet(const char_t* chars): extends(chars) {
    }
    linet(const linet& copy): extends(copy) {
    }
    linet() {
    }
    virtual ~linet() {
    }

    /// read / write
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;
        char_t cr = 0;
        ssize_t amount = 0;
        string_t chars;

        this->set_default();
        do {
            if (0 < (amount = reader.read(&c, 1))) {
                count += amount;
                if (('\r' != c)) {
                    if (('\n' != c)) {
                        chars.append(&c, 1);
                    } else {
                        success = this->is_set(chars);
                        break;
                    }
                } else {
                    if (cr != c) {
                        cr = c;
                    } else {
                        chars.append(&cr, 1);
                    }
                }
            } else {
                count = amount;
                break;
            }
        } while (0 < amount);
        return success;
    }
    virtual bool write(ssize_t& count, writer_t& writer) {
        bool success = false;
        const char_t* chars = 0;
        size_t length = 0;
        ssize_t amount = 0;

        if ((chars = this->has_chars(length))) {
            if (length <= (amount = writer.write(chars, length))) {
                count = amount;
                if (2 <= (amount = writer.write("\r\n"))) {
                    count += amount;
                    success = true;
                }
            }
        }
        return success;
    }
}; /// class linet
typedef linet<> line;

} /// namespace message
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_MESSAGE_LINE_HPP 
