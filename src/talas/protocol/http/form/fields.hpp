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
///   File: fields.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_HTTP_FORM_FIELDS_HPP
#define TALAS_PROTOCOL_HTTP_FORM_FIELDS_HPP

#include "talas/protocol/xttp/message/part.hpp"
#include "talas/protocol/http/form/field.hpp"
#include <list>

namespace talas {
namespace protocol {
namespace http {
namespace form {

/// class fieldst
template <class TExtends = xttp::message::part, class TImplements = typename TExtends::implements>
class exported fieldst: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef fieldst derives;

    typedef form::field field_t;
    typedef std::list<field_t*> list_t;
    typedef list_t::const_iterator const_iterator_t;

    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    fieldst(const string_t& chars): extends(chars), read_started_(false), field_(0) {
        separate();
    }
    fieldst(const char_t* chars, size_t length): extends(chars, length), read_started_(false), field_(0) {
        separate();
    }
    fieldst(const char_t* chars): extends(chars), read_started_(false), field_(0) {
        separate();
    }
    fieldst(const fieldst& copy): extends(copy), read_started_(false), field_(0) {
        separate();
    }
    fieldst(): read_started_(false), field_(0) {
        this->set_is_combined(false);
    }
    virtual ~fieldst() {
        clear_list();
        free_field();
    }

    /// read / write
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = true;
        const char_t* chars = 0;
        size_t length = 0;
        field_t* f = 0;

        if (!(read_started_)) {
            set_default();
        }
        do {
            LOGGER_IS_LOGGED_DEBUG("read_field(count, c, reader)...");
            if ((f = read_field(count, c, reader))) {
                LOGGER_IS_LOGGED_DEBUG("...field = \"" << f->chars() << "\" on read_field(count, c, reader)");

                if ((chars = f->has_chars(length))) {
                    list_.push_back(f);
                    on_add_field(*f);
                } else {
                    free_field(f);
                    break;
                }
            }
        } while ((f) && ('&' == c));
        return success;
    }
    virtual bool write(ssize_t& count, writer_t& writer) {
        bool success = true;
        if ((this->is_combined())) {
            success = this->write_this(count, writer);
        } else {
            const char_t* chars = 0;
            size_t length = 0;
            ssize_t amount = 0;
            field_t* f = 0;
            const_iterator_t i, begin, end;
    
            for (count = 0, begin = list_.begin(), end = list_.end(), i = begin; i != end; ++i) {
                if ((f = (*i))) {
                    if ((chars = f->has_chars(length))) {
                        if (i != begin) {
                            LOGGER_IS_LOGGED_DEBUG("writer.write(\"&\")...");
                            if (1 <= (amount = writer.write("&"))) {
                                LOGGER_IS_LOGGED_DEBUG("...amount = " << amount << " on writer.write(\"&\")");
                                count += amount;
                            } else {
                                success = false;
                                break;
                            }
                        }
                        LOGGER_IS_LOGGED_DEBUG("writer.write(chars, length) with chars = \"" << chars << "\"");
                        if (length <= (amount = writer.write(chars, length))) {
                            LOGGER_IS_LOGGED_DEBUG("...amount = " << amount << " on writer.write(chars, length) with chars = \"" << chars << "\"");
                            count += amount;
                            continue;
                        }
                    }
                }
                success = false;
                break;
            }
        }
        return success;
    }

    /// combine / separate
    virtual bool combine() {
        bool success = true;
        this->clear();
        if ((this->set_is_combined())) {
            const char_t* chars = 0;
            size_t length = 0;
            field_t* f = 0;
            const_iterator_t i, end;
            
            for (end = list_.end(), i = list_.begin(); i != end; ++i) {
                if ((f = (*i))) {
                    if ((chars = f->has_chars(length))) {
                        if (0 < (this->length())) {
                            this->append("&");
                        }
                        this->append(chars, length);
                        continue;
                    }
                }
                success = false;
                break;
            }
        }
        return success;
    }
    virtual bool separate() {
        bool success = true;
        if ((this->is_combined())) {
            const char_t* chars = 0;
            size_t length = 0;
    
            set_defaults();
            if ((chars = this->has_chars(length))) {
                const char_t *end = chars + length, *first = chars, *last = 0;
                field_t* f = 0;
                char_t c = 0;
    
                for (; chars != end; ++chars) {
                    if ('&' != (c = *chars)) {
                        last = chars;
                    } else {
                        if (last) {
                            if ((f = add_field(first, (last - first) + 1))) {
                                on_add_field(*f);
                                first = ++last;
                                last = 0;
                            } else {
                                success = false;
                                break;
                            }
                        } else {
                            success = false;
                            break;
                        }
                    }
                }
            }
        }
        return success;
    }

