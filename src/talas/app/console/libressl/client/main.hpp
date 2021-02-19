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
///   File: main.hpp
///
/// Author: $author$
///   Date: 2/18/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_APP_CONSOLE_LIBRESSL_CLIENT_MAIN_HPP
#define TALAS_APP_CONSOLE_LIBRESSL_CLIENT_MAIN_HPP

#include "talas/app/console/libressl/client/main_opt.hpp"

namespace talas {
namespace app {
namespace console {
namespace libressl {
namespace client {

///////////////////////////////////////////////////////////////////////
/// class maint
///////////////////////////////////////////////////////////////////////
template 
<class TExtends = libressl::client::main_opt, class TImplements = typename TExtends::Implements>
class EXPORT_CLASS maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef maint Derives;

    typedef typename TExtends::char_t char_t;
    typedef typename TExtends::string_t string_t;
    typedef typename TExtends::reader_t reader_t;
    typedef typename TExtends::writer_t writer_t;
    typedef typename TExtends::sized_reader_t sized_reader_t;

    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    maint() {
    }
    virtual ~maint() {
    }
private:
    maint(const maint& copy): Extends(copy) {
    }

protected:
    typedef typename TExtends::socket_t socket_t;
    typedef typename socket_t::attached_t socket_attached_t;
    typedef typename TExtends::socket_reader_t socket_reader_t;
    typedef typename TExtends::socket_writer_t socket_writer_t;
    typedef typename TExtends::tls_t tls_t;
    typedef typename TExtends::tls_writer_t tls_writer_t;
    typedef typename TExtends::tls_reader_t tls_reader_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int tls_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;

        TALAS_LOG_DEBUG("tls_init()...");
        if (!(err = tls_init())) {

            err = Extends::tls_sockets_run(argc, argv, env);
            TALAS_LOG_DEBUG("tls_cleanup()...");
            tls_cleanup();
        } else {
            TALAS_LOG_ERROR("...failed err = " << err << " on tls_init()");
        }
        return err;
    }
    virtual int tls_client_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
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

                    err = all_tls_client_sockets_connect(tls, argc, argv, env);
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
    virtual int tls_client_sockets_connect(struct tls* tls, int argc, char_t** argv, char_t** env) {
        int err = 0;
        const string_t& host = this->host();
        const char *host_chars = 0;

        if ((host_chars = host.has_chars())) {
            const string_t& port = this->port();
            const char *port_chars = 0;

            if ((port_chars = port.has_chars())) {
                size_t portno = 0;
                
                if ((0 < (portno = port.to_unsigned()))) {
                    talas::network::ip::v4::endpoint ep(host_chars, portno);
                    talas::network::ip::v4::tcp::transport tp;
                    socket_t s(*this);
                    
                    if ((s.open(tp))) {
                        if ((s.connect(ep))) {
                            err = tls_client_sockets_connect_socket(s, tls, argc, argv, env);
                        }
                        if ((s.close())) {
                        }
                    }
                }
            }
        }
        return err;
    }
    virtual int before_tls_client_sockets_connect(struct tls* tls, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_tls_client_sockets_connect(struct tls* tls, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_tls_client_sockets_connect(struct tls* tls, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_tls_client_sockets_connect(tls, argc, argv, env))) {
            int err2 = 0;
            err = tls_client_sockets_connect(tls, argc, argv, env);
            if ((err2 = after_tls_client_sockets_connect(tls, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int tls_client_sockets_connect_socket(socket_t& socket, struct tls* tls, int argc, char_t** argv, char_t** env) {
        int err = 0;
        const string_t& host = this->host();
        const char *host_chars = 0;

        if ((host_chars = host.has_chars())) {
            const string_t& port = this->port();
            const char *port_chars = 0;

            if ((port_chars = port.has_chars())) {
                socket_attached_t sock = socket.attached_to();

                TALAS_LOG_DEBUG("tls_connect(tls, sock, host_chars = \"" << host_chars << "\")...");
                if (!(err = tls_connect_socket(tls, sock, host_chars))) {
        
                    TALAS_LOG_DEBUG("tls_handshake(tls)...");
                    if (!(err = tls_handshake(tls))) {

                        err = all_tls_client_make_request(tls, argc, argv, env);
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
            }
        }
        return err;
    }
    virtual int before_tls_client_sockets_connect_socket(socket_t& socket, struct tls* tls, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_tls_client_sockets_connect_socket(socket_t& socket, struct tls* tls, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_tls_client_sockets_connect_socket(socket_t& socket, struct tls* tls, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_tls_client_sockets_connect_socket(socket, tls, argc, argv, env))) {
            int err2 = 0;
            err = tls_client_sockets_connect_socket(socket, tls, argc, argv, env);
            if ((err2 = after_tls_client_sockets_connect_socket(socket, tls, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int tls_client_make_request(struct tls* tls, int argc, char_t** argv, char_t** env) {
        int err = 0;
        
        if ((tls)) {
            string_t& request = this->request();
            tls_writer_t writer(tls);

            if (!(err = this->all_write_request(writer, request, argc, argv, env))) {
                string_t& response = this->response();
                tls_reader_t reader(tls);
                
                if (!(err = this->all_read_response(response, reader, argc, argv, env))) {

                    if (!(err = this->all_on_recv_response(response, reader, argc, argv, env))) {
                    }
                }
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int tls_client_write_request(struct tls* tls, int argc, char_t** argv, char_t** env) {
        string_t& request = this->request();
        const char_t* request_chars = 0; size_t request_len = 0;
        int err = 0;

        if ((tls) && (request_chars = request.has_chars(request_len))) {
            tls_writer_t tls_writer(tls);
            ssize_t count = 0, amount = 0;

            TALAS_LOG_DEBUG("tls_writer.write(tls, request_chars = \"" << request_chars << "\", request_len = " << request_len << ")...");
            if (((0 < (amount = tls_writer.write(tls, request_chars, request_len))))) {
                char_t* recved = 0; size_t recved_size = 0;
                
                if ((recved = this->recved(recved_size))) {
                    tls_reader_t tls_reader(tls);

                    do {
                        if (0 < (amount = tls_reader.read(tls, recved, recved_size))) {
                            this->out(recved, amount);
                            this->out_flush();
                            count += amount;
                        } else {
                            if (0 > (amount)) {
                                TALAS_LOG_ERROR("...failed amount = " << amount << " tls_reader.read(tls, recved, recved_size = " << recved_size << ")");
                            }
                        }
                    } while (0 < (amount));
                }
            } else {
                TALAS_LOG_ERROR("...failed amount = " << amount << " tls_writer.write(tls, request_chars = \"" << request_chars << "\", request_len = " << request_len << ")");
            }
        }
        return err;
    }
    virtual int before_tls_client_make_request(struct tls* tls, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_tls_client_make_request(struct tls* tls, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_tls_client_make_request(struct tls* tls, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_tls_client_make_request(tls, argc, argv, env))) {
            int err2 = 0;
            err = tls_client_make_request(tls, argc, argv, env);
            if ((err2 = after_tls_client_make_request(tls, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
}; /// class maint
typedef maint<> main;

} /// namespace client 
} /// namespace libressl 
} /// namespace console 
} /// namespace app 
} /// namespace talas 

#endif /// ndef TALAS_APP_CONSOLE_LIBRESSL_CLIENT_MAIN_HPP 