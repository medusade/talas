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
///   Date: 2/22/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_APP_CONSOLE_SONY_CLIENT_MAIN_HPP
#define TALAS_APP_CONSOLE_SONY_CLIENT_MAIN_HPP

#include "talas/app/console/sony/client/main_opt.hpp"

#if !defined(TALAS_APP_CONSOLE_SONY_CLIENT_PORT)
#define TALAS_APP_CONSOLE_SONY_CLIENT_PORT "10000"
#endif /// !defined(TALAS_APP_CONSOLE_SONY_CLIENT_PORT)

namespace talas {
namespace app {
namespace console {
namespace sony {
namespace client {

///////////////////////////////////////////////////////////////////////
/// class maint
///////////////////////////////////////////////////////////////////////
template <class TExtends = main_opt, class TImplements = typename TExtends::Implements>
class EXPORT_CLASS maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef maint Derives;

    typedef typename TExtends::writer_t writer_t;
    typedef typename TExtends::reader_t reader_t;
    typedef typename TExtends::string_t string_t;
    typedef typename TExtends::char_t char_t;
    
    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    maint()
    : before_write_request_(0),
      port_(TALAS_APP_CONSOLE_SONY_CLIENT_PORT),

      request_line_begin_("POST "), request_line_end_(" HTTP/1.0\r\n"), 
      request_headers_begin_("Content-Type:text/json\r\nContent-Length:"), request_headers_end_("\r\n\r\n"),
      
      next_path_("/sony/avContent"), 
      next_begin_("{\"method\": \"setPlayNextContent\", \"id\": 73, \"params\": [{\"output\": \""), 
      next_end_("\"}], \"version\": \"1.0\"}\r\n"),
      
      previous_path_("/sony/avContent"), 
      previous_begin_("{\"method\": \"setPlayPreviousContent\", \"id\": 73, \"params\": [{\"output\": \""), 
      previous_end_("\"}], \"version\": \"1.0\"}\r\n"),
      
      pause_path_("/sony/avContent"), 
      pause_begin_("{\"method\": \"pausePlayingContent\", \"id\": 73, \"params\": [{\"output\": \""), 
      pause_end_("\"}], \"version\": \"1.1\"}\r\n"),
      
      start_path_("/sony/avContent"), 
      start_begin_("{\"method\": \"setPlayContent\", \"id\": 73, \"params\": [{\"output\": \"\", \"resume\": true, \"uri\": \""), 
      start_end_("\"}], \"version\": \"1.2\"}\r\n"),
      
      stop_path_("/sony/avContent"), 
      stop_begin_("{\"method\": \"stopPlayingContent\", \"id\": 73, \"params\": [{\"output\": \""), 
      stop_end_("\"}], \"version\": \"1.1\"}\r\n"),
      
      input_path_("/sony/avContent"), 
      set_input_begin_("{\"method\": \"setPlayContent\", \"id\": 73, \"params\": [{\"output\": \"\", \"resume\": true, \"uri\": \""), 
      set_input_end_("\"}]"), 
      get_input_begin_("{\"method\": \"getPlayingContentInfo\", \"id\": 73, \"params\": [{\"output\": \""), 
      get_input_end_("\"}]"), 
      input_end_(", \"version\": \"1.2\"}\r\n"),
      
      volume_path_("/sony/audio"), 
      set_volume_begin_("{\"method\": \"setAudioVolume\", \"id\": 73, \"params\": [{\"volume\": \""), 
      set_volume_end_("\"}]"), 
      get_volume_begin_("{\"method\": \"getVolumeInformation\", \"id\": 73, \"params\": [{\"output\": \""), 
      get_volume_end_("\"}]"), 
      volume_end_(", \"version\": \"1.1\"}\r\n"),
      
