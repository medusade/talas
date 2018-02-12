########################################################################
# Copyright (c) 1988-2018 $organization$
#
# This software is provided by the author and contributors ``as is''
# and any express or implied warranties, including, but not limited to,
# the implied warranties of merchantability and fitness for a particular
# purpose are disclaimed. In no event shall the author or contributors
# be liable for any direct, indirect, incidental, special, exemplary,
# or consequential damages (including, but not limited to, procurement
# of substitute goods or services; loss of use, data, or profits; or
# business interruption) however caused and on any theory of liability,
# whether in contract, strict liability, or tort (including negligence
# or otherwise) arising in any way out of the use of this software,
# even if advised of the possibility of such damage.
#
#   File: libtalas.pri
#
# Author: $author$
#   Date: 2/9/2018
#
# QtCreator .pri file for talas library libtalas
########################################################################

########################################################################
# libtalas
libtalas_TARGET = talas
libtalas_TEMPLATE = lib
libtalas_CONFIG += staticlib

libtalas_INCLUDEPATH += \
$${talas_INCLUDEPATH} \
$${talas_bn_INCLUDEPATH} \
$${talas_mp_INCLUDEPATH} \

libtalas_DEFINES += \
$${talas_DEFINES} \

########################################################################
# ecc
libtalas_ecc_HEADERS += \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/msotoodeh/public_key.hpp \
$${TALAS_SRC}/thirdparty/msotoodeh/curve25519/curve25519_mehdi.hxx \
$${TALAS_SRC}/thirdparty/google/curve25519/curve25519-donna.h \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/google/donna/public_key.hpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/public_key.hpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/private_key.hpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/key.hpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/base_point.hpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/array.hpp \

libtalas_ecc_SOURCES += \
$${TALAS_SRC}/thirdparty/msotoodeh/curve25519/curve25519_mehdi.cxx \
$${TALAS_SRC}/thirdparty/google/curve25519/curve25519-donna.c \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/google/donna/public_key.cpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/private_key.cpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/key.cpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/base_point.cpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/array.cpp \

########################################################################
# rsa
libtalas_rsa_HEADERS += \
$${TALAS_SRC}/talas/crypto/rsa/mp/key_generator.hpp \
$${TALAS_SRC}/talas/crypto/rsa/mp/private_key.hpp \
$${TALAS_SRC}/talas/crypto/rsa/mp/public_key.hpp \
$${TALAS_SRC}/talas/crypto/rsa/mp/key.hpp \
$${TALAS_SRC}/talas/crypto/rsa/bn/key_generator.hpp \
$${TALAS_SRC}/talas/crypto/rsa/bn/private_key.hpp \
$${TALAS_SRC}/talas/crypto/rsa/bn/public_key.hpp \
$${TALAS_SRC}/talas/crypto/rsa/bn/key.hpp \
$${TALAS_SRC}/talas/crypto/rsa/private_key.hpp \
$${TALAS_SRC}/talas/crypto/rsa/public_key.hpp \
$${TALAS_SRC}/talas/crypto/rsa/key.hpp \
$${TALAS_SRC}/talas/crypto/random/prime/mp/generator.hpp \
$${TALAS_SRC}/talas/crypto/random/prime/mp/miller_rabin.hpp \
$${TALAS_SRC}/talas/crypto/random/prime/mp/reader.hpp \
$${TALAS_SRC}/talas/crypto/random/prime/mp/number.hpp \
$${TALAS_SRC}/talas/crypto/random/prime/bn/generator.hpp \
$${TALAS_SRC}/talas/crypto/random/prime/bn/miller_rabin.hpp \
$${TALAS_SRC}/talas/crypto/random/prime/bn/reader.hpp \
$${TALAS_SRC}/talas/crypto/random/prime/bn/number.hpp \
$${TALAS_SRC}/talas/crypto/bn/number.hpp \
$${TALAS_SRC}/talas/crypto/random/prime/generator.hpp \
$${TALAS_SRC}/talas/crypto/random/prime/reader.hpp \
$${TALAS_SRC}/talas/crypto/random/prime/small_primes.hpp \

