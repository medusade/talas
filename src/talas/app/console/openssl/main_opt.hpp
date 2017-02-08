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
///   File: main_opt.hpp
///
/// Author: $author$
///   Date: 2/7/2017
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_APP_CONSOLE_OPENSSL_MAIN_OPT_HPP
#define _TALAS_APP_CONSOLE_OPENSSL_MAIN_OPT_HPP

#include "talas/crypto/console/main.hpp"

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

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

namespace talas {
namespace app {
namespace console {
namespace openssl {

} // namespace openssl 
} // namespace console 
} // namespace app 
} // namespace talas 

#endif // _TALAS_APP_CONSOLE_OPENSSL_MAIN_OPT_HPP 
