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
///   Date: 2/25/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_APP_CONSOLE_VIZIO_CLIENT_MAIN_OPT_HPP
#define TALAS_APP_CONSOLE_VIZIO_CLIENT_MAIN_OPT_HPP

#include "talas/app/console/vizio/base/main.hpp"
#include "talas/app/console/libressl/client/main.hpp"

#define TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPT "hdmi-input"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPTARG "[1...]"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPTUSE "Select HDMI input"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPTVAL_S "m::"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPTVAL_C 'm'
#define TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPTION \
   {TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPT "input"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPTARG ""
#define TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPTUSE "Set/Get current input"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPTVAL_S "i::"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPTVAL_C 'i'
#define TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPTION \
   {TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPT "volume-up"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPTARG "[ 1... ]"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPTUSE "Increase volume"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPTVAL_S "u::"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPTVAL_C 'u'
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPTION \
   {TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPT "volume-down"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPTARG "[ 1... ]"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPTUSE "Decrease volume"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPTVAL_S "d::"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPTVAL_C 'd'
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPTION \
   {TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPT "volume"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPTARG "[ [1...] | +[1...] | -[1..] | up[1..] | down[1..] ]"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPTUSE "Set/Get volume"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPTVAL_S "v::"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPTVAL_C 'v'
#define TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPTION \
   {TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPT "auth-token"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPTARG "[ string ]"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPTUSE "Set / Get auth token"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPTVAL_S "a::"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPTVAL_C 'a'
#define TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPTION \
   {TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPT "pairing-pair"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPTARG ""
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPTUSE "Pair application"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPTVAL_S "r::"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPTVAL_C 'r'
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPTION \
   {TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPT "pairing-start"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPTARG ""
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPTUSE "Start application pairing"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPTVAL_S "s::"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPTVAL_C 's'
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPTION \
   {TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPT "pairing-stop"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPTARG ""
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPTUSE "Stop application pairing"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPTVAL_S "t::"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPTVAL_C 't'
#define TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPTION \
   {TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPT "power"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPTARG ""
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPTUSE "Power status"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPTVAL_S "w::"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPTVAL_C 'w'
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPTION \
   {TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPT "power-on"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPTARG ""
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPTUSE "Power on"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPTVAL_S "n::"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPTVAL_C 'n'
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPTION \
   {TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPT "power-off"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPTARG ""
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPTUSE "Power off"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPTVAL_S "f::"
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPTVAL_C 'f'
#define TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPTION \
   {TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_VIZIO_MAIN_OPTIONS_CHARS_EXTEND \
   TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPTVAL_S \
   TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPTVAL_S \
    TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPTVAL_S \
    TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPTVAL_S \
    TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPTVAL_S \
    TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPTVAL_S \
    TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPTVAL_S \
    TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPTVAL_S \
    TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPTVAL_S \
    TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPTVAL_S \
    TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPTVAL_S \
    TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPTVAL_S \

#define TALAS_APP_CONSOLE_VIZIO_MAIN_OPTIONS_OPTIONS_EXTEND \
   TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPTION \
   TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPTION \
    TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPTION \
    TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPTION \
    TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPTION \
    TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPTION \
    TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPTION \
    TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPTION \
    TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPTION \
    TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPTION \
    TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPTION \
    TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPTION \

#define TALAS_APP_CONSOLE_VIZIO_MAIN_OPTIONS_CHARS \
   TALAS_APP_CONSOLE_VIZIO_MAIN_OPTIONS_CHARS_EXTEND \
   TALAS_APP_CONSOLE_NETWORK_BASE_MAIN_OPTIONS_CHARS \

#define TALAS_APP_CONSOLE_VIZIO_MAIN_OPTIONS_OPTIONS \
   TALAS_APP_CONSOLE_VIZIO_MAIN_OPTIONS_OPTIONS_EXTEND \
   TALAS_APP_CONSOLE_NETWORK_BASE_MAIN_OPTIONS_OPTIONS \

namespace talas {
namespace app {
namespace console {
namespace vizio {
namespace client {

///////////////////////////////////////////////////////////////////////
/// class main_optt
///////////////////////////////////////////////////////////////////////
template 
<class TExtends = vizio::base::maint< vizio::base::main_optt<libressl::client::main> >, 
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
    typedef typename TExtends::sized_reader_t sized_reader_t;

    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    main_optt() {
    }
    virtual ~main_optt() {
    }
private:
    main_optt(const main_optt& copy) {
        throw exception(exception_unexpected);
    }

protected:
    typedef typename TExtends::io_t io_t;
    typedef typename TExtends::in_reader_t in_reader_t;
    typedef typename TExtends::out_writer_t out_writer_t;
    typedef typename TExtends::err_writer_t err_writer_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_hdmi_n_input_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
            err = this->on_hdmi_1_input_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual int on_hdmi_1_input_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            err = this->on_hdmi_n_input_option(optval, optarg, optname, optind, argc, argv, env);
        } else {
        }
        return err;
    }
    virtual int on_hdmi_input_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            err = this->on_hdmi_n_input_option(optval, optarg, optname, optind, argc, argv, env);
        } else {
            err = this->on_hdmi_1_input_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* hdmi_input_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPTUSE;
        optarg = TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPTARG;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_get_input_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            err = this->on_set_input_option(optval, optarg, optname, optind, argc, argv, env);
        } else {
        }
        return err;
    }
    virtual int on_set_input_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
            err = this->on_get_input_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual int on_input_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            err = this->on_set_input_option(optval, optarg, optname, optind, argc, argv, env);
        } else {
            err = this->on_get_input_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* input_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPTUSE;
        optarg = TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPTARG;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_up_volume_up_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_set_volume_up_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
            err = this->on_up_volume_up_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual int on_volume_up_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            err = this->on_set_volume_up_option(optval, optarg, optname, optind, argc, argv, env);
        } else {
            err = this->on_up_volume_up_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* volume_up_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPTUSE;
        optarg = TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPTARG;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_down_volume_down_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_set_volume_down_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
            err = this->on_down_volume_down_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual int on_volume_down_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            err = this->on_set_volume_down_option(optval, optarg, optname, optind, argc, argv, env);
        } else {
            err = this->on_down_volume_down_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* volume_down_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPTUSE;
        optarg = TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPTARG;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_get_volume_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_set_volume_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        } else {
            err = this->on_get_volume_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual int on_volume_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            err = this->on_set_volume_option(optval, optarg, optname, optind, argc, argv, env);
        } else {
            err = this->on_get_volume_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* volume_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPTUSE;
        optarg = TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPTARG;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_get_auth_token_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_set_auth_token_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual int on_auth_token_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            err = this->on_set_auth_token_option(optval, optarg, optname, optind, argc, argv, env);
        } else {
            err = this->on_get_auth_token_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* auth_token_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPTUSE;
        optarg = TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPTARG;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_pairing_pair_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual const char_t* pairing_pair_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPTUSE;
        optarg = TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPTARG;
        return chars;
    }
    virtual int on_pairing_start_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual const char_t* pairing_start_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPTUSE;
        optarg = TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPTARG;
        return chars;
    }
    virtual int on_pairing_stop_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual const char_t* pairing_stop_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPTUSE;
        optarg = TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPTARG;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_get_power_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_set_power_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual int on_power_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            err = this->on_set_power_option(optval, optarg, optname, optind, argc, argv, env);
        } else {
            err = this->on_get_power_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* power_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPTUSE;
        optarg = TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPTARG;
        return chars;
    }
    virtual int on_power_on_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual const char_t* power_on_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPTUSE;
        optarg = TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPTARG;
        return chars;
    }
    virtual int on_power_off_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual const char_t* power_off_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPTUSE;
        optarg = TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPTARG;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {
        case TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPTVAL_C:
            err = this->on_hdmi_input_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPTVAL_C:
            err = this->on_input_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPTVAL_C:
            err = this->on_volume_up_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPTVAL_C:
            err = this->on_volume_down_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPTVAL_C:
            err = this->on_volume_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPTVAL_C:
            err = this->on_auth_token_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPTVAL_C:
            err = this->on_pairing_pair_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPTVAL_C:
            err = this->on_pairing_start_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPTVAL_C:
            err = this->on_pairing_stop_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPTVAL_C:
            err = this->on_power_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPTVAL_C:
            err = this->on_power_on_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPTVAL_C:
            err = this->on_power_off_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        default:
            err = Extends::on_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {
        case TALAS_APP_CONSOLE_VIZIO_MAIN_HDMI_INPUT_OPTVAL_C:
            chars = hdmi_input_option_usage(optarg, longopt);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_INPUT_OPTVAL_C:
            chars = input_option_usage(optarg, longopt);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_UP_OPTVAL_C:
            chars = volume_up_option_usage(optarg, longopt);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_DOWN_OPTVAL_C:
            chars = volume_down_option_usage(optarg, longopt);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_VOLUME_OPTVAL_C:
            chars = volume_option_usage(optarg, longopt);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_AUTH_TOKEN_OPTVAL_C:
            chars = auth_token_option_usage(optarg, longopt);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_PAIR_OPTVAL_C:
            chars = pairing_pair_option_usage(optarg, longopt);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_START_OPTVAL_C:
            chars = pairing_start_option_usage(optarg, longopt);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_PAIRING_STOP_OPTVAL_C:
            chars = pairing_stop_option_usage(optarg, longopt);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OPTVAL_C:
            chars = power_option_usage(optarg, longopt);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_ON_OPTVAL_C:
            chars = power_on_option_usage(optarg, longopt);
            break;
        case TALAS_APP_CONSOLE_VIZIO_MAIN_POWER_OFF_OPTVAL_C:
            chars = power_off_option_usage(optarg, longopt);
            break;
        default:
            chars = Extends::option_usage(optarg, longopt);
            break;
        }
        return chars;
    }
    virtual const char_t* options(const struct option*& longopts) {
        static const char_t* chars = TALAS_APP_CONSOLE_VIZIO_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            TALAS_APP_CONSOLE_VIZIO_MAIN_OPTIONS_OPTIONS
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
} /// namespace vizio
} /// namespace console 
} /// namespace app 
} /// namespace talas 

#endif /// ndef TALAS_APP_CONSOLE_VIZIO_CLIENT_MAIN_OPT_HPP
