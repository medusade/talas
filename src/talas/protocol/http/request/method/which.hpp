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
#ifndef TALAS_PROTOCOL_HTTP_REQUEST_METHOD_WHICH_HPP
#define TALAS_PROTOCOL_HTTP_REQUEST_METHOD_WHICH_HPP

#include "talas/protocol/http/message/part.hpp"

#define TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_CONNECT "CONNECT"
#define TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_DELETE "DELETE"
#define TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_GET "GET"
#define TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_HEAD "HEAD"
#define TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_OPTIONS "OPTIONS"
#define TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_PATCH "PATCH"
#define TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_POST "POST"
#define TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_PUT "PUT"
#define TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_TRACE "TRACE"
#define TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_RESTART "restart"
#define TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_STOP "stop"
#define TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_UNKNOWN "unknown"

#define TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAMES \
    TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_CONNECT, \
    TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_DELETE, \
    TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_GET, \
    TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_HEAD, \
    TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_OPTIONS, \
    TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_PATCH, \
    TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_POST, \
    TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_PUT, \
    TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_TRACE, \
    TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_RESTART, \
    TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_STOP, \
    TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_UNKNOWN, \

namespace talas {
namespace protocol {
namespace http {
namespace request {
namespace method {

/// enum which_t
typedef int which_t;
enum {
    none = 0,

    CONNECT, DELETE, GET, HEAD, OPTIONS, PATCH, POST, PUT, TRACE, 
    restart, stop, unknown, 

    next,
    first = (none + 1),
    last = (next - 1),
    count = ((last - first) + 1)
}; /// enum which_t

/// class whicht
template <class TExtends = message::part,  class TImplements = typename TExtends::implements>
class exported whicht: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef whicht derives;

    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    whicht(method::which_t of): of_(of), name_(name_of(of)) {
    }
    whicht(const whicht& copy): of_(copy.of_) {
    }
    whicht(): of_(method::none), name_(0) {
    }
    virtual ~whicht() {
    }

    /// name... / of...
    static const char_t** name_of() {
        static const char_t* name[method::count + 1] = {
            TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAMES
            0
        };
        return name;
    }
    static const char_t* name_of(method::which_t of) {
        const char_t** name = name_of();
        if ((name) && (of >= method::first) && (of <= method::last)) {
            return name[of - method::first];
        }
        return name_of_none();
    }
    static method::which_t of_name(const char_t* name) {
        if ((name)) {
            const char* to = 0;
            int unequal = 0;
            for (method::which_t of = method::first; of <= method::last; ++of) {
                if ((to = name_of(of))) {
                    if (!(unequal = chars_t::compare(name, to)))
                        return of;
                }
            }
        }
        return of_name_none();
    }
    static const char_t* name_of_none() {
        return TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAME_UNKNOWN;
    }
    static method::which_t of_name_none() {
        return method::none;
    }

    /// of / name
    virtual whicht& operator = (const char_t* name) {
        name_ = name_of(of_ = of_name(name));
        return *this;
    }
    virtual whicht& operator = (method::which_t of) {
        name_ = name_of(of_ = of);
        return *this;
    }
    virtual operator method::which_t() const {
        return of();
    }
    virtual method::which_t of() const {
        return of_;
    }
    virtual const char_t* name() const {
        return name_;
    }

protected:
    method::which_t of_;
    const char_t* name_;
}; /// class whicht
typedef whicht<> which;

} /// namespace method
} /// namespace request
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_REQUEST_METHOD_WHICH_HPP 
