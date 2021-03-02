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
///   File: array.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_XTTP_CONTENT_JSON_ARRAY_HPP
#define TALAS_PROTOCOL_XTTP_CONTENT_JSON_ARRAY_HPP

#include "talas/protocol/xttp/content/json/node.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace content {
namespace json {

/// class arrayt
template <class TExtends = json::node, class TImplements = typename TExtends::implements>
class exported arrayt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef arrayt derives;
    
    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    arrayt(const node* item, ...): extends(array_node) {
        va_list va;
        va_start(va, item);
        this->set(item, va);
        va_end(va);
    }
    arrayt(const node* item, va_list va): extends(array_node) {
        this->set(item, va);
    }
    arrayt(const arrayt& copy): extends(copy) {
    }
    arrayt(): extends(array_node) {
        this->combine();
    }
    virtual ~arrayt() {
    }
}; /// class arrayt
typedef arrayt<> array;

} /// namespace json
} /// namespace content
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_CONTENT_JSON_ARRAY_HPP 
