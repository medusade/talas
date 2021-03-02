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
///   Date: 2/25/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_APP_CONSOLE_VIZIO_CLIENT_MAIN_HPP
#define TALAS_APP_CONSOLE_VIZIO_CLIENT_MAIN_HPP

#include "talas/app/console/vizio/client/main_opt.hpp"

namespace talas {
namespace app {
namespace console {
namespace vizio {
namespace client {

///////////////////////////////////////////////////////////////////////
/// class maint
///////////////////////////////////////////////////////////////////////
template <class TExtends = vizio::client::main_opt, class TImplements = typename TExtends::Implements>
class EXPORT_CLASS maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;
    typedef maint Derives;

    typedef typename TExtends::char_t char_t;
    typedef typename TExtends::string_t string_t;
    typedef typename TExtends::reader_t reader_t;
    typedef typename TExtends::writer_t writer_t;
    typedef typename TExtends::sized_reader_t sized_reader_t;

    ///////////////////////////////////////////////////////////////////////
    /// constructor / destructor
    ///////////////////////////////////////////////////////////////////////
    maint()
    : run_(0),
      before_write_request_(0),

      get_request_("GET "), put_request_("PUT "), post_request_("POST "), request_protocol_(" HTTP/1.0\r\n"), 
      auth_header_("AUTH:"), content_type_header_("Content-Type:"), content_type_("application/json"),
      content_length_header_("Content-Length:"), content_length_("0"), header_end_("\r\n"), 

      json_content_begin_("{ \""), json_content_middle_("\", \""), json_content_end_("\" }\r\n"), 
      json_content_int_middle_(", \""), json_content_int_end_(" }\r\n"), 
      json_content_name_("DEVICE_NAME\": \""), json_content_id_("DEVICE_ID\": \""), 
      json_content_challenge_type_("CHALLENGE_TYPE\": "), json_content_challenge_token_("PAIRING_REQ_TOKEN\": "), 
      json_content_challenge_value_("RESPONSE_VALUE\": \""), 
      json_content_keylist_("KEYLIST\": [{ \""), json_content_keylist_end_(" }]"), 
      json_content_codeset_("CODESET\": "), json_content_code_("CODE\": "), 
      json_content_action_("ACTION\": \""), json_content_keydown_("KEYDOWN\""), 
      json_content_keyup_("KEYUP\""), json_content_keypress_("KEYPRESS\""), 

      key_command_request_(put_request_), key_command_path_("/key_command/"),
      volume_codeset_("5"), volume_up_code_("1"), volume_down_code_("0"),
      power_codeset_("11"), power_on_code_("1"), power_off_code_("0"), power_toggle_code_("2"),
      power_mode_request_(get_request_), power_mode_path_("/state/device/power_mode"),
      
