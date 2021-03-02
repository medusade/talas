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
///   File: version.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_HTTP_CGI_VERSION_HPP
#define TALAS_PROTOCOL_HTTP_CGI_VERSION_HPP

#include "talas/protocol/xttp/protocol/version.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace cgi {

/// class versiont
template <class TExtends = xttp::protocol::extended::version, class TImplements = typename TExtends::implements>
class exported versiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef versiont derives;

    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    versiont(const string_t& major, const string_t& minor): extends(major, minor) {
        this->combine();
    }
    versiont(const char_t* major, const char_t* minor): extends(major, minor) {
        this->combine();
    }
    versiont(const string_t& chars): extends(chars) {
        this->separate();
    }
    versiont(const char_t* chars, size_t length): extends(chars, length) {
        this->separate();
    }
    versiont(const char_t* chars): extends(chars) {
        this->separate();
    }
    versiont(const versiont& copy): extends(copy) {
    }
    versiont() {
        this->set_default();
    }
    virtual ~versiont() {
    }

    /// ...major_chars / ...minor_chars
    virtual const char_t* default_major_chars() const {
        return "1";
    }
    virtual const char_t* default_minor_chars() const {
        return "0";
    }
}; /// class versiont
typedef versiont<> version;

} /// namespace cgi
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_CGI_VERSION_HPP 
