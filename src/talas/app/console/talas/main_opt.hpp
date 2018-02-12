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
///   File: main_opt.hpp
///
/// Author: $author$
///   Date: 11/18/2014
///////////////////////////////////////////////////////////////////////
#ifndef _TALAS_APP_CONSOLE_TALAS_MAIN_OPT_HPP
#define _TALAS_APP_CONSOLE_TALAS_MAIN_OPT_HPP

#include "talas/console/main.hpp"
#include "talas/console/main_opt.hpp"

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPT "ecc"
#define TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTARG_25519_C "9"
#define TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTARG_25519_S "25519"
#define TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTARG "{ " \
    "(" TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTARG_25519_C ")" \
        TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTARG_25519_S \
    " }"
#define TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTUSE ""
#define TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTVAL_S "c:"
#define TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTVAL_C 'c'
#define TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTION \
   {TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPT "cipher"
#define TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG_AES_C "a"
#define TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG_AES_S "aes"
#define TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG_DES3_C "d"
#define TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG_DES3_S "des3"
#define TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG "{ " \
    "(" TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG_AES_C ")" \
        TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG_AES_S \
    " | (" TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG_DES3_C ")" \
           TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG_DES3_S \
    " }"
#define TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTUSE ""
#define TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTVAL_S "i:"
#define TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTVAL_C 'i'
#define TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTION \
   {TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPT "hash"
#define TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_MD5_C "m"
#define TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_MD5_S "md5"
#define TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA1_C "1"
#define TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA1_S "sha1"
#define TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA256_C "2"
#define TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA256_S "sha256"
#define TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA512_C "5"
#define TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA512_S "sha512"
#define TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG "{ " \
    "(" TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_MD5_C ")" \
        TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_MD5_S \
    " | (" TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA1_C ")" \
           TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA1_S \
    " | (" TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA256_C ")" \
           TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA256_S \
    " | (" TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA512_C ")" \
           TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_SHA512_S \
    " }"
#define TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTUSE ""
#define TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTVAL_S "h:"
#define TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTVAL_C 'h'
#define TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTION \
   {TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPT "encrypt"
#define TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPTARG ""
#define TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPTUSE ""
#define TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPTVAL_S "e:"
#define TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPTVAL_C 'e'
#define TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPTION \
   {TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPT "decrypt"
#define TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPTARG ""
#define TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPTUSE ""
#define TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPTVAL_S "d:"
#define TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPTVAL_C 'd'
#define TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPTION \
   {TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPT "generate"
#define TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_ECC_25519_C "e"
#define TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_ECC_25519_S "ecc"
#define TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_RSA_C "r"
#define TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_RSA_S "rsa"
#define TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_PRIME_C "p"
#define TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_PRIME_S "prime"
#define TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_MILLER_RABIN_C "m"
#define TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_MILLER_RABIN_S "miller-rabin"
#define TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG "{ " \
    "(" TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_ECC_25519_C ")" \
        TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_ECC_25519_S \
    " | " "(" TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_RSA_C ")" \
              TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_RSA_S \
    " | " "(" TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_PRIME_C ")" \
              TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_PRIME_S \
    " | " "(" TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_MILLER_RABIN_C ")" \
              TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_MILLER_RABIN_S \
    " }"
#define TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTUSE ""
#define TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTVAL_S "g:"
#define TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTVAL_C 'g'
#define TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTION \
   {TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPT "sign"
#define TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPTARG ""
#define TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPTUSE ""
#define TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPTVAL_S "n:"
#define TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPTVAL_C 'n'
#define TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPTION \
   {TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPT "key"
#define TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPTARG ""
#define TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPTUSE ""
#define TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPTVAL_S "k:"
#define TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPTVAL_C 'k'
#define TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPTION \
   {TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPT "iv"
#define TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPTARG ""
#define TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPTUSE ""
#define TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPTVAL_S "v:"
#define TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPTVAL_C 'v'
#define TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPTION \
   {TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPT "random"
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPTARG ""
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPTUSE ""
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPTVAL_S "r:"
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPTVAL_C 'r'
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPTION \
   {TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPT "bits"
#define TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPTARG "n"
#define TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPTUSE "Number of bits"
#define TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPTVAL_S "b:"
#define TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPTVAL_C 'b'
#define TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPTION \
   {TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPT "number"
#define TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG_BN_C "b"
#define TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG_BN_S "bn"
#define TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG_MP_C "m"
#define TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG_MP_S "mp"
#define TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG "{ " \
    "(" TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG_BN_C ")" \
        TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG_BN_S \
    " | (" TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG_MP_C ")" \
           TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG_MP_S \
    " }"
#define TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTUSE ""
#define TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTVAL_S "u:"
#define TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTVAL_C 'u'
#define TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTION \
   {TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPT "random-seed"
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPTARG "n"
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPTUSE "Random seed value"
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPTVAL_S "s:"
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPTVAL_C 's'
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPTION \
   {TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPTVAL_C}, \

#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPT "plain-text"
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPTARG_RESULT 0
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPTARG "string"
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPTUSE "Plain text"
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPTVAL_S "p:"
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPTVAL_C 'p'
#define TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPTION \
   {TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPTARG_REQUIRED, \
    TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPTARG_RESULT, \
    TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPTVAL_C}, \

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define TALAS_APP_CONSOLE_TALAS_MAIN_OPTIONS_CHARS \
   TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTVAL_S \
   TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTVAL_S \
   TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTVAL_S /*\
   TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPTVAL_S \
   TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPTVAL_S \
   TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPTVAL_S \
   TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPTVAL_S \
   TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPTVAL_S \
   TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPTVAL_S */\
   TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTVAL_S \
   TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTVAL_S \
   TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPTVAL_S \
   TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPTVAL_S \
   TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPTVAL_S \
   TALAS_CONSOLE_MAIN_OPTIONS_CHARS

#define TALAS_APP_CONSOLE_TALAS_MAIN_OPTIONS_OPTIONS \
   TALAS_APP_CONSOLE_TALAS_MAIN_CIPHER_OPTION \
   TALAS_APP_CONSOLE_TALAS_MAIN_HASH_OPTION \
   TALAS_APP_CONSOLE_TALAS_MAIN_GENERATE_OPTION /*\
   TALAS_APP_CONSOLE_TALAS_MAIN_ENCRYPT_OPTION \
   TALAS_APP_CONSOLE_TALAS_MAIN_DECRYPT_OPTION \
   TALAS_APP_CONSOLE_TALAS_MAIN_SIGN_OPTION \
   TALAS_APP_CONSOLE_TALAS_MAIN_KEY_OPTION \
   TALAS_APP_CONSOLE_TALAS_MAIN_IV_OPTION \
   TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_OPTION */\
   TALAS_APP_CONSOLE_TALAS_MAIN_ECC_OPTION \
   TALAS_APP_CONSOLE_TALAS_MAIN_NUMBER_OPTION \
   TALAS_APP_CONSOLE_TALAS_MAIN_BITS_OPTION \
   TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_SEED_OPTION \
   TALAS_APP_CONSOLE_TALAS_MAIN_RANDOM_PLAIN_OPTION \
   TALAS_CONSOLE_MAIN_OPTIONS_OPTIONS

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define TALAS_APP_CONSOLE_TALAS_MAIN_SOURCE_ARG "[source]"
#define TALAS_APP_CONSOLE_TALAS_MAIN_SOURCE_ARG_USE "source file"

#define TALAS_APP_CONSOLE_TALAS_MAIN_TARGET_ARG "[target]"
#define TALAS_APP_CONSOLE_TALAS_MAIN_TARGET_ARG_USE "target file"

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define TALAS_APP_CONSOLE_TALAS_MAIN_ARGS \
    TALAS_APP_CONSOLE_TALAS_MAIN_SOURCE_ARG " " /*\
    TALAS_APP_CONSOLE_TALAS_MAIN_TARGET_ARG " " \*/

#define TALAS_APP_CONSOLE_TALAS_MAIN_ARGV \
    TALAS_APP_CONSOLE_TALAS_MAIN_SOURCE_ARG " - " TALAS_APP_CONSOLE_TALAS_MAIN_SOURCE_ARG_USE, /*\
    TALAS_APP_CONSOLE_TALAS_MAIN_TARGET_ARG " - " TALAS_APP_CONSOLE_TALAS_MAIN_TARGET_ARG_USE, \*/

namespace talas {
namespace app {
namespace console {
namespace talas {

} // namespace talas 
} // namespace console 
} // namespace app 
} // namespace talas 

#endif // _TALAS_APP_CONSOLE_TALAS_MAIN_OPT_HPP 
