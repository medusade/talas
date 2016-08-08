///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2016 $organization$
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
///   Date: 1/6/2016
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_HPP
#define _TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_HPP

#include "talas/protocol/tls/openssl/daemon/main_opt.hpp"
#include "talas/protocol/tls/openssl/openssl.hpp"

#define TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_ACCEPT_HOST "*"
#define TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_ACCEPT_PORT 4433
#define TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_HOST "localhost"
#define TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_PORT 4433
#define TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_KEY "./creds/localhost.key.pem"
#define TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_KEY_TYPE SSL_FILETYPE_PEM
#define TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_CERT "./creds/localhost.cert.pem"
#define TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_CERT_TYPE SSL_FILETYPE_PEM
#define TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_TRUST "./creds/localhost.cert.pem"
#define TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_CERTS "./creds/certs"
#define TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_REQUEST "GET / HTTP/1.0\r\n\r\n"
#define TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_RESPONSE "HTTP/1.0 200 OK\r\n\r\nOK\r\n"
#define TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_VERIFY_CLIENT false
#define TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_VERIFY_DEPTH 1

namespace talas {
namespace protocol {
namespace tls {
namespace openssl {
namespace daemon {

typedef coral::console::daemon::main_implements main_implements;
typedef coral::console::daemon::main main_extends;
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
        accept_host = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_ACCEPT_HOST;
        accept_port = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_ACCEPT_PORT;
        host = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_HOST;
        port = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_PORT;
        key = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_KEY;
        key_type = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_KEY_TYPE;
        cert = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_CERT;
        cert_type = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_CERT_TYPE;
        trust = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_TRUST;
        certs = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_CERTS;
        request = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_REQUEST;
        request_len = chars_t::count(request);
        response = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_RESPONSE;
        response_len = chars_t::count(response);
        verify_client = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_VERIFY_CLIENT;
        verify_depth = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_VERIFY_DEPTH;
        done = false; http = 0; count = 0; verify = 0;
        error = 0; error_string = 0;
        meth = 0; ctx = 0; ssl = 0; bio = 0;
        run_ = 0;
    }
    virtual ~main() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    char* accept_host; int accept_port;
    char* host; int port;
    char* key; int key_type;
    char* cert; int cert_type;
    char* trust; char* certs;
    char* request; int request_len;
    char* response; int response_len;
    bool verify_client; int verify_depth;
    bool done; char http; int count; long verify;
    unsigned long error; char* error_string;
    SSL_METHOD* meth; SSL_CTX* ctx; SSL* ssl; BIO* bio;
    int (Derives::*run_)(int argc, char** argv, char** env);

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
            err = run_server(argc, argv, env);
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
                                    TALAS_LOG_MESSAGE_DEBUG("SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL)...");
                                    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);
                                    TALAS_LOG_MESSAGE_DEBUG("SL_CTX_set_verify_depth(ctx, 1)...");
                                    SSL_CTX_set_verify_depth(ctx, verify_depth);
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
        } while (did_accept && !done);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_accept_request(int argc, char** argv, char** env) {
        int err = 0;
        if (!(err = run_read_http(http, argc, argv, env))) {
            err = run_write_http(response, response_len, argc, argv, env);
        }
        return err;
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

#include "talas/protocol/tls/openssl/daemon/main_opt.cpp"
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace daemon 
} // namespace openssl 
} // namespace tls 
} // namespace protocol 
} // namespace talas 

#endif // _TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_HPP 
