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
///   File: parts.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_HTTP_MESSAGE_PARTS_HPP
#define TALAS_PROTOCOL_HTTP_MESSAGE_PARTS_HPP

#include "talas/protocol/xttp/message/parts.hpp"
#include "talas/protocol/http/message/header/fields.hpp"
#include "talas/protocol/http/message/body/content.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace message {

/// class partst
template 
<class TLine = xttp::message::line,
 class TExtends = xttp::message::extended::partst
 <TLine, http::message::header::fields, http::message::body::content>, 
 class TImplements = typename TExtends::implements>
class exported partst: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef partst derives;

    typedef typename extends::line_t line_t;
    typedef typename extends::headers_t headers_t;
    typedef typename extends::field_t field_t;
    typedef typename extends::content_t content_t;
    typedef typename extends::part_t part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    partst(const line_t& line, const headers_t& headers, const content_t& content): extends(line, headers, content) {
        this->combine();
    }
    partst(const line_t& line, const headers_t& headers, const content_t* content): extends(line, headers, content) {
        this->combine();
    }
    partst(const line_t& line, const headers_t& headers): extends(line, headers) {
        this->combine();
    }
    partst(const string_t& chars): extends(chars) {
        this->separate();
    }
    partst(const char_t* chars, size_t length): extends(chars, length) {
        this->separate();
    }
    partst(const char_t* chars): extends(chars) {
        this->separate();
    }
    partst(const partst& copy): extends(copy) {
    }
    partst() {
        this->set_default();
    }
    virtual ~partst() {
    }
}; /// class partst
typedef partst<> parts;

} /// namespace message
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_MESSAGE_PARTS_HPP 
