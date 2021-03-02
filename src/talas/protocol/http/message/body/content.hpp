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
#ifndef TALAS_PROTOCOL_HTTP_MESSAGE_BODY_CONTENT_HPP
#define TALAS_PROTOCOL_HTTP_MESSAGE_BODY_CONTENT_HPP

#include "talas/protocol/xttp/message/body/content.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace message {
namespace body {

/// class contentt
template 
<class TExtends = xttp::message::body::content, class TImplements = typename TExtends::implements>
class exported contentt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef contentt derives;

    typedef typename extends::part_t part_t;
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
}; /// class contentt
typedef contentt<> content;

} /// namespace body
} /// namespace message
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_MESSAGE_BODY_CONTENT_HPP 
