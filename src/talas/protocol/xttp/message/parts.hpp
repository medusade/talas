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
///   File: parts.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_XTTP_MESSAGE_PARTS_HPP
#define TALAS_PROTOCOL_XTTP_MESSAGE_PARTS_HPP

#include "talas/protocol/xttp/message/part.hpp"
#include "talas/protocol/xttp/message/line.hpp"
#include "talas/protocol/xttp/message/header/fields.hpp"
#include "talas/protocol/xttp/message/body/content.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace message {

namespace extended {
/// class partst
template 
<class TLine = message::line, class TFields = header::fields, class TContent = body::content,
 class TExtends = message::part, class TImplements = typename TExtends::implements>
class exported partst: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef partst derives;

    typedef TLine line_t;
    typedef TFields headers_t;
    typedef typename headers_t::field_t field_t;
    typedef TContent content_t;
    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    partst(const partst& copy, const content_t& content): extends(copy), content_(&content) {
    }
    partst(const partst& copy, const content_t* content): extends(copy), content_(content) {
    }
    partst(const line_t& line, const headers_t& headers, const content_t& content): line_(line), headers_(headers), content_(&content) {
    }
    partst(const line_t& line, const headers_t& headers, const content_t* content): line_(line), headers_(headers), content_(content) {
    }
    partst(const line_t& line, const headers_t& headers): line_(line), headers_(headers), content_(0) {
    }
    partst(const string_t& chars): extends(chars), content_(0) {
    }
    partst(const char_t* chars, size_t length): extends(chars, length), content_(0) {
    }
    partst(const char_t* chars): extends(chars), content_(0) {
    }
    partst(const partst& copy): extends(copy), content_(copy.content_) {
    }
    partst(): content_(0) {
    }
    virtual ~partst() {
    }

    /// set
    using extends::set;
    virtual derives& set(const line_t& line, const headers_t& headers, const content_t& content) {
        set_line(line);
        set_headers(headers);
        set_content(content);
        return *this;
    }

    /// read... / write...
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;
        ssize_t amount = 0;

