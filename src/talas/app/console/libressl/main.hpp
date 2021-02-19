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
///   Date: 2/3/2017, 2/14/2021
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_APP_CONSOLE_LIBRESSL_MAIN_HPP
#define _TALAS_APP_CONSOLE_LIBRESSL_MAIN_HPP

#include "talas/app/console/libressl/main_opt.hpp"
#include "talas/protocol/tls/libressl/libressl.hpp"
#include "talas/network/os/sockets.hpp"

namespace talas {
namespace app {
namespace console {
namespace libressl {

typedef talas::console::main_implements main_implements;
typedef talas::console::main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main: virtual public main_implements, public main_extends {
public:
    typedef main_implements Implements;
    typedef main_extends Extends;
    typedef main Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main()
    : run_(0),
      connect_socket_cbs_(0),
      accept_one_(false),
      host_("localhost"), port_("4433"),
      request_("GET / HTTP/1.0\r\nHost:localhost:4433\r\n\r\nHello\r\n"),
      response_("HTTP/1.0 200 Ok\r\nHost:localhost:4433\r\n\r\nHello\r\n"),
      protocols_("secure"),
      ciphers_("ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-SHA384:ECDHE-ECDSA-AES256-SHA384"),
      key_file_("localhost.key.pem"),
      cert_file_("localhost.cert.pem") {
    }
    virtual ~main() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    class _EXPORT_CLASS socket: public network::os::socket {
    public:
        socket(Derives& _main): main(_main) {}
        Derives& main;
    };
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int (Derives::*run_)(int argc, char** argv, char** env);
    virtual int run(int argc, char** argv, char** env) {
        int err = 0;

        TALAS_LOG_DEBUG("tls_init()...");
        if (!(err = tls_init())) {
            if ((run_)) {
                err = (this->*run_)(argc, argv, env);
            } else {
                err = run_client(argc, argv, env);
            }
            TALAS_LOG_DEBUG("tls_cleanup()...");
            tls_cleanup();
        } else {
            TALAS_LOG_ERROR("...failed err = " << err << " on tls_init()");
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_client(int argc, char** argv, char** env) {
        int err = 0;
        size_t request_len = request_.length();
        const char *request_chars = request(request_len, argc, argv, env);
        struct tls *tls = 0;

        TALAS_LOG_DEBUG("tls_client()...");
        if ((tls = tls_client())) {
            struct tls_config *config = 0;

            TALAS_LOG_DEBUG("tls_config_new()...");
            if ((config = tls_config_new())) {

                TALAS_LOG_DEBUG("tls_config_insecure_noverifycert()...");
                tls_config_insecure_noverifycert(config);

                TALAS_LOG_DEBUG("tls_config_insecure_noverifyname()...");
                tls_config_insecure_noverifyname(config);

                TALAS_LOG_DEBUG("tls_configure(tls, config)...");
                if (!(err = tls_configure(tls, config))) {

                    if (!(socket_connect(tls))) {
                        err = 1;
                    }
                    TALAS_LOG_DEBUG("tls_reset(tls)...");
                    tls_reset(tls);
                } else {
                    TALAS_LOG_ERROR("...failed err = " << err << " tls_configure(tls, config)");
                }
                TALAS_LOG_DEBUG("tls_config_free()...");
                tls_config_free(config);
                config = 0;
            } else {
                TALAS_LOG_ERROR("...failed config = " << 0 << " on tls_config_new()");
            }
            TALAS_LOG_DEBUG("tls_free()...");
            tls_free(tls);
            tls = 0;
        } else {
            TALAS_LOG_ERROR("...failed tls = " << 0 << " on tls_client()");
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool socket_connect(struct tls* tls) {
        bool success = false;
        const char *host_chars = host_.chars(), *port_chars = port_.chars();
        size_t port = port_.to_unsigned();

        if ((network::os::sockets::startup())) {
            network::ip::v4::endpoint ep(host_chars, port);
            network::ip::v4::tcp::transport tp;
            socket s(*this);

            if ((s.open(tp))) {
                if ((s.connect(ep))) {
                    success = connect_socket_cbs(s, tls);
                }
                s.close();
            }
            network::os::sockets::cleanup();
        }
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    bool (Derives::*connect_socket_cbs_)(socket& s, struct tls* tls);
    virtual bool connect_socket_cbs(socket& s, struct tls* tls) {
        bool success = false;
        if ((connect_socket_cbs_)) {
            success = (this->*connect_socket_cbs_)(s, tls);
        } else {
            success = connect_socket(s, tls);
        }
        return success;
    }
    virtual bool connect_cbs(socket& s, struct tls* tls) {
        bool success = false;
        const char *host_chars = host_.chars();
        tls_read_cb read_cb = network_os_socket_read_cb;
        tls_write_cb write_cb = network_os_socket_write_cb;
        void *cb_arg = &s;
        int err = 0;

        TALAS_LOG_DEBUG("tls_connect_cbs(tls, read_cb, write_cb, cb_arg, host_chars = \"" << host_chars << "\")...");
        if (!(err = tls_connect_cbs(tls, read_cb, write_cb, cb_arg, host_chars))) {

            TALAS_LOG_DEBUG("tls_handshake(tls)...");
            if (!(err = tls_handshake(tls))) {
                success = make_request(tls);
            } else {
                TALAS_LOG_ERROR("...failed err = " << err << " \"" << tls_error(tls) << "\" on tls_handshake(tls)");
            }
            TALAS_LOG_DEBUG("tls_close(tls)...");
            if ((err = tls_close(tls))) {
                TALAS_LOG_ERROR("...failed err = " << err << " tls_close(tls)");
            }
        } else {
            TALAS_LOG_ERROR("...failed err = " << err << " tls_connect_cbs(tls, read_cb, write_cb, cb_arg, host_chars = \"" << host_chars << "\")");
        }
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool connect_socket(socket& s, struct tls* tls) {
        bool success = false;
        int err = 0;
        const char *host_chars = host_.chars(), *port_chars = port_.chars();
        network::os::socket::attached_t sock = s.attached_to();

        TALAS_LOG_DEBUG("tls_connect(tls, sock, host_chars = \"" << host_chars << "\")...");
        if (!(err = tls_connect_socket(tls, sock, host_chars))) {

            TALAS_LOG_DEBUG("tls_handshake(tls)...");
            if (!(err = tls_handshake(tls))) {
                success = make_request(tls);
            } else {
                TALAS_LOG_ERROR("...failed err = " << err << " \"" << tls_error(tls) << "\" on tls_handshake(tls)");
            }
            TALAS_LOG_DEBUG("tls_close(tls)...");
            if ((err = tls_close(tls))) {
                TALAS_LOG_ERROR("...failed err = " << err << " tls_close(tls)");
            }
        } else {
            TALAS_LOG_ERROR("...failed err = " << err << " tls_connect_socket(tls, sock, host_chars = \"" << host_chars << "\")");
        }
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool make_request(struct tls* tls) {
        bool success = false;
        const char *request_chars = request_.chars();
        ssize_t request_len = request_.length();
        ssize_t count = 0, amount = 0;

        TALAS_LOG_DEBUG("tls_write(tls, request_chars = \"" << request_chars << "\", request_len = " << request_len << ")...");
        if ((success = (0 < (amount = tls_write(tls, request_chars, request_len))))) {
            char buf[1023];
            do {
                if (0 < (amount = tls_read(tls, buf, sizeof(buf)))) {
                    this->out(buf, amount);
                    this->out_flush();
                    count += amount;
                }
            } while (amount);
        } else {
            TALAS_LOG_ERROR("...failed amount = " << amount << " tls_write(tls, request_chars = \"" << request_chars << "\", request_len = " << request_len << ")");
        }
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char* request(size_t& length,int argc, char** argv, char** env) {
        const char *request_chars = request_.chars(length);
        if (optind < argc) {
            const char *arg = 0;
            if ((arg = argv[optind]) && (arg[0])) {
                request_chars = (request_.assign(arg)).chars(length);
            }
        }
        return request_chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_server(int argc, char** argv, char** env) {
        int err = 0;
        const char *key_file_chars = key_file_.chars(), *cert_file_chars = cert_file_.chars();
        const char *protocols_chars = protocols_.chars(), *ciphers_chars = ciphers_.chars();
        size_t response_len = response_.length();
        const char *response_chars = response(response_len, argc, argv, env);
        struct tls_config *config = 0;
        struct tls *tls = 0;

        TALAS_LOG_DEBUG("tls_config_new()...");
        if ((config = tls_config_new())) {

            TALAS_LOG_DEBUG("tls_server()...");
            if ((tls = tls_server())) {
                unsigned int protocols = 0;

                TALAS_LOG_DEBUG("tls_config_parse_protocols()...");
                if (!(err = tls_config_parse_protocols(&protocols, protocols_chars))) {

                    TALAS_LOG_DEBUG("tls_config_set_protocols()...");
                    if (!(err = tls_config_set_protocols(config, protocols))) {

                        TALAS_LOG_DEBUG("tls_config_set_ciphers()...");
                        if (!(err = tls_config_set_ciphers(config, ciphers_chars))) {

                            TALAS_LOG_DEBUG("tls_config_set_key_file()...");
                            if (!(err = tls_config_set_key_file(config, key_file_chars))) {

                                TALAS_LOG_DEBUG("tls_config_set_cert_file()...");
                                if (!(err = tls_config_set_cert_file(config, cert_file_chars))) {

                                    TALAS_LOG_DEBUG("tls_configure()...");
                                    if (!(err = tls_configure(tls, config))) {

                                        if (!(socket_accept(tls))) {
                                            err = 1;
                                        }
                                    } else {
                                        TALAS_LOG_ERROR("...failed err = " << err << " \"" << tls_error(tls) << "\" on tls_configure()");
                                    }
                                } else {
                                    TALAS_LOG_ERROR("...failed err = " << err << " \"" << tls_config_error(config) << "\" on tls_config_set_cert_file()");
                                }
                            } else {
                                TALAS_LOG_ERROR("...failed err = " << err << " \"" << tls_config_error(config) << "\" on tls_config_set_key_file()");
                            }
                        } else {
                            TALAS_LOG_ERROR("...failed err = " << err << " on tls_config_set_ciphers()");
                        }
                    } else {
                        TALAS_LOG_ERROR("...failed err = " << err << " on tls_config_set_protocols()");
                    }
                } else {
                    TALAS_LOG_ERROR("...failed err = " << err << " on tls_config_parse_protocols()");
                }
                TALAS_LOG_DEBUG("tls_free()...");
                tls_free(tls);
                tls = 0;
            } else {
                TALAS_LOG_ERROR("...failed tls = " << 0 << " on tls_server()");
            }
            TALAS_LOG_DEBUG("tls_config_free()...");
            tls_config_free(config);
            config = 0;
        } else {
            TALAS_LOG_ERROR("...failed config = " << 0 << " on tls_config_new()");
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool socket_accept(struct tls* tls) {
        bool success = false;
        const char *host_chars = host_.chars(), *port_chars = port_.chars();
        size_t port = port_.to_unsigned();

        if ((network::os::sockets::startup())) {
            network::ip::v4::endpoint ep(port);
            network::ip::v4::tcp::transport tp;
            socket ss(*this);

            if ((ss.open(tp))) {
                if ((ss.listen(ep))) {
                    socket s(*this);

                    for (bool done = false; !done;) {
                        if ((ss.accept(s, ep))) {
                            if (!(accept_socket_cbs(s, tls))) {
                                done = true;
                            }
                            s.close();
                            if ((accept_one_)) {
                                done = true;
                            }
                        } else {
                            done = true;
                        }
                    }
                }
                ss.close();
            }
            network::os::sockets::cleanup();
        }
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool accept_socket_cbs(socket& s, struct tls* tls) {
        bool success = false;
        tls_read_cb read_cb = network_os_socket_read_cb;
        tls_write_cb write_cb = network_os_socket_write_cb;
        void *cb_arg = &s;
        struct tls *tlc = 0;
        int err = 0;

        TALAS_LOG_DEBUG("tls_accept_cbs()...");
        if ((success = !(err = tls_accept_cbs(tls, &tlc, read_cb, write_cb, cb_arg)))) {
            success = process_request(tlc);

            /*TALAS_LOG_DEBUG("tls_close(tlc)...");
            if (!(success = !(err = tls_close(tlc)))) {
                TALAS_LOG_ERROR("...failed err = " << err << " \"" << tls_error(tlc) << "\" on tls_close()");
            }
            TALAS_LOG_DEBUG("tls_free(tlc)...");
            tls_free(tlc);*/
            tlc = 0;
        } else {
            TALAS_LOG_ERROR("...failed err = " << err << " \"" << tls_error(tls) << "\" on tls_accept_cbs()");
        }
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool accept_socket(socket& s, struct tls* tls) {
        bool success = false;
        int err = 0;
        network::os::socket::attached_t sock = s.attached_to();
        struct tls *tlc = 0;

        TALAS_LOG_DEBUG("tls_accept_socket()...");
        if ((success = !(err = tls_accept_socket(tls, &tlc, sock)))) {
            success = process_request(tlc);

            /*TALAS_LOG_DEBUG("tls_close(tlc)...");
            if (!(success = !(err = tls_close(tlc)))) {
                TALAS_LOG_ERROR("...failed err = " << err << " \"" << tls_error(tlc) << "\" on tls_close()");
            }
            TALAS_LOG_DEBUG("tls_free(tlc)...");
            tls_free(tlc);*/
            tlc = 0;
        } else {
            TALAS_LOG_ERROR("...failed err = " << err << " \"" << tls_error(tls) << "\" on tls_accept_socket()");
        }
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual bool process_request(struct tls* tlc) {
        bool success = false;
        const char *response_chars = response_.chars();
        ssize_t response_len = response_.length();
        ssize_t count = 0, amount = 0;
        char buf[1023];

        do {
            if (0 < (amount = tls_read(tlc, buf, sizeof(buf)))) {
                this->out(buf, amount);
                this->out_flush();
                count += amount;
            }
        } while (amount == sizeof(buf));

        TALAS_LOG_DEBUG("tls_write(tlc, buf = \"" << response_chars << "\", len = " << response_len << ")...");
        if ((success = (0 < (amount = tls_write(tlc, response_chars, response_len))))) {
        } else {
            TALAS_LOG_ERROR("...failed amount = " << amount << " \"" << tls_error(tlc) << "\" on tls_write()");
        }
        return success;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char* response(size_t& length,int argc, char** argv, char** env) {
        const char *response_chars = response_.chars(length);
        if (optind < argc) {
            const char *arg = 0;
            if ((arg = argv[optind]) && (arg[0])) {
                response_chars = (response_.assign(arg)).chars(length);
            }
        }
        return response_chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    static ssize_t network_os_socket_read_cb
    (struct tls *_ctx, void *_buf, size_t _buflen, void *_cb_arg) {
        socket *s = ((socket*)_cb_arg);
        ssize_t count = -1;
        if ((_ctx) && (_buf) && (s)) {
            if ((_buflen)) {
                if (0 < (count = s->recv(_buf, _buflen, 0))) {
                    s->main.outln();
                    s->main.out("<---[");
                    s->main.outx(_buf, count);
                    s->main.outln("]");
                }
            } else {
                count = 0;
            }
        }
        return count;
    }
    static ssize_t network_os_socket_write_cb
    (struct tls *_ctx, const void *_buf, size_t _buflen, void *_cb_arg) {
        socket *s= ((socket*)_cb_arg);
        ssize_t count = -1;
        if ((_ctx) && (_buf) && (s)) {
            if ((_buflen)) {
                if (0 < (count = s->send(_buf, _buflen, 0))) {
                    s->main.outln();
                    s->main.out("--->[");
                    s->main.outx(_buf, count);
                    s->main.outln("]");
                }
            } else {
                count = 0;
            }
        }
        return count;
    }

#include "talas/app/console/libressl/main_opt.cpp"
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    /*typedef int (Derives::*run_t)(int argc, char** argv, char** env);
    run_t run_;*/
    bool accept_one_;
    string_t host_, port_, request_, response_,
             protocols_, ciphers_, key_file_, cert_file_;
};

} // namespace libressl 
} // namespace console 
} // namespace app 
} // namespace talas 

#endif // _TALAS_APP_CONSOLE_LIBRESSL_MAIN_HPP 
