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
///   File: writer.hpp
///
/// Author: $author$
///   Date: 2/20/2021
///////////////////////////////////////////////////////////////////////
#ifndef TALAS_PROTOCOL_XTTP_MESSAGE_WRITER_HPP
#define TALAS_PROTOCOL_XTTP_MESSAGE_WRITER_HPP

#include "talas/protocol/xttp/message/part.hpp"
#include "talas/io/string/writer.hpp"

namespace talas {
namespace protocol {
namespace xttp {
namespace message {

/// class writert
template 
<class TPart = part, class TWriter = typename TPart::writer_t,
 class TExtends = io::string::writert<TWriter>, class TImplements = typename TExtends::Implements>
class exported writert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef writert derives;

    typedef TPart part_t;
    
    /// constructor / destructor
    writert(const writert& copy): extends(copy) {
    }
    writert(part_t& part): extends(part) {
    }
    virtual ~writert() {
    }
}; /// class writert
typedef writert<> writer;

} /// namespace message
} /// namespace xttp
} /// namespace protocol
} /// namespace talas

#endif /// ndef TALAS_PROTOCOL_XTTP_MESSAGE_WRITER_HPP 
