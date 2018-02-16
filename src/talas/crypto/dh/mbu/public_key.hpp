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
///   Date: 2/12/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_CRYPTO_DH_MBU_PUBLIC_KEY_HPP
#define _TALAS_CRYPTO_DH_MBU_PUBLIC_KEY_HPP

#include "talas/crypto/dh/public_key.hpp"
#include "talas/crypto/dh/mbu/key.hpp"

namespace talas {
namespace crypto {
namespace dh {
namespace mbu {

typedef dh::public_key_implements public_key_implements;
///////////////////////////////////////////////////////////////////////
///  Class: public_key_implemented
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS public_key_implemented: virtual public public_key_implements {
public:
    typedef public_key_implements Implements;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual byte_t* g() const {
        return 0;
    }
    virtual byte_t* n() const {
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////
///  Class: public_keyt
///////////////////////////////////////////////////////////////////////
template
<class TImplements = public_key_implemented, 
 class TExtends = dh::public_keyt<public_key_implemented, key> >

class _EXPORT_CLASS public_keyt: virtual public TImplements, public TExtends {
public:
    typedef TImplements Implements;
    typedef TExtends Extends;

    enum { key_min = Extends::key_min, key_max = Extends::key_max};

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    public_keyt
    (const unsigned& generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if (!(this->create_msb
             (generator, genbytes, modulus, modbytes, exponent, expbytes))) {
            const creator_exception e = failed_to_create;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_create)...")
            throw(e);
        }
    }
    public_keyt
    (const byte_t* generator, size_t genbytes,
     const byte_t* modulus, size_t modbytes,
     const byte_t* exponent, size_t expbytes) {
        if (!(this->create_msb
             (generator, genbytes, modulus, modbytes, exponent, expbytes))) {
            const creator_exception e = failed_to_create;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_create)...")
            throw(e);
        }
    }
    public_keyt() {
    }
    virtual ~public_keyt() {
        if (!(this->destroyed())) {
            const creator_exception e = failed_to_destroy;
            TALAS_LOG_ERROR("...throw(const creator_exception e = failed_to_destroy)...")
            throw(e);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t create_secret_msb
    (byte_t* secret, size_t secbytes, const byte_t* exponent, size_t expbytes) {
        size_t size = 0;

        if ((secret) && (secbytes >= this->modbytes_) 
            && (exponent) && (expbytes) && (expbytes == this->modbytes_)) {
            ::mbu_montgomery mont;

            TALAS_LOG_DEBUG("::mbu_init_montgomery(&mont, this->n_, this->modbytes_ = " << this->modbytes_ << ")...");
            ::mbu_init_montgomery(&mont, this->n_, this->modbytes_);

            TALAS_LOG_DEBUG("::mbu_mod_exp_montgomery(secret, this->x_, &mont, exponent, expbytes)...");
            ::mbu_mod_exp_montgomery(secret, this->x_, &mont, exponent, expbytes);
            TALAS_LOG_DEBUG("...::mbu_mod_exp_montgomery(secret = " << x_to_string(secret, expbytes) << ", this->x_, &mont, exponent, expbytes = " << expbytes << ");...");
            size = expbytes;
        }
        return size;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual mbu::public_key_implemented* mbu_key_implemented() const {
        return (mbu::public_key_implemented*)this;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual byte_t* g() const {
        return (byte_t*)(this->g_);
    }
    virtual byte_t* n() const {
        return (byte_t*)(this->n_);
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_exponent_msb
    (const byte_t* exponent, size_t expbytes) {
        ssize_t size = 0;

        if ((Extends::set_exponent_msb(exponent, expbytes))) {
            size = set_exponent_modulus_msb(exponent, expbytes);
        }
        return size;
    }
    
protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t set_exponent_modulus_msb
    (const byte_t* exponent, size_t expbytes) {
        if ((this->genbytes_) && (this->modbytes_) 
            && (exponent) && (expbytes) && (expbytes == this->expbytes_)) {
            unsigned char x[key_max];
            ::mbu_montgomery mont;

            TALAS_LOG_DEBUG("::mbu_set(x, exponent = " << x_to_string(exponent, expbytes) << ", expbytes = " << expbytes << ")...");
            ::mbu_set(x, exponent, expbytes);

            TALAS_LOG_DEBUG("::mbu_init_montgomery(&mont, this->n_, this->modbytes_ = " << this->modbytes_ << ")...");
            ::mbu_init_montgomery(&mont, this->n_, this->modbytes_);

            TALAS_LOG_DEBUG("::mbu_mod_exp_montgomery(this->x_, this->g_, &mont, x, this->modbytes = " << this->modbytes_ << ");...");
            ::mbu_mod_exp_montgomery(this->x_, this->g_, &mont, x, this->modbytes_);
            TALAS_LOG_DEBUG("...::mbu_mod_exp_montgomery(this->x_ = " << x_to_string(this->x_, this->expbytes_) << ", this->g_, &mont, x, this->expbytes);...");
            return this->modbytes_;
        }
        return 0;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};
typedef public_keyt<> public_key;

} // namespace mbu 
} // namespace dh 
} // namespace crypto 
} // namespace talas 

#endif // _TALAS_CRYPTO_DH_MBU_PUBLIC_KEY_HPP 
