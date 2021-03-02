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
///   Date: 2/14/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_HPP
#define TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_HPP

#include "talas/app/console/network/client/main_opt.hpp"

#if !defined (TALAS_APP_CONSOLE_NETWORK_CLIENT_REQUEST)
#define TALAS_APP_CONSOLE_NETWORK_CLIENT_REQUEST \
    "GET / HTTP/1.0\r\nHost:localhost\r\nContent-Type:text/plain\r\nContent-Length:5\r\n\r\nGet\r\n"
#endif /// !defined (TALAS_APP_CONSOLE_NETWORK_CLIENT_REQUEST)

namespace talas {
namespace app {
namespace console {
namespace network {
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
    maint(): request_(TALAS_APP_CONSOLE_NETWORK_CLIENT_REQUEST), content_length_(0) {
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
    virtual int client_sockets_run(socket_t& socket, int argc, char_t** argv, char_t** env) {
        string_t& request = this->request();
        int err = 0;

        if (!(err = all_send_request(socket, request, argc, argv, env))) {
            string_t& response = this->response();

            if (!(err = all_recv_response(response, socket, argc, argv, env))) {
                
                if (!(err = all_on_recv_response(response, socket, argc, argv, env))) {
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_recv_response(string_t& response, socket_t& socket, int argc, char_t** argv, char_t** env) {
        int err = 0;
        const char_t* chars = 0; size_t length = 0;
        
        if ((chars = response.has_chars(length))) {
            size_t content_length = 0, content_size = 0;
            char_t* content = 0;

            this->outln(chars, length);
            if ((0 < (content_length = this->content_length())) && (content = this->content(content_size))) {
                socket_reader_t socket_reader(socket);
                sized_reader_t content_reader(socket_reader, content_length);
                ssize_t amount = 0;
                
                for (length = 0; (0 < (amount = content_reader.read(content, content_size))); length += amount) {
                    this->outln(content, amount);
                }
            }
        }
        return err;
    }
    virtual int before_on_recv_response(string_t& response, socket_t& socket, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_on_recv_response(string_t& response, socket_t& socket, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_on_recv_response(string_t& response, socket_t& socket, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_on_recv_response(response, socket, argc, argv, env))) {
            int err2 = 0;
            err = on_recv_response(response, socket, argc, argv, env);
            if ((err2 = after_on_recv_response(response, socket, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_recv_response(string_t& response, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;

        if (!(err = all_on_process_response(response, argc, argv, env))) {
            char_t* content = 0; size_t content_size = 0;

            if ((content = this->content(content_size))) {
                string_t& content_type = this->content_type();
                size_t content_length = 0;
                ssize_t amount = 0;
                
                if ((0 < (content_length = this->content_length()))) {
                    sized_reader_t content_reader(reader, content_length);
                    
                    err = all_on_recv_response_content
                    (content, content_size, content_length, content_type, content_reader, argc, argv, env);
                } else {
                    const char_t* chars = 0; size_t length = 0;

                    if ((chars = content_type.has_chars(length))) {
                        err = all_on_recv_response_content
                        (content, content_size, content_length, content_type, reader, argc, argv, env);
                    }
                }
            }
        }
        return err;
    }
    virtual int before_on_recv_response(string_t& response, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_on_recv_response(string_t& response, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_on_recv_response(string_t& response, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_on_recv_response(response, reader, argc, argv, env))) {
            int err2 = 0;
            err = on_recv_response(response, reader, argc, argv, env);
            if ((err2 = after_on_recv_response(response, reader, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_recv_response_content
    (char_t* content, size_t content_size, size_t content_length, 
     string_t& content_type, reader_t& content_reader, int argc, char_t** argv, char_t** env) {
        int err = 0;

        if ((content) && (content_size)) {
            string_t& content_encoding = this->content_encoding();
            size_t length = 0;
            ssize_t amount = 0;

            for (length = 0; (0 < (amount = content_reader.read(content, content_size))); length += amount) {
                if ((err = all_on_process_response_content
                     (content, amount, content_length, content_encoding, content_type, argc, argv, env))) {
                    break;
                }
            }
        }
        return err;
    }
    virtual int before_on_recv_response_content
    (char_t* content, size_t content_size, size_t content_length, 
     string_t& content_type, reader_t& content_reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_on_recv_response_content
    (char_t* content, size_t content_size, size_t content_length, 
     string_t& content_type, reader_t& content_reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_on_recv_response_content(char_t* content, size_t content_size, size_t content_length, string_t& content_type, reader_t& content_reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_on_recv_response_content(content, content_size, content_length, content_type, content_reader, argc, argv, env))) {
            int err2 = 0;
            err = on_recv_response_content(content, content_size, content_length, content_type, content_reader, argc, argv, env);
            if ((err2 = after_on_recv_response_content(content, content_size, content_length, content_type, content_reader, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_process_response(string_t& response, int argc, char_t** argv, char_t** env) {
        int err = 0;
        const char_t* chars = 0; size_t length = 0;
        
        if ((chars = response.has_chars(length))) {
            this->outln(chars, length);
        }
        return err;
    }
    virtual int before_on_process_response(string_t& response, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_on_process_response(string_t& response, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_on_process_response(string_t& response, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_on_process_response(response, argc, argv, env))) {
            int err2 = 0;
            err = on_process_response(response, argc, argv, env);
            if ((err2 = after_on_process_response(response, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_process_response_content
    (char_t* content, size_t content_size, size_t content_length, 
     string_t& content_encoding, string_t& content_type, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if ((content) && (content_size)) {
            this->outln(content, content_size);
        }
        return err;
    }
    virtual int before_on_process_response_content
    (char_t* content, size_t content_size, size_t content_length, 
     string_t& content_encoding, string_t& content_type, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_on_process_response_content
    (char_t* content, size_t content_size, size_t content_length, 
     string_t& content_encoding, string_t& content_type, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_on_process_response_content
    (char_t* content, size_t content_size, size_t content_length, 
     string_t& content_encoding, string_t& content_type, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_on_process_response_content(content, content_size, content_length, content_encoding, content_type, argc, argv, env))) {
            int err2 = 0;
            err = on_process_response_content(content, content_size, content_length, content_encoding, content_type, argc, argv, env);
            if ((err2 = after_on_process_response_content(content, content_size, content_length, content_encoding, content_type, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int send_request(socket_t& socket, string_t& request, int argc, char_t** argv, char_t** env) {
        socket_writer_t writer(socket);
        int err = 0;
        
        if (!(err = all_write_request(writer, request, argc, argv, env))) {
        }
        return err;
    }
    virtual int before_send_request(socket_t& socket, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_send_request(socket_t& socket, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_send_request(socket_t& socket, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_send_request(socket, request, argc, argv, env))) {
            int err2 = 0;
            err = send_request(socket, request, argc, argv, env);
            if ((err2 = after_send_request(socket, request, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int recv_response(string_t& response, socket_t& socket, int argc, char_t** argv, char_t** env) {
        socket_reader_t reader(socket);
        int err = 0;
        
        if (!(err = all_read_response(response, reader, argc, argv, env))) {
        }
        return err;
    }
    virtual int before_recv_response(string_t& response, socket_t& socket, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_recv_response(string_t& response, socket_t& socket, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_recv_response(string_t& response, socket_t& socket, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_recv_response(response, socket, argc, argv, env))) {
            int err2 = 0;
            err = recv_response(response, socket, argc, argv, env);
            if ((err2 = after_recv_response(response, socket, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        const char_t* chars = 0; size_t length = 0;
        int err = 0;

        if ((chars = request.has_chars(length))) {
            ssize_t count = 0;

            TALAS_LOG_DEBUG("writer.write(chars = \"" << chars << "\", length = " << length << ")...");
            if (((ssize_t)length) != (count = writer.write(chars, length))) {
                TALAS_LOG_ERROR("...failed " << count << " = writer.write(chars = \"" << chars << "\", length = " << length << ")...");
            } else {
                TALAS_LOG_DEBUG("..." << count << " = writer.write(chars = \"" << chars << "\", length = " << length << ")");
            }
        }
        return err;
    }
    virtual int before_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_write_request(writer_t& writer, string_t& request, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_write_request(writer, request, argc, argv, env))) {
            int err2 = 0;
            err = write_request(writer, request, argc, argv, env);
            if ((err2 = after_write_request(writer, request, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int read_response(string_t& response, reader_t& reader, int argc, char_t** argv, char_t** env) {
        char_t* chars = 0; size_t size = 0;
        int err = 0;
        
        if ((chars = this->recved(size)) && (size)) {
            ssize_t amount = 0, count = 0;
            string_t response_line;

            TALAS_LOG_DEBUG("reader.read_crlf(chars, size = " << size << "))...");
            if (0 < (amount = reader.read_crlf(chars, size))) {

                response_line.assign(chars, amount);
                TALAS_LOG_DEBUG("..." << amount << " = reader.read_crlf(chars = \"" << response_line << "\", size = " << size << "))...");
                if (!(err = all_on_read_response_line(response, response_line, reader, argc, argv, env))) {
                    while (2 < amount) {

                        TALAS_LOG_DEBUG("reader.read_crlf(chars, size = " << size << "))...");
                        if (0 < (amount = reader.read_crlf(chars, size))) {
            
                            response_line.assign(chars, amount);
                            TALAS_LOG_DEBUG("..." << amount << " = reader.read_crlf(chars = \"" << response_line << "\", size = " << size << "))...");
                            if ((err = all_on_read_response_header(response, response_line, reader, argc, argv, env))) {
                                break;
                            }
                        } else {
                            TALAS_LOG_ERROR("...failed" << amount << " = reader.read_crlf(chars, size = " << size << "))...");
                            err = 1;
                        }
                    }
                }
            } else {
                TALAS_LOG_ERROR("...failed" << amount << " = reader.read_crlf(chars, size = " << size << "))...");
                err = 1;
            }
        } else {
            err = 1;
        }
        return err;
    }
    virtual int before_read_response(string_t& response, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_read_response(string_t& response, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_read_response(string_t& response, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_read_response(response, reader, argc, argv, env))) {
            int err2 = 0;
            err = read_response(response, reader, argc, argv, env);
            if ((err2 = after_read_response(response, reader, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_read_response_line(string_t& response, string_t& response_line, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        response.assign(response_line);
        return err;
    }
    virtual int before_on_read_response_line(string_t& response, string_t& response_line, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_on_read_response_line(string_t& response, string_t& response_line, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_on_read_response_line(string_t& response, string_t& response_line, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_on_read_response_line(response, response_line, reader, argc, argv, env))) {
            int err2 = 0;
            err = on_read_response_line(response, response_line, reader, argc, argv, env);
            if ((err2 = after_on_read_response_line(response, response_line, reader, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_read_response_header(string_t& response, string_t& response_header, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        response.append(response_header);
        if (!(err = all_on_read_message_header(response, response_header, reader, argc, argv, env))) {
        }
        return err;
    }
    virtual int before_on_read_response_header(string_t& response, string_t& response_header, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_on_read_response_header(string_t& response, string_t& response_header, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_on_read_response_header(string_t& response, string_t& response_header, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_on_read_response_header(response, response_header, reader, argc, argv, env))) {
            int err2 = 0;
            err = on_read_response_header(response, response_header, reader, argc, argv, env);
            if ((err2 = after_on_read_response_header(response, response_header, reader, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_read_message_header(string_t& message, string_t& message_header, reader_t& reader, int argc, char_t** argv, char_t** env) {
        const char_t* chars = 0; size_t length = 0;
        int err = 0;

        if ((chars = message_header.has_chars(length))) {
            char_t c = 0, name_separator = this->message_header_name_separator();
            string_t name, value;

            for (size_t i = 0; i < length; ++i) {

                if ((name_separator == (c = chars[i]))) {
                    if (0 < (i)) { 
                        const char_t sp = ((const char_t)' ');

                        name.assign(chars, i);
                        for (++i; i < length; ++i) {

                            if (sp != (c = chars[i])) {
                                const char_t cr = ((const char_t)'\r');
 
                                for (size_t j = i+1; j < length; ++j) {
                                    if (!(cr != (c = chars[j]))) {
                                        length = j;
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        if ((i < length)) {
                            value.assign(chars+i, length-i);
                        }
                        err = all_on_read_message_header_fields(name, value, argc, argv, env);
                    } else {
                        err = 1;
                    }
                    break;
                }
            }
        }
        return err;
    }
    virtual int before_on_read_message_header(string_t& message, string_t& message_header, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_on_read_message_header(string_t& message, string_t& message_header, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_on_read_message_header(string_t& message, string_t& message_header, reader_t& reader, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_on_read_message_header(message, message_header, reader, argc, argv, env))) {
            int err2 = 0;
            err = on_read_message_header(message, message_header, reader, argc, argv, env);
            if ((err2 = after_on_read_message_header(message, message_header, reader, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_read_message_header_fields(string_t& name, string_t& value, int argc, char_t** argv, char_t** env) {
        const string_t& content_length_message_header_name = this->content_length_message_header_name();
        int err = 0, unequal = 0;

        if (!(unequal = name.compare(content_length_message_header_name))) {
            this->set_content_length(value);
        } else {
            const string_t& content_type_message_header_name = this->content_type_message_header_name();

            if (!(unequal = name.compare(content_type_message_header_name))) {
                this->set_content_type(value);
            } else {
            }
        }
        return err;
    }
    virtual int before_on_read_message_header_fields(string_t& name, string_t& value, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int after_on_read_message_header_fields(string_t& name, string_t& value, int argc, char_t** argv, char_t** env) {
        int err = 0;
        return err;
    }
    virtual int all_on_read_message_header_fields(string_t& name, string_t& value, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if (!(err = before_on_read_message_header_fields(name, value, argc, argv, env))) {
            int err2 = 0;
            err = on_read_message_header_fields(name, value, argc, argv, env);
            if ((err2 = after_on_read_message_header_fields(name, value, argc, argv, env))) {
                if (!(err)) err = err2;
            }
        }
        return err;
    }
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual string_t& set_request(const char_t* to, size_t length) {
        string_t& request = this->request();
        request.assign(to, length);
        return request;
    }
    virtual string_t& set_request(const char_t* to) {
        string_t& request = this->request();
        request.assign(to);
        return request;
    }
    virtual string_t& set_request(const string_t& to) {
        string_t& request = this->request();
        request.assign(to);
        return request;
    }
    virtual string_t& request() const {
        return (string_t&)request_;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual string_t& set_response(const char_t* to, size_t length) {
        string_t& response = this->response();
        response.assign(to, length);
        return response;
    }
    virtual string_t& set_response(const char_t* to) {
        string_t& response = this->response();
        response.assign(to);
        return response;
    }
    virtual string_t& set_response(const string_t& to) {
        string_t& response = this->response();
        response.assign(to);
        return response;
    }
    virtual string_t& response() const {
        return (string_t&)response_;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual string_t& set_content_encoding(const char_t* to, size_t length) {
        string_t& content_encoding = this->content_encoding();
        const string_t to_s(to, length);
        set_content_encoding(to_s);
        return content_encoding;
    }
    virtual string_t& set_content_encoding(const char_t* to) {
        string_t& content_encoding = this->content_encoding();
        const string_t to_s(to);
        set_content_encoding(to_s);
        return content_encoding;
    }
    virtual string_t& set_content_encoding(const string_t& to) {
        string_t& content_encoding = this->content_encoding();
        TALAS_LOG_DEBUG("...content_encoding.assign(\"" << to << "\")...");
        content_encoding.assign(to);
        return content_encoding;
    }
    virtual string_t& content_encoding() const {
        return (string_t&)content_encoding_;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual string_t& set_content_type(const char_t* to, size_t length) {
        string_t& content_type = this->content_type();
        const string_t to_s(to, length);
        set_content_type(to_s);
        return content_type;
    }
    virtual string_t& set_content_type(const char_t* to) {
        string_t& content_type = this->content_type();
        const string_t to_s(to);
        set_content_type(to_s);
        return content_type;
    }
    virtual string_t& set_content_type(const string_t& to) {
        string_t& content_type = this->content_type();
        TALAS_LOG_DEBUG("...content_type.assign(\"" << to << "\")...");
        content_type.assign(to);
        return content_type;
    }
    virtual string_t& content_type() const {
        return (string_t&)content_type_;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual size_t& set_content_length(const char_t* to, size_t length) {
        size_t& content_length = this->content_length();
        const string_t to_s(to, length);
        set_content_length(to_s);
        return content_length;
    }
    virtual size_t& set_content_length(const char_t* to) {
        size_t& content_length = this->content_length();
        const string_t to_s(to);
        set_content_length(to_s);
        return content_length;
    }
    virtual size_t& set_content_length(const string_t& to) {
        size_t& content_length = this->content_length();
        unsigned length = 0;
        if (0 < (length = to.to_unsigned())) {
            TALAS_LOG_DEBUG("...content_length = " << length << "...");
            content_length = length;
        }
        return content_length;
    }
    virtual size_t& content_length() const {
        return (size_t&)content_length_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const string_t& content_type_message_header_name() const {
        static const string_t header_name("Content-Type");
        return header_name;
    }
    virtual const string_t& content_length_message_header_name() const {
        static const string_t header_name("Content-Length");
        return header_name;
    }
    virtual const char_t message_header_name_separator() const {
        return (const char_t)':';
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    string_t request_, response_, content_type_, content_encoding_;
    ssize_t content_length_;
}; /// class maint
typedef maint<> main;

} /// namespace client 
} /// namespace network 
} /// namespace console 
} /// namespace app 
} /// namespace talas 

#endif /// ndef TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_HPP 