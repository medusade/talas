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
#ifndef TALAS_PROTOCOL_HTTP_REQUEST_LINE_HPP
#define TALAS_PROTOCOL_HTTP_REQUEST_LINE_HPP

#include "talas/protocol/xttp/request/line.hpp"
#include "talas/protocol/http/protocol/identifier.hpp"
#include "talas/protocol/http/request/method/name.hpp"
#include "talas/protocol/http/request/resource/identifier.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace request {

/// class linet
template 
<class TExtends = xttp::request::extended::linet
 <request::method::name, request::resource::identifier, protocol::identifier>, 
 class TImplements = typename TExtends::implements>
class exported linet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef linet derives;

    typedef typename extends::method_t method_t;
    typedef typename extends::parameters_t parameters_t;
    typedef typename extends::parameters_t resource_t;
    typedef typename extends::protocol_t protocol_t;
    typedef typename extends::line_t line_t;
    typedef typename extends::part_t part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    linet(const method_t& method, const parameters_t& parameters, const protocol_t& protocol)
    : extends(method, parameters, protocol) {
        this->combine();
    }
    linet(const string_t& method, const string_t& parameters, const string_t& protocol)
    : extends(method, parameters, protocol) {
        this->combine();
    }
    linet(const char_t* method, const char_t* parameters, const char_t* protocol)
    : extends(method, parameters, protocol) {
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

    /// ...path
    virtual parameters_t& set_path(const string_t& to) {
        return this->set_parameters(to);
    }
    virtual const parameters_t& path() const {
        return this->parameters();
    }

    /// ...resource
    virtual parameters_t& set_resource(const string_t& to) {
        return this->set_parameters(to);
    }
    virtual const parameters_t& resource() const {
        return this->parameters();
    }
}; /// class linet
typedef linet<> line;

} /// namespace request
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_REQUEST_LINE_HPP 
