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
#   File: Makefile
#
# Author: $author$
#   Date: 11/18/2018
#
# generic Gcc Makefile for talas Library libtalas
########################################################################


#
# target
#
libtalas_LIBTARGET = libtalas.${LIBEXT}

########################################################################

#
# user c++ flags
#
libtalas_USRCXXFLAGS += \
${talas_USRCXXFLAGS} \

#
# user defines
#
libtalas_USRDEFINES += \
${talas_USRDEFINES} \

#
# user includes
#
libtalas_USRINCLUDES += \
${talas_USRINCLUDES} \

#
# user libdirs
#
libtalas_USRLIBDIRS += \
${talas_USRLIBDIRS} \

########################################################################

#
# Library .c sources
#
libtalas_LIB_C_SOURCES += \
${TALAS_SRC}/thirdparty/google/curve25519/curve25519-donna.c \

#
# Library .cc sources
#
#libtalas_LIB_CC_SOURCES += \
#${TALAS_SRC}/talas/base/Base.cc \

#
# Library .cxx sources
#
libtalas_LIB_CXX_SOURCES += \
${TALAS_SRC}/thirdparty/msotoodeh/curve25519/curve25519_mehdi.cxx \

#
# Library .cpp sources
#
libtalas_LIB_CPP_SOURCES += \
${TALAS_SRC}/talas/crypto/random/pseudo.cpp \
${TALAS_SRC}/talas/crypto/random/generator.cpp \
\
${TALAS_SRC}/talas/crypto/hash/openssl/sha512.cpp \
${TALAS_SRC}/talas/crypto/hash/openssl/sha256.cpp \
${TALAS_SRC}/talas/crypto/hash/openssl/sha1.cpp \
${TALAS_SRC}/talas/crypto/hash/openssl/md5.cpp \
${TALAS_SRC}/talas/crypto/hash/mac.cpp \
\
${TALAS_SRC}/talas/crypto/cipher/devine/aes.cpp \
${TALAS_SRC}/talas/crypto/cipher/openssl/des.cpp \
\
${TALAS_SRC}/talas/crypto/rsa/mp/key_generator.cpp \
${TALAS_SRC}/talas/crypto/rsa/mp/private_key.cpp \
${TALAS_SRC}/talas/crypto/rsa/mp/public_key.cpp \
${TALAS_SRC}/talas/crypto/rsa/mp/key.cpp \
${TALAS_SRC}/talas/crypto/random/prime/mp/generator.cpp \
${TALAS_SRC}/talas/crypto/random/prime/mp/miller_rabin.cpp \
${TALAS_SRC}/talas/crypto/random/prime/mp/reader.cpp \
${TALAS_SRC}/talas/crypto/random/prime/mp/number.cpp \
${TALAS_SRC}/talas/crypto/random/prime/small_primes.cpp \
\
${TALAS_SRC}/talas/crypto/ecc/curve25519/google/donna/public_key.cpp \
${TALAS_SRC}/talas/crypto/ecc/curve25519/private_key.cpp \
${TALAS_SRC}/talas/crypto/ecc/curve25519/key.cpp \
${TALAS_SRC}/talas/crypto/ecc/curve25519/base_point.cpp \
${TALAS_SRC}/talas/crypto/ecc/curve25519/array.cpp \

#
# Library .m sources
#
#libtalas_LIB_M_SOURCES += \
#${TALAS_SRC}/talas/base/Base.m \

#
# Library .mm sources
#
#libtalas_LIB_MM_SOURCES += \
#${TALAS_SRC}/talas/base/Base.mm \


########################################################################




