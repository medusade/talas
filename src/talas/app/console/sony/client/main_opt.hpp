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
///   Date: 2/22/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_APP_CONSOLE_SONY_CLIENT_MAIN_OPT_HPP
#define TALAS_APP_CONSOLE_SONY_CLIENT_MAIN_OPT_HPP

#include "talas/app/console/network/client/main.hpp"

#define XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPT "next"
#define XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPTARG ""
#define XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPTUSE "Play next"
#define XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPTVAL_S "x::"
#define XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPTVAL_C 'x'
#define XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPTION \
   {XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPT, \
    XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPTARG_RESULT, \
    XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPTVAL_C}, \

#define XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPT "previous"
#define XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPTARG ""
#define XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPTUSE "Play prevous"
#define XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPTVAL_S "e::"
#define XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPTVAL_C 'e'
#define XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPTION \
   {XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPT, \
    XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPTARG_RESULT, \
    XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPTVAL_C}, \

#define XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPT "pause"
#define XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPTARG ""
#define XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPTUSE "Pause play"
#define XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPTVAL_S "u::"
#define XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPTVAL_C 'u'
#define XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPTION \
   {XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPT, \
    XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPTARG_RESULT, \
    XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPTVAL_C}, \

#define XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPT "resume"
#define XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPTARG ""
#define XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPTUSE "Resume play"
#define XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPTVAL_S "m::"
#define XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPTVAL_C 'm'
#define XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPTION \
   {XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPT, \
    XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPTARG_RESULT, \
    XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPTVAL_C}, \

#define XOS_APP_CONSOLE_SONY_MAIN_START_OPT "start"
#define XOS_APP_CONSOLE_SONY_MAIN_START_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_SONY_MAIN_START_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_SONY_MAIN_START_OPTARG ""
#define XOS_APP_CONSOLE_SONY_MAIN_START_OPTUSE "Start play"
#define XOS_APP_CONSOLE_SONY_MAIN_START_OPTVAL_S "s::"
#define XOS_APP_CONSOLE_SONY_MAIN_START_OPTVAL_C 's'
#define XOS_APP_CONSOLE_SONY_MAIN_START_OPTION \
   {XOS_APP_CONSOLE_SONY_MAIN_START_OPT, \
    XOS_APP_CONSOLE_SONY_MAIN_START_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_SONY_MAIN_START_OPTARG_RESULT, \
    XOS_APP_CONSOLE_SONY_MAIN_START_OPTVAL_C}, \

#define XOS_APP_CONSOLE_SONY_MAIN_STOP_OPT "stop"
#define XOS_APP_CONSOLE_SONY_MAIN_STOP_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_SONY_MAIN_STOP_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_SONY_MAIN_STOP_OPTARG ""
#define XOS_APP_CONSOLE_SONY_MAIN_STOP_OPTUSE "Stop play"
#define XOS_APP_CONSOLE_SONY_MAIN_STOP_OPTVAL_S "t::"
#define XOS_APP_CONSOLE_SONY_MAIN_STOP_OPTVAL_C 't'
#define XOS_APP_CONSOLE_SONY_MAIN_STOP_OPTION \
   {XOS_APP_CONSOLE_SONY_MAIN_STOP_OPT, \
    XOS_APP_CONSOLE_SONY_MAIN_STOP_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_SONY_MAIN_STOP_OPTARG_RESULT, \
    XOS_APP_CONSOLE_SONY_MAIN_STOP_OPTVAL_C}, \

#define XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPT "input"
#define XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPTARG ""
#define XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPTUSE "Input info"
#define XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPTVAL_S "i::"
#define XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPTVAL_C 'i'
#define XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPTION \
   {XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPT, \
    XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPTARG_RESULT, \
    XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPTVAL_C}, \

#define XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPT "volume"
#define XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPTARG "[0..100]"
#define XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPTUSE "Set / Get volume"
#define XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPTVAL_S "v::"
#define XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPTVAL_C 'v'
#define XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPTION \
   {XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPT, \
    XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPTARG_RESULT, \
    XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPTVAL_C}, \

#define XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPT "power-on"
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPTARG ""
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPTUSE "Turn Power on"
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPTVAL_S "n::"
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPTVAL_C 'n'
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPTION \
   {XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPT, \
    XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPTARG_RESULT, \
    XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPTVAL_C}, \