      pairing_start_request_(put_request_), pairing_start_path_("/pairing/start"), 
      pairing_cancel_request_(put_request_), pairing_cancel_path_("/pairing/cancel"),
      pairing_pair_request_(put_request_), pairing_pair_path_("/pairing/pair"),
      pairing_name_("vizio-application"), pairing_id_("vizio-identifier"), pairing_token_("1"), 
      pairing_challenge_type_("1"), pairing_challenge_token_("1"), pairing_challenge_value_("1") {
    }
    virtual ~maint() {
    }
private:
    maint(const maint& copy) {
        throw exception(exception_unexpected);
    }

protected:
    typedef typename TExtends::io_t io_t;
    typedef typename TExtends::in_reader_t in_reader_t;
    typedef typename TExtends::out_writer_t out_writer_t;
    typedef typename TExtends::err_writer_t err_writer_t;
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int (Derives::*run_)(int argc, char_t**argv, char_t**env);
    virtual int run(int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((run_)) {
            err = (this->*run_)(argc, argv, env);
        } else {
            err = Extends::run(argc, argv, env);
        }
        return err;
    }
    virtual int get_auth_token_run(int argc, char_t**argv, char_t**env) {
        int err = 0;
        this->outln(pairing_token_.chars());
        return err;
    }
    virtual int set_get_auth_token_run(int argc, char_t**argv, char_t**env) {
        int err = 0;
        run_ = &Derives::get_auth_token_run;
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int (Derives::*before_write_request_)(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env);
    virtual int before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if ((before_write_request_)) {
            err = (this->*before_write_request_)(writer, request, argc, argv, env);
        } else {
            err = default_before_write_request(writer, request, argc, argv, env);
        }
        return err;
    }
    virtual int default_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        this->outln();
        this->out(request.chars());
        this->outln();
        err = Extends::before_write_request(writer, request, argc, argv, env);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int pairing_pair_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        int optind = 0;
        if (((optind = ::optind) < argc) && (argv)) {
            const char_t* arg = 0;
            if ((arg = argv[optind]) && (arg[0])) {
                pairing_challenge_token_.assign(arg);
                if (((++optind) < argc) && (arg = argv[optind]) && (arg[0])) {
                    pairing_challenge_value_.assign(arg);
                }
            }
        }
        request_line_.assign(pairing_pair_request_);
        request_line_.append(pairing_pair_path_);
        json_content_.assign(json_content_begin_);
        json_content_.append(json_content_id_);
        json_content_.append(pairing_id_);
        json_content_.append(json_content_middle_);
        json_content_.append(json_content_challenge_type_);
        json_content_.append(pairing_challenge_type_);
        json_content_.append(json_content_int_middle_);
        json_content_.append(json_content_challenge_value_);
        json_content_.append(pairing_challenge_value_);
        json_content_.append(json_content_middle_);
        json_content_.append(json_content_challenge_token_);
        json_content_.append(pairing_challenge_token_);
        json_content_.append(json_content_int_end_);
        err = json_content_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int pairing_cancel_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        request_line_.assign(pairing_cancel_request_);
        request_line_.append(pairing_cancel_path_);
        err = auth_pairing_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int pairing_start_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        request_line_.assign(pairing_start_request_);
        request_line_.append(pairing_start_path_);
        err = pairing_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int auth_pairing_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = json_pairing_before_write_request(writer, request, argc, argv, env))) {
            err = auth_json_content_before_write_request(writer, request, argc, argv, env);
        }
        return err;
    }
    virtual int pairing_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = json_pairing_before_write_request(writer, request, argc, argv, env))) {
            err = json_content_before_write_request(writer, request, argc, argv, env);
        }
        return err;
    }
    virtual int json_pairing_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        json_content_.assign(json_content_begin_);
        json_content_.append(json_content_id_);
        json_content_.append(pairing_id_);
        json_content_.append(json_content_middle_);
        json_content_.append(json_content_name_);
        json_content_.append(pairing_name_);
        json_content_.append(json_content_end_);
        return err;
    }
    virtual int json_content_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        content_length_.assign_unsigned(json_content_.length());
        request_content_.assign(json_content_);
        err = all_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int auth_json_content_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        content_length_.assign_unsigned(json_content_.length());
        request_content_.assign(json_content_);
        err = auth_before_write_request(writer, request, argc, argv, env);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int hdmi_1_input_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        err = hdmi_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int hdmi_n_input_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        err = hdmi_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int hdmi_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        err = input_before_write_request(writer, request, argc, argv, env);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int set_input_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        err = input_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int get_input_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        err = input_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int input_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        err = out_before_write_request(writer, request, argc, argv, env);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int volume_up_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        err = volume_before_write_request(volume_up_code_, writer, request, argc, argv, env);
        return err;
    }
    virtual int volume_down_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        err = volume_before_write_request(volume_down_code_, writer, request, argc, argv, env);
        return err;
    }
    virtual int volume_before_write_request(const string_t& volume_code, writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        request_line_.assign(key_command_request_);
        request_line_.append(key_command_path_);
        json_content_.assign(json_content_begin_);
        json_content_.append(json_content_keylist_);
        json_content_.append(json_content_codeset_);
        json_content_.append(volume_codeset_);
        json_content_.append(json_content_int_middle_);
        json_content_.append(json_content_code_);
        json_content_.append(volume_code);
        json_content_.append(json_content_int_middle_);
        json_content_.append(json_content_action_);
        json_content_.append(json_content_keypress_);
        json_content_.append(json_content_keylist_end_);
        json_content_.append(json_content_int_end_);
        err = auth_json_content_before_write_request(writer, request, argc, argv, env);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int power_on_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        err = power_before_write_request(power_on_code_, writer, request, argc, argv, env);
        return err;
    }
    virtual int power_off_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        err = power_before_write_request(power_off_code_, writer, request, argc, argv, env);
        return err;
    }
    virtual int power_toggle_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        err = power_before_write_request(power_toggle_code_, writer, request, argc, argv, env);
        return err;
    }
    virtual int power_before_write_request(const string_t& power_code, writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        request_line_.assign(key_command_request_);
        request_line_.append(key_command_path_);
        json_content_.assign(json_content_begin_);
        json_content_.append(json_content_keylist_);
        json_content_.append(json_content_codeset_);
        json_content_.append(power_codeset_);
        json_content_.append(json_content_int_middle_);
        json_content_.append(json_content_code_);
        json_content_.append(power_code);
        json_content_.append(json_content_int_middle_);
        json_content_.append(json_content_action_);
        json_content_.append(json_content_keypress_);
        json_content_.append(json_content_keylist_end_);
        json_content_.append(json_content_int_end_);
        err = auth_json_content_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int power_mode_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        request_line_.assign(power_mode_request_);
        request_line_.append(power_mode_path_);
        request_content_.assign(json_content_);
        err = auth_before_write_request(writer, request, argc, argv, env);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int auth_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;

        request_line_.append(request_protocol_);

        request_headers_.assign(auth_header_);
        request_headers_.append(pairing_token_);
        request_headers_.append(header_end_);

        request_headers_.append(content_type_header_);
        request_headers_.append(content_type_);
        request_headers_.append(header_end_);

        request_headers_.append(content_length_header_);
        request_headers_.append(content_length_);
        request_headers_.append(header_end_);
        request_headers_.append(header_end_);

        request.assign(request_line_);
        request.append(request_headers_);
        request.append(request_content_);
        err = out_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int all_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;

        request_line_.append(request_protocol_);

        request_headers_.assign(content_type_header_);
        request_headers_.append(content_type_);
        request_headers_.append(header_end_);

        request_headers_.append(content_length_header_);
        request_headers_.append(content_length_);
        request_headers_.append(header_end_);
        request_headers_.append(header_end_);

        request.assign(request_line_);
        request.append(request_headers_);
        request.append(request_content_);
        err = out_before_write_request(writer, request, argc, argv, env);
        return err;
    }
    virtual int out_before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        this->outln();
        this->out(request.chars());
        this->outln();
        return err;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_hdmi_n_input_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        if (!(err = this->set_client_run(argc, argv, env))) {
            before_write_request_ = &Derives::hdmi_n_input_before_write_request;
        }
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
        if (!(err = this->set_client_run(argc, argv, env))) {
            before_write_request_ = &Derives::hdmi_1_input_before_write_request;
        }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_get_input_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            err = this->on_set_input_option(optval, optarg, optname, optind, argc, argv, env);
        } else {
        if (!(err = this->set_client_run(argc, argv, env))) {
            before_write_request_ = &Derives::get_input_before_write_request;
        }
        }
        return err;
    }
    virtual int on_set_input_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
        if (!(err = this->set_client_run(argc, argv, env))) {
            before_write_request_ = &Derives::set_input_before_write_request;
        }
        } else {
            err = this->on_get_input_option(optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_up_volume_up_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if (!(err = this->set_client_run(argc, argv, env))) {
            before_write_request_ = &Derives::volume_up_before_write_request;
        }
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
    ///////////////////////////////////////////////////////////////////////
    virtual int on_down_volume_down_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if (!(err = this->set_client_run(argc, argv, env))) {
            before_write_request_ = &Derives::volume_down_before_write_request;
        }
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

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_get_auth_token_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        err = set_get_auth_token_run(argc, argv, env);
        return err;
    }
    virtual int on_set_auth_token_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            pairing_token_.assign(optarg);
        } else {
            err = set_get_auth_token_run(argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_pairing_pair_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if (!(err = this->set_client_run(argc, argv, env))) {
            before_write_request_ = &Derives::pairing_pair_before_write_request;
        }
        return err;
    }
    virtual int on_pairing_start_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if (!(err = this->set_client_run(argc, argv, env))) {
            before_write_request_ = &Derives::pairing_start_before_write_request;
        }
        return err;
    }
    virtual int on_pairing_stop_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if (!(err = this->set_client_run(argc, argv, env))) {
            before_write_request_ = &Derives::pairing_cancel_before_write_request;
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_get_power_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if (!(err = this->set_client_run(argc, argv, env))) {
            before_write_request_ = &Derives::power_mode_before_write_request;
        }
        return err;
    }
    virtual int on_set_power_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if (!(err = this->set_client_run(argc, argv, env))) {
            before_write_request_ = &Derives::power_mode_before_write_request;
            if ((optarg) && (optarg[0])) {
                before_write_request_ = &Derives::power_toggle_before_write_request;
            }
        }
        return err;
    }
    virtual int on_power_on_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if (!(err = this->set_client_run(argc, argv, env))) {
            before_write_request_ = &Derives::power_on_before_write_request;
        }
        return err;
    }
    virtual int on_power_off_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if (!(err = this->set_client_run(argc, argv, env))) {
            before_write_request_ = &Derives::power_off_before_write_request;
        }
        return err;
    }
    virtual int on_power_toggle_option
    (int optval, const char_t* optarg, const char_t* optname, 
     int optind, int argc, char_t**argv, char_t**env) {
        int err = 0;
        if (!(err = this->set_client_run(argc, argv, env))) {
            before_write_request_ = &Derives::power_toggle_before_write_request;
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    string_t get_request_, put_request_, post_request_, request_protocol_, 
            auth_header_, content_type_header_, content_type_, 
            content_length_header_, content_length_, header_end_, 

            json_content_begin_, json_content_middle_, json_content_end_, 
            json_content_int_middle_, json_content_int_end_, 
            json_content_name_, json_content_id_, 
            json_content_challenge_type_, json_content_challenge_token_, 
            json_content_challenge_value_, json_content_auth_token_, 
            json_content_keylist_, json_content_keydown_, json_content_keyup_, json_content_keypress_,
            json_content_codeset_, json_content_code_, json_content_action_, 
            json_content_keylist_end_, json_content_keylist_int_end_, json_content_, 

            key_command_request_, key_command_path_,
            volume_codeset_, volume_up_code_, volume_down_code_, 
            power_codeset_, power_on_code_, power_off_code_, power_toggle_code_,
            power_mode_request_, power_mode_path_, 

            pairing_start_request_, pairing_start_path_, 
            pairing_cancel_request_, pairing_cancel_path_, 
            pairing_pair_request_, pairing_pair_path_, 
            pairing_name_, pairing_id_, pairing_token_, 
            pairing_challenge_type_, pairing_challenge_token_, pairing_challenge_value_, 

            request_line_, request_headers_, request_content_;
}; /// class maint
typedef maint<> main;

} /// namespace client
} /// namespace vizio
} /// namespace console 
} /// namespace app 
} /// namespace talas 

#endif /// ndef TALAS_APP_CONSOLE_VIZIO_CLIENT_MAIN_HPP
