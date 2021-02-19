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
///   Date: 2/18/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_APP_CONSOLE_PROTOCOL_TLS_CLIENT_MAIN_OPT_HPP
#define TALAS_APP_CONSOLE_PROTOCOL_TLS_CLIENT_MAIN_OPT_HPP

#include "talas/app/console/protocol/tls/base/main.hpp"
#include "talas/app/console/network/client/main.hpp"

namespace talas {
namespace app {
namespace console {
namespace protocol {
namespace tls {
namespace client {

///////////////////////////////////////////////////////////////////////
/// class main_optt
///////////////////////////////////////////////////////////////////////
template 
<class TExtends = network::client::maint
 <protocol::tls::base::maint<network::client::main_opt> >, 
 class TImplements = typename TExtends::Implements>
class EXPORT_CLASS main_optt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef main_optt Derives;

    typedef typename TExtends::char_t char_t;
    typedef typename TExtends::string_t string_t;
    typedef typename TExtends::reader_t reader_t;
    typedef typename TExtends::writer_t writer_t;
    typedef talas::io::sized::readert<reader_t> sized_reader_t;

    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    main_optt(): tls_sockets_run_(0) {
    }
    virtual ~main_optt() {
    }
private:
    main_optt(const main_optt& copy): Extends(copy) {
    }
    
protected:
    typedef typename TExtends::socket_t socket_t;
    typedef talas::io::socket::readert<reader_t, socket_t> socket_reader_t;
    typedef talas::io::socket::writert<writer_t, socket_t> socket_writer_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int (Derives::*tls_sockets_run_)(int argc, char_t** argv, char_t** env);
    virtual int tls_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if ((this->tls_sockets_run_)) {
            err = (this->*tls_sockets_run_)(argc, argv, env);
        } else {
            err = Extends::tls_sockets_run(argc, argv, env);
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int tls_client_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        err = this->all_plain_client_sockets_run(argc, argv, env);
        return err;
    }
    virtual int before_tls_client_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_tls_client_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_tls_client_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = this->before_tls_client_sockets_run(argc, argv, env))) {
            int err2 = 0;
            err = this->tls_client_sockets_run(argc, argv, env);
            if ((err2 = this->after_tls_client_sockets_run(argc, argv, env))) {
                if (!(err)) {
                    err = err2;
                }
            }
        }
        return err;
    }
    virtual int set_client_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        tls_sockets_run_ = &Derives::all_tls_client_sockets_run;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
}; /// class main_optt
typedef main_optt<> main_opt;

} /// namespace client 
} /// namespace tls 
} /// namespace protocol 
} /// namespace console 
} /// namespace app 
} /// namespace talas 

#endif /// ndef TALAS_APP_CONSOLE_PROTOCOL_TLS_CLIENT_MAIN_OPT_HPP 