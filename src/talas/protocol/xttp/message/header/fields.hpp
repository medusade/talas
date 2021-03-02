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
#ifndef TALAS_PROTOCOL_XTTP_MESSAGE_HEADER_FIELDS_HPP
#define TALAS_PROTOCOL_XTTP_MESSAGE_HEADER_FIELDS_HPP

#include "talas/protocol/xttp/message/header/field.hpp"
#include <list>

namespace talas {
namespace protocol {
namespace xttp {
namespace message {
namespace header {

namespace extended {
/// class fieldst
template 
<class TField = field, 
 class TExtends = part, class TImplements = typename TExtends::implements>
class exported fieldst: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef fieldst derives;

    typedef TField field_t;
    typedef std::list<field_t*> list_t;
    typedef typename list_t::const_iterator const_iterator_t;
    typedef typename list_t::iterator iterator_t;
    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    fieldst(const field_t* f, va_list va)
    : content_length_(0), content_length_field_(0), 
      content_type_field_(0), content_encoding_field_(0), field_(0) {
    }
    fieldst(const field_t& f)
    : content_length_(0), content_length_field_(0), 
      content_type_field_(0), content_encoding_field_(0), field_(0) {
    }
    fieldst(const string_t& chars)
    : extends(chars), content_length_(0), content_length_field_(0), 
      content_type_field_(0), content_encoding_field_(0), field_(0) {
    }
    fieldst(const char_t* chars, size_t length)
    : extends(chars, length), content_length_(0), content_length_field_(0), 
      content_type_field_(0), content_encoding_field_(0), field_(0) {
    }
    fieldst(const char_t* chars)
    : extends(chars), content_length_(0), content_length_field_(0), 
      content_type_field_(0), content_encoding_field_(0), field_(0) {
    }
    fieldst(const fieldst& copy)
    : extends(copy), content_length_(0), content_length_field_(0), 
      content_type_field_(0), content_encoding_field_(0), field_(0) {
    }
    fieldst()
    : content_length_(0), content_length_field_(0), 
      content_type_field_(0), content_encoding_field_(0), field_(0) {
    }
    virtual ~fieldst() {
    }

    /// ...set
    using extends::set;
    virtual derives& set(const fieldst& to) {
        clear_list();
        add(to);
        this->assign(to);
        return *this;
    }
    virtual bool is_set(const fieldst& to) {
        bool success = true;
        clear_list();
        add(to);
        success = combine();
        return success;
    }
    virtual bool is_setl(const field_t* f, ...) {
        bool success = true;
        va_list va;
        va_start(va, f);
        clear_list();
        addv(f, va);
        va_end(va);
        success = combine();
        return success;
    }
    virtual bool is_setv(const field_t* f, va_list va) {
        bool success = true;
        clear_list();
        addv(f, va);
        success = combine();
        return success;
    }
    virtual bool is_set(const field_t& f) {
        bool success = true;
        clear_list();
        add(f);
        success = combine();
        return success;
    }
    virtual bool is_set(const string_t& name, const string_t& value) {
        bool success = true;
        clear_list();
        add(name, value);
        success = combine();
        return success;
    }
    virtual bool is_set(const string_t& name_value) {
        bool success = true;
        clear_list();
        add(name_value);
        success = combine();
        return success;
    }

    /// read / write
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;
        const char_t* chars = 0;
        size_t length = 0;
        field_t* f = 0;