#define XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPT "power-off"
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPTARG ""
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPTUSE "Turn Power off"
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPTVAL_S "f::"
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPTVAL_C 'f'
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPTION \
   {XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPT, \
    XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPTARG_RESULT, \
    XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPTVAL_C}, \

#define XOS_APP_CONSOLE_SONY_MAIN_POWER_OPT "power"
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_OPTARG_RESULT 0
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_OPTARG "{ active | off }"
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_OPTUSE "Turn Power on/off"
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_OPTVAL_S "w::"
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_OPTVAL_C 'w'
#define XOS_APP_CONSOLE_SONY_MAIN_POWER_OPTION \
   {XOS_APP_CONSOLE_SONY_MAIN_POWER_OPT, \
    XOS_APP_CONSOLE_SONY_MAIN_POWER_OPTARG_REQUIRED, \
    XOS_APP_CONSOLE_SONY_MAIN_POWER_OPTARG_RESULT, \
    XOS_APP_CONSOLE_SONY_MAIN_POWER_OPTVAL_C}, \

#define XOS_APP_CONSOLE_SONY_MAIN_OPTIONS_CHARS_EXTEND \
    XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPTVAL_S \
    XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPTVAL_S \
    XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPTVAL_S \
    XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPTVAL_S \
    XOS_APP_CONSOLE_SONY_MAIN_START_OPTVAL_S \
    XOS_APP_CONSOLE_SONY_MAIN_STOP_OPTVAL_S \
    XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPTVAL_S \    
    XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPTVAL_S \
    XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPTVAL_S \
    XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPTVAL_S \
    XOS_APP_CONSOLE_SONY_MAIN_POWER_OPTVAL_S \
 
#define XOS_APP_CONSOLE_SONY_MAIN_OPTIONS_OPTIONS_EXTEND \
    XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPTION \
    XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPTION \
    XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPTION \
    XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPTION \
    XOS_APP_CONSOLE_SONY_MAIN_START_OPTION \
    XOS_APP_CONSOLE_SONY_MAIN_STOP_OPTION \
    XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPTION \
    XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPTION \
    XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPTION \
    XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPTION \
    XOS_APP_CONSOLE_SONY_MAIN_POWER_OPTION \
 
#define XOS_APP_CONSOLE_SONY_MAIN_OPTIONS_CHARS \
    XOS_APP_CONSOLE_SONY_MAIN_OPTIONS_CHARS_EXTEND \
    TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_OPTIONS_CHARS \

#define XOS_APP_CONSOLE_SONY_MAIN_OPTIONS_OPTIONS \
   XOS_APP_CONSOLE_SONY_MAIN_OPTIONS_OPTIONS_EXTEND \
    TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_OPTIONS_OPTIONS \

