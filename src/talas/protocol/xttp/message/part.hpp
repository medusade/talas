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
///   File: part.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_XTTP_MESSAGE_PART_HPP
#define TALAS_PROTOCOL_XTTP_MESSAGE_PART_HPP

#include "talas/base/string.hpp"
#include "talas/io/reader.hpp"
#include "talas/io/writer.hpp"
#include "talas/io/logger.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace message {

/// class partt
template <class TExtends = string_t, class TImplements = typename TExtends::Implements>
class exported partt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef partt derives;
    
    typedef TExtends string_t;
    typedef typename string_t::char_t char_t;
    typedef io::readert<char_t> reader_t;
    typedef io::writert<char_t> writer_t;

    /// constructor / destructor
    partt(const string_t& chars): extends(chars), is_combined_(true) {
    }
    partt(const char_t* chars, size_t length): extends(chars, length), is_combined_(true) {
    }
    partt(const char_t* chars): extends(chars), is_combined_(true) {
    }
    partt(const partt& copy): extends(copy), is_combined_(copy.is_combined_) {
    }
    partt(): is_combined_(true) {
    }
    virtual ~partt() {
    }

    /// read / write
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;
        return success;
    }
    virtual bool write(ssize_t& count, writer_t& writer) {
        bool success = false;
        return success;
    }

    /// read_line / read_this / write_this
    virtual bool read_line(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;
        char_t cr = 0;
        ssize_t amount = 0;
        string_t chars;

        this->set_default();
        do {
            if (0 < (amount = reader.read(&c, 1))) {
                count += amount;
                if (('\r' != c)) {
                    if (('\n' != c)) {
                        chars.append(&c, 1);
                    } else {
                        success = this->is_set(chars);
                        break;
                    }
                } else {
                    if (cr != c) {
                        cr = c;
                    } else {
                        chars.append(&cr, 1);
                    }
                }
            } else {
                count = amount;
                break;
            }
        } while (0 < amount);
        return success;
    }
    virtual bool read_this(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;
        ssize_t amount = 0;
        string_t chars;
        
        set_default();
        do {
            if (0 < (amount = reader.read(&c, 1))) {
                count += amount;
                if (('\r' != c) && ('\n' != c)) {
                    chars.append(&c, 1);
                } else {
                    break;
                }
            } else {
                count = amount;
                return false;
            }
        } while (0 < amount);
        if ((chars.has_chars())) {
            this->assign(chars);
            success = separate();
        }
        return success;
    }
    virtual bool write_this(ssize_t& count, writer_t& writer) {
        bool success = false;
        const char_t* chars = 0;
        size_t length = 0;
        
        if ((chars = this->has_chars(length))) {
            ssize_t amount = 0;

            if (length <= (amount = writer.write(chars, length))) {
                count = amount;
                success = true;
            }
        }
        return success;
    }

    /// clear / ...set
    virtual derives& clear() {
        extends::clear();
        return *this;
    }
    virtual derives& set(const partt& to) {
        this->assign(to);
        return *this;
    }
    virtual derives& set(const string_t& to) {
        this->assign(to);
        separate();
        return *this;
    }
    virtual derives& set(const char_t* to, size_t length) {
        this->assign(to, length);
        separate();
        return *this;
    }
    virtual derives& set(const char_t* to) {
        this->assign(to);
        separate();
        return *this;
    }
    virtual bool is_set(const string_t& to) {
        bool success = false;
        this->assign(to);
        success = separate();
        return success;
    }
    virtual bool is_set(const char_t* to, size_t length) {
        bool success = false;
        this->assign(to, length);
        success = separate();
        return success;
    }
    virtual bool is_set(const char_t* to) {
        bool success = false;
        this->assign(to);
        success = separate();
        return success;
    }

    /// combine / separate
    virtual bool combine() {
        bool success = true;
        return success;
    }
    virtual bool separate() {
        bool success = true;
        return success;
    }

    /// set_default...
    virtual derives& set_default() {
        this->clear();
        set_defaults();
        return *this;
    }
    virtual derives& set_defaults() {
        return *this;
    }

    /// ...is_equal
    virtual bool is_equal(const string_t& to) const {
        int unequal = compare(*this, to, compare);
        return !unequal;
    }
    virtual bool uncased_is_equal(const string_t& to) const {
        int unequal = compare(*this, to, uncased_compare);
        return !unequal;
    }

    /// ...compare
    virtual int compare(const string_t& to) const {
        int unequal = compare(*this, to, compare);
        return unequal;
    }
    virtual int uncased_compare(const string_t& to) const {
        int unequal = compare(*this, to, uncased_compare);
        return unequal;
    }
    static int compare(const string_t& s, const string_t& to, int compare(const char_t& c, const char_t& c2)) {
        int unequal = 0, compared = 0;
        const char_t *chars = 0, *to_chars = 0, *end = 0;
        size_t length = 0, to_length = 0;

        if ((chars = s.has_chars(length))) {
            if ((to_chars = to.has_chars(to_length))) {
                if (((end = (chars + length)) - chars) > to_length) {
                    end = (chars + to_length);
                    unequal = 1;
                } else {
                    if (to_length > length) {
                        unequal = -1;
                    }
                }
                for (; chars != end; ++chars, ++to_chars) {
                    if ((compared = compare(*chars, *to_chars))) {
                        return compared;
                    }
                }
            } else {
                unequal = 1;
            }
        } else {
            if ((to_chars = to.has_chars(to_length))) {
                unequal = -1;
            }
        }
        return unequal;
    }
    static int compare(const char_t& c, const char_t& c2) {
        if (c > c2) { return 1; } else {
            if (c < c2) { return -1; }
        }
        return 0;
    }
    static int uncased_compare(const char_t& c, const char_t& c2) {
        return compare(tolower(c), tolower(c2));
    }
    
    /// ...is_combined
    virtual bool set_is_combined(bool to = true) {
        is_combined_ = to;
        return is_combined_;
    }
    virtual bool is_combined() const {
        return is_combined_;
    }

    /// ...is_logged
    virtual bool set_is_logged(bool to = true) {
        return logged_.set_is_logging(to);
    }
    virtual bool is_logged() const {
        return logged_.is_logging();
    }

    /// ...is_logging
    virtual bool set_is_logging(bool to = true) {
        return logged_.set_is_logging(to);
    }
    virtual bool is_logging() const {
        return logged_.is_logging();
    }

protected:
    bool is_combined_;
    logged logged_;
}; /// class partt
typedef partt<> part;

} /// namespace message
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_MESSAGE_PART_HPP 
