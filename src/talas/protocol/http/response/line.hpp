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
#ifndef TALAS_PROTOCOL_HTTP_RESPONSE_LINE_HPP
#define TALAS_PROTOCOL_HTTP_RESPONSE_LINE_HPP

#include "talas/protocol/xttp/response/line.hpp"
#include "talas/protocol/http/protocol/identifier.hpp"
#include "talas/protocol/http/response/status/code.hpp"
#include "talas/protocol/http/response/status/reason.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace response {

/// class linet
template 
<class TExtends = xttp::response::extended::linet
 <response::status::code, response::status::reason, protocol::identifier>, 
 class TImplements = typename TExtends::implements>
class exported linet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef linet derives;

    typedef typename extends::status_t status_t;
    typedef typename extends::reason_t reason_t;
    typedef typename extends::protocol_t protocol_t;
    typedef typename extends::line_t line_t;
    typedef typename extends::part_t part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    linet(const protocol_t& protocol, const status_t& status, const reason_t& reason): extends(protocol, status, reason) {
        this->combine();
    }
    linet(const string_t& protocol, const string_t& status, const string_t& reason): extends(protocol, status, reason) {
        this->combine();
    }
    linet(const char_t* protocol, const char_t* status, const char_t* reason): extends(protocol, status, reason) {
        this->combine();
    }
    linet(const string_t &copy): extends(copy) {
        this->separate();
    }
    linet(const char_t* chars, size_t length): extends(chars, length) {
        this->separate();
    }
    linet(const char_t* chars): extends(chars) {
        this->separate();
    }
    linet(const linet& copy): extends(copy) {
    }
    linet() {
        this->set_default();
    }
    virtual ~linet() {
    }
}; /// class linet
typedef linet<> line;

} /// namespace response
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_RESPONSE_LINE_HPP 
