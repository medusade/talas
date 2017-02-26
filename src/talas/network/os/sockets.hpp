///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2017 $organization$
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
///   File: sockets.hpp
///
/// Author: $author$
///   Date: 2/5/2017
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_NETWORK_OS_SOCKETS_HPP
#define _TALAS_NETWORK_OS_SOCKETS_HPP

#include "talas/base/base.hpp"
#if !defined(USE_NADIR_BASE)
#include "xos/network/os/sockets.hpp"
#include "xos/network/os/socket.hpp"
#include "xos/network/ip/v6/tcp/transport.hpp"
#include "xos/network/ip/v6/endpoint.hpp"
#include "xos/network/ip/v4/tcp/transport.hpp"
#include "xos/network/ip/v4/endpoint.hpp"
#include "xos/io/socket/tcp/reader.hpp"
#include "xos/io/socket/tcp/writer.hpp"
#else // !defined(USE_NADIR_BASE)
#include "rete/network/os/Sockets.hpp"
#include "rete/network/os/Socket.hpp"
#include "rete/network/ip/v6/tcp/Transport.hpp"
#include "rete/network/ip/v6/Endpoint.hpp"
#include "rete/network/ip/v4/tcp/Transport.hpp"
#include "rete/network/ip/v4/Endpoint.hpp"
#include "rete/io/socket/tcp/Writer.hpp"
#include "rete/io/socket/Writer.hpp"
#include "rete/io/socket/tcp/Reader.hpp"
#include "rete/io/socket/Reader.hpp"
#include "nadir/io/reader.hpp"
#include "nadir/io/writer.hpp"
#endif // !defined(USE_NADIR_BASE)

namespace talas {
namespace network {

#if !defined(USE_NADIR_BASE)
typedef xos::network::transport transport;
typedef xos::network::endpoint endpoint;
typedef xos::network::socket socket;

namespace ip {
namespace v4 {
typedef xos::network::ip::v4::endpoint endpoint;
namespace tcp {
typedef xos::network::ip::v4::tcp::transport transport;
} // namespace tcp
} // namespace v4

namespace v6 {
typedef xos::network::ip::v6::endpoint endpoint;
namespace tcp {
typedef xos::network::ip::v6::tcp::transport transport;
} // namespace tcp
} // namespace v6
} // namespace ip

namespace os {
namespace sockets = xos::network::os::sockets;
typedef xos::network::os::socket socket;
} // namespace os
#else // !defined(USE_NADIR_BASE)
typedef rete::network::Transport transport;
typedef rete::network::Endpoint endpoint;
typedef rete::network::Socket socket;

namespace ip {
namespace v4 {
typedef rete::network::ip::v4::Endpoint endpoint_extends;
class _EXPORT_CLASS endpoint: public endpoint_extends {
public:
    typedef endpoint_extends Extends;
    typedef Extends::Attached attached_t;
    endpoint(const string_t& host, unsigned port)
    : Extends(host.chars(), port) {}
    endpoint(const char* host, unsigned port)
    : Extends(host, port) {}
    endpoint(unsigned port)
    : Extends(port) {}
    endpoint() {}
    attached_t attach(const string_t& host, unsigned port)
    { return this->Attach(host, port); }
    attached_t attach(const char* host, unsigned port)
    { return this->Attach(host, port); }
    attached_t attach(unsigned port)
    { return this->Attach(port); }
    attached_t detach()
    { return this->Detach(); }
};
namespace tcp {
typedef rete::network::ip::v4::tcp::Transport transport;
} // namespace tcp
} // namespace v4

namespace v6 {
typedef rete::network::ip::v6::Endpoint endpoint_extends;
class _EXPORT_CLASS endpoint: public endpoint_extends {
public:
    typedef endpoint_extends Extends;
    typedef Extends::Attached attached_t;
    endpoint(const string_t& host, unsigned port)
    : Extends(host.chars(), port) {}
    endpoint(const char* host, unsigned port)
    : Extends(host, port) {}
    endpoint(unsigned port)
    : Extends(port) {}
    endpoint() {}
    attached_t attach(const string_t& host, unsigned port)
    { return this->Attach(host, port); }
    attached_t attach(const char* host, unsigned port)
    { return this->Attach(host, port); }
    attached_t attach(unsigned port)
    { return this->Attach(port); }
    attached_t detach()
    { return this->Detach(); }
};
namespace tcp {
typedef rete::network::ip::v6::tcp::Transport transport;
} // namespace tcp
} // namespace v6
} // namespace ip

namespace os {
typedef rete::network::os::Socket socket_extends;
class _EXPORT_CLASS socket: public socket_extends {
public:
    typedef socket_extends Extends;
    virtual bool open(const transport& tp) { return Extends::Open(tp); }
    virtual bool close() { return Extends::Close(); }
    virtual bool connect(const endpoint& ep) { return Extends::Connect(ep); }
    virtual bool listen(const endpoint& ep) { return Extends::Listen(ep); }
    virtual bool accept(socket& sk, const endpoint& ep) { return Extends::Accept(sk, ep); }
};
namespace sockets {
bool startup();
bool cleanup();
} // namespace sockets
} // namespace os
#endif // !defined(USE_NADIR_BASE)

} // namespace network 

#if !defined(USE_NADIR_BASE)
namespace io {
namespace socket {
namespace tcp {
typedef xos::io::socket::tcp::reader reader;
typedef xos::io::socket::tcp::writer writer;
} // namespace tcp
} // namespace socket
} // namespace io
#else // !defined(USE_NADIR_BASE)
namespace io {
namespace socket {
namespace tcp {
typedef nadir::io::reader nadir_reader_implements;
typedef rete::io::socket::Reader reader_implements;
typedef rete::io::socket::tcp::Reader reader_extend;
class _EXPORT_CLASS reader
: virtual public nadir_reader_implements,
  virtual public reader_implements, public reader_extend {
public:
    reader(network::socket& sk): reader_extend(sk) {}
    virtual ssize_t read(nadir::io::reader::what_t* what, size_t size) {
        size_t count = this->Read(what, size);
        return count;
    }
};
typedef nadir::io::writer nadir_writer_implements;
typedef rete::io::socket::Writer writer_implements;
typedef rete::io::socket::tcp::Writer writer_extend;
class _EXPORT_CLASS writer
: virtual public nadir_writer_implements,
  virtual public writer_implements, public writer_extend {
public:
    writer(network::socket& sk): writer_extend(sk) {}
    virtual ssize_t write(const nadir::io::writer::what_t* what, ssize_t size) {
        size_t count = 0;
        if (0 > (size)) {
            count = this->Write(what);
        } else {
            count = this->Write(what, size);
        }
        return count;
    }
};
} // namespace tcp
} // namespace socket
} // namespace io
#endif // !defined(USE_NADIR_BASE)

} // namespace talas 

#endif // _TALAS_NETWORK_OS_SOCKETS_HPP 
