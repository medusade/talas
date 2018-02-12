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
///   File: key.hpp
///
/// Author: $author$
///   Date: 2/12/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DH_MBU_KEY_HPP
#define _TALAS_CRYPTO_DH_MBU_KEY_HPP

#include "talas/crypto/dh/key.hpp"
#include "mbuint.h"

namespace talas {
namespace crypto {
namespace dh {
namespace mbu {

typedef dh::key_implements keyt_implements;
typedef dh::key keyt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = keyt_implements, class TExtends = keyt_extends>

class _EXPORT_CLASS keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    enum {key_min = 1, key_max = 256};
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    keyt
    (const unsigned& generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes) {
        clear();
        if (!(this->create_msb(generator, genbytes, modulus, modbytes))) {
            const creator_exception e = failed_to_create;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_create)...")
            throw(e);
        }
    }
    keyt() {
        clear();
    }
    virtual ~keyt() {
        if (!(this->destroyed())) {
            const creator_exception e = failed_to_destroy;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_destroy)...")
            throw(e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    using Implements::set_msb;
    virtual bool set_msb
    (const byte_t* generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes) {
        if ((generator) && (genbytes) && (genbytes == this->genbytes())
            && (modulus) && (modbytes) && (modbytes == this->modbytes())) {

            TALAS_LOG_DEBUG(":mbu_set(g_, generator, genbytes = " << genbytes << ")...");
            ::mbu_set(g_, generator, genbytes);

            TALAS_LOG_DEBUG("::mbu_set(m_, modulus, modbytes = " << modbytes << ")...");
            ::mbu_set(n_, modulus, modbytes);
            return true;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual void clear() {

        TALAS_LOG_DEBUG("::memset(g_, 0, key_max = " << key_max << ")...");
        ::memset(g_, 0, key_max);

        TALAS_LOG_DEBUG("::memset(n_, 0, key_max = " << key_max << ")...");
        ::memset(n_, 0, key_max);
        Extends::clear();
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual size_t genbytes_min() const {
        return key_min;
    }
    virtual size_t genbytes_max() const {
        return key_max;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual size_t modbytes_min() const {
        return key_min;
    }
    virtual size_t modbytes_max() const {
        return key_max;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    unsigned char g_[key_max], n_[key_max];
};
typedef keyt<> key;

} // namespace mbu 
} // namespace dh 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DH_MBU_KEY_HPP 
