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
///   File: identifier.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_HTTP_CGI_IDENTIFIER_HPP
#define TALAS_PROTOCOL_HTTP_CGI_IDENTIFIER_HPP

#include "talas/protocol/xttp/protocol/identifier.hpp"
#include "talas/protocol/http/cgi/environment/variable/which.hpp"
#include "talas/protocol/http/cgi/name.hpp"
#include "talas/protocol/http/cgi/version.hpp"
#include "talas/base/logger.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace cgi {

/// class identifiert
template 
<class TExtends = xttp::protocol::extended::identifiert<cgi::name, cgi::version>, 
 class TImplements = typename TExtends::implements>
class exported identifiert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef identifiert derives;

    typedef typename extends::name_t name_t;
    typedef typename extends::version_t version_t;
    typedef typename extends::part_t part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    identifiert(const name_t& name, const version_t& version): extends(name, version)  {
        this->combine();
    }
    identifiert(const string_t& name, const string_t& version): extends(name, version)  {
        this->combine();
    }
    identifiert(const char_t* name, const char_t* version): extends(name, version)  {
        this->combine();
    }
    identifiert(const string_t& chars): extends(chars)  {
        this->separate();
    }
    identifiert(const char_t* chars, size_t length): extends(chars, length)  {
        this->separate();
    }
    identifiert(const char_t* chars): extends(chars)  {
        this->separate();
    }
    identifiert(const identifiert& copy): extends(copy) {
    }
    identifiert() {
        this->set_default();
    }
    virtual ~identifiert() {
    }

    /// get    
    virtual const char_t* get(int argc, char_t** argv, char_t** env) {
        environment::variable::which gi(environment::variable::GATEWAY_INTERFACE);
        const char_t *chars = 0;

        if ((chars = gi.name()) && (chars[0])) {
            const char_t *value = 0;

            LOGGER_IS_LOGGED_DEBUG("::getenv(\"" << chars << "\")...");
            if ((value = ::getenv(chars))) {
                LOGGER_IS_LOGGED_DEBUG("...\"" << value << "\" = ::getenv(\"" << chars << "\")");
                if ((this->is_set(value))) {
                    return this->has_chars();
                }
            } else {
                LOGGER_IS_LOGGED_ERROR("...failed errno = " << errno << " on ::getenv(\"" << chars << "\")");
            }
        }
        return 0;
    }
}; /// class identifiert
typedef identifiert<> identifier;

} /// namespace cgi
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_CGI_IDENTIFIER_HPP 
