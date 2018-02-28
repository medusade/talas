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
///   File: main.hpp
///
/// Author: $author$
///   Date: 2/10/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_APP_CONSOLE_DH_MAIN_HPP
#define _TALAS_APP_CONSOLE_DH_MAIN_HPP

#include "talas/app/console/dh/main_opt.hpp"
#include "talas/crypto/console/mpinteger/main.hpp"

#include "talas/crypto/dh/mbu/private_key.hpp"
#include "talas/crypto/dh/mbu/public_key.hpp"
#include "talas/crypto/dh/mbu/key.hpp"

#include "talas/crypto/dh/bn/private_key.hpp"
#include "talas/crypto/dh/bn/public_key.hpp"
#include "talas/crypto/dh/bn/key.hpp"

#include "talas/crypto/dh/mp/private_key.hpp"
#include "talas/crypto/dh/mp/public_key.hpp"
#include "talas/crypto/dh/mp/key.hpp"

#include "talas/crypto/dh/private_key.hpp"
#include "talas/crypto/dh/public_key.hpp"
#include "talas/crypto/dh/key.hpp"

namespace talas {
namespace app {
namespace console {
namespace dh {

unsigned g = 5;

unsigned char n[] = {
    0xc4, 0x2f, 0xe2, 0x51, 0x84, 0x52, 0x26, 0x61, 0x7e, 0x78, 0x1c, 
    0x95, 0x2c, 0x22, 0x9e, 0x20, 0x44, 0xd3, 0xbc, 0x40, 0xfc, 0x5f, 
    0xaa, 0x58, 0x34, 0x33, 0x38, 0x8f, 0x26, 0x83, 0xd2, 0xc8, 0x52, 
    0x45, 0xa4, 0x46, 0x12, 0x4a, 0xfa, 0x6f, 0x8c, 0x06, 0x54, 0x05, 
    0x68, 0xa5, 0x50, 0xba, 0x06, 0xd1, 0x00, 0x49, 0x96, 0x08, 0xa6, 
    0xd2, 0xda, 0x2e, 0x76, 0xed, 0xda, 0xd2, 0x6d, 0x4b, };

unsigned char x[] = { 
    0xFB, 0xA4, 0xCE, 0x82, 0xCF, 0xC7, 0x2D, 0x88, 0xA5, 0xA2, 0x40, 
    0x9D, 0x9C, 0x64, 0x9F, 0x82, 0xBF, 0x5A, 0xD2, 0xCF, 0xFE, 0x7B, 
    0xDB, 0x31, 0x0E, 0xD7, 0x39, 0x6B, 0xC4, 0xFA, 0xC5, 0xEC, 0xAE, 
    0xC1, 0x38, 0xBF, 0x63, 0x10, 0x49, 0x53, 0x5A, 0xB3, 0x21, 0xA3, 
    0x57, 0x0E, 0x3D, 0xD6, 0xE6, 0x10, 0xD4, 0x1D, 0x34, 0x8B, 0xBD, 
    0x5A, 0x59, 0x09, 0xB7, 0x8B, 0x4D, 0xE3, 0x75, 0x39, };

unsigned char y[] = { 
    0xE5, 0x89, 0x0D, 0x34, 0xD1, 0x6C, 0x2B, 0xAE, 0x59, 0x96, 0x3B, 
    0x10, 0xA0, 0x46, 0x98, 0x41, 0x6F, 0x3F, 0x6B, 0x9B, 0xC3, 0x0E, 
    0x84, 0x30, 0x3C, 0xDE, 0xEF, 0x38, 0xD3, 0x76, 0x16, 0x89, 0x14, 
    0xD8, 0x05, 0xF4, 0xB4, 0x3A, 0xE5, 0x92, 0x01, 0xBB, 0xD7, 0x79, 
    0x2A, 0x46, 0xFE, 0xD3, 0x60, 0x28, 0x16, 0x94, 0xF0, 0xA5, 0x58, 
    0x8D, 0x9A, 0x8D, 0x16, 0x9C, 0xE8, 0x72, 0xAB, 0x09, };

unsigned char k1[sizeof(x)], k2[sizeof(y)];

typedef main_opt_implements main_implements;
typedef crypto::console::mpinteger::main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main: virtual public main_implements,public main_extends {
public:
    typedef main_implements Implements;
    typedef main_extends Extends;
    typedef main Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main(): run_(0) {
    }
    virtual ~main() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    int (Derives::*run_)(int argc, char_t** argv, char_t** env);
    virtual int run(int argc, char_t** argv, char_t** env) {
        int err = 0;

        TALAS_LOG_DEBUG("try {...");
        try {
            if ((run_)) {
                err = (this->*run_)(argc, argv, env);
            } else {
                err = run_bn(argc, argv, env);
            }
            TALAS_LOG_DEBUG("...} try");
        } catch (...) {
            TALAS_LOG_DEBUG("...catch (...)");
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_bn(int argc, char_t** argv, char_t** env) {
        int err = 0;
        crypto::dh::bn::key key(g, 1, n, sizeof(n), x, sizeof(x));
        crypto::dh::bn::public_key pub(g, 1, n, sizeof(n), x, sizeof(x));
        crypto::dh::bn::private_key prv(pub, y, sizeof(y));
        err = run(key, pub, prv, argc, argv, env);
        return err;
    }
    virtual int run_mp(int argc, char_t** argv, char_t** env) {
        int err = 0;
        crypto::dh::mp::key key(g, 1, n, sizeof(n), x, sizeof(x));
        crypto::dh::mp::public_key pub(g, 1, n, sizeof(n), x, sizeof(x));
        crypto::dh::mp::private_key prv(pub, y, sizeof(y));
        err = run(key, pub, prv, argc, argv, env);
        return err;
    }
    virtual int run_mbu(int argc, char_t** argv, char_t** env) {
        int err = 0;
        crypto::dh::mbu::key key(g, 1, n, sizeof(n), x, sizeof(x));
        crypto::dh::mbu::public_key pub(g, 1, n, sizeof(n), x, sizeof(x));
        crypto::dh::mbu::private_key prv(pub, y, sizeof(y));
        err = run(key, pub, prv, argc, argv, env);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run
    (crypto::dh::key& key, 
     crypto::dh::public_key& pub,
     crypto::dh::private_key& prv,
     int argc, char_t** argv, char_t** env) {
        int err = 0;
        size_t size = 0;

        if ((size = key.get_exponent_msb(k1, sizeof(k1)))) {
            this->out("x = ");
            this->outx(k1, size);
            this->outln();
        }
        if ((key.create_msb(g, 1, n, sizeof(n), y, sizeof(y)))) {
            if ((size = key.get_exponent_msb(k1, sizeof(k1)))) {
                this->out("y = ");
                this->outx(k1, size);
                this->outln();
            }
        }
        if ((size = prv.get_exponent_msb(k1, sizeof(k1)))) {
            this->out("k1 = ");
            this->outx(k1, size);
            this->outln();
        }
        if ((pub.create_msb(g, 1, n, sizeof(n), y, sizeof(y)))) {
            if ((prv.create(pub, x, sizeof(x)))) {
                if ((size = prv.get_exponent_msb(k2, sizeof(k2)))) {
                    this->out("k2 = ");
                    this->outx(k2, size);
                    this->outln();
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_mp_integer_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            if (!(optarg[0] != TALAS_CRYPTO_CONSOLE_MPINTEGER_MAIN_MP_INTEGER_OPTARG_BN[1])) {
                run_ = &Derives::run_bn;
            } else {
                if (!(optarg[0] != TALAS_CRYPTO_CONSOLE_MPINTEGER_MAIN_MP_INTEGER_OPTARG_MP[1])) {
                    run_ = &Derives::run_mp;
                } else {
                    if (!(optarg[0] != TALAS_CRYPTO_CONSOLE_MPINTEGER_MAIN_MP_INTEGER_OPTARG_MBU[1])) {
                        run_ = &Derives::run_mbu;
                    } else {
                    }
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace dh 
} // namespace console 
} // namespace app 
} // namespace talas 

#endif // _TALAS_APP_CONSOLE_DH_MAIN_HPP 
