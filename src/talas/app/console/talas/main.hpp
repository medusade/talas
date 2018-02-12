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
///   File: main.hpp
///
/// Author: $author$
///   Date: 11/18/2014
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_APP_CONSOLE_TALAS_MAIN_HPP
#define _TALAS_APP_CONSOLE_TALAS_MAIN_HPP

#include "talas/crypto/hash/implementation/implementation.hpp"
#include "talas/crypto/console/main.hpp"
#include "talas/crypto/rsa/mp/key_generator.hpp"
#include "talas/crypto/rsa/mp/private_key.hpp"
#include "talas/crypto/rsa/mp/public_key.hpp"
#include "talas/crypto/random/prime/mp/generator.hpp"
#include "talas/crypto/random/prime/mp/miller_rabin.hpp"
#include "talas/crypto/random/prime/mp/reader.hpp"
#include "talas/crypto/random/prime/mp/number.hpp"
#include "talas/crypto/rsa/bn/key_generator.hpp"
#include "talas/crypto/rsa/bn/private_key.hpp"
#include "talas/crypto/rsa/bn/public_key.hpp"
#include "talas/crypto/random/prime/bn/generator.hpp"
#include "talas/crypto/random/prime/bn/miller_rabin.hpp"
#include "talas/crypto/random/prime/bn/reader.hpp"
#include "talas/crypto/random/prime/bn/number.hpp"
#include "talas/crypto/ecc/curve25519/msotoodeh/public_key.hpp"
#include "talas/crypto/ecc/curve25519/google/donna/public_key.hpp"
#include "talas/crypto/ecc/curve25519/shared_secret.hpp"
#include "talas/crypto/ecc/curve25519/public_key.hpp"
#include "talas/crypto/ecc/curve25519/private_key.hpp"
#include "talas/crypto/ecc/curve25519/key.hpp"
#include "talas/crypto/ecc/curve25519/base_point.hpp"
#include "talas/crypto/cipher/devine/aes.hpp"
#include "talas/crypto/cipher/openssl/des.hpp"
#include "talas/crypto/random/pseudo.hpp"
#include "talas/crypto/byte_array.hpp"
#include "thirdparty/gnu/glibc/stdlib/rand_r.h"
#include "xos/base/array.hpp"
#include "talas/app/console/talas/main_opt.hpp"
#include "talas/app/console/talas/rsa_test_keys.cpp"
#include "talas/app/console/talas/rsa_test_keys_pem.cpp"

#define TALAS_APP_CONSOLE_TALAS_MAIN_PRIME_BITS 1024

#define TALAS_APP_CONSOLE_TALAS_MAIN_RSA_MODULUS_BITS 2048
#define TALAS_APP_CONSOLE_TALAS_MAIN_RSA_EXPONENT_BITS 24
#define TALAS_APP_CONSOLE_TALAS_MAIN_RSA_EXPONENT 0x010001

#define TALAS_APP_CONSOLE_TALAS_MAIN_KB_BLOCKSIZE 64
#define TALAS_APP_CONSOLE_TALAS_MAIN_BLOCKSIZE (TALAS_APP_CONSOLE_TALAS_MAIN_KB_BLOCKSIZE*1024)