        this->set_defaults();
        do {
            if ((f = read_field(count, c, reader))) {
                if ((chars = f->has_chars(length))) {
                    list_.push_back(f);
                    on_add_field(*f);
                } else {
                    free_field(f);
                    success = true;
                    break;
                }
            }
        } while (f);
        return success;
    }
    virtual bool write(ssize_t& count, writer_t& writer) {
        bool success = true;
        const char_t* chars = 0;
        size_t length = 0;
        ssize_t amount = 0;
        field_t* f = 0;
        const_iterator_t i, end;

        for (count = 0, end = list_.end(), i = list_.begin(); i != end; ++i) {
            if ((f = (*i))) {
                if ((chars = f->has_chars(length))) {
                    if (length <= (amount = writer.write(chars, length))) {
                        count += amount;
                        if (2 <= (amount = writer.write("\r\n"))) {
                            count += amount;
                            continue;
                        }
                    }
                }
            }
            success = false;
            break;
        }
        if (success) {
            if (2 <= (amount = writer.write("\r\n"))) {
                count += amount;
            } else {
                success = false;
            }
        }
        return success;
    }

    /// combine / separate
    virtual bool combine() {
        bool success = true;
        const char_t* chars = 0;
        size_t length = 0;
        field_t* f = 0;
        const_iterator_t i, end;

        this->clear();
        for (end = list_.end(), i = list_.begin(); i != end; ++i) {
            if ((f = (*i))) {
                if ((chars = f->has_chars(length))) {
                    this->append(chars, length);
                    this->append("\r\n");
                    continue;
                }
            }
            success = false;
            break;
        }
        if ((success)) {
            this->append("\r\n");
        }
        return success;
    }
    virtual bool separate() {
        bool success = true;
        const char_t* chars = 0;
        size_t length = 0;

        this->set_defaults();
        if ((chars = this->has_chars(length))) {
            const char_t *end = chars + length, *first = chars, *last = 0;
            field_t* f = 0;
            char_t c = 0;

            for (; chars != end; ++chars) {
                if ('\r' != (c = *chars)) {
                    if ('\n' != (c)) {
                        last = chars;
                    } else {
                        if (last) {
                            if ((f = add_field(first, (last - first) + 1))) {
                                on_add_field(*f);
                                first = last + 3;
                                last = 0;
                            } else {
                                success = false;
                                break;
                            }
                        } else {
                            break;
                        }
                    }
                } else {
                }
            }
        }
        return success;
    }

    /// set_default...
    virtual derives& set_default() {
        this->clear();
        set_defaults();
        this->combine();
        return *this;
    }
    virtual derives& set_defaults() {
        clear_list();
        content_encoding_.set_default();
        content_type_.set_default();
        content_length_field_ = 0;
        content_type_field_ = 0;
        content_encoding_field_ = 0;
        content_length_ = 0;
        return *this;
    }

    /// add...
    virtual list_t& add(const fieldst& f) {
        add(f.list_);
        return list_;
    }
    virtual list_t& add(const list_t& list) {
        const field_t* f = 0;
        const_iterator_t e = list.end();
        for (const_iterator_t i = list.begin(); i != e; ++i) {
            if (f = *i) {
                add(*f);
            }
        }
        return list_;
    }
    virtual list_t& addl(const field_t* f, ...) {
        va_list va;
        va_start(va, f);
        addv(f, va);
        va_end(va);
        return list_;
    }
    virtual list_t& addv(const field_t* f, va_list va) {
        typedef const field_t* const_field_pointer_t;
        if (0 != (f)) {
            do {
                add(*f);
            } while (0 != (f = va_arg(va, const_field_pointer_t)));
        }
        return list_;
    }
    virtual field_t* add(const field_t& f) {
        return add(f.name(), f.value());
    }
    virtual field_t* add(const string_t& name, const string_t& value) {
        field_t* f = 0;
        if ((f = add_field(name, value))) {
            on_add_field(*f);
            return f;
        }
        return 0;
    }
    virtual field_t* add(const string_t& name_value) {
        field_t* f = 0;
        if ((f = add_field(name_value))) {
            on_add_field(*f);
            return f;
        }
        return 0;
    }

