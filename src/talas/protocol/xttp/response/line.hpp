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
///   File: line.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_XTTP_RESPONSE_LINE_HPP
#define TALAS_PROTOCOL_XTTP_RESPONSE_LINE_HPP

#include "talas/protocol/xttp/message/part.hpp"
#include "talas/protocol/xttp/message/line.hpp"
#include "talas/protocol/xttp/protocol/identifier.hpp"
#include "talas/protocol/xttp/response/status.hpp"
#include "talas/protocol/xttp/response/reason.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace response {

namespace extended {
/// class linet
template 
<class TStatus = response::status, 
 class TReason = response::reason, class TProtocol = protocol::identifier, 
 class TExtends = message::line, class TImplements = typename TExtends::implements>
class exported linet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef linet derives;

    typedef TStatus status_t;
    typedef TReason reason_t;
    typedef TProtocol protocol_t;
    typedef extends line_t;
    typedef typename extends::part_t part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    linet(const protocol_t& protocol, const status_t& status, const reason_t& reason)
    : protocol_(protocol), status_(status), reason_(reason) {
    }
    linet(const string_t& protocol, const string_t& status, const string_t& reason)
    : protocol_(protocol), status_(status), reason_(reason) {
    }
    linet(const char_t* protocol, const char_t* status, const char_t* reason)
    : protocol_(protocol), status_(status), reason_(reason) {
    }
    linet(const string_t &copy): extends(copy) {
    }
    linet(const char_t* chars, size_t length): extends(chars, length) {
    }
    linet(const char_t* chars): extends(chars) {
    }
    linet(const linet& copy)
    : extends(copy), protocol_(copy.protocol_), status_(copy.status_), reason_(copy.reason_) {
    }
    linet() {
    }
    virtual ~linet() {
    }

    /// read / write
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = this->read_line(count, c, reader);
        return success;
    }
    virtual bool write(ssize_t& count, writer_t& writer) {
        bool success = this->write_this(count, writer);
        return success;
    }

    /// combine / separate
    virtual bool combine() {
        bool success = false;
        const char_t *status = 0, *reason = 0, *protocol = 0;
        if ((protocol = protocol_.has_chars()) 
            && (status = status_.has_chars()) && (reason = reason_.has_chars())) {
            this->assignl(protocol, " ", status, " ", reason, NULL);
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
            char_t c = 0;
            const char_t* end = chars + length;
            string_t *part = 0, protocol, status, reason;

            for (part = &protocol; chars != end; ++chars) {
                if (' ' != (c = *chars)) {
                    part->append(&c, 1);
                } else {
                    if (part == &protocol) {
                        if (protocol.has_chars()) {
                            // ?' '
                            part = &status;
                        } else {
                            // ' '
                            return false;
                        }
                    } else {
                        if (part != &reason) {
                            if (status.has_chars()) {
                                // ?' '?' '
                                part = &reason;
                            } else {
                                // ?' '' '
                                return false;
                            }
                        } else {
                            // ?' '?' '*' '
                            part->append(&c, 1);
                        }
                    }
                }
            }
            if ((protocol.has_chars()) 
                && (status.has_chars()) && (reason.has_chars())) {
                protocol_.set(protocol);
                status_.set(status);
                reason_.set(reason);
                success = true;
            }
        }
        return success;
    }

    /// set
    using extends::set;
    virtual derives& set(const linet& to) {
        protocol_.set(to.protocol_);
        status_.set(to.status_);
        reason_.set(to.reason_);
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
        protocol_.set_default();
        status_.set_default();
        reason_.set_default();
        return *this;
    }

    /// ...protocol
    virtual protocol_t& set_protocol(const protocol_t& to) {
        protocol_.set(to);
        combine();
        return protocol_;
    }
    virtual const protocol_t& protocol() const {
        return protocol_;
    }

    /// ...status
    virtual status_t& set_status(const status_t& to) {
        status_.set(to);
        combine();
        return status_;
    }
    virtual const status_t& status() const {
        return status_;
    }

    /// ...reason
    virtual reason_t& set_reason(const reason_t& to) {
        reason_.set(to);
        combine();
        return reason_;
    }
    virtual const reason_t& reason() const {
        return reason_;
    }

protected:
    protocol_t protocol_;
    status_t status_;
    reason_t reason_;
}; /// class linet
typedef linet<> line;
} /// namespace extended

/// class linet
template 
<class TExtends = extended::line, class TImplements = typename TExtends::implements>
class exported linet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef linet derives;

    typedef typename extends::status_t status_t;
    typedef typename extends::reason_t reason_t;
    typedef typename extends::protocol_t protocol_t;
    typedef typename extends::line_t line_t;
    typedef typename extends::part_t part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    linet(const protocol_t& protocol, const status_t& status, const reason_t& reason): extends(protocol, status, reason) {
        this->combine();
    }
    linet(const string_t& protocol, const string_t& status, const string_t& reason): extends(protocol, status, reason) {
        this->combine();
    }
    linet(const char_t* protocol, const char_t* status, const char_t* reason): extends(protocol, status, reason) {
        this->combine();
    }
    linet(const string_t &copy): extends(copy) {
        this->separate();
    }
    linet(const char_t* chars, size_t length): extends(chars, length) {
        this->separate();
    }
    linet(const char_t* chars): extends(chars) {
        this->separate();
    }
    linet(const linet& copy): extends(copy) {
    }
    linet() {
        this->set_default();
    }
    virtual ~linet() {
    }
}; /// class linet
typedef linet<> line;

} /// namespace response
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_RESPONSE_LINE_HPP 
