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
///   File: des3.hpp
///
/// Author: $author$
///   Date: 5/16/2015
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_CIPHER_DES3_HPP
#define _TALAS_CRYPTO_CIPHER_DES3_HPP

#include "talas/crypto/cipher/des.hpp"

namespace talas {
namespace crypto {
namespace cipher {

#define TALAS_CRYPTO_CIPHER_DES3_NAME "des3"

typedef cipher::des des3_implements;
///////////////////////////////////////////////////////////////////////
///  Class: des3t
///////////////////////////////////////////////////////////////////////
template <class TImplements = des3_implements>

class _EXPORT_CLASS des3t: virtual public TImplements {
public:
    typedef TImplements Implements;

    enum {
        BLOCKSIZE = Implements::BLOCKSIZE,

        KEYMIN    = Implements::KEYMIN*3,
        KEYMAX    = Implements::KEYMAX*3,
        KEYINC    = Implements::KEYINC*3,
        KEYSIZE   = Implements::KEYSIZE*3,

        IVMIN     = Implements::IVMIN,
        IVMAX     = Implements::IVMAX,
        IVINC     = Implements::IVINC,
        IVSIZE    = Implements::IVSIZE
    };

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t key_size_min() const {
        return KEYMIN;
    }
    virtual ssize_t key_size_max() const {
        return KEYMAX;
    }
    virtual ssize_t key_size_inc() const {
        return KEYINC;
    }
    virtual ssize_t key_size() const {
        return KEYSIZE;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t iv_size_min() const {
        return IVMIN;
    }
    virtual ssize_t iv_size_max() const {
        return IVMAX;
    }
    virtual ssize_t iv_size_inc() const {
        return IVINC;
    }
    virtual ssize_t iv_size() const {
        return IVSIZE;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t block_size() const {
        return BLOCKSIZE;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* name() const {
        return TALAS_CRYPTO_CIPHER_DES3_NAME;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef des3t<> des3;

} // namespace cipher 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_CIPHER_DES3_HPP 