namespace talas {
namespace app {
namespace console {
namespace sony {
namespace client {

///////////////////////////////////////////////////////////////////////
/// class main_optt
///////////////////////////////////////////////////////////////////////
template <class TExtends = network::client::main, class TImplements = typename TExtends::Implements>
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
    main_optt(): power_argument_("off"), volume_argument_("0"), input_argument_("") {
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
    virtual int on_next_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual const char_t* next_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPTUSE;
        optarg = XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPTARG;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_previous_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual const char_t* previous_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPTUSE;
        optarg = XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPTARG;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_pause_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual const char_t* pause_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPTUSE;
        optarg = XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPTARG;
        return chars;
    }
    virtual int on_resume_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual const char_t* resume_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPTUSE;
        optarg = XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPTARG;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_start_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual const char_t* start_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = XOS_APP_CONSOLE_SONY_MAIN_START_OPTUSE;
        optarg = XOS_APP_CONSOLE_SONY_MAIN_START_OPTARG;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_stop_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual const char_t* stop_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = XOS_APP_CONSOLE_SONY_MAIN_STOP_OPTUSE;
        optarg = XOS_APP_CONSOLE_SONY_MAIN_STOP_OPTARG;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_set_volume_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual int on_get_volume_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual int on_volume_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            set_volume_argument(optarg);
            err = this->on_set_volume_option(optval, optarg, optname, optind, argc, argv, env);
        } else {
            err = this->on_get_volume_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* volume_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPTUSE;
        optarg = XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPTARG;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_set_input_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual int on_get_input_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual int on_input_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            set_input_argument(optarg);
            err = this->on_set_input_option(optval, optarg, optname, optind, argc, argv, env);
        } else {
            err = this->on_get_input_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* input_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPTUSE;
        optarg = XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPTARG;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_power_on_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual const char_t* power_on_option_usage(const char_t*& optarg, const struct option* longopt) {
        optarg = XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPTARG;
        const char_t* chars = XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPTUSE;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_power_off_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual const char_t* power_off_option_usage(const char_t*& optarg, const struct option* longopt) {
        optarg = XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPTARG;
        const char_t* chars = XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPTUSE;
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_set_power_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_get_power_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        return err;
    }
    virtual int on_power_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            set_power_argument(optarg);
            err = this->on_set_power_option(optval, optarg, optname, optind, argc, argv, env);
        } else {
            err = this->on_get_power_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* power_option_usage(const char_t*& optarg, const struct option* longopt) {
        optarg = XOS_APP_CONSOLE_SONY_MAIN_POWER_OPTARG;
        const char_t* chars = XOS_APP_CONSOLE_SONY_MAIN_POWER_OPTUSE;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {
        case XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPTVAL_C:
            err = this->on_next_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPTVAL_C:
            err = this->on_previous_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPTVAL_C:
            err = this->on_pause_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPTVAL_C:
            err = this->on_resume_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_START_OPTVAL_C:
            err = this->on_start_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_STOP_OPTVAL_C:
            err = this->on_stop_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPTVAL_C:
            err = this->on_volume_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPTVAL_C:
            err = this->on_input_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPTVAL_C:
            err = this->on_power_on_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPTVAL_C:
            err = this->on_power_off_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_POWER_OPTVAL_C:
            err = this->on_power_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        default:
            err = Extends::on_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {
        case XOS_APP_CONSOLE_SONY_MAIN_NEXT_OPTVAL_C:
            chars = next_option_usage(optarg, longopt);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_PREVIOUS_OPTVAL_C:
            chars = previous_option_usage(optarg, longopt);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_PAUSE_OPTVAL_C:
            chars = pause_option_usage(optarg, longopt);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_RESUME_OPTVAL_C:
            chars = resume_option_usage(optarg, longopt);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_START_OPTVAL_C:
            chars = start_option_usage(optarg, longopt);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_STOP_OPTVAL_C:
            chars = stop_option_usage(optarg, longopt);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_VOLUME_OPTVAL_C:
            chars = volume_option_usage(optarg, longopt);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_INPUT_OPTVAL_C:
            chars = input_option_usage(optarg, longopt);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_POWER_ON_OPTVAL_C:
            chars = power_on_option_usage(optarg, longopt);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_POWER_OFF_OPTVAL_C:
            chars = power_off_option_usage(optarg, longopt);
            break;
        case XOS_APP_CONSOLE_SONY_MAIN_POWER_OPTVAL_C:
            chars = power_option_usage(optarg, longopt);
            break;
        default:
            chars = Extends::option_usage(optarg, longopt);
            break;
        }
        return chars;
    }
    virtual const char_t* options(const struct option*& longopts) {
        static const char_t* chars = XOS_APP_CONSOLE_SONY_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            XOS_APP_CONSOLE_SONY_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual string_t& set_power_argument(const char_t* to) {
        power_argument_.assign(to);
        return (string_t&)power_argument_;
    }
    virtual string_t& power_argument() const {
        return (string_t&)power_argument_;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual string_t& set_volume_argument(const char_t* to) {
        volume_argument_.assign(to);
        return (string_t&)volume_argument_;
    }
    virtual string_t& volume_argument() const {
        return (string_t&)volume_argument_;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual string_t& set_input_argument(const char_t* to) {
        input_argument_.assign(to);
        return (string_t&)input_argument_;
    }
    virtual string_t& input_argument() const {
        return (string_t&)input_argument_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    string_t power_argument_, volume_argument_, input_argument_;
}; /// class main_optt
typedef main_optt<> main_opt;

} /// namespace client 
} /// namespace sony 
} /// namespace console 
} /// namespace app 
} /// namespace talas 

#endif /// ndef TALAS_APP_CONSOLE_SONY_CLIENT_MAIN_OPT_HPP 