///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2015 $organization$
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
///   Date: 12/25/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_APP_CONSOLE_OPENSSL_MAIN_HPP
#define _TALAS_APP_CONSOLE_OPENSSL_MAIN_HPP

#include "talas/app/console/openssl/main_opt.hpp"
#include "talas/protocol/tls/openssl/bio_rw.hpp"
#include "talas/protocol/tls/openssl/openssl.hpp"
#include "talas/network/os/sockets.hpp"

#define TALAS_APP_CONSOLE_OPENSSL_VERIFY_CLIENT false

#define TALAS_APP_CONSOLE_OPENSSL_ACCEPT_HOST "*"
#define TALAS_APP_CONSOLE_OPENSSL_ACCEPT_PORT 4433
#define TALAS_APP_CONSOLE_OPENSSL_ACCEPT_RESPONSE "HTTP/1.0 200 OK\r\n\r\nOk\r\n"

#define TALAS_APP_CONSOLE_OPENSSL_HOST "localhost"
#define TALAS_APP_CONSOLE_OPENSSL_PORT 443
#define TALAS_APP_CONSOLE_OPENSSL_KEY "localhost.key.pem"
#define TALAS_APP_CONSOLE_OPENSSL_KEY_TYPE SSL_FILETYPE_PEM
#define TALAS_APP_CONSOLE_OPENSSL_CERT "localhost.cert.pem"
#define TALAS_APP_CONSOLE_OPENSSL_CERT_TYPE SSL_FILETYPE_PEM
#define TALAS_APP_CONSOLE_OPENSSL_TRUST "localhost.cert.pem"
#define TALAS_APP_CONSOLE_OPENSSL_CERTS "/certs"
#define TALAS_APP_CONSOLE_OPENSSL_REQUEST "GET / HTTP/1.0\r\n\r\nHello\r\n"

