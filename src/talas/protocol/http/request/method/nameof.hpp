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
///   File: nameof.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAMEOF_HPP
#define TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAMEOF_HPP

#include "talas/protocol/http/request/method/name.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace request {
namespace method {
namespace nameof {

/// class CONNECT
class exported CONNECT: public method::name {
public:
    typedef method::name extends;
    typedef name derives;
    /// constructor / destructor
    CONNECT(const CONNECT& copy): extends(copy) {}
    CONNECT(): extends(method::CONNECT) {}
    virtual ~CONNECT() {}
}; /// class CONNECT

/// class DELETE
class exported DELETE: public method::name {
public:
    typedef method::name extends;
    typedef name derives;
    /// constructor / destructor
    DELETE(const DELETE& copy): extends(copy) {}
    DELETE(): extends(method::DELETE) {}
    virtual ~DELETE() {}
}; /// class DELETE

/// class GET
class exported GET: public method::name {
public:
    typedef method::name extends;
    typedef name derives;
    /// constructor / destructor
    GET(const GET& copy): extends(copy) {}
    GET(): extends(method::GET) {}
    virtual ~GET() {}
}; /// class GET

/// class HEAD
class exported HEAD: public method::name {
public:
    typedef method::name extends;
    typedef name derives;
    /// constructor / destructor
    HEAD(const HEAD& copy): extends(copy) {}
    HEAD(): extends(method::HEAD) {}
    virtual ~HEAD() {}
}; /// class HEAD

/// class OPTIONS
class exported OPTIONS: public method::name {
public:
    typedef method::name extends;
    typedef name derives;
    /// constructor / destructor
    OPTIONS(const OPTIONS& copy): extends(copy) {}
    OPTIONS(): extends(method::OPTIONS) {}
    virtual ~OPTIONS() {}
}; /// class OPTIONS

/// class PATCH
class exported PATCH: public method::name {
public:
    typedef method::name extends;
    typedef name derives;
    /// constructor / destructor
    PATCH(const PATCH& copy): extends(copy) {}
    PATCH(): extends(method::PATCH) {}
    virtual ~PATCH() {}
}; /// class PATCH

/// class POST
class exported POST: public method::name {
public:
    typedef method::name extends;
    typedef name derives;
    /// constructor / destructor
    POST(const POST& copy): extends(copy) {}
    POST(): extends(method::POST) {}
    virtual ~POST() {}
}; /// class POST

/// class PUT
class exported PUT: public method::name {
public:
    typedef method::name extends;
    typedef name derives;
    /// constructor / destructor
    PUT(const PUT& copy): extends(copy) {}
    PUT(): extends(method::PUT) {}
    virtual ~PUT() {}
}; /// class PUT

/// class TRACE
class exported TRACE: public method::name {
public:
    typedef method::name extends;
    typedef name derives;
    /// constructor / destructor
    TRACE(const TRACE& copy): extends(copy) {}
    TRACE(): extends(method::TRACE) {}
    virtual ~TRACE() {}
}; /// class TRACE

/// class restart
class exported restart: public method::name {
public:
    typedef method::name extends;
    typedef name derives;
    /// constructor / destructor
    restart(const restart& copy): extends(copy) {}
    restart(): extends(method::restart) {}
    virtual ~restart() {}
}; /// class restart

/// class stop
class exported stop: public method::name {
public:
    typedef method::name extends;
    typedef name derives;
    /// constructor / destructor
    stop(const stop& copy): extends(copy) {}
    stop(): extends(method::stop) {}
    virtual ~stop() {}
}; /// class stop

/// class unknown
class exported unknown: public method::name {
public:
    typedef method::name extends;
    typedef name derives;
    /// constructor / destructor
    unknown(const unknown& copy): extends(copy) {}
    unknown(): extends(method::unknown) {}
    virtual ~unknown() {}
}; /// class unknown

} /// namespace nameof
} /// namespace method
} /// namespace request
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_REQUEST_METHOD_NAMEOF_HPP 
