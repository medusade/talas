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
#   File: talas.pri
#
# Author: $author$
#   Date: 11/18/2014
########################################################################

talas_HEADERS += \
$${TALAS_SRC}/talas/app/console/talas/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/talas/main.hpp \
$${TALAS_SRC}/talas/console/main.hpp \
$${TALAS_SRC}/talas/console/main_opt.hpp \
$${TALAS_SRC}/talas/console/main_main.hpp \

talas_SOURCES += \
$${TALAS_SRC}/talas/app/console/talas/main.cpp \
$${TALAS_SRC}/talas/console/main_opt.cpp \
$${TALAS_SRC}/talas/console/main_main.cpp \

talas_HEADERS += \
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
$${TALAS_SRC}/talas/crypto/random/generator.hpp \
$${TALAS_SRC}/talas/crypto/random/prime/reader.hpp \
$${TALAS_SRC}/talas/crypto/random/reader.hpp \
$${TALAS_SRC}/talas/crypto/random/prime/small_primes.hpp \
$${TALAS_SRC}/talas/crypto/cipher/devine/aes.hpp \
$${TALAS_SRC}/talas/crypto/cipher/aes.hpp \
$${TALAS_SRC}/talas/crypto/cipher/base.hpp \
$${TALAS_SRC}/talas/crypto/ecc/curve25519/msotoodeh/public_key.hpp \
$${TALAS_SRC}/thirdparty/msotoodeh/curve25519/curve25519_mehdi.hxx \

talas_SOURCES += \
$${TALAS_SRC}/talas/crypto/rsa/mp/key_generator.cpp \
$${TALAS_SRC}/talas/crypto/rsa/mp/private_key.cpp \
$${TALAS_SRC}/talas/crypto/rsa/mp/public_key.cpp \
$${TALAS_SRC}/talas/crypto/rsa/mp/key.cpp \
$${TALAS_SRC}/talas/crypto/random/prime/mp/generator.cpp \
$${TALAS_SRC}/talas/crypto/random/prime/mp/miller_rabin.cpp \
$${TALAS_SRC}/talas/crypto/random/prime/mp/reader.cpp \
$${TALAS_SRC}/talas/crypto/random/prime/mp/number.cpp \
$${TALAS_SRC}/talas/crypto/random/prime/small_primes.cpp \
$${TALAS_SRC}/talas/crypto/cipher/devine/aes.cpp \
$${TALAS_SRC}/talas/crypto/cipher/base.cpp \
$${TALAS_SRC}/thirdparty/msotoodeh/curve25519/curve25519_mehdi.cxx \
