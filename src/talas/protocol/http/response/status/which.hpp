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
#ifndef TALAS_PROTOCOL_HTTP_RESPONSE_STATUS_WHICH_HPP
#define TALAS_PROTOCOL_HTTP_RESPONSE_STATUS_WHICH_HPP

#include "talas/protocol/xttp/response/status.hpp"
#include "talas/protocol/http/message/part.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace response {
namespace status {

/// enum which_t
typedef int which_t;
enum {
    none = 0,

    Continue = 100,
    Switching_Protocols = 101,
    
    OK = 200,
    Created = 201,
    Accepted = 202,
    Non_Authoritative_Information = 203,
    No_Content = 204,
    Reset_Content = 205,
    Partial_Content = 206,

    Bad_Request = 400,
    Unauthorized = 401,
    Payment_Required = 402,
    Forbidden = 403,
    Not_Found = 404,
    Method_Not_Allowed = 405,

    Internal_Server_Error = 500,
    Not_Implemented = 501,
    Bad_Gateway = 502,
    Service_Unavailable = 503,
    Gateway_Timeout = 504,
    HTTP_Version_not_supported = 505,
    
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
    whicht(status::which_t of): of_(of), name_(name_of(of)) {
    }
    whicht(const whicht& copy): of_(copy.of_) {
    }
    whicht(): of_(status::none), name_(0) {
    }
    virtual ~whicht() {
    }

    /// name... / of...
    static const char_t* name_of(status::which_t of) {
        if ((of >= status::first) && (of <= status::last)) {
            switch (of) {
            case OK: return "OK";
            case Not_Found: return "Not Found";
            case Not_Implemented: return "Not Implemented";
            case Method_Not_Allowed: return "Method Not Allowed";
            case Internal_Server_Error: return "Internal Server Error";
            }
        }
        return name_of_none();
    }
    static status::which_t of_name(const char_t* name) {
        if ((name)) {
            const char* to = 0;
            int unequal = 0;
            for (status::which_t of = status::first; of <= status::last; ++of) {
                if ((to = name_of(of))) {
                    if (!(unequal = chars_t::compare(name, to)))
                        return of;
                }
            }
        }
        return of_name_none();
    }
    static const char_t* name_of_none() {
        return "Unknown";
    }
    static status::which_t of_name_none() {
        return status::none;
    }

    /// of / name
    virtual whicht& operator = (const char_t* name) {
        name_ = name_of(of_ = of_name(name));
        return *this;
    }
    virtual whicht& operator = (status::which_t of) {
        name_ = name_of(of_ = of);
        return *this;
    }
    virtual operator status::which_t() const {
        return of();
    }
    virtual status::which_t of() const {
        return of_;
    }
    virtual const char_t* name() const {
        return name_;
    }

protected:
    status::which_t of_;
    const char_t* name_;
}; /// class whicht
typedef whicht<> which;

} /// namespace status
} /// namespace response
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_RESPONSE_STATUS_WHICH_HPP 
