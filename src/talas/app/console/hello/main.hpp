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
#include "talas/protocol/tls/openssl/server.hpp"
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
    typedef main Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main()
    : certs_("certs"), trust_("localhost.cert.pem"),
      cert_("localhost.cert.pem"), key_("localhost.key.pem"),
      host_("localhost"), port_(443),
      accept_host_("*"), accept_port_(4433),
      accept_verify_(false), accept_one_(false),
      request_("GET / HTTP/1.0\r\n\r\n"),
      response_("HTTP/1.0 200 OK\r\n\r\n"),
      version_min_(1,0), version_max_(1,2),
      versions_(version_min_, version_max_),
      run_(0) {
    }
    virtual ~main() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef int (Derives::*run_t)(int argc, char_t **argv, char_t **env);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    string_t certs_, trust_, cert_, key_;
    string_t host_; unsigned port_;
    string_t accept_host_; unsigned accept_port_;
    bool accept_verify_, accept_one_;
    string_t request_, response_;
    talas::protocol::tls::version version_min_, version_max_;
    talas::protocol::tls::versions versions_;
    run_t run_;
    network::ip::v4::endpoint ep_;
    network::ip::v4::tcp::transport tp_;
    network::os::socket sk_;

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run(int argc, char_t **argv, char_t **env) {
        int err = 0;
        if ((talas::protocol::tls::openssl::startup())) {
            if ((run_)) {
                err = (this->*run_)(argc, argv, env);
            } else {
                err = run_default(argc, argv, env);
            }
            talas::protocol::tls::openssl::cleanup();
        }
        return err;
    }
    virtual int run_default(int argc, char_t **argv, char_t **env) {
        int err = run_tcp_client(argc, argv, env);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_tcp_client(int argc, char_t **argv, char_t **env) {
        int err = 0;
        talas::protocol::tls::openssl::client_context context;
        talas::protocol::tls::openssl::client client(context);
        io::socket::tcp::reader rsock(sk_);
        io::socket::tcp::writer wsock(sk_);
        talas::protocol::tls::openssl::connection connection(rsock, wsock);

        if ((create_context(context))) {

            if ((client.create())) {

                if ((network::os::sockets::startup())) {

                    if ((ep_.attach(host_, port_))) {

                        if ((sk_.open(tp_))) {

                            if ((sk_.connect(ep_))) {

                                if ((client.connect(connection))) {

                                    request(connection);
                                }
                            }
                            sk_.close();
                        }
                        ep_.detach();
                    }
                    network::os::sockets::cleanup();
                }
                client.destroy();
            }
            destroy_context(context);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool request(talas::protocol::tls::connection& connection) {
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
    virtual int run_tcp_server(int argc, char_t **argv, char_t **env) {
        int err = 0;
        talas::protocol::tls::openssl::server_context context;
        talas::protocol::tls::openssl::server server(context);

        if ((create_context(context))) {

            if ((server.create())) {

                if ((network::os::sockets::startup())) {

                    if ((ep_.attach(accept_port_))) {

                        if ((sk_.open(tp_))) {

                            if ((sk_.listen(ep_))) {
                                network::os::socket sk;
                                io::socket::tcp::reader rsock(sk);
                                io::socket::tcp::writer wsock(sk);
                                talas::protocol::tls::openssl::connection connection(rsock, wsock);

                                if ((sk_.accept(sk, ep_))) {

                                    if ((server.accept(connection))) {

                                        respond(connection);
                                    }
                                    sk.close();
                                }
                            }
                            sk_.close();
                        }
                        ep_.detach();
                    }
                    network::os::sockets::cleanup();
                }
                server.destroy();
            }
            destroy_context(context);
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create_context
    (talas::protocol::tls::openssl::context& context) {
        if ((context.create(versions_))) {

            if ((context.set_verify_certificate_file_locations(trust_, certs_))) {

                if ((context.set_certificate_file(cert_))) {

                    if ((context.set_private_key_file(key_))) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    virtual bool destroy_context
    (talas::protocol::tls::openssl::context& context) {
        if ((context.destroy())) {
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool respond(talas::protocol::tls::connection& connection) {
        bool success = true;
        if ((success = receive_request(connection))) {
            success = send_response(connection);
        }
        return success;
    }
    virtual bool send_response(talas::protocol::tls::connection& connection) {
        bool success = write_http(connection, response_);
        return success;
    }
    virtual bool receive_request(talas::protocol::tls::connection& connection) {
        bool success = true;
        string_t request;
        if ((success = read_http(connection, request))) {
            out(request.chars(), request.length());
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

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_client_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        run_ = &Derives::run_tcp_client;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_server_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        run_ = &Derives::run_tcp_server;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_verify_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        accept_verify_ = true;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_one_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        accept_one_ = true;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_host_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            accept_host_.assign(host_.assign(optarg));
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_port_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            accept_port_ = (port_ = chars_t::to_unsigned(optarg));
        }
        return err;
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
