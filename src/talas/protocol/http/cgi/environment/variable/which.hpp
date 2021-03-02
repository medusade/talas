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
///   File: which.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_WHICH_HPP
#define TALAS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_WHICH_HPP

#include "talas/base/chars.hpp"
#include "talas/base/string.hpp"

#define TALAS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_WHICH_NAMES \
    "GATEWAY_INTERFACE", \
    "SERVER_NAME", \
    "SERVER_PORT", \
    "SERVER_PROTOCOL", \
    "SERVER_SOFTWARE", \
    "AUTH_TYPE", \
    "CONTENT_FILE", \
    "CONTENT_LENGTH", \
    "CONTENT_TYPE", \
    "OUTPUT_FILE", \
    "PATH_INFO", \
    "PATH_TRANSLATED", \
    "QUERY_STRING", \
    "REMOTE_ADDR", \
    "REMOTE_USER", \
    "REQUEST_LINE", \
    "REQUEST_METHOD", \
    "REMOTE_HOST", \
    "REMOTE_IDENT", \
    "HTTP_ACCEPT", \
    "HTTP_USER_AGENT", \
    "SCRIPT_NAME",

namespace talas {
namespace protocol {
namespace http {
namespace cgi {
namespace environment {
namespace variable {

/// enum which_t
typedef int which_t;
enum {
    none = -1,

    GATEWAY_INTERFACE,
    SERVER_NAME,
    SERVER_PORT,
    SERVER_PROTOCOL,
    SERVER_SOFTWARE,
    AUTH_TYPE,
    CONTENT_FILE,
    CONTENT_LENGTH,
    CONTENT_TYPE,
    OUTPUT_FILE,
    PATH_INFO,
    PATH_TRANSLATED,
    QUERY_STRING,
    REMOTE_ADDR,
    REMOTE_USER,
    REQUEST_LINE,
    REQUEST_METHOD,
    REMOTE_HOST,
    REMOTE_IDENT,
    HTTP_ACCEPT,
    HTTP_USER_AGENT,
    SCRIPT_NAME,

    next,
    first = (none + 1),
    last = (next - 1),
    count = ((last - first) + 1)
}; /// enum which_t

/// class whicht
template <class TExtends = extend, class TImplements = implement>
class exported whicht: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef whicht derives;

    typedef xos::string string_t;
    typedef xos::chars chars_t;
    typedef char char_t;
    
    /// constructor / destructor
    whicht(variable::which_t of): of_(of), name_(name_of(of)) {
    }
    whicht(const whicht& copy): of_(copy.of_) {
    }
    whicht(): of_(variable::none), name_(0) {
    }
    virtual ~whicht() {
    }

    /// name... / of...
    static const char_t** name_of() {
        static const char_t* name[variable::count + 1] = {
            TALAS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_WHICH_NAMES
            0
        };
        return name;
    }
    static const char_t* name_of(variable::which_t of) {
        const char_t** name = name_of();
        if ((name) && (of >= variable::first) && (of <= variable::last)) {
            return name[of - variable::first];
        }
        return 0;
    }
    static variable::which_t of_name(const char_t* name) {
        if ((name)) {
            const char* to = 0;
            int unequal = 0;
            for (variable::which_t of = variable::first; of <= variable::last; ++of) {
                if ((to = name_of(of))) {
                    if (!(unequal = chars_t::compare(name, to)))
                        return of;
                }
            }
        }
        return variable::none;
    }

    /// of / name
    virtual whicht& operator = (const char_t* name) {
        name_ = name_of(of_ = of_name(name));
        return *this;
    }
    virtual whicht& operator = (variable::which_t of) {
        name_ = name_of(of_ = of);
        return *this;
    }
    virtual operator variable::which_t() const {
        return of();
    }
    virtual variable::which_t of() const {
        return of_;
    }
    virtual const char_t* name() const {
        return name_;
    }

protected:
    variable::which_t of_;
    const char_t* name_;
}; /// class whicht
typedef whicht<> which;

} /// namespace variable
} /// namespace environment
} /// namespace cgi
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_CGI_ENVIRONMENT_VARIABLE_WHICH_HPP 
