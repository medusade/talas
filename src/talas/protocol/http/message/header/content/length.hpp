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
///   File: length.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_HTTP_MESSAGE_HEADER_CONTENT_LENGTH_HPP
#define TALAS_PROTOCOL_HTTP_MESSAGE_HEADER_CONTENT_LENGTH_HPP

#include "talas/protocol/xttp/message/header/content/length.hpp"
#include "talas/protocol/http/message/header/field.hpp"
#include "talas/protocol/http/message/body/content.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace message {
namespace header {
namespace content {

/// class lengtht
template 
<class TExtends = xttp::message::header::content::extended::lengtht
 <http::message::body::content, http::message::header::field>, 
 class TImplements = typename TExtends::implements>
class exported lengtht: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef lengtht derives;

    typedef typename extends::content_t content_t;
    typedef typename extends::part_t part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    lengtht(const content_t& content) {
        this->set_length(content);
    }
    lengtht(const string_t& chars) {
        this->set_length(chars);
    }
    lengtht(const char_t* chars, size_t length) {
        this->set_length(chars, length);
    }
    lengtht(const char_t* chars) {
        this->set_length(chars);
    }
    lengtht(size_t length) {
        this->set_length(length);
    }
    lengtht(const lengtht& copy) {
        this->set_length(copy.value());
    }
    lengtht() {
        this->set_length();
    }
    virtual ~lengtht() {
    }
}; /// class lengtht
typedef lengtht<> length;

} /// namespace content
} /// namespace header
} /// namespace message
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_MESSAGE_HEADER_CONTENT_LENGTH_HPP 
