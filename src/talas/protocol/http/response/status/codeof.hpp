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
///   File: codeof.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_HTTP_RESPONSE_STATUS_CODEOF_HPP
#define TALAS_PROTOCOL_HTTP_RESPONSE_STATUS_CODEOF_HPP

#include "talas/protocol/http/response/status/code.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace response {
namespace status {
namespace codeof {

/// class OK
class exported OK: public status::code {
public:
    typedef status::code extends;
    /// constructor / destructor
    OK(const OK& copy): extends(copy) {}
    OK(): extends(status::OK) {}
    virtual ~OK() {}
}; /// class OK

/// class Not_Found
class exported Not_Found: public status::code {
public:
    typedef status::code extends;
    /// constructor / destructor
    Not_Found(const Not_Found& copy): extends(copy) {}
    Not_Found(): extends(status::Not_Found) {}
    virtual ~Not_Found() {}
}; /// class Not_Found

} /// namespace codeof
} /// namespace status
} /// namespace response
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_RESPONSE_STATUS_CODEOF_HPP 