libtalas_rsa_SOURCES += \
$${TALAS_SRC}/talas/crypto/rsa/mp/key_generator.cpp \
$${TALAS_SRC}/talas/crypto/rsa/mp/private_key.cpp \
$${TALAS_SRC}/talas/crypto/rsa/mp/public_key.cpp \
$${TALAS_SRC}/talas/crypto/rsa/mp/key.cpp \
$${TALAS_SRC}/talas/crypto/random/prime/mp/generator.cpp \
$${TALAS_SRC}/talas/crypto/random/prime/mp/miller_rabin.cpp \
$${TALAS_SRC}/talas/crypto/random/prime/mp/reader.cpp \
$${TALAS_SRC}/talas/crypto/random/prime/mp/number.cpp \
$${TALAS_SRC}/talas/crypto/random/prime/small_primes.cpp \

########################################################################
# cipher
libtalas_cipher_HEADERS += \
$${TALAS_SRC}/talas/crypto/cipher/devine/aes.hpp \
$${TALAS_SRC}/talas/crypto/cipher/aes.hpp \
$${TALAS_SRC}/talas/crypto/cipher/openssl/des.hpp \
$${TALAS_SRC}/talas/crypto/cipher/des3.hpp \
$${TALAS_SRC}/talas/crypto/cipher/des.hpp \
$${TALAS_SRC}/talas/crypto/cipher/base.hpp \

libtalas_cipher_SOURCES += \
$${TALAS_SRC}/talas/crypto/cipher/devine/aes.cpp \
$${TALAS_SRC}/talas/crypto/cipher/openssl/des.cpp \

########################################################################
# hash
libtalas_hash_HEADERS += \
$${TALAS_SRC}/talas/crypto/hash/openssl/sha512.hpp \
$${TALAS_SRC}/talas/crypto/hash/sha512.hpp \
$${TALAS_SRC}/talas/crypto/hash/openssl/sha256.hpp \
$${TALAS_SRC}/talas/crypto/hash/sha256.hpp \
$${TALAS_SRC}/talas/crypto/hash/openssl/sha1.hpp \
$${TALAS_SRC}/talas/crypto/hash/sha1.hpp \
$${TALAS_SRC}/talas/crypto/hash/openssl/md5.hpp \
$${TALAS_SRC}/talas/crypto/hash/md5.hpp \
$${TALAS_SRC}/talas/crypto/hash/mac.hpp \
$${TALAS_SRC}/talas/crypto/hash/base.hpp \

libtalas_hash_SOURCES += \
$${TALAS_SRC}/talas/crypto/hash/openssl/sha512.cpp \
$${TALAS_SRC}/talas/crypto/hash/openssl/sha256.cpp \
$${TALAS_SRC}/talas/crypto/hash/openssl/sha1.cpp \
$${TALAS_SRC}/talas/crypto/hash/openssl/md5.cpp \
$${TALAS_SRC}/talas/crypto/hash/mac.cpp \
$${TALAS_SRC}/talas/crypto/hash/base.cpp \

########################################################################
# random
libtalas_random_HEADERS += \
$${TALAS_SRC}/talas/crypto/random/pseudo.hpp \
$${TALAS_SRC}/talas/crypto/random/generator.hpp \
$${TALAS_SRC}/talas/crypto/random/reader.hpp \

libtalas_random_SOURCES += \
$${TALAS_SRC}/talas/crypto/random/pseudo.cpp \
$${TALAS_SRC}/talas/crypto/random/generator.cpp \

########################################################################
libtalas_HEADERS += \
$${libtalas_ecc_HEADERS} \
$${libtalas_rsa_HEADERS} \
$${libtalas_cipher_HEADERS} \
$${libtalas_hash_HEADERS} \
$${libtalas_random_HEADERS} \
$${TALAS_SRC}/talas/crypto/base.hpp \
$${TALAS_SRC}/talas/base/base.hpp \

libtalas_SOURCES += \
$${libtalas_ecc_SOURCES} \
$${libtalas_rsa_SOURCES} \
$${libtalas_cipher_SOURCES} \
$${libtalas_hash_SOURCES} \
$${libtalas_random_SOURCES} \

########################################################################
