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
///   File: private_key.hpp
///
/// Author: $author$
///   Date: 2/12/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DH_MBU_PRIVATE_KEY_HPP
#define _TALAS_CRYPTO_DH_MBU_PRIVATE_KEY_HPP

#include "talas/crypto/dh/mbu/public_key.hpp"
#include "talas/crypto/dh/private_key.hpp"

namespace talas {
namespace crypto {
namespace dh {
namespace mbu {

///////////////////////////////////////////////////////////////////////
///  Class: private_keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = dh::private_key_implements, 
 class TExtends = dh::private_keyt<dh::private_key_implements, key> >

class _EXPORT_CLASS private_keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    enum { key_min = Extends::key_min, key_max = Extends::key_max};

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    private_keyt
    (const dh::public_key_implements& public_key,
     const byte_t* exponent, size_t expbytes) {
        if (!(this->create(public_key, exponent, expbytes))) {
            const creator_exception e = failed_to_create;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_create)...")
            throw(e);
        }
    }
    private_keyt() {
    }
    virtual ~private_keyt() {
        if (!(this->destroyed())) {
            const creator_exception e = failed_to_destroy;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_destroy)...")
            throw(e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bool create
    (const dh::public_key_implements& public_key,
     const byte_t* exponent, size_t expbytes) {
        if ((exponent) && (expbytes)) {
            public_key_implemented* pub = 0;

            if ((pub = public_key.mbu_key_implemented())) {
                size_t genbytes = 0, modbytes = 0;
                byte_t *g = 0, *n = 0;

                if ((g = pub->g()) && (genbytes = pub->genbytes()) 
                    && (n = pub->n()) && (modbytes = pub->modbytes())
                    && (genbytes <= modbytes)) {

                    if ((Implements::create(genbytes, modbytes, expbytes))) {
                        
                        TALAS_LOG_DEBUG("::mbu_set(this->g_, g, modbytes = " << modbytes << ")...")
                        ::mbu_set(this->g_, g, modbytes);

                        TALAS_LOG_DEBUG("::mbu_set(this->n_, n, modbytes = " << modbytes << ")...")
                        ::mbu_set(this->n_, n, modbytes);

                        if ((pub->create_secret_msb
                             (this->x_, expbytes, exponent, expbytes))) {
                            return true;
                        }
                        Implements::destroy();
                    }
                }
            }
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef private_keyt<> private_key;
typedef private_key::Implements private_key_implements;

} // namespace mbu 
} // namespace dh 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DH_MBU_PRIVATE_KEY_HPP 
