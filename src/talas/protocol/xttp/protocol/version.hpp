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
///   File: version.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_XTTP_PROTOCOL_VERSION_HPP
#define TALAS_PROTOCOL_XTTP_PROTOCOL_VERSION_HPP

#include "talas/protocol/xttp/message/part.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace protocol {

namespace extended {
/// class versiont
template <class TExtends = message::part, class TImplements = typename TExtends::implements>
class exported versiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef versiont derives;

    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    versiont(const string_t& major, const string_t& minor): major_(major), minor_(minor) {
    }
    versiont(const char_t* major, const char_t* minor): major_(major), minor_(minor) {
    }
    versiont(const string_t& chars): extends(chars) {
    }
    versiont(const char_t* chars, size_t length): extends(chars, length) {
    }
    versiont(const char_t* chars): extends(chars) {
    }
    versiont(const versiont& copy): extends(copy), major_(copy.major_), minor_(copy.minor_) {
    }
    versiont() {
    }
    virtual ~versiont() {
    }

    /// read / write
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;
        ssize_t amount = 0;
        string_t chars;
        
        set_default();
        do {
            if (0 < (amount = reader.read(&c, 1))) {
                count += amount;
                if ((' ' != c) && ('\r' != c) && ('\n' != c)) {
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
    virtual bool write(ssize_t& count, writer_t& writer) {
        bool success = false;
        const char_t* chars = 0;
        size_t length = 0;
        
        if ((chars = this->has_chars(length)) && (3 <= (length))) {
            ssize_t amount = 0;

            if (3 <= (amount = writer.write(chars, length))) {
                count = amount;
                success = true;
            }
        }
        return success;
    }

    /// combine / separate
    virtual bool combine() {
        bool success = false;
        const char_t *major = 0, *minor = 0;

        this->clear();
        if ((major = major_.has_chars()) && (minor = minor_.has_chars())) {
            this->assign(major);
            this->append(".");
            this->append(minor);
            success = true;
        }
        return success;
    }
    virtual bool separate() {
        bool success = false;
        const char_t* chars = 0;
        size_t length = 0;

        set_defaults();
        if ((chars = this->has_chars(length)) && (3 <= length)) {
            char_t c = 0;
            const char_t* end = chars + length;
            string_t *part = 0, major, minor;
            
            for (part = &major; chars != end; ++chars) {
                if ('.' != (c = *chars)) {
                    if (('0' <= c) && ('9' >= c)) {
                        // '0'..'9'
                        part->append(&c, 1);
                    } else {
                        // not '0'..'9'
                        return false;
                    }
                } else {
                    if (part != &minor) {
                        if (major.has_chars()) {
                            // ?'.'
                            part = &minor;
                        } else {
                            // '.'
                            return false;
                        }
                    } else {
                        // ?'.'*'.'
                        return false;
                    }
                }
            }
            if ((major.has_chars()) && (minor.has_chars())) {
                // ?'.'?
                major_.assign(major);
                minor_.assign(minor);
                success = true;
            }
        }
        return success;
    }

    /// set
    using extends::set;
    virtual derives& set(const versiont& to) {
        major_.set(to.major_);
        minor_.set(to.minor_);
        this->assign(to);
        return *this;
    }

    /// set_default...
    virtual derives& set_default() {
        this->clear();
        set_defaults();
        combine();
        return *this;
    }
    virtual derives& set_defaults() {
        major_.assign(default_major_chars());
        minor_.assign(default_minor_chars());
        return *this;
    }

    /// ...major
    virtual part_t& set_major(const string_t& to) {
        major_.assign(to);
        combine();
        return major_;
    }
    virtual part_t& set_major(const char_t* to, size_t length) {
        major_.assign(to, length);
        combine();
        return major_;
    }
    virtual part_t& set_major(const char_t* to) {
        major_.assign(to);
        combine();
        return major_;
    }
    virtual part_t& set_major(char_t to) {
        major_.assign(&to, 1);
        combine();
        return major_;
    }
    virtual const part_t& major() const {
        return major_;
    }

    /// ...minor
    virtual part_t& set_minor(const string_t& to) {
        minor_.assign(to);
        combine();
        return minor_;
    }
    virtual part_t& set_minor(const char_t* to, size_t length) {
        minor_.assign(to, length);
        combine();
        return minor_;
    }
    virtual part_t& set_minor(const char_t* to) {
        minor_.assign(to);
        combine();
        return minor_;
    }
    virtual part_t& set_minor(char_t to) {
        minor_.assign(&to, 1);
        combine();
        return minor_;
    }
    virtual const part_t& minor() const {
        return minor_;
    }

    /// ...major_chars / ...minor_chars
    virtual const char_t* default_major_chars() const {
        return "1";
    }
    virtual const char_t* default_minor_chars() const {
        return "0";
    }

protected:
    part_t major_, minor_;
}; /// class versiont
typedef versiont<> version;
} /// namespace extended

/// class versiont
template <class TExtends = extended::version, class TImplements = typename TExtends::implements>
class exported versiont: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef versiont derives;

    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    versiont(const string_t& major, const string_t& minor): extends(major, minor) {
        this->combine();
    }
    versiont(const char_t* major, const char_t* minor): extends(major, minor) {
        this->combine();
    }
    versiont(const string_t& chars): extends(chars) {
        this->separate();
    }
    versiont(const char_t* chars, size_t length): extends(chars, length) {
        this->separate();
    }
    versiont(const char_t* chars): extends(chars) {
        this->separate();
    }
    versiont(const versiont& copy): extends(copy) {
    }
    versiont() {
        this->set_default();
    }
    virtual ~versiont() {
    }
}; /// class versiont
typedef versiont<> version;

} /// namespace protocol
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_PROTOCOL_VERSION_HPP 