    /// set_default...
    virtual derives& set_default() {
        this->set_is_combined(false);
        this->clear();
        set_defaults();
        return *this;
    }
    virtual derives& set_defaults() {
        clear_list();
        free_field();
        return *this;
    }

    /// add / get / free / clear field
    virtual field_t* read_field(ssize_t& count, char_t& c, reader_t& reader) {
        field_t* f = 0;
        if ((f = get_field())) {
            if ((f->read(count, c, reader))) {
                return f;
            }
            free_field(f);
        }
        return 0;
    }
    virtual void on_add_field(field &f) {
    }
    virtual field_t* add_field(const char_t *chars, size_t length) {
        if ((chars) && (length)) {
            field_t* f = 0;
            if ((f = get_field())) {
                f->assign(chars, length);
                if ((f->separate())) {
                    list_.push_back(f);
                    return f;
                }
                free_field(f);
            }
        }
        return 0;
    }
    virtual field_t* get_field() {
        field_t* f = 0;
        if (!(f = field_)) {
            f = new field;
        } else {
            field_ = 0;
        }
        return f;
    }
    virtual void free_field(field_t* f = 0) {
        if ((f)) {
            if ((field_)) {
                if ((field_ != f)) {
                    delete field_;
                    field_ = f;
                }
            } else {
                field_ = f;
            }
        } else {
            if ((field_)) {
                delete field_;
                field_ = 0;
            }
        }
    }
    virtual void clear_list() {
        for (field_t* f = 0; !list_.empty(); list_.pop_front()) {
            if ((f = list_.front())) {
                delete f;
            }
        }
    }

    /// has_value_of
    virtual const char_t* has_value_of(const string_t& named) const {
        const char_t* chars = 0;
        if ((chars = named.has_chars())) {
            return has_value_of(chars);
        }
        return 0;
    }
    virtual const char_t* has_value_of(const char_t* named) const {
        const field_t* found = 0;
        if ((found = find(named))) {
            return found->value().has_chars();
        }
        return 0;
    }

    /// find...
    virtual const field_t* find(const string& named) const {
        const char* chars = 0;
        if ((chars = named.has_chars())) {
            return find(chars);
        }
        return 0;
    }
    virtual const field_t* find(const char* named) const {
        const_iterator_t at;
        return find_first(at, named);
    }
    virtual const field_t* find_first(const_iterator_t& at, const char* named) const {
        if ((named) && (named[0])) {
            const field_t* found = 0;
            const_iterator_t end = list_.end();
            for (at = list_.begin(); at != end; ++at) {
                if ((found = (*at)) && (!(found->name().compare(named)))) {
                    return found;
                }
            }
        }
        return 0;
    }
    virtual const field_t* find_last(const_iterator_t& at, const char* named) const {
        if ((named) && (named[0])) {
            const field_t* found = 0;
            const_iterator_t begin = list_.begin();
            for (at = list_.end(); at != begin; ) {
                if ((found = (*--at)) && (!(found->name().compare(named)))) {
                    return found;
                }
            }
        }
        return 0;
    }
    virtual const field_t* find_next(const_iterator_t& at, const char* named) const {
        if ((named) && (named[0])) {
            const field_t* found = 0;
            for (const_iterator_t end = list_.end(); at != end; ) {
                if ((found = (*++at)) && (!(found->name().compare(named)))) {
                    return found;
                }
            }
        }
        return 0;
    }
    virtual const field_t* find_prev(const_iterator_t& at, const char* named) const {
        if ((named) && (named[0])) {
            const field_t* found = 0;
            for (const_iterator_t begin = list_.begin(); at != begin; ) {
                if ((found = (*--at)) && (!(found->name().compare(named)))) {
                    return found;
                }
            }
        }
        return 0;
    }

    /// first / last / next / prev
    virtual const field_t* first(const_iterator_t& at) const {
        if ((at = list_.begin()) != list_.end()) {
            return (*at);
        }
        return 0;
    }
    virtual const field_t* next(const_iterator_t& at) const {
        if ((at != list_.end())) {
            if ((++at != list_.end())) {
                return (*at);
            }
        }
        return 0;
    }
    virtual const field_t* last(const_iterator_t& at) const {
        if ((at = list_.end()) != list_.begin()) {
            return (*--at);
        }
        return 0;
    }
    virtual const field_t* prev(const_iterator_t& at) const {
        if ((at != list_.begin())) {
            return (*--at);
        }
        return 0;
    }
    virtual size_t length() const {
        return list_.size();
    }

    /// start / finish read
    virtual bool start_read() {
        read_started_ = true;
        set_default();
        return true;
    }
    virtual bool finish_read() {
        read_started_ = false;
        return true;
    }

protected:
    bool read_started_;
    field_t* field_;
    list_t list_;
}; /// class fieldst
typedef fieldst<> fields;

} /// namespace form
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_HTTP_FORM_FIELDS_HPP 
