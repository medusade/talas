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
///   File: name.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_HTTP_CGI_NAME_HPP
#define TALAS_PROTOCOL_HTTP_CGI_NAME_HPP

#include "talas/protocol/xttp/protocol/name.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace cgi {

/// class namet
template <class TExtends = xttp::protocol::extended::name, class TImplements = typename TExtends::implements>
class exported namet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef namet derives;

    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    namet(const string_t &copy): extends(copy) {
    }
    namet(const char_t* chars, size_t length): extends(chars, length) {
    }
    namet(const char_t* chars): extends(chars) {
    }
    namet(const namet& copy): extends(copy) {
    }
    namet() {
        this->set_default();
    }
    virtual ~namet() {
    }

    /// ...name_chars
    virtual const char_t* default_name_chars() const {
        return "CGI";
    }
}; /// class namet
typedef namet<> name;

} /// namespace cgi
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_CGI_NAME_HPP 
