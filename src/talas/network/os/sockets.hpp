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
#include "xos/network/os/sockets.hpp"
#include "xos/network/os/socket.hpp"
#include "xos/network/ip/v6/tcp/transport.hpp"
#include "xos/network/ip/v6/endpoint.hpp"
#include "xos/network/ip/v4/tcp/transport.hpp"
#include "xos/network/ip/v4/endpoint.hpp"
#include "xos/io/socket/tcp/reader.hpp"
#include "xos/io/socket/tcp/writer.hpp"

namespace talas {
namespace network {

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

} // namespace network 

namespace io {
namespace socket {
namespace tcp {
typedef xos::io::socket::tcp::reader reader;
typedef xos::io::socket::tcp::writer writer;
} // namespace tcp
} // namespace socket
} // namespace io

} // namespace talas 

#endif // _TALAS_NETWORK_OS_SOCKETS_HPP 
