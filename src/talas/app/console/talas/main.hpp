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
#include "talas/crypto/ecc/curve25519/msotoodeh/public_key.hpp"
#include "talas/crypto/ecc/curve25519/google/donna/public_key.hpp"
#include "talas/crypto/ecc/curve25519/shared_secret.hpp"
#include "talas/crypto/ecc/curve25519/public_key.hpp"
#include "talas/crypto/ecc/curve25519/private_key.hpp"
#include "talas/crypto/ecc/curve25519/key.hpp"
#include "talas/crypto/ecc/curve25519/base_point.hpp"
#include "talas/crypto/cipher/devine/aes.hpp"
#include "talas/crypto/random/pseudo.hpp"
#include "thirdparty/gnu/glibc/stdlib/rand_r.h"
#include "talas/app/console/talas/main_opt.hpp"

#define TALAS_APP_CONSOLE_TALAS_MAIN_KB_BLOCKSIZE 64
#define TALAS_APP_CONSOLE_TALAS_MAIN_BLOCKSIZE (TALAS_APP_CONSOLE_TALAS_MAIN_KB_BLOCKSIZE*1024)

namespace talas {
namespace app {
namespace console {
namespace talas {

typedef crypto::console::main_implements main_implements;
typedef crypto::console::main main_extends;
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
    main()
    : run_(0),
      run_ecc_25519_(0),
      run_ecc_25519_exchange_(0),
      get_random_generator_(0),
      pseudo_random_seed_(0),
      pseudo_random_(pseudo_random_seed_),
      ecc_algorithm_(ecc_algorithm_none),
      hash_algorithm_(hash_algorithm_none),
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
    enum cipher_algorithm_t {
        cipher_algorithm_none,
        cipher_algorithm_aes,
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

        out("private-key1: "); outxln(sk.elements(), sk.size());
        out(" public-key1: "); outxln(pk.elements(), pk.size());
        out("     secret1: "); outxln(s.elements(), s.size());
        outln();

        out("private-key2: "); outxln(sk2.elements(), sk2.size());
        out(" public-key2: "); outxln(pk2.elements(), pk2.size());
        out("     secret2: "); outxln(s2.elements(), s2.size());
        outln();

        if ((bytes_t::compare(s, s2, s.length()))) {
            errln("failed secret1 != secret2");
            return 1;
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual ecc_algorithm_t set_ecc_algorithm(ecc_algorithm_t to) {
        switch (ecc_algorithm_ = to) {
        case ecc_algorithm_25519:
            run_ecc_25519_ = 0;
            run_ecc_25519_exchange_ = 0;
            run_ = &Derives::run_ecc_25519;
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

        out("   plain-text: "); outxln(plain_text, sizeof(plain_text));

        if ((encipher_text)) {
            aes_t cbc(cbc_key, sizeof(cbc_key), cbc_iv, sizeof(cbc_iv));

            if (0 < (length = cbc.encrypt
                (encipher_text, sizeof(encipher_text), plain_text, sizeof(plain_text)))) {
                out("  cipher-text: "); outxln(encipher_text, length);
            } else {
                errln("failed on encrypt()");
                return 1;
            }
        }
        if ((decipher_text) && (length)) {
            aes_t cbc(cbc_key, sizeof(cbc_key), cbc_iv, sizeof(cbc_iv));

            if (sizeof(plain_text) <= (length = cbc.decrypt
                (decipher_text, sizeof(decipher_text), encipher_text, length))) {
                out("decipher-text: "); outxln(decipher_text, length);
                if ((bytes_t::compare(decipher_text, plain_text, sizeof(plain_text)))) {
                    errln("decipher_text != plain_text");
                    return 1;
                }
            } else {
                errln("failed on decrypt()");
                return 1;
            }
        }
        return err;
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
            err = this->hash(hash, 0,0);
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
#include "talas/app/console/talas/main_opt.cpp"

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
protected:
    run_t run_, run_ecc_25519_;
    run_ecc_25519_exchange_t run_ecc_25519_exchange_;
    get_random_generator_t get_random_generator_;
    pseudo_random_seed_t pseudo_random_seed_;
    pseudo_random_t pseudo_random_;
    ecc_algorithm_t ecc_algorithm_;
    hash_algorithm_t hash_algorithm_;
    md5_t md5_;
    sha1_t sha1_;
    sha256_t sha256_;
    sha512_t sha512_;
    size_t block_size_;
    char block_[TALAS_APP_CONSOLE_TALAS_MAIN_BLOCKSIZE];
};

} // namespace talas 
} // namespace console 
} // namespace app 
} // namespace talas 

#endif // _TALAS_APP_CONSOLE_TALAS_MAIN_HPP 
