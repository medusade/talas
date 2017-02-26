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
///   File: main_opt.cpp
///
/// Author: $author$
///   Date: 2/13/2017
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_APP_CONSOLE_HELLO_MAIN_HPP
#include "talas/app/console/hello/main_opt.hpp"

namespace talas {
namespace app {
namespace console {
namespace hello {

typedef implement_base main_implements;
typedef base main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main: virtual public main_implements, public main_extends {
public:
    typedef main_implements Implements;
    typedef main_extends Extends;
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main() {
    }
    virtual ~main() {
    }
#endif // _TALAS_APP_CONSOLE_HELLO_MAIN_HPP

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        switch(optval) {
        case TALAS_APP_CONSOLE_HELLO_MAIN_CLIENT_OPTVAL_C:
            err = on_client_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_HELLO_MAIN_SERVER_OPTVAL_C:
            err = on_server_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_HELLO_MAIN_VERIFY_OPTVAL_C:
            err = on_verify_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_HELLO_MAIN_ONE_OPTVAL_C:
            err = on_one_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_HELLO_MAIN_HOST_OPTVAL_C:
            err = on_host_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_HELLO_MAIN_PORT_OPTVAL_C:
            err = on_port_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        default:
            err = Extends::on_option
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char* option_usage
    (const char*& optarg, const struct option* longopt) {
        const char* chars = "";
        switch(longopt->val) {
        case TALAS_APP_CONSOLE_HELLO_MAIN_CLIENT_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_HELLO_MAIN_CLIENT_OPTARG;
            chars = TALAS_APP_CONSOLE_HELLO_MAIN_CLIENT_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_HELLO_MAIN_SERVER_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_HELLO_MAIN_SERVER_OPTARG;
            chars = TALAS_APP_CONSOLE_HELLO_MAIN_SERVER_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_HELLO_MAIN_VERIFY_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_HELLO_MAIN_VERIFY_OPTARG;
            chars = TALAS_APP_CONSOLE_HELLO_MAIN_VERIFY_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_HELLO_MAIN_ONE_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_HELLO_MAIN_ONE_OPTARG;
            chars = TALAS_APP_CONSOLE_HELLO_MAIN_ONE_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_HELLO_MAIN_HOST_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_HELLO_MAIN_HOST_OPTARG;
            chars = TALAS_APP_CONSOLE_HELLO_MAIN_HOST_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_HELLO_MAIN_PORT_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_HELLO_MAIN_PORT_OPTARG;
            chars = TALAS_APP_CONSOLE_HELLO_MAIN_PORT_OPTUSE;
            break;
        default:
            chars = Extends::option_usage(optarg, longopt);
        }
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char* options(const struct option*& longopts) {
        int err = 0;
        static const char* chars = TALAS_APP_CONSOLE_HELLO_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            TALAS_APP_CONSOLE_HELLO_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_APP_CONSOLE_HELLO_MAIN_HPP
};

} // namespace hello
} // namespace console 
} // namespace app 
} // namespace talas 
#endif // _TALAS_APP_CONSOLE_HELLO_MAIN_HPP
