///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2015 $organization$
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
///   File: byte_array.hpp
///
/// Author: $author$
///   Date: 5/13/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_BYTE_ARRAY_HPP
#define _TALAS_CRYPTO_BYTE_ARRAY_HPP

#include "talas/crypto/base.hpp"
#include "xos/base/array.hpp"

namespace talas {
namespace crypto {

typedef xos::base::array_implements byte_array_implements;
typedef xos::base::byte_array byte_array_extends;
///////////////////////////////////////////////////////////////////////
///  Class: byte_array
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS byte_array
: virtual public byte_array_implements, public byte_array_extends {
public:
    typedef byte_array_implements Implements;
    typedef byte_array_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    byte_array(uint32_t value, size_t length) {
        set_size(length);
        append(value, length);
    }
    virtual ~byte_array() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Extends::append;
    virtual size_t append(uint32_t value, size_t length) {
        uint32_t msb = 0;
        size_t i = 0;
        byte_t b = 0;
        for (i = 0; i < length; ++i, value >>= 8) {
            (msb <<= 8) |= (value & 255);
        }
        for (i = 0; i < length; ++i, msb >>= 8) {
            b = (msb & 255);
            this->append(&b, 1);
        }
        return length;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_BYTE_ARRAY_HPP 
