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

#include "talas/crypto/console/main.hpp"
#include "talas/protocol/tls/openssl/bio_rw.hpp"
#include "talas/protocol/tls/openssl/openssl.hpp"

#define TALAS_APP_CONSOLE_OPENSSL_VERIFY_CLIENT false

#define TALAS_APP_CONSOLE_OPENSSL_ACCEPT_HOST "*"
#define TALAS_APP_CONSOLE_OPENSSL_ACCEPT_PORT 4433
#define TALAS_APP_CONSOLE_OPENSSL_ACCEPT_RESPONSE "HTTP/1.0 200 OK\r\n\r\nOK\r\n"

#define TALAS_APP_CONSOLE_OPENSSL_HOST "localhost"
#define TALAS_APP_CONSOLE_OPENSSL_PORT 443
#define TALAS_APP_CONSOLE_OPENSSL_KEY "./creds/localhost.key.pem"
#define TALAS_APP_CONSOLE_OPENSSL_KEY_TYPE SSL_FILETYPE_PEM
#define TALAS_APP_CONSOLE_OPENSSL_CERT "./creds/localhost.cert.pem"
#define TALAS_APP_CONSOLE_OPENSSL_CERT_TYPE SSL_FILETYPE_PEM
#define TALAS_APP_CONSOLE_OPENSSL_TRUST "./creds/localhost.cert.pem"
#define TALAS_APP_CONSOLE_OPENSSL_CERTS "./creds/certs"
#define TALAS_APP_CONSOLE_OPENSSL_REQUEST "GET / HTTP/1.0\r\n\r\n"

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPT "client"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPTARG ""
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPTUSE "Run as client"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPTVAL_S "c"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPTVAL_C 'c'
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPTION \
   {TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPT, \
    TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPT "server"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPTARG ""
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPTUSE "Run as server"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPTVAL_S "s"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPTVAL_C 's'
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPTION \
   {TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPT, \
    TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPT "verify-client"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPTARG ""
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPTUSE "Verify client"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPTVAL_S "v"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPTVAL_C 'v'
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPTION \
   {TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPT, \
    TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPT "port"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPTARG "<number>"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPTUSE "Port number"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPTVAL_S "p:"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPTVAL_C 'p'
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPTION \
   {TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPT, \
    TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPT "connection-type"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_RW_C "r"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_RW_S "read-write"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_SSL_C "s"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_SSL_S "ssl"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG "{" \
    "(" TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_RW_C ")" \
        TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_RW_S \
    " | (" TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_SSL_C ")" \
        TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_SSL_S \
    "}"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTUSE ""
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTVAL_S "n:"
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTVAL_C 'n'
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTION \
   {TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPT, \
    TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTVAL_C}, \

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define TALAS_APP_CONSOLE_OPENSSL_MAIN_OPTIONS_CHARS \
   TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPTVAL_S \
   TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPTVAL_S \
   TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPTVAL_S \
   TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPTVAL_S \
   TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTVAL_S \
   TALAS_CONSOLE_MAIN_OPTIONS_CHARS

#define TALAS_APP_CONSOLE_OPENSSL_MAIN_OPTIONS_OPTIONS \
   TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPTION \
   TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPTION \
   TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPTION \
   TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPTION \
   TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTION \
   TALAS_CONSOLE_MAIN_OPTIONS_OPTIONS

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
        count = 0; verify = 0;
        error = 0; error_string = 0;
        meth = 0; ctx = 0; ssl = 0;
        bio = 0;
        run_ = 0;
        run_connection_ = 0;
        run_accept_connection_ = 0;
    }
    virtual ~main() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    typedef int (Derives::*run_t)(int argc, char** argv, char** env);

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    run_t run_, run_connection_, run_accept_connection_;
    bool verify_client;
    char* accept_host; int accept_port;
    char* host; int port;
    char* key; int key_type;
    char* cert; int cert_type;
    char* trust; char* certs;
    char* request; int request_len; char response;
    char* accept_response; int accept_response_len; char accept_request;
    int count; long verify;
    unsigned long error; char* error_string;
    SSL_METHOD* meth; SSL_CTX* ctx; SSL* ssl;
    BIO* bio;

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
                                err = run_accept_connection(argc, argv, env);
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
    virtual int run_ssl_accept_connection(int argc, char** argv, char** env) {
        int err = 0;
        BIO *ssl_bio = 0;
        protocol::tls::openssl::port port(accept_host, accept_port);

        TALAS_LOG_MESSAGE_DEBUG("ssl = SSL_new(ctx)...");
        if ((ssl = SSL_new(ctx))) {
            TALAS_LOG_MESSAGE_DEBUG("...ssl = SSL_new(ctx))");

            TALAS_LOG_MESSAGE_DEBUG("ssl_bio = BIO_new_ssl(ctx, FALSE)...");
            if ((ssl_bio = BIO_new_ssl(ctx, FALSE))) {
                TALAS_LOG_MESSAGE_DEBUG("...ssl_bio = BIO_new_ssl(ctx, FALSE)");

                TALAS_LOG_MESSAGE_DEBUG("bio = BIO_new_accept(port)...");
                if ((bio = BIO_new_accept(port))) {
                    TALAS_LOG_MESSAGE_DEBUG("...bio = BIO_new_accept(port)");

                    TALAS_LOG_MESSAGE_DEBUG("...BIO_set_accept_bios(bio, ssl_bio)");
                    BIO_set_accept_bios(bio, ssl_bio);
                    ssl_bio = 0;

                    err = run_accept(argc, argv, env);

                    if ((bio)) {
                        TALAS_LOG_MESSAGE_DEBUG("...BIO_free_all(bio)");
                        BIO_free_all(bio);
                    }
                }
                if ((ssl_bio)) {
                    TALAS_LOG_MESSAGE_DEBUG("...BIO_free_all(ssl_bio)");
                    BIO_free_all(ssl_bio);
                }
            } else {
            }
            if ((ssl)) {
                TALAS_LOG_MESSAGE_DEBUG("...SSL_free(ssl)");
                SSL_free(ssl);
            }
        } else {
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_accept(int argc, char** argv, char** env) {
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
                }
            } else {
                error_string = ERR_error_string(error = ERR_get_error(), NULL);
                TALAS_LOG_MESSAGE_DEBUG
                ("failed (" << error << ") \"" << error_string << "\" on " <<
                 "BIO_do_accept(bio)");
                err = 1;
            }
        } while (did_accept);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_accept_request(int argc, char** argv, char** env) {
        int err = 0;
        if (!(err = run_read_request(argc, argv, env))) {
            err = run_write_response(argc, argv, env);
        }
        if (0 <= (count)) {
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
    virtual int run_rw_connection(int argc, char** argv, char** env) {
        int err = 0;
        FILE *in_file = std_in(),
             *out_file = std_out();
        io::read::file rfile(in_file);
        io::write::file wfile(out_file);
        io::reader* rd = &rfile;
        io::writer* wr = &wfile;
        protocol::tls::openssl::BIO_RW rw(rd, wr);
        BIO *rw_bio = 0, *conn_bio = 0, *ssl_bio = 0;

        TALAS_LOG_MESSAGE_DEBUG("BIO_new_connect(host = \"" << host << "\")...");
        if ((bio = BIO_new_connect(host))) {
            TALAS_LOG_MESSAGE_DEBUG("...BIO_new_connect(host = \"" << host << "\")");

            BIO_set_conn_hostname(bio, host);
            BIO_set_conn_int_port(bio, &port);

            TALAS_LOG_MESSAGE_DEBUG("protocol::tls::openssl::BIO_new_rw(&rw)...");
            if ((rw_bio = protocol::tls::openssl::BIO_new_rw(&rw))) {
                TALAS_LOG_MESSAGE_DEBUG("...protocol::tls::openssl::BIO_new_rw(&rw)");

                if ((conn_bio = BIO_push(rw_bio, bio))) {
                    bio = conn_bio;
                    TALAS_LOG_MESSAGE_DEBUG("BIO_new_ssl(ctx, TRUE)...");
                    if ((ssl_bio = BIO_new_ssl(ctx, TRUE))) {
                        TALAS_LOG_MESSAGE_DEBUG("...BIO_new_ssl(ctx, TRUE)");

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
                } else {
                    BIO_free_all(rw_bio);
                }
            }
            TALAS_LOG_MESSAGE_DEBUG("...BIO_free_all(bio)");
            BIO_free_all(bio);
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

        TALAS_LOG_MESSAGE_DEBUG("count = BIO_read(bio, &http, 1)...");
        for (bool done = false; !done; ) {
            if (0 < (count = BIO_read(bio, &http, 1))) {
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
        TALAS_LOG_MESSAGE_DEBUG("...count = " << count << " = BIO_read(bio, &http, 1)");
        if (0 > (count)) {
            error_string = ERR_error_string(error = ERR_get_error(), NULL);
            TALAS_LOG_MESSAGE_DEBUG
            ("failed (" << error << ") \"" << error_string << "\" on " <<
             "BIO_read(bio, &http, 1)");
        } else {
            if (0 < (count)) {
                err = 0;
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_write_http
    (const char* http, int http_len, int argc, char** argv, char** env) {
        int err = 0;

        TALAS_LOG_MESSAGE_DEBUG("BIO_write(bio, http = \"" << http << "\", http_len = " << http_len << ")...");
        if (0 <= (BIO_write(bio, http, http_len))) {
            TALAS_LOG_MESSAGE_DEBUG("...BIO_write(bio, http = \"" << http << "\", http_len = " << http_len << ")");
        } else {
            error_string = ERR_error_string(error = ERR_get_error(), NULL);
            TALAS_LOG_MESSAGE_DEBUG
            ("failed (" << error << ") \"" << error_string << "\" on " <<
             count << " != BIO_write(bio, http = \"" << http << "\", http_len = " << http_len << ")");
            err = 1;
        }
        return err;
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
                run_connection_ = &Derives::run_rw_connection;
            } else {
                if (!(chars_t::compare(optarg, TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_SSL_C))
                    || !(chars_t::compare(optarg, TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG_SSL_S))) {
                    run_connection_ = &Derives::run_ssl_connection;
                } else {
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {
        case TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPTVAL_C:
            err = on_client_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPTVAL_C:
            err = on_server_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPTVAL_C:
            err = on_verify_client_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPTVAL_C:
            err = on_port_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTVAL_C:
            err = on_connection_type_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        default:
            err = Extends::on_option
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* option_usage
    (const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {
        case TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPTARG;
            chars = TALAS_APP_CONSOLE_OPENSSL_MAIN_CLIENT_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPTARG;
            chars = TALAS_APP_CONSOLE_OPENSSL_MAIN_SERVER_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPTARG;
            chars = TALAS_APP_CONSOLE_OPENSSL_MAIN_VERIFY_CLIENT_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPTARG;
            chars = TALAS_APP_CONSOLE_OPENSSL_MAIN_PORT_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTARG;
            chars = TALAS_APP_CONSOLE_OPENSSL_MAIN_CONNECTION_TYPE_OPTUSE;
            break;
        default:
            chars = Extends::option_usage(optarg, longopt);
        }
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* options(const struct option*& longopts) {
        int err = 0;
        static const char_t* chars = TALAS_APP_CONSOLE_OPENSSL_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            TALAS_APP_CONSOLE_OPENSSL_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace openssl 
} // namespace console 
} // namespace app 
} // namespace talas 

#endif // _TALAS_APP_CONSOLE_OPENSSL_MAIN_HPP 
