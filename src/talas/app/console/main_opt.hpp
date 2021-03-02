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
///   Date: 2/23/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_APP_CONSOLE_MAIN_OPT_HPP
#define TALAS_APP_CONSOLE_MAIN_OPT_HPP

#include "talas/console/main.hpp"

namespace talas {
namespace app {
namespace console {

#define TALAS_APP_CONSOLE_MAIN_HELP_OPT "help"
#define TALAS_APP_CONSOLE_MAIN_HELP_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_OPTIONAL
#define TALAS_APP_CONSOLE_MAIN_HELP_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_MAIN_HELP_OPTARG ""
#define TALAS_APP_CONSOLE_MAIN_HELP_OPTUSE ""
#define TALAS_APP_CONSOLE_MAIN_HELP_OPTVAL_S "h::"
#define TALAS_APP_CONSOLE_MAIN_HELP_OPTVAL_C 'h'
#define TALAS_APP_CONSOLE_MAIN_HELP_OPTION \
   {TALAS_APP_CONSOLE_MAIN_HELP_OPT, \
    TALAS_APP_CONSOLE_MAIN_HELP_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_MAIN_HELP_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_MAIN_HELP_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_MAIN_OPTIONS_CHARS_EXTEND \
    TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTVAL_S \
    TALAS_APP_CONSOLE_MAIN_HELP_OPTVAL_S \

#define TALAS_APP_CONSOLE_MAIN_OPTIONS_OPTIONS_EXTEND \
    TALAS_CONSOLE_MAIN_LOGGING_LEVELS_OPTION \
    TALAS_APP_CONSOLE_MAIN_HELP_OPTION \

#define TALAS_APP_CONSOLE_MAIN_OPTIONS_CHARS \
   TALAS_APP_CONSOLE_MAIN_OPTIONS_CHARS_EXTEND \

#define TALAS_APP_CONSOLE_MAIN_OPTIONS_OPTIONS \
   TALAS_APP_CONSOLE_MAIN_OPTIONS_OPTIONS_EXTEND \

///////////////////////////////////////////////////////////////////////
/// class main_optt
///////////////////////////////////////////////////////////////////////
template <class TExtends = talas::console::main, class TImplements = typename TExtends::Implements>
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
    virtual int on_help_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        }
        return err;
    }
    virtual const char_t* help_option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = TALAS_APP_CONSOLE_MAIN_HELP_OPTUSE;
        optarg = TALAS_APP_CONSOLE_MAIN_HELP_OPTARG;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {
        case TALAS_APP_CONSOLE_MAIN_HELP_OPTVAL_C:
            err = this->on_help_option(optval, optarg, optname, optind, argc, argv, env);
            break;
        default:
            err = Extends::on_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* option_usage(const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {
        case TALAS_APP_CONSOLE_MAIN_HELP_OPTVAL_C:
            chars = help_option_usage(optarg, longopt);
            break;
        default:
            chars = Extends::option_usage(optarg, longopt);
            break;
        }
        return chars;
    }
    virtual const char_t* options(const struct option*& longopts) {
        static const char_t* chars = TALAS_APP_CONSOLE_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            TALAS_APP_CONSOLE_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
}; /// class main_optt
typedef main_optt<> main_opt;

} /// namespace console 
} /// namespace app 
} /// namespace talas 

#endif /// ndef TALAS_APP_CONSOLE_MAIN_OPT_HPP 