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
///   Date: 11/18/2014, 2/23/2021
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CONSOLE_MAIN_HPP
#define _TALAS_CONSOLE_MAIN_HPP

#include "xos/base/getopt/main.hpp"
#include "talas/console/main_opt.hpp"
#include "talas/base/exception.hpp"
#include "talas/io/logger.hpp"
#include "talas/io/reader.hpp"
#include "talas/io/writer.hpp"

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

    typedef typename TExtends::char_t char_t;
    typedef typename talas::stringt<char_t> string_t;
    typedef talas::io::writert<char_t, char_t> writer_t;
    typedef talas::io::readert<char_t, char_t> reader_t;
    typedef talas::io::sized::readert<reader_t> sized_reader_t;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    maint() {
    }
    virtual ~maint() {
    }
private:
    maint(const maint& copy) {
        throw exception(exception_unexpected);
    }

protected:
    typedef xos::extend io_t;
    typedef io_t io_extends_t;

    ///////////////////////////////////////////////////////////////////////
    /// class io_extend_t
    ///////////////////////////////////////////////////////////////////////
    class exported io_extend_t: public io_extends_t {
    public:
        typedef io_extends_t extends;
        typedef io_extend_t derives;
    
        ///////////////////////////////////////////////////////////////////////
        /// constructor / destructor
        ///////////////////////////////////////////////////////////////////////
        io_extend_t(const io_extend_t& copy): extends(copy), io_(copy.io_) {
        }
        io_extend_t(io_t& io): io_(io) {
        }
        virtual ~io_extend_t() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
    protected:
        io_t& io_;
    }; /// class io_extend_t

    ///////////////////////////////////////////////////////////////////////
    /// class in_reader_t
    ///////////////////////////////////////////////////////////////////////
    class exported in_reader_t: virtual public reader_t, public io_extend_t {
    public:
        typedef reader_t implements;
        typedef io_extend_t extends;
        typedef in_reader_t derives;
    
        typedef typename implements::what_t what_t;
        typedef typename implements::sized_t sized_t;

        ///////////////////////////////////////////////////////////////////////
        /// constructor / destructor
        ///////////////////////////////////////////////////////////////////////
        in_reader_t(const in_reader_t& copy): extends(copy) {
        }
        in_reader_t(io_t& io): extends(io) {
        }
        virtual ~in_reader_t() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual ssize_t read(what_t* what, size_t size) {
            ssize_t count = 0;
            count = this->io_.in(what, size);
            return count;
        }    
        virtual ssize_t fill() {
            ssize_t count = 0;
            count = this->io_.out_fill();
            return count;
        }    
    }; /// class in_reader_t

    ///////////////////////////////////////////////////////////////////////
    /// class out_writer_t
    ///////////////////////////////////////////////////////////////////////
    class exported out_writer_t: virtual public writer_t, public io_extend_t {
    public:
        typedef writer_t implements;
        typedef io_extend_t extends;
        typedef out_writer_t derives;
    
        typedef typename implements::what_t what_t;
        typedef typename implements::sized_t sized_t;

        ///////////////////////////////////////////////////////////////////////
        /// constructor / destructor
        ///////////////////////////////////////////////////////////////////////
        out_writer_t(const out_writer_t& copy): extends(copy) {
        }
        out_writer_t(io_t& io): extends(io) {
        }
        virtual ~out_writer_t() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual ssize_t write(const what_t* what, size_t size) {
            ssize_t count = 0;
            count = this->io_.out(what, size);
            return count;
        }    
        virtual ssize_t flush() {
            ssize_t count = 0;
            count = this->io_.out_flush();
            return count;
        }    
    }; /// class out_writer_t

    ///////////////////////////////////////////////////////////////////////
    /// class err_writer_t
    ///////////////////////////////////////////////////////////////////////
    class exported err_writer_t: virtual public writer_t, public io_extend_t {
    public:
        typedef writer_t implements;
        typedef io_extend_t extends;
        typedef err_writer_t derives;
    
        typedef typename implements::what_t what_t;
        typedef typename implements::sized_t sized_t;

        ///////////////////////////////////////////////////////////////////////
        /// constructor / destructor
        ///////////////////////////////////////////////////////////////////////
        err_writer_t(const err_writer_t& copy): extends(copy) {
        }
        err_writer_t(io_t& io): extends(io) {
        }
        virtual ~err_writer_t() {
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        virtual ssize_t write(const what_t* what, size_t size) {
            ssize_t count = 0;
            count = this->io_.err(what, size);
            return count;
        }    
        virtual ssize_t flush() {
            ssize_t count = 0;
            count = this->io_.err_flush();
            return count;
        }    
    }; /// class err_writer_t

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
