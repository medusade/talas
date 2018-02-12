///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
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
///   File: public_key.hpp
///
/// Author: $author$
///   Date: 2/11/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DH_PUBLIC_KEY_HPP
#define _TALAS_CRYPTO_DH_PUBLIC_KEY_HPP

#include "talas/crypto/dh/private_key.hpp"

namespace talas {
namespace crypto {
namespace dh {

typedef private_key_implements public_key_implementst_implements;
///////////////////////////////////////////////////////////////////////
///  Class: public_key_implementst
///////////////////////////////////////////////////////////////////////
template
<class TImplements = public_key_implementst_implements>

class _EXPORT_CLASS public_key_implementst: virtual public TImplements {
public:
    typedef TImplements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create(const private_key_implements& private_key) {
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef public_key_implementst<> public_key_implements;

} // namespace dh 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DH_PUBLIC_KEY_HPP 
