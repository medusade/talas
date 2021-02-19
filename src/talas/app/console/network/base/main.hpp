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
///   Date: 2/14/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_APP_CONSOLE_NETWORK_BASE_MAIN_HPP
#define TALAS_APP_CONSOLE_NETWORK_BASE_MAIN_HPP

#include "talas/app/console/network/base/main_opt.hpp"
#include "talas/io/socket/reader.hpp"
#include "talas/io/socket/writer.hpp"

#if !defined(TALAS_APP_CONSOLE_NETWORK_BASE_MAIN_RECVED_SIZE)
#define TALAS_APP_CONSOLE_NETWORK_BASE_MAIN_RECVED_SIZE 2048
#endif /// !defined(TALAS_APP_CONSOLE_NETWORK_BASE_MAIN_RECVED_SIZE)

namespace talas {
namespace app {
namespace console {
namespace network {
namespace base {

///////////////////////////////////////////////////////////////////////
/// class maint
///////////////////////////////////////////////////////////////////////
template <class TExtends = main_opt, class TImplements = typename TExtends::Implements>
class EXPORT_CLASS maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef maint Derives;

    typedef typename TExtends::char_t char_t;
    typedef typename TExtends::string_t string_t;
    typedef typename TExtends::reader_t reader_t;
    typedef typename TExtends::writer_t writer_t;
    
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
    typedef talas::io::socket::readert<reader_t, socket_t> socket_reader_t;
    typedef talas::io::socket::writert<writer_t, socket_t> socket_writer_t;
    typedef talas::io::sized::readert<reader_t> sized_reader_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        err = this->all_plain_sockets_run(argc, argv, env);
        return err;
    }
    virtual int before_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        TALAS_LOG_DEBUG("talas::network::os::sockets::startup()...");
        if (!(talas::network::os::sockets::startup())) {
            TALAS_LOG_ERROR("...failed on talas::network::os::sockets::startup()");
            err = 1;
        }
        return err;
    }
    virtual int after_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        TALAS_LOG_DEBUG("talas::network::os::sockets::cleanup()...");
        if (!(talas::network::os::sockets::cleanup())) {
            TALAS_LOG_ERROR("...failed on talas::network::os::sockets::cleanup()");
            err = 1;
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int plain_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int before_plain_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_plain_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_plain_sockets_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = this->before_plain_sockets_run(argc, argv, env))) {
            int err2 = 0;
            err = this->plain_sockets_run(argc, argv, env);
            if ((err2 = this->after_plain_sockets_run(argc, argv, env))) {
                if (!(err)) {
                    err = err2;
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual char_t* content(size_t& size) const {
        size = sizeof(content_);
        return (char_t*)content_;
    }
    virtual char_t* recved(size_t& size) const {
        size = sizeof(recved_);
        return (char_t*)recved_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    char_t content_[TALAS_APP_CONSOLE_NETWORK_BASE_MAIN_RECVED_SIZE],
           recved_[TALAS_APP_CONSOLE_NETWORK_BASE_MAIN_RECVED_SIZE];
}; /// class maint
typedef maint<> main;

} /// namespace base 
} /// namespace network 
} /// namespace console 
} /// namespace app 
} /// namespace talas 

#endif /// ndef TALAS_APP_CONSOLE_NETWORK_BASE_MAIN_HPP 