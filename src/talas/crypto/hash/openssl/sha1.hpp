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
///   File: sha1.hpp
///
/// Author: $author$
///   Date: 11/14/2014
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_HASH_OPENSSL_SHA1_HPP
#define _TALAS_CRYPTO_HASH_OPENSSL_SHA1_HPP

#include "talas/crypto/hash/sha1.hpp"

namespace talas {
namespace crypto {
namespace hash {
namespace openssl {

typedef hash::sha1_implements sha1_implements;
typedef hash::sha1 sha1_extends;
///////////////////////////////////////////////////////////////////////
///  Class: sha1
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS sha1: virtual public sha1_implements, public sha1_extends {
public:
    typedef sha1_implements Implements;
    typedef sha1_extends Extends;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    sha1() {
    }
    virtual ~sha1() {
    }

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void initial();
    virtual void final();
    virtual void transform();
    virtual void update(const uint8_t* in, size_t inlen);

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace openssl 
} // namespace hash 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_HASH_OPENSSL_SHA1_HPP 
