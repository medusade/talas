########################################################################
# Copyright (c) 1988-2014 $organization$
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
#   Date: 11/18/2014
########################################################################

libtalas_INCLUDEPATH += \
$${talas_INCLUDEPATH} \

libtalas_DEFINES += \
$${talas_DEFINES} \

libtalas_HEADERS += \
$${TALAS_SRC}/thirdparty/google/curve25519/curve25519-donna.h \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/google/donna/public_key.hpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/public_key.hpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/private_key.hpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/key.hpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/base_point.hpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/array.hpp \
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
$${TALAS_SRC}/talas/crypto/random/pseudo.hpp \
$${TALAS_SRC}/talas/crypto/random/generator.hpp \
$${TALAS_SRC}/talas/crypto/base.hpp \
$${TALAS_SRC}/talas/base/base.hpp \

libtalas_SOURCES += \
$${TALAS_SRC}/thirdparty/google/curve25519/curve25519-donna.c \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/google/donna/public_key.cpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/private_key.cpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/key.cpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/base_point.cpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/array.cpp \
$${TALAS_SRC}/talas/crypto/hash/openssl/sha512.cpp \
$${TALAS_SRC}/talas/crypto/hash/openssl/sha256.cpp \
$${TALAS_SRC}/talas/crypto/hash/openssl/sha1.cpp \
$${TALAS_SRC}/talas/crypto/hash/openssl/md5.cpp \
$${TALAS_SRC}/talas/crypto/hash/mac.cpp \
$${TALAS_SRC}/talas/crypto/hash/base.cpp \
$${TALAS_SRC}/talas/crypto/random/pseudo.cpp \
$${TALAS_SRC}/talas/crypto/random/generator.cpp \

