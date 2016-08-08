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
///   File: main_opt.cpp
///
/// Author: $author$
///   Date: 1/6/2016
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_HPP

#include "talas/protocol/tls/openssl/daemon/main_opt.hpp"

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
#endif // _TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_HPP

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_host_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        //if ((optarg) && (optarg[0])) {
        //    TALAS_LOG_DEBUG("optarg = \"" << optarg << "\"...");
        //    if (!(set_host(optarg))) {
        //        TALAS_LOG_ERROR("...failed on set_host(\"" << optarg << "\")");
        //    }
        //}
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_port_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        //if ((optarg) && (optarg[0])) {
        //    TALAS_LOG_DEBUG("optarg = \"" << optarg << "\"...");
        //    if (!(set_port(optarg))) {
        //        TALAS_LOG_ERROR("...failed on set_port(\"" << optarg << "\")");
        //    }
        //}
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_cert_file_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        //if ((optarg) && (optarg[0])) {
        //    TALAS_LOG_DEBUG("optarg = \"" << optarg << "\"...");
        //    if (!(set_cert_file(optarg))) {
        //        TALAS_LOG_ERROR("...failed on set_cert_file(\"" << optarg << "\")");
        //    }
        //}
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_key_file_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        //if ((optarg) && (optarg[0])) {
        //    TALAS_LOG_DEBUG("optarg = \"" << optarg << "\"...");
        //    if (!(set_key_file(optarg))) {
        //        TALAS_LOG_ERROR("...failed on set_key_file(\"" << optarg << "\")");
        //    }
        //}
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_trust_cert_file_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        //if ((optarg) && (optarg[0])) {
        //    TALAS_LOG_DEBUG("optarg = \"" << optarg << "\"...");
        //    if (!(set_trust_cert_file(optarg))) {
        //        TALAS_LOG_ERROR("...failed on set_trust_cert_file(\"" << optarg << "\")");
        //    }
        //}
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_trust_cert_directory_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        //if ((optarg) && (optarg[0])) {
        //    TALAS_LOG_DEBUG("optarg = \"" << optarg << "\"...");
        //    if (!(set_trust_cert_directory(optarg))) {
        //        TALAS_LOG_ERROR("...failed on set_trust_cert_directory(\"" << optarg << "\")");
        //    }
        //}
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
        case TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_HOST_OPTVAL_C:
            err = on_host_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_PORT_OPTVAL_C:
            err = on_port_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_CERT_FILE_OPTVAL_C:
            err = on_cert_file_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_KEY_FILE_OPTVAL_C:
            err = on_key_file_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_TRUST_CERT_FILE_OPTVAL_C:
            err = on_trust_cert_file_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_TRUST_CERT_DIRECTORY_OPTVAL_C:
            err = on_trust_cert_directory_option
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
        case TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_HOST_OPTVAL_C:
            optarg = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_HOST_OPTARG;
            chars = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_HOST_OPTUSE;
            break;
        case TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_PORT_OPTVAL_C:
            optarg = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_PORT_OPTARG;
            chars = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_PORT_OPTUSE;
            break;
        case TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_CERT_FILE_OPTVAL_C:
            optarg = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_CERT_FILE_OPTARG;
            chars = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_CERT_FILE_OPTUSE;
            break;
        case TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_KEY_FILE_OPTVAL_C:
            optarg = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_KEY_FILE_OPTARG;
            chars = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_KEY_FILE_OPTUSE;
            break;
        case TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_TRUST_CERT_FILE_OPTVAL_C:
            optarg = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_TRUST_CERT_FILE_OPTARG;
            chars = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_TRUST_CERT_FILE_OPTUSE;
            break;
        case TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_TRUST_CERT_DIRECTORY_OPTVAL_C:
            optarg = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_TRUST_CERT_DIRECTORY_OPTARG;
            chars = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_TRUST_CERT_DIRECTORY_OPTUSE;
            break;
        default:
            chars = Extends::option_usage(optarg, longopt);
        }
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* options(const struct option*& longopts) {
        int err = 0;
        static const char_t* chars = TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

#ifndef _TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_HPP
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace daemon
} // namespace openssl 
} // namespace tls 
} // namespace protocol 
} // namespace talas 

#endif // _TALAS_PROTOCOL_TLS_OPENSSL_DAEMON_MAIN_HPP