    /// on_add_field...
    virtual void on_add_field(const field_t& f) {
        const part_t &name = f.name();
        if (!(name.uncased_compare(content_length_name_chars()))) {
            on_add_field_content_length(f);
        } else {
            if (!(name.uncased_compare(content_type_name_chars()))) {
                on_add_field_content_type(f);
            } else {
                if (!(name.uncased_compare(content_encoding_name_chars()))) {
                    on_add_field_content_encoding(f);
                } else {
                }
            }
        }
    }
    virtual void on_add_field_content_length(const field_t& f) {
        size_t content_length = f.value().to_unsigned();
        if (0 < (content_length)) {
            content_length_field_ = &f;
            content_length_ = content_length;
        }
    }
    virtual void on_add_field_content_type(const field_t& f) {
        const char_t* chars = 0;
        size_t length = 0;
        if ((chars = f.value().has_chars(length))) {
            content_type_.set(chars, length);
            content_type_field_ = &f;
        }
    }
    virtual void on_add_field_content_encoding(const field_t& f) {
        const char_t* chars = 0;
        size_t length = 0;
        if ((chars = f.value().has_chars(length))) {
            content_encoding_.set(chars, length);
            content_encoding_field_ = &f;
        }
    }

    /// read... / add...
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
    virtual field_t* add_field(const string_t& name, const string_t& value) {
        const char_t *chars = 0;
        size_t length = 0;
        if ((chars = name.has_chars(length))) {
            field_t* f = 0;
            if ((f = get_field())) {
                f->set(name, value);
                list_.push_back(f);
                return f;
            }
        }
        return 0;
    }
    virtual field_t* add_field(const string_t& s) {
        const char_t *chars = 0;
        size_t length = 0;
        if ((chars = s.has_chars(length))) {
            return add_field(chars, length);
        }
        return 0;
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
    
    /// set_field_value
    virtual field_t* set_field_value(const field_t* of, const string_t& to) {
        if (of) {
            for (iterator_t end = list_.end(), i = list_.begin(); i != end; ++i) {
                field_t* f = *i;
                if (f == of) {
                    f->set_value(to);
                    return f;
                }
            }
        }
        return 0;
    }
    virtual field_t* set_field_value(const field_t* of, const size_t& value) {
        unsigned_to_string to(value);
        return set_field_value(of, to);
    }
    virtual field_t* set_field_value(const field_t* of, const char_t* chars) {
        string_t to(chars);
        return set_field_value(of, to);
    }

    /// get... / free... / clear...
    virtual field_t* get_field() {
        field_t* f = 0;
        if (!(f = field_)) {
            f = new field_t;
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
            if ((content_length_field_)) {
                delete content_length_field_;
                content_length_field_ = 0;
            }
            if ((content_type_field_)) {
                delete content_type_field_;
                content_type_field_ = 0;
            }
            if ((content_encoding_field_)) {
                delete content_encoding_field_;
                content_encoding_field_ = 0;
            }
            if ((field_)) {
                delete field_;
                field_ = 0;
            }
        }
    }
    virtual void clear_list() {
        for (field_t* f = 0; !list_.empty(); list_.pop_front()) {
            if ((f = list_.front())) {
                if ((f == content_length_field_)) {
                    content_length_field_ = 0;
                } else {
                    if ((f == content_type_field_)) {
                        content_type_field_ = 0;
                    } else {
                        if ((f == content_encoding_field_)) {
                            content_encoding_field_ = 0;
                        } else {
                        }
                    }
                }
                delete f;
            }
        }
    }

    /// ...content_length...
    virtual field_t* add_content_length_field(size_t len) {
        string_t name(content_length_name_chars());
        const char_t *chars = 0; size_t length = 0;
        if ((chars = name.has_chars(length))) {
            unsigned_to_string value(len);
            field_t* f = 0;
            if ((f = add_field(name, value))) {
                content_length_field_ = f;
                return f;
            }
        }
        return 0;
    }
    virtual const field* content_length_field() const {
        return content_length_field_;
    }
    virtual size_t set_content_length(size_t to) {
        const field* f = 0;
        if (!(f = set_field_value(content_length_field_, to))) {
            f = add_content_length_field(to);
        }
        content_length_ = to;
        combine();
        return content_length_;
    }
    virtual size_t clear_content_length() {
        content_length_ = 0;
        return content_length_;
    }
    virtual size_t content_length() const {
        return content_length_;
    }

    /// ...content_type...
    virtual field_t* add_content_type_field(const string_t& value) {
        string_t name(content_type_name_chars());
        const char_t *chars = 0; size_t length = 0;
        if ((chars = name.has_chars(length))) {
            field_t* f = 0;
            if ((f = add_field(name, value))) {
                content_type_field_ = f;
                return f;
            }
        }
        return 0;
    }
    virtual field_t* add_content_type_field(const char_t* chars) {
        string_t value(chars);
        return add_content_type_field(value);
    }
    virtual const field* content_type_field() const {
        return content_type_field_;
    }
    virtual part& set_content_type(const string_t& to) {
        const field* f = 0;
        if (!(f = set_field_value(content_type_field_, to))) {
            f = add_content_type_field(to);
        }
        content_type_.set(to);
        combine();
        return content_type_;
    }
    virtual part& set_content_type(const char_t* chars) {
        string_t to(chars);
        return set_content_type(to);
    }
    virtual const part& content_type() const {
        return content_type_;
    }

    /// ...content_encoding...
    virtual const field* content_encoding_field() const {
        return content_encoding_field_;
    }
    virtual const part& content_encoding() const {
        return content_encoding_;
    }

    /// content_..._name_chars
    virtual const char_t* content_length_name_chars() const {
        return "Content-Length";
    }
    virtual const char_t* content_type_name_chars() const {
        return "Content-Type";
    }
    virtual const char_t* content_encoding_name_chars() const {
        return "Content-Encoding";
    }

    /// first / next / prev
    virtual const field_t* first(const_iterator_t& at) const {
        if ((at = list_.begin()) != list_.end()) {
            const field_t* f = (*at);
            return f;
        }
        return 0;
    }
    virtual const field_t* next(const_iterator_t& at) const {
        if ((at != list_.end())) {
            if ((++at != list_.end())) {
                const field_t* f = (*at);
                return f;
            }
        }
        return 0;
    }
    virtual const field_t* prev(const_iterator_t& at) const {
        if ((at != list_.begin())) {
            const field_t* f = (*--at);
            return f;
        }
        return 0;
    }

protected:
    size_t content_length_;
    const field_t *content_length_field_, *content_type_field_, *content_encoding_field_;
    field_t *field_;
    list_t list_;
    part_t content_type_, content_encoding_;
}; /// class fieldst
typedef fieldst<> fields;
} /// namespace extened

/// class fieldst
template 
<class TExtends = extended::fields, class TImplements = typename TExtends::implements>
class exported fieldst: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef fieldst derives;

    typedef typename extends::field_t field_t;
    typedef typename extends::list_t list_t;
    typedef typename list_t::const_iterator const_iterator_t;
    typedef typename extends::part_t part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    fieldst(const field_t* f, ...) {
        va_list va;
        va_start(va, f);
        this->is_setv(f, va);
        va_end(va);
    }
    fieldst(const field_t* f, va_list va): extends(f, va) {
        this->is_setv(f, va);
    }
    fieldst(const field_t& f): extends(f) {
        this->is_set(f);
    }
    fieldst(const string_t& chars): extends(chars) {
        this->separate();
    }
    fieldst(const char_t* chars, size_t length): extends(chars, length) {
        this->separate();
    }
    fieldst(const char_t* chars): extends(chars) {
        this->separate();
    }
    fieldst(const fieldst& copy): extends(copy) {
        this->separate();
    }
    fieldst() {
        this->set_default();
    }
    virtual ~fieldst() {
        this->clear_list();
        this->free_field();
    }
}; /// class fieldst
typedef fieldst<> fields;

} /// namespace header
} /// namespace message
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_MESSAGE_HEADER_FIELDS_HPP 
