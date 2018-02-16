///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2014 $organization$
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
///   Date: 11/18/2014
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CONSOLE_MAIN_HPP
#define _TALAS_CONSOLE_MAIN_HPP

#include "talas/console/main_opt.hpp"
#include "talas/io/logger.hpp"
#include "xos/base/getopt/main.hpp"
#include "xos/base/main.hpp"

#define TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPT "logging"
#define TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTARG_RESULT 0
#define TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTARG TALAS_MAIN_LOGGING_OPTARG
#define TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTUSE TALAS_MAIN_LOGGING_OPTUSE
#define TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTVAL_S "l:"
#define TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTVAL_C 'l'
#define TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTION \
   {TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPT, \
    TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTARG_REQUIRED, \
    TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTARG_RESULT, \
    TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTVAL_C}, \

#define TALAS_CONSOLE_MAIN_HELP_OPT "help"
#define TALAS_CONSOLE_MAIN_HELP_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_NONE
#define TALAS_CONSOLE_MAIN_HELP_OPTARG_RESULT 0
#define TALAS_CONSOLE_MAIN_HELP_OPTARG TALAS_MAIN_HELP_OPTARG
#define TALAS_CONSOLE_MAIN_HELP_OPTUSE TALAS_MAIN_HELP_OPTUSE
#define TALAS_CONSOLE_MAIN_HELP_OPTVAL_S "?"
#define TALAS_CONSOLE_MAIN_HELP_OPTVAL_C '?'
#define TALAS_CONSOLE_MAIN_HELP_OPTION \
   {TALAS_CONSOLE_MAIN_HELP_OPT, \
    TALAS_CONSOLE_MAIN_HELP_OPTARG_REQUIRED, \
    TALAS_CONSOLE_MAIN_HELP_OPTARG_RESULT, \
    TALAS_CONSOLE_MAIN_HELP_OPTVAL_C}, \

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define TALAS_CONSOLE_MAIN_OPTIONS_CHARS \
    TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTVAL_S \
    TALAS_CONSOLE_MAIN_HELP_OPTVAL_S \

#define TALAS_CONSOLE_MAIN_OPTIONS_OPTIONS \
    TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTION \
    TALAS_CONSOLE_MAIN_HELP_OPTION \

namespace talas {
namespace console {

typedef xos::base::getopt::main_implement main_implements;
typedef xos::base::getopt::main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: maint
///////////////////////////////////////////////////////////////////////
template
<class TImplements = main_implements, class TExtends = main_extends>

class _EXPORT_CLASS maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    maint() {
    }
    virtual ~maint() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_logging_levels_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = this->on_logging_option
        (TALAS_MAIN_LOGGING_OPTVAL_C,
         optarg, optname, optind, argc, argv, env);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_help_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = this->usage(argc, argv, env);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        switch(optval) {
        case TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTVAL_C:
            err = on_logging_levels_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_CONSOLE_MAIN_HELP_OPTVAL_C:
            err = on_help_option
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
    virtual const char* option_usage
    (const char*& optarg, const struct option* longopt) {
        const char* chars = "";
        switch(longopt->val) {
        case TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTVAL_C:
            optarg = TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTARG;
            chars = TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTUSE;
            break;
        case TALAS_CONSOLE_MAIN_HELP_OPTVAL_C:
            optarg = TALAS_CONSOLE_MAIN_HELP_OPTARG;
            chars = TALAS_CONSOLE_MAIN_HELP_OPTUSE;
            break;
        default:
            chars = Extends::option_usage(optarg, longopt);
        }
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* options(const struct option*& longopts) {
        int err = 0;
        static const char* chars = TALAS_CONSOLE_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            TALAS_CONSOLE_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
};
typedef maint<> main;

} // namespace console 
} // namespace talas 

#endif // _TALAS_CONSOLE_MAIN_HPP 
