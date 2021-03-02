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
#ifndef TALAS_PROTOCOL_XTTP_REQUEST_LINE_HPP
#define TALAS_PROTOCOL_XTTP_REQUEST_LINE_HPP

#include "talas/protocol/xttp/message/part.hpp"
#include "talas/protocol/xttp/message/line.hpp"
#include "talas/protocol/xttp/protocol/identifier.hpp"
#include "talas/protocol/xttp/request/method.hpp"
#include "talas/protocol/xttp/request/parameters.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace request {

namespace extended {
/// class linet
template 
<class TMethod = request::method, 
 class TParameters = request::parameters, class TProtocol = protocol::identifier,
 class TExtends = message::line, class TImplements = typename TExtends::implements>

class exported linet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef linet derives;

    typedef TMethod method_t;
    typedef TParameters parameters_t;
    typedef TProtocol protocol_t;
    typedef extends line_t;
    typedef message::line::part_t part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    linet(const method_t& method, const parameters_t& parameters, const protocol_t& protocol)
    : method_(method), parameters_(parameters), protocol_(protocol) {
    }
    linet(const string_t& method, const string_t& parameters, const string_t& protocol)
    : method_(method), parameters_(parameters), protocol_(protocol) {
    }
    linet(const char_t* method, const char_t* parameters, const char_t* protocol)
    : method_(method), parameters_(parameters), protocol_(protocol) {
    }
    linet(const string_t &copy): extends(copy) {
    }
    linet(const char_t* chars, size_t length): extends(chars, length) {
    }
    linet(const char_t* chars): extends(chars) {
    }
    linet(const linet& copy)
    : extends(copy), method_(copy.method_), parameters_(copy.parameters_), protocol_(copy.protocol_) {
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
        const char_t *method = 0, *parameters = 0, *protocol = 0;
        if ((method = method_.has_chars())
            && (parameters = parameters_.has_chars())
            && (protocol = protocol_.has_chars())) {
            this->assignl(method, " ", parameters, " ", protocol, NULL);
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
            string_t *part = 0, method, parameters, protocol;

            for (part = &method; chars != end; ++chars) {
                if (' ' != (c = *chars)) {
                    part->append(&c, 1);
                } else {
                    if (part == &method) {
                        if (method.has_chars()) {
                            // ?' '
                            part = &parameters;
                        } else {
                            // ' '
                            return false;
                        }
                    } else {
                        if (part != &protocol) {
                            if (parameters.has_chars()) {
                                // ?' '?' '
                                part = &protocol;
                            } else {
                                // ?' '' '
                                return false;
                            }
                        } else {
                            // ?' '?'/'*' '
                            return false;
                        }
                    }
                }
            }
            if ((method.has_chars())
                && (parameters.has_chars())
                && (protocol.has_chars())) {
                method_.set(method);
                parameters_.set(parameters);
                protocol_.set(protocol);
                success = true;
            }
        }
        return success;
    }

    /// set
    using extends::set;
    virtual derives& set(const linet& to) {
        method_.set(to.method_);
        parameters_.set(to.parameters_);
        protocol_.set(to.protocol_);
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
        method_.set_default();
        parameters_.set_default();
        protocol_.set_default();
        return *this;
    }

    /// ...method
    virtual method_t& set_method(const method_t& to) {
        method_.set(to);
        combine();
        return method_;
    }
    virtual const method_t& method() const {
        return method_;
    }

    /// ...parameters
    virtual parameters_t& set_parameters(const string_t& to) {
        parameters_.set(to);
        combine();
        return parameters_;
    }
    virtual const parameters_t& parameters() const {
        return parameters_;
    }

protected:
    method_t method_;
    parameters_t parameters_;
    protocol_t protocol_;
}; /// class linet
typedef linet<> line;
} /// namespace extended

/// class linet
template <class TExtends = extended::line, class TImplements = typename TExtends::implements>
class exported linet: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef linet derives;

    typedef typename extends::method_t method_t;
    typedef typename extends::parameters_t parameters_t;
    typedef typename extends::protocol_t protocol_t;
    typedef typename extends::line_t line_t;
    typedef typename extends::part_t part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    linet(const method_t& method, const parameters_t& parameters, const protocol_t& protocol)
    : extends(method, parameters, protocol) {
        this->combine();
    }
    linet(const string_t& method, const string_t& parameters, const string_t& protocol)
    : extends(method, parameters, protocol) {
        this->combine();
    }
    linet(const char_t* method, const char_t* parameters, const char_t* protocol)
    : extends(method, parameters, protocol) {
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

} /// namespace request
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_REQUEST_LINE_HPP 
