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
///   File: node.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_XTTP_CONTENT_JSON_NODE_HPP
#define TALAS_PROTOCOL_XTTP_CONTENT_JSON_NODE_HPP

#include "talas/protocol/xttp/content/json/node_type.hpp"
#include "talas/protocol/xttp/content/json/boolean.hpp"
#include "talas/protocol/xttp/content/json/number.hpp"
#include "talas/protocol/xttp/content/json/string.hpp"
#include <sstream>
#include <list>

namespace talas {
namespace protocol {
namespace xttp {
namespace content {
namespace json {

class exported node;
typedef ::std::list<node> nodes;
typedef message::part node_extends;
typedef node_extends::implements node_implements;

/// class node
class exported node: virtual public node_implements, public node_extends {
public:
    typedef node_implements implements;
    typedef node_extends extends;
    typedef node derives;
    
    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    node(const bool& copy): type_(boolean_node), boolean_(copy) {
        this->combine();
    }
    node(const signed& copy): type_(number_node), number_(copy) {
        this->combine();
    }
    node(const unsigned& copy): type_(number_node), number_(copy) {
        this->combine();
    }
    node(const double& copy): type_(number_node), number_(copy) {
        this->combine();
    }
    node(const string_t& name, const node& value): type_(named_node), string_(name) {
        nodes_.push_front(value);
        this->combine();
    }
    node(const char_t* name, const node& value): type_(named_node), string_(name) {
        nodes_.push_front(value);
        this->combine();
    }
    node(const string_t& chars): type_(string_node), string_(chars) {
        this->combine();
    }
    node(const char_t* chars): type_(string_node), string_(chars) {
        this->combine();
    }
protected:
    node(node_type type, const node* item, ...): type_(type) {
        va_list va;
        va_start(va, item);
        set(item, va);
        va_end(va);
    }
    node(node_type type, const node* item, va_list va): type_(type) {
        set(item, va);
    }
    node(node_type type): type_(type) {
    }
public:
    node(const node& copy)
    : extends(copy), type_(copy.type_), 
      boolean_(copy.boolean_), number_(copy.number_), string_(copy.string_), nodes_(copy.nodes_) {
    }
    node(): type_(null_node) {
        this->combine();
    }
    virtual ~node() {
    }

    /// set
    virtual derives& set(node_type type, const node* to, ...) {
        va_list va;
        va_start(va, to);
        set(type, to, va);
        va_end(va);
        return *this;
    }
    virtual derives& set(node_type type, const node* to, va_list va) {
        type_ = type;
        set(to, va);
        return *this;
    }
    virtual derives& set(node_type type, const node& to) {
        type_ = type;
        set(to);
        return *this;
    }
    virtual derives& set(const node* to, ...) {
        va_list va;
        va_start(va, to);
        set(to, va);
        va_end(va);
        return *this;
    }
    virtual derives& set(const node* to, va_list va) {
        typedef const node* const_nodes_t;
        for (nodes_.clear(); to; to = va_arg(va, const_nodes_t)) {
            nodes_.push_back(*to);
        }
        combine();
        return *this;
    }
    virtual derives& set(const node& to) {
        nodes_.clear();
        nodes_.push_back(to);
        combine();
        return *this;
    }
    virtual derives& set(const string_t& name, const node& to) {
        type_ = named_node;
        string_.set(name);
        nodes_.clear();
        nodes_.push_front(to);
        combine();
        return *this;
    }
    virtual derives& set(const char_t* name, const node& to) {
        type_ = named_node;
        string_.set(name);
        nodes_.clear();
        nodes_.push_front(to);
        combine();
        return *this;
    }
    virtual derives& set(const string_t& to) {
        type_ = string_node;
        string_.set(to);
        combine();
        return *this;
    }
    virtual derives& set(const char_t* to) {
        type_ = string_node;
        string_.set(to);
        combine();
        return *this;
    }
    virtual derives& set(const double& to) {
        type_ = number_node;
        number_.set(to);
        combine();
        return *this;
    }
    virtual derives& set(const signed& to) {
        type_ = number_node;
        number_.set(to);
        combine();
        return *this;
    }
    virtual derives& set(const unsigned& to) {
        type_ = number_node;
        number_.set(to);
        combine();
        return *this;
    }

    /// read / write
    virtual bool read(ssize_t& count, char_t& c, reader_t& reader) {
        bool success = false;
        // success = this->read_this(count, c, reader);
        return success;
    }
    virtual bool write(ssize_t& count, writer_t& writer) {
        bool success = false;
        // success = this->write_this(count, writer);
        return success;
    }

    /// combine / separate
    virtual bool combine() {
        json::nodes::const_iterator begin = nodes_.begin(), end = nodes_.end();
        const char_t* chars = 0; size_t length = 0;
        bool success = true;
        switch (type_) {
        case boolean_node:
            this->assign(boolean_);
            break;
        case number_node:
            this->assign(number_);
            break;
        case string_node:
            string_.to_literal(*this);
            break;

        case named_node:
            string_.to_literal(*this);
            this->append(&colon(), 1); 
            this->append(&sp(), 1); 
            if (begin != end) {
                const node& n = *begin;
                if ((chars = n.has_chars(length))) {
                    this->append(chars, length);
                    break;
                }
            }
            this->append(&quot(), 1); 
            this->append(&quot(), 1); 
            break;

        case array_node:
        case object_node:
            if (array_node != type_) {
                this->assign(&lp(), 1);
            } else {
                this->assign(&lb(), 1);
            }
            for (json::nodes::const_iterator i = begin; i != end; ++i) {
                const json::node& n = *i;
                if ((chars = n.has_chars(length))) {
                    if (i != begin) {
                        this->append(&comma(), 1); 
                        this->append(&sp(), 1); 
                    }
                    this->append(chars, length);
                }
            }
            if (array_node != type_) {
                this->append(&rp(), 1);
            } else {
                this->append(&rb(), 1);
            }
            break;
        default:
            this->clear();
            break;
        }
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
        type_ = null_node;
        boolean_.set_default();
        number_.set_default();
        string_.set_default();
        nodes_.clear();
        return *this;
    }

    /// ...
    virtual const char_t& colon() const {
        static const char_t c = ':';
        return c;
    }
    virtual const char_t& comma() const {
        static const char_t c = ',';
        return c;
    }
    virtual const char_t& lb() const {
        static const char_t c = '[';
        return c;
    }
    virtual const char_t& rb() const {
        static const char_t c = ']';
        return c;
    }
    virtual const char_t& lp() const {
        static const char_t c = '{';
        return c;
    }
    virtual const char_t& rp() const {
        static const char_t c = '}';
        return c;
    }
    virtual const char_t& sp() const {
        static const char_t c = ' ';
        return c;
    }
    virtual const char_t& apos() const {
        static const char_t c = '\'';
        return c;
    }
    virtual const char_t& quot() const {
        static const char_t c = '"';
        return c;
    }

protected:
     node_type type_;
     json::boolean boolean_;
     json::number number_;
     json::string string_;
     json::nodes nodes_;
}; /// class node

} /// namespace json
} /// namespace content
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_CONTENT_JSON_NODE_HPP 
