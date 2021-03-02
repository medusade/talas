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
///   File: reason.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_HTTP_RESPONSE_STATUS_REASON_HPP
#define TALAS_PROTOCOL_HTTP_RESPONSE_STATUS_REASON_HPP

#include "talas/protocol/http/response/status/code.hpp"
#include "talas/protocol/xttp/response/reason.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace response {
namespace status {

/// class reasont
template 
<class TExtends = xttp::response::extended::reasont
 <status::code, status::which_t, status::OK>, 
 class TImplements = typename TExtends::implements>
class exported reasont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef reasont derives;

    typedef typename extends::status_t status_t;
    typedef typename extends::which_t which_t;
    enum { none = extends::none };
    typedef typename extends::part_t part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    reasont(const string_t& chars): extends(chars) {
        this->set_which();
    }
    reasont(const char_t* chars, size_t length): extends(chars, length) {
        this->set_which();
    }
    reasont(const char_t* chars): extends(chars) {
        this->set_which();
    }
    reasont(status_t status): extends(status) {
        this->set_name();
    }
    reasont(which_t which): extends(which) {
        this->set_name();
    }
    reasont(const reasont& copy): extends(copy) {
    }
    reasont() {
        this->set_default();
    }
    virtual ~reasont() {
    }

    /// ...name... / ...which
    virtual which_t of_name(const char_t* name) const {
        return which::of_name(name);
    }
    virtual const char_t* name_of_chars(which_t which) const {
        return which::name_of(which);
    }
    virtual const char_t* default_name_chars() const {
        return which::name_of(default_which());
    }
    virtual which_t default_which() const {
        return none;
    }
}; /// class reasont
typedef reasont<> reason;

} /// namespace status
} /// namespace response
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_RESPONSE_STATUS_REASON_HPP 
