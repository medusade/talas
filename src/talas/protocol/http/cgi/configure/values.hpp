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
///   File: values.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_HTTP_CGI_CONFIGURE_VALUES_HPP
#define TALAS_PROTOCOL_HTTP_CGI_CONFIGURE_VALUES_HPP

#include "talas/protocol/http/cgi/configure/setting.hpp"
#include "talas/io/crt/file/reader.hpp"
#include "talas/io/crt/file/writer.hpp"
#include "talas/base/array.hpp"

namespace talas {
namespace protocol {
namespace http {
namespace cgi {
namespace configure {

/// class valuest
template 
<class TExtends = arrayt<configure::value, configure::count>, 
 class TImplements = typename TExtends::implements>
class exported valuest: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef valuest derives;

    typedef configure::setting setting_t;
    typedef configure::value::part_t part_t;
    typedef configure::value::string_t string_t;
    typedef configure::value::chars_t chars_t;
    typedef configure::value::string_t::char_t char_t;
    typedef configure::value::reader_t reader_t;
    typedef configure::value::writer_t writer_t;
    typedef io::crt::file::readert<reader_t> file_reader_t;

    /// constructor / destructor
    valuest(const valuest& copy) {
        init();
    }
    valuest() {
        init();
    }
    virtual ~valuest() {
    }

    /// read / write
    virtual int read(const string_t& file_name, const string_t& file_pattern) {
        int count = 0;
        const char_t *name, *pattern = 0;
        init();
        if ((name = file_name.has_chars()) && (pattern = file_pattern.has_chars())) {
            count = read(name, pattern);
        }
        return count;
    }
    virtual int read(const char_t* file_name, const char_t* file_pattern) {
        int count = 0;
        init();
        if ((file_name) && (file_name[0]) && (file_pattern) && (file_pattern[0])) {
            file_reader_t file;
            
            if ((file.open_safe(file_name, file_pattern))) {
                count = read(file);
                file.close();
            }
        }
        return count;
    }
    virtual int read(reader_t& reader) {
        int count = 0;
        ssize_t amount = 0;
        setting_t setting;
        char_t c = 0;

        init();
        do {
            if ((setting.read(amount, c, reader))) {
                if (('\r' == c)) {
                    if (0 < (reader.read(&c, 1))) {
                        if (('\n' == c)) {
                            configure::value& value = setting.value();
                            configure::which_t which = value.which();
                            configure::value& what = operator[](which);
        
                            if (&null_ != (&what)) {
                                if ((what.is_set(which, value))) {
                                    what.set_setting();
                                    ++count;
                                }
                            }
                            continue;
                        }
                    }
                }
            }
            break;
        } while (0 < (amount));
        return count;
    }
    virtual int write(writer_t& writer) {
        int count = 0;
        ssize_t amount = 0;
        configure::value* value = 0;
        const char_t *name = 0, *setting = 0;

        for (configure::which_t which = configure::first; which <= configure::last; ++which) {
            if ((value = value_of(which)) && (name = value->of()) && (setting = value->setting())) {
                if (0 < (amount = writer.write(name))) {
                    if (0 < (amount = writer.write("="))) {
                        if (0 <= (amount = writer.write(setting))) {
                            if (0 < (amount = writer.write("\r\n"))) {
                                ++count;
                            }
                        }
                    }
                }
            }
        }
        return count;
    }

    /// setting_of
    virtual const char_t* setting_of(configure::value*& value, const char_t* name) const {
        if ((value = value_of(name))) {
            return value->setting();
        }
        return 0;
    }
    virtual const char_t* setting_of(configure::value*& value, configure::which_t which) const {
        if ((value = value_of(which))) {
            return value->setting();
        }
        return 0;
    }
    virtual const char_t* setting_of(const char_t* name) const {
        configure::value* value = 0;
        if ((value = value_of(name))) {
            return value->setting();
        }
        return 0;
    }
    virtual const char_t* set_setting_of(configure::which_t which, const char_t* to) {
        configure::value* value = 0;
        if ((value = value_of(which))) {
            return value->set_setting(to);
        }
        return 0;
    }
    virtual const char_t* setting_of(configure::which_t which) const {
        configure::value* value = 0;
        if ((value = value_of(which))) {
            return value->setting();
        }
        return 0;
    }

    /// value_of
    virtual configure::value* value_of(const char_t* name) const {
        configure::value& value = operator[](name);
        if ((&null_ != (&value)) && (configure::none != (value.which()))) {
            return &value;
        }
        return 0;
    }
    virtual configure::value* value_of(configure::which_t which) const {
        configure::value& value = operator[](which);
        if ((&null_ != (&value)) && (configure::none != (value.which()))) {
            return &value;
        }
        return 0;
    }

    /// first / next
    virtual configure::value* first(configure::which_t& which) const {
        configure::value* value = 0;
        for (which = configure::first; which <= configure::last; ++which) {
            if ((value = value_of(which))) {
                return value;
            }
        }
        return 0;
    }
    virtual configure::value* next(configure::which_t& which) const {
        if ((which < configure::last)) {
            configure::value* value = 0;
            do {
                if ((value = value_of(++which))) {
                    return value;
                }
            } while (which <= configure::last);
        }
        return 0;
    }

    /// operator[]
    virtual configure::value& operator[](const char_t* name) const {
        configure::which_t which = configure::which::of_name(name);
        if ((which >= configure::first) && (which <= configure::last)) {
            return (configure::value&)(extends::operator[](which - configure::first));
        }
        return (configure::value&)null_;
    }
    virtual configure::value& operator[](configure::which_t which) const {
        if ((which >= configure::first) && (which <= configure::last)) {
            return (configure::value&)(extends::operator[](which - configure::first));
        }
        return (configure::value&)null_;
    }

    /// ...is_logged
    virtual bool set_is_logged(bool to = true) {
        return logged_.set_is_logged(to);
    }
    virtual bool is_logged() const {
        return logged_.is_logged();
    }

protected:
    /// init
    virtual valuest& init() {
        configure::value* value = 0; size_t size = 0;
        if ((value = this->elements()) && (count <= (size = this->size()))) {
            for (configure::which_t which = configure::first; which <= configure::last; ++which) {
                configure::value& v = value[which - configure::first];
                v.set_which(which);
                v.clear();
            }
        }
        return *this;
    }

    /// end_of_name
    virtual const char_t* end_of_name(const char_t* chars) const {
        const char_t* name = 0;
        if ((name = chars) && (name[0])) {
            for (char_t end = '=', c = *(name); c; c = *(++name)) {
                if (end == c) {
                    if (name != chars) {
                        return name;
                    }
                    break;
                }
            }
        }
        return 0;
    }

protected:
    configure::value null_;
    xos::extended::logged logged_;
}; /// class valuest
typedef valuest<> values;

} /// namespace configure
} /// namespace cgi
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_CGI_CONFIGURE_VALUES_HPP 
