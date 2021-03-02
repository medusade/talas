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
///   File: main_opt.hpp
///
/// Author: $author$
///   Date: 2/14/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_OPT_HPP
#define TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_OPT_HPP

#include "talas/app/console/network/base/main.hpp"

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPT "client"
#define TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPTARG ""
#define TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPTUSE "Run as client"
#define TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPTVAL_S "c"
#define TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPTVAL_C 'c'
#define TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPTION \
   {TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPT, \
    TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_OPTIONS_CHARS_EXTEND \
   TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPTVAL_S \

#define TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_OPTIONS_OPTIONS_EXTEND \
    TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPTION \

#define TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_OPTIONS_CHARS \
    TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_OPTIONS_CHARS_EXTEND \
    TALAS_APP_CONSOLE_NETWORK_BASE_MAIN_OPTIONS_CHARS \

#define TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_OPTIONS_OPTIONS \
    TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_OPTIONS_OPTIONS_EXTEND \
    TALAS_APP_CONSOLE_NETWORK_BASE_MAIN_OPTIONS_OPTIONS \

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

namespace talas {
namespace app {
namespace console {
namespace network {
namespace client {

///////////////////////////////////////////////////////////////////////
/// class main_optt
///////////////////////////////////////////////////////////////////////
template <class TExtends = network::base::main, class TImplements = typename TExtends::Implements>
class EXPORT_CLASS main_optt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef main_optt Derives;

    typedef typename TExtends::writer_t writer_t;
    typedef typename TExtends::reader_t reader_t;
    typedef typename TExtends::string_t string_t;
    typedef typename TExtends::char_t char_t;
    
    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    main_optt(): plain_sockets_run_(0) {
    }
    virtual ~main_optt() {
    }
private:
    main_optt(const main_optt& copy): Extends(copy) {
    }

protected:
    typedef typename TExtends::socket_t socket_t;
    typedef typename TExtends::socket_reader_t socket_reader_t;
    typedef typename TExtends::socket_writer_t socket_writer_t;
    typedef typename TExtends::sized_reader_t sized_reader_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int (Derives::*plain_sockets_run_)(int argc, char_t** argv, char_t** env);
    virtual int plain_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if ((this->plain_sockets_run_)) {
            err = (this->*plain_sockets_run_)(argc, argv, env);
        } else {
            err = Extends::plain_sockets_run(argc, argv, env);
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int plain_client_sockets_run(int argc, char_t** argv, char_t** env) {
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
                            err = this->all_client_sockets_run(s, argc, argv, env);
                        }
                        if ((s.close())) {
                        }
                    }
                }
            }
        }
        return err;
    }
    virtual int before_plain_client_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_plain_client_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_plain_client_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = this->before_plain_client_sockets_run(argc, argv, env))) {
            int err2 = 0;
            err = this->plain_client_sockets_run(argc, argv, env);
            if ((err2 = this->after_plain_client_sockets_run(argc, argv, env))) {
                if (!(err)) {
                    err = err2;
                }
            }
        }
        return err;
    }
    virtual int set_client_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        plain_sockets_run_ = &Derives::all_plain_client_sockets_run;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int client_sockets_run(socket_t& socket, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int before_client_sockets_run(socket_t& socket, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_client_sockets_run(socket_t& socket, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_client_sockets_run(socket_t& socket, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = this->before_client_sockets_run(socket, argc, argv, env))) {
            int err2 = 0;
            err = this->client_sockets_run(socket, argc, argv, env);
            if ((err2 = this->after_client_sockets_run(socket, argc, argv, env))) {
                if (!(err)) {
                    err = err2;
                }
            }
        }
        return err;
    }
    virtual int set_client_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = this->set_sockets_run(argc, argv, env))) {
            if (!(err = this->set_client_sockets_run(argc, argv, env))) {
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_client_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = this->set_client_run(argc, argv, env))) {
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
        case TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPTVAL_C:
            err = on_client_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        default:
            err = Extends::on_option
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* option_usage
    (const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {
        case TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPTARG;
            chars = TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_CLIENT_OPTUSE;
            break;
        default:
            chars = Extends::option_usage(optarg, longopt);
        }
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* options(const struct option*& longopts) {
        int err = 0;
        static const char_t* chars = TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
}; /// class main_optt
typedef main_optt<> main_opt;

} /// namespace client 
} /// namespace network 
} /// namespace console 
} /// namespace app 
} /// namespace talas 

#endif /// ndef TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_OPT_HPP 