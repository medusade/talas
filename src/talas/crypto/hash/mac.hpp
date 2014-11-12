///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2014 $organization$
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
///   File: mac.hpp
///
/// Author: $author$
///   Date: 11/11/2014
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_HASH_MAC_HPP
#define _TALAS_CRYPTO_HASH_MAC_HPP

#include "talas/crypto/base.hpp"

namespace talas {
namespace crypto {
namespace hash {
namespace mac {

enum {
    IPAD = 0x36,
    OPAD = 0x5c
};

} // namespace mac
} // namespace hash 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_HASH_MAC_HPP 
