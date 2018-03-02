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
///   Date: 2/21/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_APP_CONSOLE_DSA_MAIN_HPP
#define _TALAS_APP_CONSOLE_DSA_MAIN_HPP

#include "talas/app/console/dsa/main_opt.hpp"
#include "talas/crypto/console/mpinteger/main.hpp"
/*
#include "talas/crypto/dsa/mbu/public_key.hpp"
#include "talas/crypto/dsa/mbu/private_key.hpp"
#include "talas/crypto/dsa/mbu/key.hpp"

*/
#include "talas/crypto/dsa/mp/public_key.hpp"
#include "talas/crypto/dsa/mp/private_key.hpp"
#include "talas/crypto/dsa/mp/key.hpp"

#include "talas/crypto/dsa/bn/public_key.hpp"
#include "talas/crypto/dsa/bn/private_key.hpp"
#include "talas/crypto/dsa/bn/key.hpp"

#include "talas/crypto/dsa/public_key.hpp"
#include "talas/crypto/dsa/private_key.hpp"
#include "talas/crypto/dsa/key.hpp"
#include <time.h>

namespace talas {
namespace app {
namespace console {
namespace dsa {

enum { 
    key_min = 64, 
    key_max = 256 
};
unsigned char p[]={
    0x8d,0xf2,0xa4,0x94,0x49,0x22,0x76,0xaa,0x3d,0x25,0x75,0x9b,0xb0,0x68,0x69,0xcb,
    0xea,0xc0,0xd8,0x3a,0xfb,0x8d,0x0c,0xf7,0xcb,0xb8,0x32,0x4f,0x0d,0x78,0x82,0xe5,
    0xd0,0x76,0x2f,0xc5,0xb7,0x21,0x0e,0xaf,0xc2,0xe9,0xad,0xac,0x32,0xab,0x7a,0xac,
    0x49,0x69,0x3d,0xfb,0xf8,0x37,0x24,0xc2,0xec,0x07,0x36,0xee,0x31,0xc8,0x02,0x91,
};
unsigned char q[]={
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc7,0x73,0x21,0x8c,
    0x73,0x7e,0xc8,0xee,0x99,0x3b,0x4f,0x2d,0xed,0x30,0xf4,0x8e,0xda,0xce,0x91,0x5f,
};
unsigned char g[]={
    0x62,0x6d,0x02,0x78,0x39,0xea,0x0a,0x13,0x41,0x31,0x63,0xa5,0x5b,0x4c,0xb5,0x00,
    0x29,0x9d,0x55,0x22,0x95,0x6c,0xef,0xcb,0x3b,0xff,0x10,0xf3,0x99,0xce,0x2c,0x2e,
    0x71,0xcb,0x9d,0xe5,0xfa,0x24,0xba,0xbf,0x58,0xe5,0xb7,0x95,0x21,0x92,0x5c,0x9c,
    0xc4,0x2e,0x9f,0x6f,0x46,0x4b,0x08,0x8c,0xc5,0x72,0xaf,0x53,0xe6,0xd7,0x88,0x02,
};
unsigned char x[key_max];
unsigned char y[key_max];
unsigned char h[key_max];
unsigned char k[key_max];
unsigned char r[key_max];
unsigned char s[key_max];
unsigned char v[key_max];

typedef main_opt_implements main_implements;
typedef crypto::console::mpinteger::main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main: virtual public main_implements, public main_extends {
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
        time_t t = 0;

        srand(time(&t));
        this->random(x,sizeof(q));        

        TALAS_LOG_DEBUG("try {...");
        try {
            if ((run_)) {
                err = (this->*run_)(argc, argv, env);
            } else {
                err = run_default(argc, argv, env);
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
        crypto::dsa::bn::key key(p, sizeof(p), q, sizeof(q), g, sizeof(g));
        crypto::dsa::bn::private_key prv(p, sizeof(p), q, sizeof(q), g, sizeof(g), x, sizeof(q));
        crypto::dsa::bn::public_key pub(p, sizeof(p), q, sizeof(q), g, sizeof(g), y, sizeof(q));
        err = run(key, prv, pub, argc, argv, env);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_mp(int argc, char_t** argv, char_t** env) {
        int err = 0;
        crypto::dsa::mp::key key(p, sizeof(p), q, sizeof(q), g, sizeof(g));
        crypto::dsa::mp::private_key prv(p, sizeof(p), q, sizeof(q), g, sizeof(g), x, sizeof(q));
        crypto::dsa::mp::public_key pub(p, sizeof(p), q, sizeof(q), g, sizeof(g), y, sizeof(q));
        err = run(key, prv, pub, argc, argv, env);
        return err;
    }
    virtual int run_mbu(int argc, char** argv, char** env) {
        int err = 1;
        LOG_ERROR("...unimplemented");
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_null(int argc, char_t** argv, char_t** env) {
        int err = 0;
        crypto::dsa::null::key key(p, sizeof(p), q, sizeof(q), g, sizeof(g));
        crypto::dsa::null::private_key prv(p, sizeof(p), q, sizeof(q), g, sizeof(g), x, sizeof(q));
        crypto::dsa::null::public_key pub(p, sizeof(p), q, sizeof(q), g, sizeof(g), y, sizeof(q));
        err = run(key, prv, pub, argc, argv, env);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_default(int argc, char_t** argv, char_t** env) {
        int err = 0;
        err = run_bn(argc, argv, env);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run
    (crypto::dsa::key& key, 
     crypto::dsa::private_key& prv,
     crypto::dsa::public_key& pub,
     int argc, char_t** argv, char_t** env) {
        int err = 0;
        ssize_t size = 0;
        size_t rbytes = 0, sbytes = 0, hbytes = 0, kbytes = 0;
        
        rbytes = sizeof(q);
        sbytes= this->size_of(q,sizeof(q));
        hbytes = sizeof(q);
        kbytes = sizeof(q);
    
        memset(h,0,hbytes-sbytes);
        this->random(h+hbytes-sbytes,sbytes);        
        sbytes = sizeof(q);

        this->out("h = ");
        this->outx(h,hbytes);
        this->outln();
        this->outln();

        this->random(k, kbytes);        
        this->out("k = ");
        this->outx(k, kbytes);
        this->outln();
        this->outln();

        if (0 < (size = prv.get_p_msb(p, sizeof(p)))) {
            this->out("p = ");
            this->outx(p, size);
            this->outln();
            this->outln();
        }
        if (0 < (size = prv.get_q_msb(q, sizeof(q)))) {
            this->out("q = ");
            this->outx(q, size);
            this->outln();
            this->outln();
        }
        if (0 < (size = prv.get_g_msb(g, sizeof(g)))) {
            this->out("g = ");
            this->outx(g, size);
            this->outln();
            this->outln();
        }
        if (0 < (size = prv.get_x_msb(x, sizeof(x)))) {
            this->out("x = ");
            this->outx(x, size);
            this->outln();
            this->outln();
        }
        if (0 < (size = prv.get_y_msb(y, sizeof(y)))) {
            this->out("y = ");
            this->outx(y, size);
            this->outln();
            this->outln();
            pub.set_y_msb(y, size);
        }        
        if (0 < (size = pub.get_y_msb(y, sizeof(y)))) {
            this->out("y = ");
            this->outx(y, size);
            this->outln();
            this->outln();
        }        
        if (0 < (size = prv.sign_msb(r, sizeof(r), s, sizeof(s), h, hbytes, k, kbytes))) {
            this->out("r = ");
            this->outx(r, size);
            this->outln();
            this->outln();

            this->out("s = ");
            this->outx(s, size);
            this->outln();
            this->outln();
        }
        if (0 < (size = pub.verify_msb(v, sizeof(v), h, hbytes, r, rbytes, s, sbytes))) {
            this->out("v = ");
            this->outx(v, size);
            this->outln();
            this->outln();

            if (memcmp(r,v,size)==0) {
                this->outln("Verified");
            } else {
                this->outln("Verify failed");
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
                        err = on_invalid_option_arg
                        (optval, optarg, optname, optind, argc, argv, env);
                    }
                }
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
};

} // namespace dsa 
} // namespace console 
} // namespace app 
} // namespace talas 

#endif // _TALAS_APP_CONSOLE_DSA_MAIN_HPP 
