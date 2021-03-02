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
///   File: which.hpp
///
/// Author: $author$
///   Date: 2/21/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_HTTP_PROTOCOL_WHICH_HPP
#define TALAS_PROTOCOL_HTTP_PROTOCOL_WHICH_HPP

#include "talas/protocol/xttp/message/part.hpp"

#define TALAS_PROTOCOL_HTTP_PROTOCOL_NAME "HTTP"

namespace talas {
namespace protocol {
namespace http {
namespace protocol {

/// class whicht
template <class TExtends = xttp::message::part, class TImplements = typename TExtends::implements>
class exported whicht: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef whicht derives; 
    
    typedef extends part_t;
    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    typedef typename extends::reader_t reader_t;
    typedef typename extends::writer_t writer_t;

    /// constructors / destructor
    whicht(const whicht& copy): extends(copy) {
    }
    whicht() {
    }
    virtual ~whicht() {
    }

    /// name... / of...
    static const char_t* name_of() {
        return TALAS_PROTOCOL_HTTP_PROTOCOL_NAME;
    }
}; /// class whicht
typedef whicht<> which;

} /// namespace protocol
} /// namespace http
} /// namespace protocol
} /// namespace talas

#endif /// TALAS_PROTOCOL_HTTP_PROTOCOL_WHICH_HPP
