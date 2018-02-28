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
///   Date: 2/26/2018
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_APP_CONSOLE_MPINTEGER_MAIN_HPP
#define _TALAS_APP_CONSOLE_MPINTEGER_MAIN_HPP

#include "talas/crypto/console/mpinteger/main.hpp"
#include "numera/mp/mp/unsigned_integer.hpp"
#include "numera/mp/bn/unsigned_integer.hpp"
#include "numera/mp/unsigned_integer.hpp"

namespace talas {
namespace app {
namespace console {
namespace mpinteger {

namespace dsa {
enum { 
    key_min = 64, key_max = 256 
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
} // namespace dsa

typedef crypto::console::mpinteger::main_implements main_implements;
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
    int (Derives::*run_)(int argc, char** argv, char** env);
    virtual int run(int argc, char** argv, char** env) {
        int err = 0;
        time_t t = 0;

        ::srand(::time(&t));

        LOG_DEBUG("try {...");
        try {
            if ((this->run_)) {
                err = (this->*run_)(argc, argv, env);
            } else {
                err = this->run_default(argc, argv, env);
            }
            LOG_DEBUG("...} try");
        } catch(...) {
            LOG_ERROR("}...catch(...)");
            err = 1;
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_bn(int argc, char** argv, char** env) {
        int err = 0;
        numera::mp::bn::unsigned_integer 
                p(dsa::p, sizeof(dsa::p)), 
                q(dsa::q, sizeof(dsa::q)), 
                g(dsa::g, sizeof(dsa::g));
        err = this->run_dsa(p, q, g);
        return err;
    }
    virtual int run_mp(int argc, char** argv, char** env) {
        int err = 0;
        numera::mp::mp::unsigned_integer 
                p(dsa::p, sizeof(dsa::p)), 
                q(dsa::q, sizeof(dsa::q)), 
                g(dsa::g, sizeof(dsa::g));
        err = this->run_dsa(p, q, g);
        return err;
    }
    virtual int run_mbu(int argc, char** argv, char** env) {
        int err = 1;
        LOG_ERROR("...unimplemented");
        return err;
    }
    virtual int run_default(int argc, char** argv, char** env) {
        int err = 0;
        err = this->run_mp(argc, argv, env);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    //typedef numera::mp::bn::unsigned_integer mp_uint;
    template <typename mp_uint>
    int run_dsa(mp_uint& p, mp_uint& q, mp_uint& g) {
        int err = 0;
        size_t size = 0, 
               psize = (sizeof(dsa::p)), 
               qsize = (sizeof(dsa::q)), 
               gsize = (sizeof(dsa::g)),
               hsize = size_of(dsa::q, qsize);
        
        memset(dsa::h, 0, qsize);
        
        if ((size = this->random(dsa::x, qsize))) {
            
            if ((size = this->random(dsa::h+qsize-hsize, hsize))) {
                this->out("h = ");
                this->outx(dsa::h, qsize);
                this->outln();
                this->outln();

                if ((size = this->random(dsa::k, qsize))) {
                    this->out("k = ");
                    this->outx(dsa::k, qsize);
                    this->outln();
                    this->outln();

                    p.get_msb(dsa::y, psize);
                    this->out("p = ");
                    this->outx(dsa::y, psize);
                    this->outln();
                    this->outln();

                    q.get_msb(dsa::y, qsize);
                    this->out("q = ");
                    this->outx(dsa::y, qsize);
                    this->outln();
                    this->outln();

                    g.get_msb(dsa::y, gsize);
                    this->out("g = ");
                    this->outx(dsa::y, size);
                    this->outln();
                    this->outln();

                    this->out("x = ");
                    this->outx(dsa::x, qsize);
                    this->outln();
                    this->outln();
                    {
                        mp_uint h(dsa::h, qsize), k(dsa::k, psize), 
                                x(dsa::x, psize), y, r, s, ik, t1, t2;
                        
                        // y = g^x mod p
                        //
                        y.mod_exp(y, g, x, p);

                        if ((size = y.get_msb(dsa::y, psize))) {
                            this->out("y = ");
                            this->outx(dsa::y, size);
                            this->outln();
                            this->outln();
                            
                            // ik = k^-1 mod q
                            //
                            ik.mod_inv(ik, k, q);
                            
                            // r = (g^k mod p) mod q
                            //
                            r.mod_exp(t1, g, k, p);
                            r.mod(r, t1, q);

                            if ((size = r.get_msb(dsa::r, qsize))) {
                                this->out("r = ");
                                this->outx(dsa::r, size);
                                this->outln();
                                this->outln();
                                
                                // s = k^-1*(h+x*r) mod q
                                //
                                s.mul(t1, r, x);
                                s.add(t2, h, t1);
                                s.mul(t1, t2, ik);
                                s.mod(s, t1, q);

                                if ((size = s.get_msb(dsa::s, qsize))) {
                                    this->out("s = ");
                                    this->outx(dsa::s, size);
                                    this->outln();
                                    this->outln();
                                    {
                                        mp_uint v, si, u1, u2;
                                        
                                        // si = s^-1 mod q
                                        //
                                        si.mod_inv(si, s, q);
                                        
                                        // u2 = r*si mod q
                                        //
                                        u2.mul(t1, r, si);
                                        u2.mod(u2, t1, q);
                                        
                                        // u1 = h*si mod q
                                        //
                                        u1.mul(t1, h, si);
                                        u1.mod(u1, t1, q);
                                        
                                        // t1 = g^u1 mod p
                                        //
                                        t1.mod_exp(t1, g, u1, p);
                                        
                                        // t2 = y^u2 mod p
                                        //
                                        t2.mod_exp(t2, y, u2, p);
                                        
                                        // u2 = t1*t2 mod p
                                        //
                                        u2.mul(u1, t1, t2);
                                        u2.mod(u2, u1, p);
                                        
                                        // v = u2 mod q
                                        //
                                        v.mod(v, u2, q);
                                        
                                        if ((size = v.get_msb(dsa::v, qsize))) {
                                            this->out("v = ");
                                            this->outx(dsa::v, size);
                                            this->outln();
                                            this->outln();
                                        }
                                    }
                                }
                            }
                        }
                    }
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

} // namespace mpinteger 
} // namespace console 
} // namespace app 
} // namespace talas 

#endif // _TALAS_APP_CONSOLE_MPINTEGER_MAIN_HPP 