        set_default();
        if ((line_.read(amount, c, reader))) {
            count = amount;
            if ((headers_.read(amount, c, reader))) {
                count += amount;
                if ((combine())) {
                    success = true;
                }
            }
        }
        return success;
    }
    virtual bool read_with_content(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;
        ssize_t amount = 0;
        if ((read(count, c, reader))) {
            if ((read_content(amount, c, reader))) {
                count += amount;
                return true;
            }
        }
        return success;
    }
    virtual bool read_content(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = true;
        size_t content_length = 0;
        if (0 < (content_length = headers_.content_length())) {
            if ((success = this_content_.read(count, c, reader, content_length))) {
                content_ = &this_content_;
            }
        }
        return success;
    }
    virtual bool write(ssize_t& count, writer_t& writer) {
        bool success = false;
        const char_t* chars = 0;
        size_t length = 0;
        
        if ((chars = this->has_chars(length))) {
            ssize_t amount = 0;

            if (length <= (amount = writer.write(chars, length))) {
                count = amount;
                
                if ((content_)) {
                    if ((content_->write(amount, writer))) {
                        count += amount;
                        success = true;
                    }
                } else {
                    success = true;
                }
            }
        }
        return success;
    }

    /// combine / separate
    virtual bool combine() {
        bool success = false;
        const char_t* chars = 0;

        if ((chars = line_.has_chars())) {
            const field_t* h = 0;
            typename headers_t::const_iterator_t i;

            this->assignl(chars, "\r\n", NULL);
            if ((h = headers_.first(i))) {
                do {
                    if ((chars = h->has_chars())) {
                        this->appendl(chars, "\r\n", NULL);
                    }
                } while ((h = headers_.next(i)));
            }
            this->appendl("\r\n", NULL);
            return true;
        }
        this->clear();
        return success;
    }
    virtual bool separate() {
        bool success = false;
        const char_t* chars = 0;
        size_t length = 0;

        set_defaults();
        if ((chars = this->has_chars(length))) {
            const char_t *end = chars + length, *first = chars, *last = 0;
            field_t* field = 0;
            char_t c = 0;

            for (bool line = false; chars != end; ++chars) {
                if ('\r' != (c = *chars)) {
                    if ('\n' != (c)) {
                        last = chars;
                    } else {
                        if (last) {
                            if (line) {
                                if ((field = headers_.add_field(first, length = ((last - first) + 1)))) {
                                    headers_.on_add_field(*field);
                                    first += length + 2;
                                    last = 0;
                                } else {
                                    set_defaults();
                                    return false;
                                }
                            } else {
                                if ((line = line_.is_set(first, length = ((last - first) + 1)))) {
                                    first += length + 2;
                                    last = 0;
                                    success = true;
                                } else {
                                    set_defaults();
                                    return false;
                                }
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
        combine();
        return *this;
    }
    virtual derives& set_defaults() {
        line_.set_default();
        headers_.set_default();
        return *this;
    }

    /// line / headers / content
    virtual line_t& set_line(const line_t& to) {
        line_.set(to);
        combine();
        return line_;
    }
    virtual const line_t& line() const {
        return line_;
    }
    virtual headers_t& set_headers(const headers_t& to) {
        headers_.set(to);
        combine();
        return headers_;
    }
    virtual const headers_t& headers() const {
        return headers_;
    }
    virtual const content_t* content() const {
        return content_;
    }
    virtual const content_t* set_content(const string_t& to) {
        content_ = &this_content_;
        this_content_.assign(to);
        this->combine();
        return content_;
    }
    virtual part_t set_content_type(const string_t& to) {
        part_t content_type(headers_.set_content_type(to));
        this->combine();
        return content_type;
    }
    virtual size_t set_content_length(size_t to) {
        size_t content_length = headers_.set_content_length(to);
        this->combine();
        return content_length;
    }
    virtual size_t content_length() const {
        return headers_.content_length();
    }
    virtual const char_t* content_chars() const {
        const char_t* chars = 0;
        if (content_) {
            chars = content_->has_chars();
        }
        return chars;
    }
    virtual const char_t* content_chars(size_t& length) const {
        const char_t* chars = 0;
        if (content_) {
            chars = content_->has_chars(length);
        }
        return chars;
    }

protected:
    line_t line_;
    headers_t headers_;
    const content_t* content_;
    content_t this_content_;
}; /// class partst
typedef partst<> parts;
} /// namespace extended

/// class partst
template 
<class TLine = message::line,
 class TExtends = extended::partst<TLine>, class TImplements = typename TExtends::implements>
class exported partst: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef partst derives;

    typedef typename extends::line_t line_t;
    typedef typename extends::headers_t headers_t;
    typedef typename extends::field_t field_t;
    typedef typename extends::content_t content_t;
    typedef typename extends::part_t part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    partst(const partst& copy, const content_t& content): extends(copy, content) {
    }
    partst(const partst& copy, const content_t* content): extends(copy, content) {
    }
    partst(const line_t& line, const headers_t& headers, const content_t& content): extends(line, headers, content) {
        this->combine();
    }
    partst(const line_t& line, const headers_t& headers, const content_t* content): extends(line, headers, content) {
        this->combine();
    }
    partst(const line_t& line, const headers_t& headers): extends(line, headers) {
        this->combine();
    }
    partst(const string_t& chars): extends(chars) {
        this->separate();
    }
    partst(const char_t* chars, size_t length): extends(chars, length) {
        this->separate();
    }
    partst(const char_t* chars): extends(chars) {
        this->separate();
    }
    partst(const partst& copy): extends(copy) {
    }
    partst() {
        this->set_default();
    }
    virtual ~partst() {
    }
}; /// class partst
typedef partst<> parts;

} /// namespace message
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_MESSAGE_PARTS_HPP 
