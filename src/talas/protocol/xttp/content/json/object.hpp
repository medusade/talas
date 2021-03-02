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
///   File: object.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_XTTP_CONTENT_JSON_OBJECT_HPP
#define TALAS_PROTOCOL_XTTP_CONTENT_JSON_OBJECT_HPP

#include "talas/protocol/xttp/content/json/node.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace content {
namespace json {

/// class objectt
template <class TExtends = json::node, class TImplements = typename TExtends::implements>
class exported objectt: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef objectt derives;
    
    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructor / destructor
    objectt(const node* item, ...): extends(object_node) {
        va_list va;
        va_start(va, item);
        this->set(item, va);
        va_end(va);
    }
    objectt(const node* item, va_list va): extends(object_node) {
        this->set(item, va);
    }
    objectt(const objectt& copy): extends(copy) {
    }
    objectt(): extends(object_node) {
        this->combine();
    }
    virtual ~objectt() {
    }
}; /// class objectt
typedef objectt<> object;

} /// namespace json
} /// namespace content
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_CONTENT_JSON_OBJECT_HPP 
