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
///   File: main_opt.cpp
///
/// Author: $author$
///   Date: 11/18/2014
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_APP_CONSOLE_TALAS_MAIN_OPT_CPP
#define _TALAS_APP_CONSOLE_TALAS_MAIN_OPT_CPP

#ifndef _TALAS_APP_CONSOLE_TALAS_MAIN_HPP
#include "talas/app/console/talas/main_opt.hpp"
namespace talas {
namespace app {
namespace console {
namespace talas {
class _EXPORT_CLASS main {
protected:
#endif // _TALAS_APP_CONSOLE_TALAS_MAIN_HPP

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_ecc_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            if ((!(optarg[1]) && (TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTARG_25519_C[0] == (optarg[0])))
                || !(chars_t::compare(optarg, TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTARG_25519_S))) {
                set_ecc_algorithm(ecc_algorithm_25519);
            } else {
                err = on_invalid_option_arg
                (optval, optarg, optname, optind, argc, argv, env);
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_cipher_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            if ((!(optarg[1]) && (TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG_AES_C[0] == (optarg[0])))
                || !(chars_t::compare(optarg, TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG_AES_S))) {
                set_cipher_algorithm(cipher_algorithm_aes);
            } else {
                if ((!(optarg[1]) && (TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG_DES3_C[0] == (optarg[0])))
                    || !(chars_t::compare(optarg, TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG_DES3_S))) {
                    set_cipher_algorithm(cipher_algorithm_des3);
                } else {
                    err = on_invalid_option_arg
                    (optval, optarg, optname, optind, argc, argv, env);
                }
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_hash_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            if ((!(optarg[1]) && (TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_MD5_C[0] == (optarg[0])))
                || !(chars_t::compare(optarg, TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_MD5_S))) {
                set_hash_algorithm(hash_algorithm_md5);
            } else {
                if ((!(optarg[1]) && (TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA1_C[0] == (optarg[0])))
                    || !(chars_t::compare(optarg, TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA1_S))) {
                    set_hash_algorithm(hash_algorithm_sha1);
                } else {
                    if ((!(optarg[1]) && (TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA256_C[0] == (optarg[0])))
                        || !(chars_t::compare(optarg, TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA256_S))) {
                        set_hash_algorithm(hash_algorithm_sha256);
                    } else {
                        if ((!(optarg[1]) && (TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA512_C[0] == (optarg[0])))
                            || !(chars_t::compare(optarg, TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA512_S))) {
                            set_hash_algorithm(hash_algorithm_sha512);
                        } else {
                            err = on_invalid_option_arg
                            (optval, optarg, optname, optind, argc, argv, env);
                        }
                    }
                }
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_encrypt_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_decrypt_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_generate_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            if ((!(optarg[1]) && (TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_MILLER_RABIN_C[0] == (optarg[0])))
                || !(chars_t::compare(optarg, TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_MILLER_RABIN_S))) {
                set_generate(generate_miller_rabin);
            } else {
                if ((!(optarg[1]) && (TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_PRIME_C[0] == (optarg[0])))
                    || !(chars_t::compare(optarg, TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_PRIME_S))) {
                    set_generate(generate_prime);
                } else {
                    if ((!(optarg[1]) && (TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_RSA_C[0] == (optarg[0])))
                        || !(chars_t::compare(optarg, TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_RSA_S))) {
                        set_generate(generate_rsa);
                    } else {
                        if ((!(optarg[1]) && (TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_ECC_25519_C[0] == (optarg[0])))
                            || !(chars_t::compare(optarg, TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_ECC_25519_S))) {
                            set_generate(generate_ecc);
                        } else {
                            err = on_invalid_option_arg
                            (optval, optarg, optname, optind, argc, argv, env);
                        }
                    }
                }
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_sign_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_key_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_iv_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_random_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_random_seed_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        unsigned value = 0;
        if ((optarg) && (optarg[0])) {
            if (0 <= (value = (chars_t::to_unsigned(optarg)))) {
                set_random_seed(value);
            } else {
                err = on_invalid_option_arg
                (optval, optarg, optname, optind, argc, argv, env);
            }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_plain_text_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            set_plain_text(optarg);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_number_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        if ((optarg) && (optarg[0])) {
            if ((!(optarg[1]) && (TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG_BN_C[0] == (optarg[0])))
                || !(chars_t::compare(optarg, TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG_BN_S))) {
                set_number(number_bn);
            } else {
                if ((!(optarg[1]) && (TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG_MP_C[0] == (optarg[0])))
                    || !(chars_t::compare(optarg, TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG_MP_S))) {
                    set_number(number_mp);
                } else {
                    err = on_invalid_option_arg
                    (optval, optarg, optname, optind, argc, argv, env);
                }
             }
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual int on_bits_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        unsigned value = 0;
        if ((optarg) && (optarg[0])) {
            if (0 < (value = (chars_t::to_unsigned(optarg)))) {
                set_bits(value);
            } else {
                err = on_invalid_option_arg
                (optval, optarg, optname, optind, argc, argv, env);
            }
        }
        return err;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual int on_option
    (int optval, const char* optarg,
     const char* optname, int optind,
     int argc, char**argv, char**env) {
        int err = 0;
        switch(optval) {
        case TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTVAL_C:
            err = on_ecc_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTVAL_C:
            err = on_cipher_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTVAL_C:
            err = on_hash_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPTVAL_C:
            err = on_encrypt_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPTVAL_C:
            err = on_decrypt_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTVAL_C:
            err = on_generate_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPTVAL_C:
            err = on_sign_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPTVAL_C:
            err = on_key_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPTVAL_C:
            err = on_iv_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPTVAL_C:
            err = on_random_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPTVAL_C:
            err = on_random_seed_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPTVAL_C:
            err = on_plain_text_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTVAL_C:
            err = on_number_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPTVAL_C:
            err = on_bits_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        default:
            err = Extends::on_option
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char* option_usage
    (const char*& optarg, const struct option* longopt) {
        const char* chars = "";
        switch(longopt->val) {
        case TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTARG;
            chars = TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG;
            chars = TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG;
            chars = TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPTARG;
            chars = TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPTARG;
            chars = TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG;
            chars = TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPTARG;
            chars = TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPTARG;
            chars = TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPTARG;
            chars = TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPTARG;
            chars = TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPTARG;
            chars = TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPTARG;
            chars = TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG;
            chars = TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTUSE;
            break;
        case TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPTVAL_C:
            optarg = TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPTARG;
            chars = TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPTUSE;
            break;
        default:
            chars = Extends::option_usage(optarg, longopt);
        }
        return chars;
    }
    ///////////////////////////////////////////////////////////////////////
    virtual const char* options(const struct option*& longopts) {
        int err = 0;
        static const char* chars = TALAS_APP_CONSOLE_TALAS_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            TALAS_APP_CONSOLE_TALAS_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    virtual const char* arguments(const char**& args) {
        static const char* _args = TALAS_APP_CONSOLE_TALAS_MAIN_ARGS;
        static const char* _argv[3] = {
            TALAS_APP_CONSOLE_TALAS_MAIN_ARGV
            0};
        args = _argv;
        return _args;
    }

#ifndef _TALAS_APP_CONSOLE_TALAS_MAIN_HPP
};

} // namespace talas
} // namespace console 
} // namespace app 
} // namespace talas 
#endif // _TALAS_APP_CONSOLE_TALAS_MAIN_HPP

#endif // _TALAS_APP_CONSOLE_TALAS_MAIN_OPT_CPP 
