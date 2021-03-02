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
///   File: field.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_HTTP_MESSAGE_HEADER_FIELD_HPP
#define TALAS_PROTOCOL_HTTP_MESSAGE_HEADER_FIELD_HPP

#include "talas/protocol/xttp/message/header/field.hpp"
#include "talas/protocol/http/message/part.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace message {
namespace header {

/// class fieldt
template 
<class TExtends = xttp::message::header::extended::fieldt<http::message::part>, 
 class TImplements = typename TExtends::implements>
class exported fieldt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef fieldt derives;

    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    fieldt(const string_t& name, const string_t& value) {
        this->set(name, value);
    }
    fieldt(const string_t& chars): extends(chars) {
        this->separate();
    }
    fieldt(const char_t* chars, size_t length): extends(chars, length) {
        this->separate();
    }
    fieldt(const char_t* chars): extends(chars) {
        this->separate();
    }
    fieldt(const fieldt& copy): extends(copy) {
    }
    fieldt() {
        this->set_default();
    }
    virtual ~fieldt() {
    }
}; /// class fieldt
typedef fieldt<> field;

} /// namespace header
} /// namespace message
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_MESSAGE_HEADER_FIELD_HPP 
