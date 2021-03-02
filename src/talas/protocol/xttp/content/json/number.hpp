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
///   File: number.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_XTTP_CONTENT_JSON_NUMBER_HPP
#define TALAS_PROTOCOL_XTTP_CONTENT_JSON_NUMBER_HPP

#include "talas/protocol/xttp/content/json/node_type.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace content {
namespace json {

/// class numbert
template <class TExtends = message::part, class TImplements = typename TExtends::implements>
class exported numbert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef numbert derives;
    
    typedef int is_t;
    enum { is_double, is_signed, is_unsigned };
    typedef extends part_t;
    typedef typename extends::sstream_t sstream_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    numbert(const string_t& chars): extends(chars), is_(is_double) {
        this->separate();
    }
    numbert(const char_t* chars, size_t length): extends(chars, length), is_(is_double) {
        this->separate();
    }
    numbert(const char_t* chars): extends(chars), is_(is_double) {
        this->separate();
    }
    numbert(const double& is): is_(is_double) {
        set(is);
    }
    numbert(const signed& is): is_(is_double) {
        set(is);
    }
    numbert(const unsigned& is): is_(is_double) {
        set(is);
    }
    numbert(const numbert& copy): extends(copy), is_(copy.is_) {
    }
    numbert(): is_(is_double) {
        this->set_default();
    }
    virtual ~numbert() {
    }

    /// set
    virtual double set(const double& to) {
        set_is(to);
        combine();
        return double_;
    }
    virtual signed set(const signed& to) {
        set_is(to);
        combine();
        return signed_;
    }
    virtual unsigned set(const unsigned& to) {
        set_is(to);
        combine();
        return unsigned_;
    }

    /// read / write
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;
        // success = this->read_this(count, c, reader);
        return success;
    }
    virtual bool write(ssize_t& count, writer_t& writer) {
        bool success = this->write_this(count, writer);
        return success;
    }

    /// combine / separate
    virtual bool combine() {
        bool success = true;
        switch (is_) {
        case is_signed:
            this->assign(signed_to_string(signed_));
            break;
        case is_unsigned:
            this->assign(unsigned_to_string(unsigned_));
            break;
        case is_double:
        default:
            this->assign(double_to_string(double_));
            break;
        }
        return success;
    }
    virtual bool separate() {
        sstream_t ss(*this);
        bool success = true;
        switch (is_) {
        case is_signed:
            ss >> signed_;
            set_is(signed_);
            break;
        case is_unsigned:
            ss >> unsigned_;
            set_is(unsigned_);
            break;
        case is_double:
        default:
            ss >> double_;
            set_is(double_);
            break;
        }
        return success;
    }

    /// set_default...
    virtual derives& set_default() {
        this->clear();
        set_defaults();
        return *this;
    }
    virtual derives& set_defaults() {
        is_ = is_double;
        double_ = 0;
        signed_ = 0;
        unsigned_ = 0;
        return *this;
    }

    /// ...is
    virtual is_t set_is(const double& d) {
        is_ = is_double;
        if (&d != &double_) double_ = d;
        signed_ = (signed)d;
        unsigned_ = (unsigned)d;
        return is_;
    }
    virtual is_t set_is(const signed& s) {
        is_ = is_signed;
        double_ = (double)s;
        if (&s != &signed_) signed_ = s;
        unsigned_ = (unsigned)s;
        return is_;
    }
    virtual is_t set_is(const unsigned& u) {
        is_ = is_unsigned;
        double_ = (double)u;
        signed_ = (signed)u;
        if (&u != &unsigned_) unsigned_ = u;
        return is_;
    }
    virtual is_t is(double& d, signed& s, unsigned& u) const {
        d = double_;
        s = signed_;
        u = unsigned_;
        return is_;
    }

protected:
    is_t is_;
    double double_;
    signed signed_;
    unsigned unsigned_;
}; /// class numbert
typedef numbert<> number;

} /// namespace json
} /// namespace content
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_CONTENT_JSON_NUMBER_HPP 
