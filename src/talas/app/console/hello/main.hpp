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
///   File: main.hpp
///
/// Author: $author$
///   Date: 2/13/2017
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_APP_CONSOLE_HELLO_MAIN_HPP
#define _TALAS_APP_CONSOLE_HELLO_MAIN_HPP

#include "talas/app/console/hello/main_opt.hpp"
#include "talas/console/main.hpp"
#include "talas/protocol/tls/openssl/client.hpp"
#include "talas/protocol/tls/openssl/connection.hpp"
#include "talas/protocol/tls/openssl/context.hpp"
#include "talas/network/os/sockets.hpp"

namespace talas {
namespace app {
namespace console {
namespace hello {

typedef talas::console::main_implements main_implements;
typedef talas::console::main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main
: virtual public main_implements, public main_extends {
public:
    typedef main_implements Implements;
    typedef main_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main()
    : certs_("certs"), trust_("localhost.cert.pem"),
      cert_("localhost.cert.pem"), key_("localhost.key.pem"),
      host_("localhost"), port_(443),
      request_("GET / HTTP/1.0\r\n\r\n") {
    }
    virtual ~main() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    string_t certs_, trust_, cert_, key_;
    string_t host_; unsigned port_;
    string_t request_;

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run(int argc, char_t **argv, char_t **env) {
        int err = 0;

        if ((talas::protocol::tls::openssl::startup())) {
            talas::protocol::tls::version v_min(1,0), v_max(1,2);
            talas::protocol::tls::versions v(v_min, v_max);
            talas::protocol::tls::openssl::client_context context;
            talas::protocol::tls::openssl::client client(context);

            if ((context.create(v))) {

                if ((context.set_verify_certificate_file_locations(trust_, certs_))) {

                    if ((context.set_certificate_file(cert_))) {

                        if ((context.set_private_key_file(key_))) {

                            if ((client.create())) {

                                if ((network::os::sockets::startup())) {
                                    network::ip::v4::endpoint ep(host_, port_);
                                    network::ip::v4::tcp::transport tp;
                                    network::os::socket s;
                                    io::socket::tcp::reader rsock(s);
                                    io::socket::tcp::writer wsock(s);
                                    talas::protocol::tls::openssl::connection connection(rsock, wsock);

                                    if ((s.open(tp))) {

                                        if ((s.connect(ep))) {

                                            if ((client.connect(connection))) {

                                                do_request(connection);
                                            }
                                        }
                                        s.close();
                                    }
                                    network::os::sockets::cleanup();
                                }
                                client.destroy();
                            }
                        }
                    }
                }
                context.destroy();
            }
            talas::protocol::tls::openssl::cleanup();
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool do_request(talas::protocol::tls::connection& connection) {
        bool success = true;
        if ((success = send_request(connection))) {
            success = receive_response(connection);
        }
        return success;
    }
    virtual bool send_request(talas::protocol::tls::connection& connection) {
        bool success = write_http(connection, request_);
        return success;
    }
    virtual bool receive_response(talas::protocol::tls::connection& connection) {
        bool success = true;
        string_t response;
        if ((success = read_http(connection, response))) {
            out(response.chars(), response.length());
            out_flush();
        }
        return success;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool write_http
    (talas::protocol::tls::connection& connection, const string_t& message) {
        bool success = false;
        size_t length = 0;
        const char* chars = 0;

        if ((chars = message.has_chars(length))) {
            ssize_t count = 0;

            TALAS_LOG_DEBUG("connection.write(chars = \"" << chars << "\", length = " << length << ")...");
            if (length == (count = connection.write(chars, length))) {
                TALAS_LOG_DEBUG("..." << count << " = connection.write(chars = \"" << chars << "\", length = " << length << ")");
                return true;
            } else {
                TALAS_LOG_ERROR("...failed " << count << " = connection.write(chars = \"" << chars << "\", length = " << length << ")");
            }
        }
        return success;
    }
    virtual bool read_http
    (talas::protocol::tls::connection& connection, string_t& message) {
        bool success = false;
        ssize_t count = 0, amount = 0;
        char http = 0, last = 0;
        int eol = 0;

        TALAS_LOG_DEBUG("connection.read(&http, 1)...");
        for (bool done = false; !done; ) {
            if (0 < (amount = connection.read(&http, 1))) {
                count += amount;
                message.append(&http, 1);
                switch(http) {
                case '\r':
                    if ('\n' != last) {
                        eol = 0;
                    } else {}
                    break;
                case '\n':
                    if ('\r' != last) {
                        eol = 0;
                    } else {
                        if (eol++) {
                            done = true;
                        }
                    }
                    break;
                default:
                    eol = 0;
                    break;
                }
                last = http;
            } else {
                done = true;
            }
        }
        if (0 < (amount)) {
            TALAS_LOG_DEBUG("...count = " << count << " = connection.read(&http, 1)...");
            success = true;
        }
        return success;
    }

#include "talas/app/console/hello/main_opt.cpp"
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace hello 
} // namespace console 
} // namespace app 
} // namespace talas 

#endif // _TALAS_APP_CONSOLE_HELLO_MAIN_HPP 
