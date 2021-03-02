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
///   File: identifier.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_XTTP_PROTOCOL_IDENTIFIER_HPP
#define TALAS_PROTOCOL_XTTP_PROTOCOL_IDENTIFIER_HPP

#include "talas/protocol/xttp/message/part.hpp"
#include "talas/protocol/xttp/protocol/name.hpp"
#include "talas/protocol/xttp/protocol/version.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace protocol {

namespace extended {
/// class identifiert
template 
<class TName = protocol::name, class TVersion = protocol::version,
 class TExtends = message::part, class TImplements = typename TExtends::implements>
class exported identifiert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef identifiert derives;

    typedef TName name_t;
    typedef TVersion version_t;
    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    identifiert(const name_t& name, const version_t& version): name_(name), version_(version)  {
    }
    identifiert(const string_t& name, const string_t& version): name_(name), version_(version)  {
    }
    identifiert(const char_t* name, const char_t* version): name_(name), version_(version)  {
    }
    identifiert(const string_t& chars): extends(chars)  {
    }
    identifiert(const char_t* chars, size_t length): extends(chars, length)  {
    }
    identifiert(const char_t* chars): extends(chars)  {
    }
    identifiert(const identifiert& copy)
    : extends(copy), name_(copy.name_), version_(copy.version_) {
    }
    identifiert() {
    }
    virtual ~identifiert() {
    }

    /// read / write
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;

        set_default();
        if ((name_.read(count, c, reader))) {
            if ('/' == (c)) {
                if ((version_.read(count, c, reader))) {
                    success = combine();
                }
            }
        }
        return success;
    }
    virtual bool write(ssize_t& count, writer_t& writer) {
        bool success = this->write_this(count, writer);
        return success;
    }

    /// combine / separate
    virtual bool combine() {
        bool success = false;
        const char_t *name = 0, *version = 0;

        this->clear();
        if ((name = name_.has_chars())
            && (version = version_.has_chars())) {
            this->assign(name);
            this->append("/");
            this->append(version);
            return true;
        }
        return success;
    }
    virtual bool separate() {
        bool success = false;
        const char_t* chars = 0;
        size_t length = 0;

        set_defaults();
        if ((chars = this->has_chars(length))) {
            char_t c = 0;
            const char_t* end = chars + length;
            string_t *part = 0, name, version;

            for (part = &name; chars != end; ++chars) {
                if ('/' != (c = *chars)) {
                    part->append(&c, 1);
                } else {
                    if (part != &version) {
                        if (name.has_chars()) {
                            // ?'/'
                            part = &version;
                        } else {
                            // '/'
                            return false;
                        }
                    } else {
                        // ?'/'*'/'
                        return false;
                    }
                }
            }
            if ((name.has_chars()) && (version.has_chars())) {
                // ?'/'?
                name_.set(name);
                version_.set(version);
                success = true;
            }
        }
        return success;
    }

    /// set
    using extends::set;
    virtual derives& set(const identifiert& to) {
        name_.set(to.name_);
        version_.set(to.version_);
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
        name_.set_default();
        version_.set_default();
        return *this;
    }

protected:
    name_t name_;
    version_t version_;
}; /// class identifiert
typedef identifiert<> identifier;
} /// namespace extended

/// class identifiert
template 
<class TExtends = xttp::protocol::extended::identifier, 
 class TImplements = typename TExtends::implements>
class exported identifiert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef identifiert derives;

    typedef typename extends::name_t name_t;
    typedef typename extends::version_t version_t;
    typedef typename extends::part_t part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    identifiert(const name_t& name, const version_t& version): extends(name, version)  {
        this->combine();
    }
    identifiert(const string_t& name, const string_t& version): extends(name, version)  {
        this->combine();
    }
    identifiert(const char_t* name, const char_t* version): extends(name, version)  {
        this->combine();
    }
    identifiert(const string_t& chars): extends(chars)  {
        this->separate();
    }
    identifiert(const char_t* chars, size_t length): extends(chars, length)  {
        this->separate();
    }
    identifiert(const char_t* chars): extends(chars)  {
        this->separate();
    }
    identifiert(const identifiert& copy): extends(copy) {
    }
    identifiert() {
        this->set_default();
    }
    virtual ~identifiert() {
    }
}; /// class identifiert
typedef identifiert<> identifier;

} /// namespace protocol
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_PROTOCOL_IDENTIFIER_HPP 