namespace talas {
typedef xos::base::byte_array byte_array;
namespace app {
namespace console {
namespace talas {

typedef crypto::random::prime::mp::reader_observer mp_reader_observer;
typedef crypto::random::prime::bn::reader_observer bn_reader_observer;
typedef crypto::console::main_implements main_implements;
typedef crypto::console::main main_extends;
///////////////////////////////////////////////////////////////////////
///  Class: main
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS main
: virtual public mp_reader_observer, virtual public bn_reader_observer,
  virtual public main_implements, public main_extends {
public:
    typedef main_implements Implements;
    typedef main_extends Extends;
    typedef main Derives;

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    main()
    : run_(0),
      run_ecc_25519_(0),
      run_ecc_25519_exchange_(0),
      run_generate_rsa_(0),
      run_rsa_exchange_(0),
      run_generate_prime_(0),
      generate_(generate_none),
      bitsof_(bitsof_none),
      prime_bits_(TALAS_APP_CONSOLE_TALAS_MAIN_PRIME_BITS),
      rsa_modulus_bits_(TALAS_APP_CONSOLE_TALAS_MAIN_RSA_MODULUS_BITS),
      rsa_exponent_bits_(TALAS_APP_CONSOLE_TALAS_MAIN_RSA_EXPONENT_BITS),
      rsa_exponent_(TALAS_APP_CONSOLE_TALAS_MAIN_RSA_EXPONENT),
      get_random_generator_(0),
      pseudo_random_seed_(0),
      pseudo_random_(pseudo_random_seed_),
      ecc_algorithm_(ecc_algorithm_none),
      hash_algorithm_(hash_algorithm_none),
      cipher_algorithm_(cipher_algorithm_none),
      block_size_(TALAS_APP_CONSOLE_TALAS_MAIN_BLOCKSIZE) {
    }
    virtual ~main() {
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    typedef io::read::file source_file_t;

    typedef crypto::hash::base hash_t;
    typedef crypto::hash::implementation::md5 md5_t;
    typedef crypto::hash::implementation::sha1 sha1_t;
    typedef crypto::hash::implementation::sha256 sha256_t;
    typedef crypto::hash::implementation::sha512 sha512_t;
    enum hash_algorithm_t {
        hash_algorithm_none,
        hash_algorithm_sha512,
        hash_algorithm_sha256,
        hash_algorithm_sha1,
        hash_algorithm_md5,
        next_hash_algorithm,
        first_hash_algorithm = (hash_algorithm_none + 1),
        last_hash_algorithm = (next_hash_algorithm - 1)
    };

    typedef crypto::cipher::base cipher_t;
    typedef crypto::cipher::devine::aes aes_t;
    typedef crypto::cipher::openssl::des3 des3_t;
    enum cipher_algorithm_t {
        cipher_algorithm_none,
        cipher_algorithm_aes,
        cipher_algorithm_des3,
        next_cipher_algorithm,
        first_cipher_algorithm = (cipher_algorithm_none + 1),
        last_cipher_algorithm = (next_cipher_algorithm - 1)
    };

    typedef crypto::ecc::curve25519::base_point curve25519_base_point_t;
    typedef crypto::ecc::curve25519::private_key curve25519_secret_key_t;
    typedef crypto::ecc::curve25519::public_key curve25519_public_key_t;
    typedef crypto::ecc::curve25519::shared_secret curve25519_shared_secret_t;
    typedef crypto::ecc::curve25519::google::donna::public_key donna_curve25519_public_key_t;
    typedef crypto::ecc::curve25519::msotoodeh::public_key mehdi_curve25519_public_key_t;
    enum ecc_algorithm_t {
        ecc_algorithm_none,
        ecc_algorithm_25519,
        next_ecc_algorithm,
        first_ecc_algorithm = (ecc_algorithm_none + 1),
        last_ecc_algorithm = (next_ecc_algorithm - 1)
    };

    typedef crypto::rsa::private_key_implements rsa_private_key_t;
    typedef crypto::rsa::public_key_implements rsa_public_key_t;

    typedef crypto::rsa::bn::key_generator bn_rsa_key_generator_t;
    typedef crypto::rsa::bn::private_key bn_rsa_private_key_t;
    typedef crypto::rsa::bn::public_key bn_rsa_public_key_t;

    typedef crypto::rsa::mp::key_generator mp_rsa_key_generator_t;
    typedef crypto::rsa::mp::private_key mp_rsa_private_key_t;
    typedef crypto::rsa::mp::public_key mp_rsa_public_key_t;

    enum bitsof_t {
        bitsof_none,
        bitsof_prime,
        bitsof_rsa,
        next_bitsof,
        first_bitsof = (bitsof_none + 1),
        last_bitsof = (next_bitsof - 1)
    };

    enum generate_t {
        generate_none,
        generate_miller_rabin,
        generate_prime,
        generate_rsa,
        generate_ecc,
        next_generate,
        first_generate = (generate_none + 1),
        last_generate = (next_generate - 1)
    };

    enum number_t {
        number_none,
        number_bn,
        number_mp,
        next_number,
        first_number = (number_none + 1),
        last_number = (next_number - 1)
    };

    typedef unsigned pseudo_random_seed_t;
    typedef crypto::random::pseudo pseudo_random_t;
    typedef crypto::random::generator random_generator_t;
    typedef random_generator_t& (Derives::*get_random_generator_t)();

    typedef int (Derives::*run_t)(int argc, char_t** argv, char_t** env);

    typedef int (Derives::*run_ecc_25519_exchange_t)
    (random_generator_t& r,
     const curve25519_secret_key_t& sk, const curve25519_secret_key_t& sk2,
     const curve25519_public_key_t& pk, const curve25519_public_key_t& pk2,
     const curve25519_shared_secret_t& s, const curve25519_shared_secret_t& s2,
     int argc, char_t** argv, char_t** env);

    typedef int (Derives::*run_generate_prime_t)
    (unsigned bytes, byte_array& b, crypto::random::pseudo& ps,
     int argc, char_t** argv, char_t** env);

    typedef int (Derives::*run_generate_rsa_t)
    (size_t modbytes, const byte_t* exponent, size_t expbytes, size_t pbytes,
     crypto::random::reader& ps, int argc, char_t** argv, char_t** env);

    typedef int (Derives::*run_rsa_exchange_t)
    (rsa_public_key_t& pub, rsa_private_key_t& prv,
     int argc, char_t** argv, char_t** env);

protected:
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if ((run_)) {
            err = (this->*run_)(argc, argv, env);
        } else {
            err = this->usage(argc, argv, env);
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_generate_rsa(int argc, char_t** argv, char_t** env) {
        int err = 0;
        size_t modbytes = ((rsa_modulus_bits_ + 7) >> 3);
        size_t expbytes = ((rsa_exponent_bits_ + 7) >> 3);
        size_t pbytes = (modbytes >> 1);
        unsigned seed = pseudo_random_seed_;
        crypto::random::pseudo ps(seed);
        crypto::byte_array _exponent(rsa_exponent_, expbytes);
		byte_t* exponent = _exponent.elements();
        if ((run_generate_rsa_)) {
            err = (this->*run_generate_rsa_)
            (modbytes, exponent, expbytes, pbytes, ps, argc, argv, env);
        } else {
            err = this->run_bn_generate_rsa
            (modbytes, exponent, expbytes, pbytes, ps, argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_mp_generate_rsa
    (size_t modbytes, const byte_t* exponent, size_t expbytes, size_t pbytes,
     crypto::random::reader& ps, int argc, char_t** argv, char_t** env) {
        int err = 0;
        mp_rsa_public_key_t pub(modbytes, expbytes);
        mp_rsa_private_key_t prv(pbytes);
        mp_rsa_key_generator_t kg(this);
        if ((kg.generate(prv, pub, modbytes, exponent, expbytes, ps))) {
            err = run_rsa_exchange(pub, prv, argc, argv, env);
        } else {
            errln("failed on generate()");
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_bn_generate_rsa
    (size_t modbytes, const byte_t* exponent, size_t expbytes, size_t pbytes,
     crypto::random::reader& ps, int argc, char_t** argv, char_t** env) {
        int err = 0;
        bn_rsa_public_key_t pub(modbytes, expbytes);
        bn_rsa_private_key_t prv(pbytes);
        bn_rsa_key_generator_t kg(this);
        if ((kg.generate(prv, pub, modbytes, exponent, expbytes, ps))) {
            err = run_rsa_exchange(pub, prv, argc, argv, env);
        } else {
            errln("failed on generate()");
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_mp_rsa_test(int argc, char_t** argv, char_t** env) {
        int err = 0;
        size_t modbytes = sizeof(rsa_public_modulus);
        size_t expbytes = sizeof(rsa_public_exponent);
        size_t pbytes = sizeof(rsa_private_p);
        mp_rsa_public_key_t pub
        (rsa_public_modulus, modbytes,
         rsa_public_exponent, expbytes);
        mp_rsa_private_key_t prv
        (rsa_private_p, rsa_private_q,
         rsa_private_dmp1, rsa_private_dmq1,
         rsa_private_iqmp, pbytes);
        err = run_rsa_exchange(pub, prv, argc, argv, env);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_bn_rsa_test(int argc, char_t** argv, char_t** env) {
        int err = 0;
        size_t modbytes = sizeof(rsa_public_modulus);
        size_t expbytes = sizeof(rsa_public_exponent);
        size_t pbytes = sizeof(rsa_private_p);
        bn_rsa_public_key_t pub
        (rsa_public_modulus, modbytes,
         rsa_public_exponent, expbytes);
        bn_rsa_private_key_t prv
        (rsa_private_p, rsa_private_q,
         rsa_private_dmp1, rsa_private_dmq1,
         rsa_private_iqmp, pbytes);
        err = run_rsa_exchange(pub, prv, argc, argv, env);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_rsa_exchange
    (rsa_public_key_t& pub, rsa_private_key_t& prv,
     int argc, char_t** argv, char_t** env) {
        int err = 0;
        if ((run_rsa_exchange_)) {
            err = (this->*run_rsa_exchange_)
            (pub, prv, argc, argv, env);
        } else {
            err = this->run_rsa_test_exchange
            (pub, prv, argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_rsa_generate_exchange
    (rsa_public_key_t& pub, rsa_private_key_t& prv,
     int argc, char_t** argv, char_t** env) {
        int err = 0;
        size_t modbytes = pub.modbytes();
        byte_array
            plain(modbytes),
            encipher(modbytes),
            decipher(modbytes);
        byte_t *inb, *outb;
        if ((plain.set(0x12, modbytes))) {
            if ((inb = plain.elements()) && (outb = encipher.elements())) {
                if (modbytes == (pub(outb, modbytes, inb, modbytes))) {
                    if ((inb = encipher.elements()) && (outb = decipher.elements())) {
                        if (modbytes == (prv(outb, modbytes, inb, modbytes))) {
                            if ((inb = plain.elements())) {
                                if ((bytes_t::compare(outb, inb, modbytes))) {
                                    errln("failed plain->public->private != plain");
                                    errxln(outb, modbytes);
                                    errxln(inb, modbytes);
                                    err = 1;
                                } else {
                                    if ((outb = encipher.elements())) {
                                        if (modbytes == (prv(outb, modbytes, inb, modbytes))) {
                                            if ((inb = encipher.elements()) && (outb = decipher.elements())) {
                                                if (modbytes == (pub(outb, modbytes, inb, modbytes))) {
                                                    if ((inb = plain.elements())) {
                                                        if ((bytes_t::compare(outb, inb, modbytes))) {
                                                            errln("failed plain->private->public != plain");
                                                            errxln(outb, modbytes);
                                                            errxln(inb, modbytes);
                                                            err = 1;
                                                        } else {
                                                            err = this->run_rsa_exchange_output
                                                            (pub, prv, argc, argv, env);
                                                        }
                                                    }
                                                }
                                            }
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
    virtual int run_rsa_test_exchange
    (rsa_public_key_t& pub, rsa_private_key_t& prv,
     int argc, char_t** argv, char_t** env) {
        int err = 0;
        size_t modbytes = pub.modbytes();
        byte_array
            plain(modbytes),
            encipher(modbytes),
            decipher(modbytes);
        byte_t *inb, *outb;
        if ((plain.set(0x12, modbytes))) {
            if ((inb = plain.elements()) && (outb = encipher.elements())) {
                outln("plain");
                outxln(inb, modbytes);
                if (modbytes == (pub(outb, modbytes, inb, modbytes))) {
                    outln("public");
                    outxln(outb, modbytes);
                    if ((inb = encipher.elements()) && (outb = decipher.elements())) {
                        if (modbytes == (prv(outb, modbytes, inb, modbytes))) {
                            outln("private");
                            outxln(outb, modbytes);
                            if ((inb = plain.elements())) {
                                if ((bytes_t::compare(outb, inb, modbytes))) {
                                    this->err("failed ");
                                    errx(outb, modbytes);
                                    this->err(" != ");
                                    errxln(inb, modbytes);
                                    err = 1;
                                } else {
                                    if ((outb = encipher.elements())) {
                                        if (modbytes == (prv(outb, modbytes, inb, modbytes))) {
                                            outln("private");
                                            outxln(outb, modbytes);
                                            if ((inb = encipher.elements()) && (outb = decipher.elements())) {
                                                if (modbytes == (pub(outb, modbytes, inb, modbytes))) {
                                                    outln("public");
                                                    outxln(outb, modbytes);
                                                    if ((inb = plain.elements())) {
                                                        if ((bytes_t::compare(outb, inb, modbytes))) {
                                                            this->err("failed ");
                                                            errx(outb, modbytes);
                                                            this->err(" != ");
                                                            errxln(inb, modbytes);
                                                            err = 1;
                                                        }
                                                    }
                                                }
                                            }
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
    virtual int run_rsa_exchange_output
    (rsa_public_key_t& pub, rsa_private_key_t& prv,
     int argc, char_t** argv, char_t** env) {
        int err = 0;
        size_t modbytes = pub.modbytes();
        size_t expbytes = pub.expbytes();
        size_t pbytes = prv.pbytes();
        byte_array _b(modbytes);
		byte_t* b = _b.elements();
        if (expbytes == (pub.get_exponent_msb(b, modbytes))) {
            out("rsa-exponent: 0x"); outxln(b, expbytes);
        }
        if (modbytes == (pub.get_modulus_msb(b, modbytes))) {
            out(" rsa-modulus: 0x"); outxln(b, modbytes);
        }
        if (pbytes == (prv.get_p_msb(b, pbytes))) {
            out("       rsa-p: 0x"); outxln(b, pbytes);
        }
        if (pbytes == (prv.get_q_msb(b, pbytes))) {
            out("       rsa-q: 0x"); outxln(b, pbytes);
        }
        if (pbytes == (prv.get_dmp1_msb(b, pbytes))) {
            out("    rsa-dmp1: 0x"); outxln(b, pbytes);
        }
        if (pbytes == (prv.get_dmq1_msb(b, pbytes))) {
            out("    rsa-dmq1: 0x"); outxln(b, pbytes);
        }
        if (pbytes == (prv.get_iqmp_msb(b, pbytes))) {
            out("    rsa-iqmp: 0x"); outxln(b, pbytes);
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_generate_prime(int argc, char_t** argv, char_t** env) {
        int err = 1;
        unsigned seed = pseudo_random_seed_;
        unsigned bits = prime_bits_;
        unsigned bytes = ((bits + 7) >> 3);
        byte_array b(bytes);
        crypto::random::pseudo ps(seed);
        if ((run_generate_prime_)) {
            err = (this->*run_generate_prime_)(bytes, b, ps, argc, argv, env);
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_generate_mp_prime
    (unsigned bytes, byte_array& _b, crypto::random::pseudo& ps,
     int argc, char_t** argv, char_t** env) {
        int err = 0;
		byte_t* b = _b.elements();
        crypto::random::prime::mp::number n(0);
        crypto::random::prime::mp::generator g(this);
        if ((g.create())) {
            g.generate(n, bytes, ps);
            g.destroy();
            if (bytes == (n.to_msb(b, bytes))) {
                outxln(b, bytes);
            }
        }
        return err;
    }
    virtual int run_miller_rabin_mp_prime
    (unsigned bytes, byte_array& _b, crypto::random::pseudo& ps,
     int argc, char_t** argv, char_t** env) {
        int err = 0;
		byte_t* b = _b.elements();
        crypto::random::prime::mp::number n(0);
        crypto::random::prime::mp::reader r(this);
        crypto::random::prime::mp::miller_rabin mr(this);
        if ((mr.create())) {
            do {
                if (bytes != (r.read_msb(n, bytes, ps))) {
                    break;
                }
            } while (!(mr.probably_prime(n, bytes, ps)));
            mr.destroy();
            if (bytes == (n.to_msb(b, bytes))) {
                outxln(b, bytes);
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_generate_bn_prime
    (unsigned bytes, byte_array& _b, crypto::random::pseudo& ps,
     int argc, char_t** argv, char_t** env) {
        int err = 0;
		byte_t* b = _b.elements();
        crypto::random::prime::bn::number n(0);
        crypto::random::prime::bn::generator g(this);
        if ((g.create())) {
            g.generate(n, bytes, ps);
            g.destroy();
            if (bytes == (n.to_msb(b, bytes))) {
                outxln(b, bytes);
            }
        }
        return err;
    }
    virtual int run_miller_rabin_bn_prime
    (unsigned bytes, byte_array& _b, crypto::random::pseudo& ps,
     int argc, char_t** argv, char_t** env) {
        int err = 0;
		byte_t* b = _b.elements();
        crypto::random::prime::bn::number n(0);
        crypto::random::prime::bn::reader r(this);
        crypto::random::prime::bn::miller_rabin mr(this);
        if ((mr.create())) {
            do {
                if (bytes != (r.read_msb(n, bytes, ps))) {
                    break;
                }
            } while (!(mr.probably_prime(n, bytes, ps)));
            mr.destroy();
            if (bytes == (n.to_msb(b, bytes))) {
                outxln(b, bytes);
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ssize_t on_read(crypto::random::prime::mp::BIGPRIME* n, size_t bytes) {
        err(".", 1);
        return bytes;
    }
    virtual ssize_t on_read(crypto::random::prime::bn::BIGPRIME* n, size_t bytes) {
        err(".", 1);
        return bytes;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual run_t set_generate(generate_t to) {
        switch (generate_ = to) {
        case generate_miller_rabin:
            run_ = &Derives::run_generate_prime;
            run_generate_prime_ = &Derives::run_miller_rabin_bn_prime;
            bitsof_ = bitsof_prime;
            break;
        case generate_prime:
            run_ = &Derives::run_generate_prime;
            run_generate_prime_ = &Derives::run_generate_bn_prime;
            bitsof_ = bitsof_prime;
            break;
        case generate_rsa:
            run_ = &Derives::run_generate_rsa;
            run_generate_rsa_ = &Derives::run_bn_generate_rsa;
            run_rsa_exchange_ = &Derives::run_rsa_generate_exchange;
            bitsof_ = bitsof_rsa;
            break;
        case generate_ecc:
            run_ = &Derives::run_ecc_25519;
            run_ecc_25519_ = 0;
            run_ecc_25519_exchange_ = 0;
            bitsof_ = bitsof_none;
            break;
        default:
            run_ = 0;
            break;
        }
        return run_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual number_t set_number(number_t to) {
        number_t number = number_none;
        switch(generate_) {
        case generate_miller_rabin:
            switch(to) {
            case number_bn:
                run_generate_prime_ = &Derives::run_miller_rabin_bn_prime;
                number = to;
                break;
            case number_mp:
                run_generate_prime_ = &Derives::run_miller_rabin_mp_prime;
                number = to;
                break;
            }
            break;
        case generate_prime:
            switch(to) {
            case number_bn:
                run_generate_prime_ = &Derives::run_generate_bn_prime;
                number = to;
                break;
            case number_mp:
                run_generate_prime_ = &Derives::run_generate_mp_prime;
                number = to;
                break;
            }
            break;
        case generate_rsa:
            switch(to) {
            case number_bn:
                run_generate_rsa_ = &Derives::run_bn_generate_rsa;
                number = to;
                break;
            case number_mp:
                run_generate_rsa_ = &Derives::run_mp_generate_rsa;
                number = to;
                break;
            }
            break;
        }
        return number;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_ecc_25519(int argc, char_t** argv, char_t** env) {
        int err = 0;
        if ((run_ecc_25519_)) {
            err = (this->*run_ecc_25519_)(argc, argv, env);
        } else {
            err = run_ecc_25519_donna(argc, argv, env);
        }
        return err;
    }
    virtual int run_ecc_25519_donna(int argc, char_t** argv, char_t** env) {
        int err = 0;
        random_generator_t& r = get_random_generator();
        curve25519_base_point_t bp;
        curve25519_secret_key_t sk(r), sk2(r);
        donna_curve25519_public_key_t pk(sk, bp), pk2(sk2, bp);
        curve25519_shared_secret_t s(sk, pk2), s2(sk2, pk);
        err = run_ecc_25519_exchange
        (r, sk, sk2, pk, pk2, s, s2, argc, argv, env);
        return err;
    }
    virtual int run_ecc_25519_mehdi(int argc, char_t** argv, char_t** env) {
        int err = 0;
        random_generator_t& r = get_random_generator();
        curve25519_base_point_t bp;
        curve25519_secret_key_t sk(r), sk2(r);
        mehdi_curve25519_public_key_t pk(sk, bp), pk2(sk2, bp);
        curve25519_shared_secret_t s(sk, pk2), s2(sk2, pk);
        err = run_ecc_25519_exchange
        (r, sk, sk2, pk, pk2, s, s2, argc, argv, env);
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_ecc_25519_exchange
    (random_generator_t& r,
     const curve25519_secret_key_t& sk, const curve25519_secret_key_t& sk2,
     const curve25519_public_key_t& pk, const curve25519_public_key_t& pk2,
     const curve25519_shared_secret_t& s, const curve25519_shared_secret_t& s2,
     int argc, char_t** argv, char_t** env) {
        int err = 0;
        if ((run_ecc_25519_exchange_)) {
            err = (this->*run_ecc_25519_exchange_)
            (r, sk, sk2, pk, pk2, s, s2, argc, argv, env);
        } else {
            err = run_ecc_25519_exchange_test
            (r, sk, sk2, pk, pk2, s, s2, argc, argv, env);
        }
        return err;
    }
    virtual int run_ecc_25519_exchange_test
    (random_generator_t& r,
     const curve25519_secret_key_t& sk, const curve25519_secret_key_t& sk2,
     const curve25519_public_key_t& pk, const curve25519_public_key_t& pk2,
     const curve25519_shared_secret_t& s, const curve25519_shared_secret_t& s2,
     int argc, char_t** argv, char_t** env) {
        int err = 0;

        out("private-key1: 0x"); outxln(sk.elements(), sk.size());
        out(" public-key1: 0x"); outxln(pk.elements(), pk.size());
        out("     secret1: 0x"); outxln(s.elements(), s.size());
        outln();

        out("private-key2: 0x"); outxln(sk2.elements(), sk2.size());
        out(" public-key2: 0x"); outxln(pk2.elements(), pk2.size());
        out("     secret2: 0x"); outxln(s2.elements(), s2.size());
        outln();

        if ((bytes_t::compare(s.elements(), s2.elements(), s.length()))) {
            errln("failed secret1 != secret2");
            return 1;
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ecc_algorithm_t set_ecc_algorithm(ecc_algorithm_t to) {
        switch (generate_) {
        case generate_ecc:
            switch (ecc_algorithm_ = to) {
            case ecc_algorithm_25519:
                run_ = &Derives::run_ecc_25519;
                run_ecc_25519_ = 0;
                run_ecc_25519_exchange_ = 0;
                break;
            default:
                run_ = 0;
                break;
            }
            break;
        default:
            run_ = 0;
            break;
        }
        return ecc_algorithm_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_aes_test(int argc, char_t** argv, char_t** env) {
        static byte_t cbc_key[8*3] = {
            0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,
            0xf1,0xe0,0xd3,0xc2,0xb5,0xa4,0x97,0x86,
            0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10
        };
        static byte_t cbc_iv[8*2] = {
            0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,
            0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef
        };
        static byte_t plain_text[8*4] = {
            0x37,0x36,0x35,0x34,0x33,0x32,0x31,0x20,
            0x4E,0x6F,0x77,0x20,0x69,0x73,0x20,0x74,
            0x68,0x65,0x20,0x74,0x69,0x6D,0x65,0x20,
            0x66,0x6F,0x72,0x20,0x00,0x31,0x00,0x00
        };
        byte_t encipher_text[8*4] = {0};
        byte_t decipher_text[8*4] = {0};
        ssize_t length = 0;
        int err = 0;

        outln("aes");
        out("   plain-text: 0x"); outxln(plain_text, sizeof(plain_text));

        if ((encipher_text)) {
            aes_t cbc(cbc_key, sizeof(cbc_key), cbc_iv, sizeof(cbc_iv));

            if (0 < (length = cbc.encrypt
                (encipher_text, sizeof(encipher_text), plain_text, sizeof(plain_text)))) {
                out("  cipher-text: 0x"); outxln(encipher_text, length);
            } else {
                errln("failed on encrypt()");
                return 1;
            }
        }
        if ((decipher_text) && (length)) {
            aes_t cbc(cbc_key, sizeof(cbc_key), cbc_iv, sizeof(cbc_iv));

            if (sizeof(plain_text) <= (length = cbc.decrypt
                (decipher_text, sizeof(decipher_text), encipher_text, length))) {
                out("decipher-text: 0x"); outxln(decipher_text, length);
                if ((bytes_t::compare(decipher_text, plain_text, sizeof(plain_text)))) {
                    errln("decipher_text != plain_text");
                    return 1;
                }
            } else {
                errln("failed on decrypt()");
                return 1;
            }
        }
        outln();
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_des3_test(int argc, char_t** argv, char_t** env) {
        static unsigned char cbc_key [8*3]={
            0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,
            0xf1,0xe0,0xd3,0xc2,0xb5,0xa4,0x97,0x86,
            0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10
        };
        static unsigned char cbc_iv [8]={
            0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10
        };
        static unsigned char plain_text[32]={
            0x37,0x36,0x35,0x34,0x33,0x32,0x31,0x20,
            0x4E,0x6F,0x77,0x20,0x69,0x73,0x20,0x74,
            0x68,0x65,0x20,0x74,0x69,0x6D,0x65,0x20,
            0x66,0x6F,0x72,0x20,0x00,0x00,0x00,0x00
        };
        static unsigned char cipher_text[32]={
            0x3F,0xE3,0x01,0xC9,0x62,0xAC,0x01,0xD0,
            0x22,0x13,0x76,0x3C,0x1C,0xBD,0x4C,0xDC,
            0x79,0x96,0x57,0xC0,0x64,0xEC,0xF5,0xD4,
            0x1C,0x67,0x38,0x12,0xCF,0xDE,0x96,0x75
        };
        byte_t encipher_text[32] = {0};
        byte_t decipher_text[32] = {0};
        ssize_t length = 0;
        int err = 0;

        outln("des3");
        out("   plain-text: 0x"); outxln(plain_text, sizeof(plain_text));

        if ((encipher_text)) {
            des3_t cbc(cbc_key, sizeof(cbc_key), cbc_iv, sizeof(cbc_iv));

            if (0 < (length = cbc.encrypt
                (encipher_text, sizeof(encipher_text), plain_text, sizeof(plain_text)))) {
                out("  cipher-text: 0x"); outxln(encipher_text, length);
                if ((bytes_t::compare(encipher_text, cipher_text, sizeof(cipher_text)))) {
                    errln("encipher_text != cipher_text");
                    return 1;
                }
            } else {
                errln("failed on encrypt()");
                return 1;
            }
        }
        if ((decipher_text) && (length)) {
            des3_t cbc(cbc_key, sizeof(cbc_key), cbc_iv, sizeof(cbc_iv));

            if (sizeof(plain_text) <= (length = cbc.decrypt
                (decipher_text, sizeof(decipher_text), encipher_text, length))) {
                out("decipher-text: 0x"); outxln(decipher_text, length);
                if ((bytes_t::compare(decipher_text, plain_text, sizeof(plain_text)))) {
                    errln("decipher_text != plain_text");
                    return 1;
                }
            } else {
                errln("failed on decrypt()");
                return 1;
            }
        }
        outln();
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual cipher_algorithm_t set_cipher_algorithm(cipher_algorithm_t to) {
        switch (cipher_algorithm_ = to) {
        case cipher_algorithm_aes:
            run_ = &Derives::run_aes_test;
            break;
        case cipher_algorithm_des3:
            run_ = &Derives::run_des3_test;
            break;
        default:
            run_ = 0;
            break;
        }
        return cipher_algorithm_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int run_md5(int argc, char_t** argv, char_t** env) {
        int err = run_hash(md5_, argc, argv, env);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int run_sha1(int argc, char_t** argv, char_t** env) {
        int err = run_hash(sha1_, argc, argv, env);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int run_sha256(int argc, char_t** argv, char_t** env) {
        int err = run_hash(sha256_, argc, argv, env);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int run_sha512(int argc, char_t** argv, char_t** env) {
        int err = run_hash(sha512_, argc, argv, env);
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int run_hash(hash_t& hash, int argc, char_t** argv, char_t** env) {
        int err = 0;
        if ((argc > optind) && (argv[optind]) && (argv[optind][0])) {
            const string_t source(argv[optind]);
            err = hash_file(source, hash);
        } else {
            const char_t* chars = 0;
            size_t length = 0;
            if ((chars = plain_text(length))) {
                err = this->hash(hash, chars, length);
            } else {
                err = this->hash(hash, 0,0);
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int hash_file(const string_t& source, hash_t& hash) {
        const char_t* chars = 0;
        size_t length = 0;
        int err = 1;
        if ((chars = source.chars(length)) && (0 < length)) {
            source_file_t source_file;

            TALAS_LOG_MESSAGE_INFO("open source file \"" << chars << "\"...");
            if ((source_file.open(chars, source_file.mode_read_binary()))) {
                TALAS_LOG_MESSAGE_INFO("...opened source file \"" << chars << "\"");

                err = hash_file(source_file, hash);

                TALAS_LOG_MESSAGE_INFO("close source file \"" << chars << "\"...");
                if ((source_file.close())) {
                    TALAS_LOG_MESSAGE_INFO("...closed source file \"" << chars << "\"");
                } else {
                    TALAS_LOG_MESSAGE_INFO("...failed to close source file \"" << chars << "\"");
                }
            } else {
                TALAS_LOG_MESSAGE_ERROR("...failed to open source file \"" << chars << "\"");
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int hash_file(source_file_t& source, hash_t& hash) {
        int err = 1;
        if (0 <= (hash.initialize())) {
            err = 0;
            for (ssize_t count = 0, amount = 0; 0 <= amount; count += amount) {
                if (0 < (amount = source.read(block_, block_size_))) {
                    if (amount != (hash.hash(block_, amount))) {
                        err = 1;
                    } else {
                        continue;
                    }
                } else {
                    if (0 > (amount)) {
                        err = 1;
                    }
                }
                if (!(err)) {
                    if (0 < (count = hash.finalize(block_, block_size_))) {
                        outxln(block_, count);
                    } else {
                        err = 1;
                    }
                }
                break;
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int hash(hash_t& hash, const void* source, size_t length) {
        int err = 1;
        if (0 <= (hash.initialize())) {
            err = 0;
            ssize_t count = 0;
            if ((source) && (length)) {
                if (length != (hash.hash(source, length))) {
                    return err = 1;
                }
            }
            if (0 < (count = hash.finalize(block_, block_size_))) {
                outxln(block_, count);
            } else {
                err = 1;
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual hash_algorithm_t set_hash_algorithm(hash_algorithm_t to) {
        switch (hash_algorithm_ = to) {
        case hash_algorithm_md5:
            run_ = &Derives::run_md5;
            break;
        case hash_algorithm_sha1:
            run_ = &Derives::run_sha1;
            break;
        case hash_algorithm_sha256:
            run_ = &Derives::run_sha256;
            break;
        case hash_algorithm_sha512:
            run_ = &Derives::run_sha512;
            break;
        default:
            run_ = 0;
            break;
        }
        return hash_algorithm_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual random_generator_t& get_random_generator() {
        if ((get_random_generator_)) {
            return (this->*get_random_generator_)();
        }
        return get_pseudo_random();
    }
    virtual random_generator_t& get_pseudo_random() {
        pseudo_random_.seed(pseudo_random_seed_);
        return pseudo_random_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual bitsof_t set_bits(unsigned to) {
        switch (bitsof_) {
        case bitsof_prime:
            prime_bits_ = to;
            break;
        case bitsof_rsa:
            rsa_modulus_bits_ = to;
            break;
        default:
            return bitsof_none;
        }
        return bitsof_;
    }


    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual unsigned set_random_seed(unsigned to) {
        pseudo_random_seed_ = to;
        return pseudo_random_seed_;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char_t* set_plain_text(const char_t* chars) {
        plain_text_.assign(chars);
        chars = plain_text_.has_chars();
        return chars;
    }
    virtual const char_t* plain_text(size_t& length) const {
        const char_t* chars = plain_text_.has_chars(length);
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
#include "talas/app/console/talas/main_opt.cpp"

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    run_t run_, run_ecc_25519_;
    run_ecc_25519_exchange_t run_ecc_25519_exchange_;
    run_generate_rsa_t run_generate_rsa_;
    run_rsa_exchange_t run_rsa_exchange_;
    run_generate_prime_t run_generate_prime_;
    generate_t generate_;
    bitsof_t bitsof_;
    unsigned prime_bits_, rsa_modulus_bits_, rsa_exponent_bits_;
    uint32_t rsa_exponent_;
    get_random_generator_t get_random_generator_;
    pseudo_random_seed_t pseudo_random_seed_;
    pseudo_random_t pseudo_random_;
    ecc_algorithm_t ecc_algorithm_;
    hash_algorithm_t hash_algorithm_;
    cipher_algorithm_t cipher_algorithm_;
    aes_t aes_;
    des3_t des3_;
    md5_t md5_;
    sha1_t sha1_;
    sha256_t sha256_;
    sha512_t sha512_;
    size_t block_size_;
    char block_[TALAS_APP_CONSOLE_TALAS_MAIN_BLOCKSIZE];
    string_t plain_text_;
};

} // namespace talas 
} // namespace console 
} // namespace app 
} // namespace talas 

#endif // _TALAS_APP_CONSOLE_TALAS_MAIN_HPP 