      power_path_("/sony/system"), 
      set_power_begin_("{\"method\": \"setPowerStatus\", \"id\": 73, \"params\": [{\"status\": \""), 
      set_power_end_("\"}]"), 
      get_power_begin_("{\"method\": \"getPowerStatus\", \"id\": 73, \"params\": ["), 
      get_power_end_("]"), 
      power_end_(", \"version\": \"1.1\"}\r\n"),
      power_on_("active"), power_off_("off") {
    }
    virtual ~maint() {
    }
private:
    maint(const maint& copy): Extends(copy) {
    }
    
protected:
    typedef typename TExtends::socket_t socket_t;
    typedef typename TExtends::socket_reader_t socket_reader_t;
    typedef typename TExtends::socket_writer_t socket_writer_t;
    typedef typename TExtends::sized_reader_t sized_reader_t;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int (Derives::*before_write_request_)
    (writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env);
    virtual int before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if ((this->before_write_request_)) {
            err = (this->*before_write_request_)(writer, request, argc, argv, env);
        } else {
            err = this->get_power_before_write_request(writer, request, argc, argv, env);
        }
        return err;
    }
    
    ///////////////////////////////////////////////////////////////////////
    /// ...next / previous...
    ///////////////////////////////////////////////////////////////////////
    virtual int next_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        next_.assign(next_begin_);
        next_.append(next_end_);
        request.assign(request_line_begin_);
        request.append(next_path_);
        request.append(request_line_end_);
        request.append(request_headers_begin_);
        request.append(unsigned_to_string(next_.length()));
        request.append(request_headers_end_);
        request.append(next_);
        return err;
    }
    virtual int previous_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        previous_.assign(previous_begin_);
        previous_.append(previous_end_);
        request.assign(request_line_begin_);
        request.append(previous_path_);
        request.append(request_line_end_);
        request.append(request_headers_begin_);
        request.append(unsigned_to_string(previous_.length()));
        request.append(request_headers_end_);
        request.append(previous_);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    /// ...pause / resume...
    ///////////////////////////////////////////////////////////////////////
    virtual int pause_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        pause_.assign(pause_begin_);
        pause_.append(pause_end_);
        request.assign(request_line_begin_);
        request.append(pause_path_);
        request.append(request_line_end_);
        request.append(request_headers_begin_);
        request.append(unsigned_to_string(pause_.length()));
        request.append(request_headers_end_);
        request.append(pause_);
        return err;
    }
    virtual int resume_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        err = start_before_write_request(writer, request, argc, argv, env);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    /// ...start / stop...
    ///////////////////////////////////////////////////////////////////////
    virtual int start_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        start_.assign(start_begin_);
        start_.append(start_end_);
        request.assign(request_line_begin_);
        request.append(start_path_);
        request.append(request_line_end_);
        request.append(request_headers_begin_);
        request.append(unsigned_to_string(start_.length()));
        request.append(request_headers_end_);
        request.append(start_);
        return err;
    }
    virtual int stop_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        stop_.assign(stop_begin_);
        stop_.append(stop_end_);
        request.assign(request_line_begin_);
        request.append(stop_path_);
        request.append(request_line_end_);
        request.append(request_headers_begin_);
        request.append(unsigned_to_string(stop_.length()));
        request.append(request_headers_end_);
        request.append(stop_);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    /// ...input...
    ///////////////////////////////////////////////////////////////////////
    virtual int set_input_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        input_.assign(set_input_begin_);
        input_.append(this->input_argument());
        input_.append(set_input_end_);
        err = input_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int get_input_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        input_.assign(get_input_begin_);
        input_.append(get_input_end_);
        err = input_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int input_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        input_.append(input_end_);
        request.assign(request_line_begin_);
        request.append(input_path_);
        request.append(request_line_end_);
        request.append(request_headers_begin_);
        request.append(unsigned_to_string(input_.length()));
        request.append(request_headers_end_);
        request.append(input_);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    /// ...volume...
    ///////////////////////////////////////////////////////////////////////
    virtual int set_volume_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        volume_.assign(set_volume_begin_);
        volume_.append(this->volume_argument());
        volume_.append(set_volume_end_);
        err = volume_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int get_volume_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        volume_.assign(get_volume_begin_);
        volume_.append(get_volume_end_);
        err = volume_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int volume_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        volume_.append(volume_end_);
        request.assign(request_line_begin_);
        request.append(volume_path_);
        request.append(request_line_end_);
        request.append(request_headers_begin_);
        request.append(unsigned_to_string(volume_.length()));
        request.append(request_headers_end_);
        request.append(volume_);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    /// ...power...
    ///////////////////////////////////////////////////////////////////////
    virtual int power_on_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        power_.assign(set_power_begin_);
        power_.append(power_on_);
        power_.append(set_power_end_);
        err = power_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int power_off_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        power_.assign(set_power_begin_);
        power_.append(power_off_);
        power_.append(set_power_end_);
        err = power_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int set_power_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        power_.assign(set_power_begin_);
        power_.append(this->power_argument());
        power_.append(set_power_end_);
        err = power_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int get_power_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        power_.assign(get_power_begin_);
        power_.append(get_power_end_);
        err = power_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int power_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        power_.append(power_end_);
        request.assign(request_line_begin_);
        request.append(power_path_);
        request.append(request_line_end_);
        request.append(request_headers_begin_);
        request.append(unsigned_to_string(power_.length()));
        request.append(request_headers_end_);
        request.append(power_);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_next_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        this->set_client_run(argc, argv, env);
        before_write_request_ = &Derives::next_before_write_request;
        return err;
    }
    virtual int on_previous_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        this->set_client_run(argc, argv, env);
        before_write_request_ = &Derives::previous_before_write_request;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_pause_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        this->set_client_run(argc, argv, env);
        before_write_request_ = &Derives::pause_before_write_request;
        return err;
    }
    virtual int on_resume_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        this->set_client_run(argc, argv, env);
        before_write_request_ = &Derives::resume_before_write_request;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_start_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        this->set_client_run(argc, argv, env);
        before_write_request_ = &Derives::start_before_write_request;
        return err;
    }
    virtual int on_stop_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        this->set_client_run(argc, argv, env);
        before_write_request_ = &Derives::stop_before_write_request;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_set_input_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        this->set_client_run(argc, argv, env);
        before_write_request_ = &Derives::get_input_before_write_request;
        if ((optarg) && (optarg[0])) {
            before_write_request_ = &Derives::set_input_before_write_request;
        }
        return err;
    }
    virtual int on_get_input_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        this->set_client_run(argc, argv, env);
        before_write_request_ = &Derives::get_input_before_write_request;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_set_volume_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        this->set_client_run(argc, argv, env);
        before_write_request_ = &Derives::get_volume_before_write_request;
        if ((optarg) && (optarg[0])) {
            before_write_request_ = &Derives::set_volume_before_write_request;
        }
        return err;
    }
    virtual int on_get_volume_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        this->set_client_run(argc, argv, env);
        before_write_request_ = &Derives::get_volume_before_write_request;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_power_on_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        this->set_client_run(argc, argv, env);
        before_write_request_ = &Derives::power_on_before_write_request;
        return err;
    }
    virtual int on_power_off_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        this->set_client_run(argc, argv, env);
        before_write_request_ = &Derives::power_off_before_write_request;
        return err;
    }
    virtual int on_set_power_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        this->set_client_run(argc, argv, env);
        before_write_request_ = &Derives::set_power_before_write_request;
        return err;
    }
    virtual int on_get_power_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        this->set_client_run(argc, argv, env);
        before_write_request_ = &Derives::get_power_before_write_request;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int set_client_run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = this->set_sockets_run(argc, argv, env))) {
            if (!(err = this->set_client_sockets_run(argc, argv, env))) {
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual string_t& port() const {
        return (string_t&)port_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    string_t port_;

    string_t request_line_begin_, request_line_end_, request_headers_begin_, request_headers_end_, request_;
    
    string_t next_path_, next_begin_, next_end_, next_;

    string_t previous_path_, previous_begin_, previous_end_, previous_;

    string_t pause_path_, pause_begin_, pause_end_, pause_;
    
    string_t start_path_, start_begin_, start_end_, start_;

    string_t stop_path_, stop_begin_, stop_end_, stop_;
    
    string_t input_path_, set_input_begin_, set_input_end_, get_input_begin_, get_input_end_, input_end_, input_;

    string_t volume_path_, set_volume_begin_, set_volume_end_, get_volume_begin_, get_volume_end_, volume_end_, volume_;

    string_t power_path_, set_power_begin_, set_power_end_, get_power_begin_, get_power_end_, power_end_, power_on_, power_off_, power_;
}; /// class maint
typedef maint<> main;

} /// namespace client 
} /// namespace sony 
} /// namespace console 
} /// namespace app 
} /// namespace talas 

#endif /// ndef TALAS_APP_CONSOLE_SONY_CLIENT_MAIN_HPP 