namespace talas {
namespace app {
namespace console {
namespace openssl {

typedef crypto::console::main_implements main_implements;
typedef crypto::console::main main_extends;
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
    main() {
        verify_client = TALAS_APP_CONSOLE_OPENSSL_VERIFY_CLIENT;
        accept_host = TALAS_APP_CONSOLE_OPENSSL_ACCEPT_HOST;
        accept_port = TALAS_APP_CONSOLE_OPENSSL_ACCEPT_PORT;
        accept_once = false;
        host = TALAS_APP_CONSOLE_OPENSSL_HOST;
        port = TALAS_APP_CONSOLE_OPENSSL_PORT;
        key = TALAS_APP_CONSOLE_OPENSSL_KEY;
        key_type = TALAS_APP_CONSOLE_OPENSSL_KEY_TYPE;
        cert = TALAS_APP_CONSOLE_OPENSSL_CERT;
        cert_type = TALAS_APP_CONSOLE_OPENSSL_CERT_TYPE;
        trust = TALAS_APP_CONSOLE_OPENSSL_TRUST;
        certs = TALAS_APP_CONSOLE_OPENSSL_CERTS;
        request = TALAS_APP_CONSOLE_OPENSSL_REQUEST;
        request_len = chars_t::count(request);
        response = 0;
        accept_response = TALAS_APP_CONSOLE_OPENSSL_ACCEPT_RESPONSE;
        accept_response_len = chars_t::count(accept_response);
        accept_request = 0;
        amount = 0; count = 0; verify = 0;
        error = 0; error_string = 0;
        meth = 0; ctx = 0; ssl = 0;
        ssl_bio = 0;
        bio = 0;
        run_ = 0;
        run_connection_ = 0;
        run_accept_connection_ = 0;
        read_data_ = 0;
        write_data_ = 0;
    }
    virtual ~main() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    typedef int (Derives::*run_t)(int argc, char** argv, char** env);
    typedef int (Derives::*read_data_t)(void *buf, int len);
    typedef int (Derives::*write_data_t)(const void *buf, int len);

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    run_t run_, run_connection_, run_accept_connection_;
    read_data_t read_data_;
    write_data_t write_data_;
    bool verify_client;
    char* accept_host; int accept_port; bool accept_once;
    char* host; int port;
    char* key; int key_type;
    char* cert; int cert_type;
    char* trust; char* certs;
    char* request; int request_len; char response;
    char* accept_response; int accept_response_len; char accept_request;
    int amount, count; long verify;
    unsigned long error; char* error_string;
    SSL_METHOD* meth; SSL_CTX* ctx; SSL* ssl;
    BIO *ssl_bio, *bio;

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run(int argc, char** argv, char** env) {
        int err = 0;

        ERR_load_BIO_strings();
        SSL_load_error_strings();
        SSL_library_init();

        if ((run_)) {
            err = (this->*run_)(argc, argv, env);
        } else {
            err = run_client(argc, argv, env);
        }

        ERR_free_strings();
        EVP_cleanup();
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_server(int argc, char** argv, char** env) {
        int err = 0;

        TALAS_LOG_MESSAGE_DEBUG("meth = TLSv1_server_method()...");
        if ((meth = TLSv1_server_method())) {
            TALAS_LOG_MESSAGE_DEBUG("...meth = TLSv1_server_method()");

            TALAS_LOG_MESSAGE_DEBUG("ctx = SSL_CTX_new(meth)...");
            if ((ctx = SSL_CTX_new(meth))) {
                TALAS_LOG_MESSAGE_DEBUG("...ctx = SSL_CTX_new(meth)");

                TALAS_LOG_MESSAGE_DEBUG("SSL_CTX_use_certificate_file(ctx, cert = \"" << cert << "\", cert_type)...");
                if ((SSL_CTX_use_certificate_file(ctx, cert, cert_type))) {
                    TALAS_LOG_MESSAGE_DEBUG("...SSL_CTX_use_certificate_file(ctx, cert = \"" << cert << "\", cert_type)");

                    TALAS_LOG_MESSAGE_DEBUG("SSL_CTX_use_PrivateKey_file(ctx, key = \"" << key << "\", key_type)...");
                    if ((SSL_CTX_use_PrivateKey_file(ctx, key, key_type))) {
                        TALAS_LOG_MESSAGE_DEBUG("...SSL_CTX_use_PrivateKey_file(ctx, key = \"" << key << "\", key_type)");

                        TALAS_LOG_MESSAGE_DEBUG("SSL_CTX_check_private_key(ctx) key = \"" << key << "\"...");
                        if ((SSL_CTX_check_private_key(ctx))) {
                            TALAS_LOG_MESSAGE_DEBUG("...SSL_CTX_check_private_key(ctx) key = \"" << key << "\"");

                            TALAS_LOG_MESSAGE_DEBUG("SSL_CTX_load_verify_locations(ctx, trust = \"" << trust << "\", certs = \"" << certs << "\")...");
                            if ((SSL_CTX_load_verify_locations(ctx, trust, certs))) {
                                TALAS_LOG_MESSAGE_DEBUG("...SSL_CTX_load_verify_locations(ctx, trust = \"" << trust << "\", certs = \"" << certs << "\")");

                                if ((verify_client)) {
                                    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);
                                    SSL_CTX_set_verify_depth(ctx, 1);
                                }
                                err = run_accept_connections(argc, argv, env);
                            } else {
                                error_string = ERR_error_string(error = ERR_get_error(), NULL);
                                TALAS_LOG_MESSAGE_DEBUG
                                ("failed (" << error << ") \"" << error_string << "\" on " <<
                                 "SSL_CTX_load_verify_locations(ctx, trust = \"" << trust << "\", certs = \"" << certs << "\")");
                            }
                        } else {
                            error_string = ERR_error_string(error = ERR_get_error(), NULL);
                            TALAS_LOG_MESSAGE_DEBUG
                            ("failed (" << error << ") \"" << error_string << "\" on " <<
                             "SSL_CTX_check_private_key(ctx) key = \"" << key << "\"");
                        }
                    } else {
                        error_string = ERR_error_string(error = ERR_get_error(), NULL);
                        TALAS_LOG_MESSAGE_DEBUG
                        ("failed (" << error << ") \"" << error_string << "\" on " <<
                         "SSL_CTX_use_PrivateKey_file(ctx, key = \"" << key << "\", key_type)");
                    }
                } else {
                    error_string = ERR_error_string(error = ERR_get_error(), NULL);
                    TALAS_LOG_MESSAGE_DEBUG
                    ("failed (" << error << ") \"" << error_string << "\" on " <<
                     "SSL_CTX_use_certificate_file(ctx, cert = \"" << cert << "\", cert_type)");
                }

                TALAS_LOG_MESSAGE_DEBUG("...SSL_CTX_free(ctx)");
                SSL_CTX_free(ctx);
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_accept_connections(int argc, char** argv, char** env) {
        int err = 0;

        TALAS_LOG_MESSAGE_DEBUG("ssl = SSL_new(ctx)...");
        if ((ssl = SSL_new(ctx))) {
            TALAS_LOG_MESSAGE_DEBUG("...ssl = SSL_new(ctx))");

            TALAS_LOG_MESSAGE_DEBUG("ssl_bio = BIO_new_ssl(ctx, FALSE)...");
            if ((ssl_bio = BIO_new_ssl(ctx, FALSE))) {
                TALAS_LOG_MESSAGE_DEBUG("...ssl_bio = BIO_new_ssl(ctx, FALSE)");

                err = run_accept_connection(argc, argv, env);

                if ((ssl_bio)) {
                    TALAS_LOG_MESSAGE_DEBUG("...BIO_free_all(ssl_bio)");
                    BIO_free_all(ssl_bio);
                    ssl_bio = 0;
                }
            } else {
            }
            if ((ssl)) {
                TALAS_LOG_MESSAGE_DEBUG("...SSL_free(ssl)");
                SSL_free(ssl);
                ssl = 0;
            }
        } else {
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_accept_connection(int argc, char** argv, char** env) {
        int err = 0;
        if ((run_accept_connection_)) {
            err = (this->*run_accept_connection_)(argc, argv, env);
        } else {
            err = run_ssl_accept_connection(argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int _run_rw_accept_connection(int argc, char** argv, char** env) {
        int err = 0;
        FILE *in_file = std_in(), *out_file = std_out();
        io::read::file rfile(in_file);
        io::write::file wfile(out_file);
        err = run_rw_accept_connection_rw(rfile, wfile, argc, argv, env);
        return err;
    }
    virtual int run_rw_accept_connection(int argc, char** argv, char** env) {
        int err = 0;
        network::ip::v4::endpoint ep(accept_port);
        network::ip::v4::tcp::transport tp;
        network::os::socket ss;

        if ((ss.open(tp))) {
            if ((ss.listen(ep))) {
                network::os::socket s;
                io::socket::tcp::reader rsock(s);
                io::socket::tcp::writer wsock(s);
                do {
                    if ((ss.accept(s, ep))) {
                        err = run_rw_accept_connection_rw(rsock, wsock, argc, argv, env);
                        s.close();
                    }
                } while ((!err) && (!accept_once));
            }
            ss.close();
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_rw_accept_connection_rw
    (io::reader& rd, io::writer& wr, int argc, char** argv, char** env) {
        int err = 0;
        protocol::tls::openssl::BIO_RW rw(&rd, &wr);
        BIO *rw_bio = 0;

        TALAS_LOG_MESSAGE_DEBUG("protocol::tls::openssl::BIO_new_rw(&rw)...");
        if ((rw_bio = protocol::tls::openssl::BIO_new_rw(&rw))) {
            TALAS_LOG_MESSAGE_DEBUG("...protocol::tls::openssl::BIO_new_rw(&rw)");

            TALAS_LOG_MESSAGE_DEBUG("...SSL_set_bio(ssl, rw_bio, rw_bio)");
            SSL_set_bio(ssl, rw_bio, rw_bio);
            rw_bio = 0;

            err = run_rw_accept(argc, argv, env);

            if ((rw_bio)) {
                TALAS_LOG_MESSAGE_DEBUG("...BIO_free_all(rw_bio)");
                BIO_free_all(rw_bio);
                rw_bio = 0;
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_rw_accept(int argc, char** argv, char** env) {
        int err = 0;
        int did_accept = 0;

        TALAS_LOG_MESSAGE_DEBUG("SSL_accept(ssl)...");
        if (1 == (did_accept = SSL_accept(ssl))) {
            TALAS_LOG_MESSAGE_DEBUG("...SSL_accept(ssl)");

            run_accept_request(argc, argv, env);
        } else {
            error_string = ERR_error_string(error = ERR_get_error(), NULL);
            TALAS_LOG_MESSAGE_DEBUG
            ("...failed (" << error << ") \"" << error_string << "\" on " <<
             "SSL_accept(ssl)");
            err = 1;
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_ssl_accept_connection(int argc, char** argv, char** env) {
        int err = 0;
        protocol::tls::openssl::port port(accept_host, accept_port);

        TALAS_LOG_MESSAGE_DEBUG("bio = BIO_new_accept(port)...");
        if ((bio = BIO_new_accept(port))) {
            TALAS_LOG_MESSAGE_DEBUG("...bio = BIO_new_accept(port)");

            TALAS_LOG_MESSAGE_DEBUG("...BIO_set_accept_bios(bio, ssl_bio)");
            BIO_set_accept_bios(bio, ssl_bio);
            ssl_bio = 0;

            err = run_ssl_accept(argc, argv, env);

            if ((bio)) {
                TALAS_LOG_MESSAGE_DEBUG("...BIO_free_all(bio)");
                BIO_free_all(bio);
                bio = 0;
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_ssl_accept(int argc, char** argv, char** env) {
        int err = 0;
        int did_accept = 0;
        BIO *accept_bio = 0;

        do {
            TALAS_LOG_MESSAGE_DEBUG("BIO_do_accept(bio)...");
            if (1 == (did_accept = BIO_do_accept(bio))) {
                TALAS_LOG_MESSAGE_DEBUG("...BIO_do_accept(bio)");

                run_accept_request(argc, argv, env);

                TALAS_LOG_MESSAGE_DEBUG("accept_bio = BIO_pop(bio)...");
                if ((accept_bio = BIO_pop(bio))) {
                    TALAS_LOG_MESSAGE_DEBUG("...accept_bio = BIO_pop(bio)");

                    TALAS_LOG_MESSAGE_DEBUG("...BIO_free_all(accept_bio)");
                    BIO_free_all(accept_bio);
                    accept_bio = 0;
                }
            } else {
                error_string = ERR_error_string(error = ERR_get_error(), NULL);
                TALAS_LOG_MESSAGE_DEBUG
                ("...failed (" << error << ") \"" << error_string << "\" on " <<
                 "BIO_do_accept(bio)");
                err = 1;
            }
        } while ((did_accept) && !(accept_once));
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_accept_request(int argc, char** argv, char** env) {
        int err = 0;
        if (!(err = run_read_request(argc, argv, env))) {
            err = run_write_response(argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_read_request(int argc, char** argv, char** env) {
        return run_read_http(accept_request, argc, argv, env);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_write_response(int argc, char** argv, char** env) {
        return run_write_http
        (accept_response, accept_response_len, argc, argv, env);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_client(int argc, char** argv, char** env) {
        int err = 0;

        TALAS_LOG_MESSAGE_DEBUG("TLSv1_client_method()...");
        if ((meth = TLSv1_client_method())) {
            TALAS_LOG_MESSAGE_DEBUG("...TLSv1_client_method()");

            TALAS_LOG_MESSAGE_DEBUG("SSL_CTX_new(meth)...");
            if ((ctx = SSL_CTX_new(meth))) {
                TALAS_LOG_MESSAGE_DEBUG("...SSL_CTX_new(meth)");

                TALAS_LOG_MESSAGE_DEBUG("SSL_CTX_load_verify_locations(ctx, trust = \"" << trust << "\", certs = \"" << certs << "\")...");
                if ((SSL_CTX_load_verify_locations(ctx, trust, certs))) {
                    TALAS_LOG_MESSAGE_DEBUG("...SSL_CTX_load_verify_locations(ctx, trust = \"" << trust << "\", certs = \"" << certs << "\")");

                    TALAS_LOG_MESSAGE_DEBUG("SSL_CTX_use_certificate_file(ctx, cert = \"" << cert << "\", cert_type)...");
                    if ((SSL_CTX_use_certificate_file(ctx, cert, cert_type))) {
                        TALAS_LOG_MESSAGE_DEBUG("...SSL_CTX_use_certificate_file(ctx, cert = \"" << cert << "\", cert_type)");

                        TALAS_LOG_MESSAGE_DEBUG("SSL_CTX_use_PrivateKey_file(ctx, key = \"" << key << "\", key_type)...");
                        if ((SSL_CTX_use_PrivateKey_file(ctx, key, key_type))) {
                            TALAS_LOG_MESSAGE_DEBUG("...SSL_CTX_use_PrivateKey_file(ctx, key = \"" << key << "\", key_type)");

                            err = run_connection(argc, argv, env);
                        } else {
                            error_string = ERR_error_string(error = ERR_get_error(), NULL);
                            TALAS_LOG_MESSAGE_DEBUG
                            ("failed (" << error << ") \"" << error_string << "\" on " <<
                             "SSL_CTX_use_PrivateKey_file(ctx, key = \"" << key << "\", key_type)");
                        }
                    } else {
                        error_string = ERR_error_string(error = ERR_get_error(), NULL);
                        TALAS_LOG_MESSAGE_DEBUG
                        ("failed (" << error << ") \"" << error_string << "\" on " <<
                         "SSL_CTX_use_certificate_file(ctx, cert = \"" << cert << "\", cert_type)");
                    }
                } else {
                    error_string = ERR_error_string(error = ERR_get_error(), NULL);
                    TALAS_LOG_MESSAGE_DEBUG
                    ("failed (" << error << ") \"" << error_string << "\" on " <<
                     "SSL_CTX_load_verify_locations(ctx, trust = \"" << trust << "\", certs = \"" << certs << "\")");
                }
                TALAS_LOG_MESSAGE_DEBUG("...SSL_CTX_free(ctx)");
                SSL_CTX_free(ctx);
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_connection(int argc, char** argv, char** env) {
        int err = 0;
        if ((run_connection_)) {
            err = (this->*run_connection_)(argc, argv, env);
        } else {
            err = run_ssl_connection(argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int _run_rw_connection(int argc, char** argv, char** env) {
        int err = 0;
        FILE *in_file = std_in(), *out_file = std_out();
        io::read::file rfile(in_file);
        io::write::file wfile(out_file);
        err = run_rw_connection_rw(rfile, wfile, argc, argv, env);
        return err;
    }
    virtual int run_rw_connection(int argc, char** argv, char** env) {
        int err = 1;
        network::ip::v4::endpoint ep(host, port);
        network::ip::v4::tcp::transport tp;
        network::os::socket s;
        io::socket::tcp::reader rsock(s);
        io::socket::tcp::writer wsock(s);
        if ((s.open(tp))) {
            if ((s.connect(ep))) {
                err = run_rw_connection_rw(rsock, wsock, argc, argv, env);
            }
            s.close();
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_rw_connection_rw
    (io::reader& rd, io::writer& wr, int argc, char** argv, char** env) {
        int err = 0;
        protocol::tls::openssl::BIO_RW rw(&rd, &wr);
        BIO *rw_bio = 0;

        TALAS_LOG_MESSAGE_DEBUG("protocol::tls::openssl::BIO_new_rw(&rw)...");
        if ((rw_bio = protocol::tls::openssl::BIO_new_rw(&rw))) {
            TALAS_LOG_MESSAGE_DEBUG("...protocol::tls::openssl::BIO_new_rw(&rw)");

            TALAS_LOG_MESSAGE_DEBUG("ssl = SSL_new(ctx)...");
            if ((ssl = SSL_new(ctx))) {
                TALAS_LOG_MESSAGE_DEBUG("...ssl = SSL_new(ctx))");

                TALAS_LOG_MESSAGE_DEBUG("...SSL_set_bio(ssl, rw_bio, rw_bio)");
                SSL_set_bio(ssl, rw_bio, rw_bio);
                rw_bio = 0;

                err = run_ssl_connect(argc, argv, env);

                if ((ssl)) {
                    TALAS_LOG_MESSAGE_DEBUG("...SSL_free(ssl)");
                    SSL_free(ssl);
                    ssl = 0;
                }
            }
            if ((rw_bio)) {
                TALAS_LOG_MESSAGE_DEBUG("...BIO_free_all(rw_bio)");
                BIO_free_all(rw_bio);
                rw_bio = 0;
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_bio_rw_connection_rw
    (io::reader& rd, io::writer& wr, int argc, char** argv, char** env) {
        int err = 0;
        protocol::tls::openssl::BIO_RW rw(&rd, &wr);
        BIO *rw_bio = 0, *conn_bio = 0, *ssl_bio = 0;

        TALAS_LOG_MESSAGE_DEBUG("protocol::tls::openssl::BIO_new_rw(&rw)...");
        if ((rw_bio = protocol::tls::openssl::BIO_new_rw(&rw))) {
            TALAS_LOG_MESSAGE_DEBUG("...protocol::tls::openssl::BIO_new_rw(&rw)");

            TALAS_LOG_MESSAGE_DEBUG("BIO_new_connect(host = \"" << host << "\")...");
            if ((bio = BIO_new_connect(host))) {
                TALAS_LOG_MESSAGE_DEBUG("...BIO_new_connect(host = \"" << host << "\")");

                BIO_set_conn_hostname(bio, host);
                BIO_set_conn_int_port(bio, &port);

                TALAS_LOG_MESSAGE_DEBUG("...BIO_push(rw_bio, bio)");
                if ((conn_bio = BIO_push(rw_bio, bio))) {
                    bio = conn_bio;
                    rw_bio = 0;

                    TALAS_LOG_MESSAGE_DEBUG("BIO_new_ssl(ctx, TRUE)...");
                    if ((ssl_bio = BIO_new_ssl(ctx, TRUE))) {
                        TALAS_LOG_MESSAGE_DEBUG("...BIO_new_ssl(ctx, TRUE)");

                        TALAS_LOG_MESSAGE_DEBUG("...BIO_push(ssl_bio, bio)");
                        if ((conn_bio = BIO_push(ssl_bio, bio))) {
                            bio = conn_bio;

                            TALAS_LOG_MESSAGE_DEBUG("BIO_get_ssl(bio, &ssl)...");
                            BIO_get_ssl(bio, &ssl);
                            if ((ssl)) {
                                TALAS_LOG_MESSAGE_DEBUG("...BIO_get_ssl(bio, &ssl)");

                                SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
                                err = run_connect(argc, argv, env);
                            }
                        } else {
                            TALAS_LOG_MESSAGE_DEBUG("...BIO_free_all(ssl)");
                            BIO_free_all(ssl_bio);
                        }
                    }
                }
                TALAS_LOG_MESSAGE_DEBUG("...BIO_free_all(bio)");
                BIO_free_all(bio);
                bio = 0;
            }
            if ((rw_bio)) {
                TALAS_LOG_MESSAGE_DEBUG("...BIO_free_all(rw_bio)");
                BIO_free_all(rw_bio);
                rw_bio = 0;
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_ssl_connection(int argc, char** argv, char** env) {
        int err = 0;

        TALAS_LOG_MESSAGE_DEBUG("BIO_new_ssl_connect(ctx)...");
        if ((bio = BIO_new_ssl_connect(ctx))) {
            TALAS_LOG_MESSAGE_DEBUG("...BIO_new_ssl_connect(ctx)");

            BIO_set_conn_hostname(bio, host);
            BIO_set_conn_int_port(bio, &port);

            TALAS_LOG_MESSAGE_DEBUG("BIO_get_ssl(bio, &ssl)...");
            BIO_get_ssl(bio, &ssl);
            if ((ssl)) {
                TALAS_LOG_MESSAGE_DEBUG("...BIO_get_ssl(bio, &ssl)");

                SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
                err = run_connect(argc, argv, env);
            }
            TALAS_LOG_MESSAGE_DEBUG("...BIO_free_all(bio)");
            BIO_free_all(bio);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_connect(int argc, char** argv, char** env) {
        int err = 0;

        TALAS_LOG_MESSAGE_DEBUG("BIO_do_connect(bio)...");
        if (1 == (BIO_do_connect(bio))) {
            TALAS_LOG_MESSAGE_DEBUG("...BIO_do_connect(bio)");

            TALAS_LOG_MESSAGE_DEBUG("X509_V_OK == (SSL_get_verify_result(ssl))...");
            if (X509_V_OK == (verify = SSL_get_verify_result(ssl))) {
                TALAS_LOG_MESSAGE_DEBUG("...X509_V_OK == (SSL_get_verify_result(ssl))");
                err = run_request(argc, argv, env);
            } else {
                TALAS_LOG_MESSAGE_DEBUG("...failed X509_V_OK != (" << verify << " = SSL_get_verify_result(ssl))");
            }
            if ((X509_V_ERR_CERT_HAS_EXPIRED == (verify)) 
                || (X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT == (verify))) {
                err = run_request(argc, argv, env);
            }
            TALAS_LOG_MESSAGE_DEBUG("...BIO_reset(bio)");
            BIO_reset(bio);
        } else {
            error_string = ERR_error_string(error = ERR_get_error(), NULL);
            TALAS_LOG_MESSAGE_DEBUG
            ("failed (" << error << ") \"" << error_string << "\" on " <<
             "BIO_do_connect(bio)");
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_ssl_connect(int argc, char** argv, char** env) {
        int err = 0;

        TALAS_LOG_MESSAGE_DEBUG("SSL_connect(ssl)...");
        if (1 == (SSL_connect(ssl))) {
            TALAS_LOG_MESSAGE_DEBUG("...SSL_connect(ssl)");

            TALAS_LOG_MESSAGE_DEBUG("X509_V_OK == (SSL_get_verify_result(ssl))...");
            if (X509_V_OK == (verify = SSL_get_verify_result(ssl))) {
                TALAS_LOG_MESSAGE_DEBUG("...X509_V_OK == (SSL_get_verify_result(ssl))");

                err = run_request(argc, argv, env);
            } else {
                TALAS_LOG_MESSAGE_DEBUG("...failed X509_V_OK != (" << verify << " = SSL_get_verify_result(ssl))");
            }
        } else {
            error_string = ERR_error_string(error = ERR_get_error(), NULL);
            TALAS_LOG_MESSAGE_DEBUG
            ("failed (" << error << ") \"" << error_string << "\" on " <<
             "SSL_connect(ssl)");
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_request(int argc, char** argv, char** env) {
        int err = 0;
        if (!(err = run_write_request(argc, argv, env))) {
            err = run_read_response(argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_write_request(int argc, char** argv, char** env) {
        return run_write_http(request, request_len, argc, argv, env);
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_read_response(int argc, char** argv, char** env) {
        return run_read_http(response, argc, argv, env);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_read_http(char& http, int argc, char** argv, char** env) {
        int err = 1;
        int eol = 0;
        char last = 0;

        count = 0;
        TALAS_LOG_MESSAGE_DEBUG("read_data(&http, 1)...");
        for (bool done = false; !done; ) {
            if (0 < (amount = read_data(&http, 1))) {
                count += amount;
                out(&http, 1);
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
        out_flush();
        if (0 < (amount)) {
            TALAS_LOG_MESSAGE_DEBUG("...count = " << count << " = read_data(&http, 1)...");
            err = 0;
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_write_http
    (const char* http, int http_len, int argc, char** argv, char** env) {
        int err = 0;

        TALAS_LOG_MESSAGE_DEBUG("write_data(http = \"" << http << "\", http_len = " << http_len << ")...");
        if (0 < (count = write_data(http, http_len))) {
            TALAS_LOG_MESSAGE_DEBUG("..." << count << " = write_data(http = \"" << http << "\", http_len = " << http_len << ")");
        } else {
            err = 1;
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int read_data(void *buf, int len) {
        int count = -1;
        if ((read_data_)) {
            count = (this->*read_data_)(buf, len);
        } else {
            count = bio_read_data(buf, len);
        }
        return count;
    }
    virtual int write_data(const void *buf, int len) {
        int count = -1;
        if ((write_data_)) {
            count = (this->*write_data_)(buf, len);
        } else {
            count = bio_write_data(buf, len);
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int bio_read_data(void *buf, int len) {
        int count = -1;
        if ((buf) && (0 < len)) {
            if (0 >= (count = BIO_read(bio, buf, len))) {
                error_string = ERR_error_string(error = ERR_get_error(), NULL);
                TALAS_LOG_MESSAGE_DEBUG
                ("failed (" << error << ") \"" << error_string << "\" on " <<
                 "BIO_read(bio, buf, len)");
            }
        }
        return count;
    }
    virtual int bio_write_data(const void *buf, int len) {
        int count = -1;
        if ((buf) && (0 < len)) {
            if (0 >= (count = BIO_write(bio, buf, len))) {
                error_string = ERR_error_string(error = ERR_get_error(), NULL);
                TALAS_LOG_MESSAGE_DEBUG
                ("failed (" << error << ") \"" << error_string << "\" on " <<
                 "BIO_write(bio, buf, len)");
            }
        }
        return count;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int ssl_read_data(void *buf, int len) {
        int count = -1;
        if ((buf) && (0 < len)) {
            if (0 >= (count = SSL_read(ssl, buf, len))) {
                error_string = ERR_error_string(error = ERR_get_error(), NULL);
                TALAS_LOG_MESSAGE_DEBUG
                ("failed (" << error << ") \"" << error_string << "\" on " <<
                 "SSL_read(ssl, buf, len)");
            }
        }
        return count;
    }
    virtual int ssl_write_data(const void *buf, int len) {
        int count = -1;
        if ((buf) && (0 < len)) {
            if (0 >= (count = SSL_write(ssl, buf, len))) {
                error_string = ERR_error_string(error = ERR_get_error(), NULL);
                TALAS_LOG_MESSAGE_DEBUG
                ("failed (" << error << ") \"" << error_string << "\" on " <<
                 "SSL_write(ssl, buf, len)");
            }
        }
        return count;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_client_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        run_ = &Derives::run_client;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_server_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        run_ = &Derives::run_server;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_verify_client_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        verify_client = true;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    char_array_t host_array;
    virtual int on_host_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            host_array.assign(optarg, chars_t::count(optarg));
            accept_host = (host = host_array.elements());
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
            accept_port = (port = chars_t::to_signed(optarg));
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_connection_type_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            if (!(chars_t::compare(optarg, TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_RW_C))
                || !(chars_t::compare(optarg, TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_RW_S))) {
                run_accept_connection_ = &Derives::run_rw_accept_connection;
                run_connection_ = &Derives::run_rw_connection;
                read_data_ = &Derives::ssl_read_data;
                write_data_ = &Derives::ssl_write_data;
            } else {
                if (!(chars_t::compare(optarg, TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_SSL_C))
                    || !(chars_t::compare(optarg, TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_SSL_S))) {
                    run_accept_connection_ = &Derives::run_ssl_accept_connection;
                    run_connection_ = &Derives::run_ssl_connection;
                    read_data_ = 0;
                    write_data_ = 0;
                } else {
                }
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_one_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        accept_once = true;
        return err;
    }

#include "talas/app/console/openssl/main_opt.cpp"
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace openssl 
} // namespace console 
} // namespace app 
} // namespace talas 

#endif // _TALAS_APP_CONSOLE_OPENSSL_MAIN_HPP 
