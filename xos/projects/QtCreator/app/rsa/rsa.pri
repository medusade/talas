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
#   File: rsa.pri
#
# Author: $author$
#   Date: 2/28/2018
#
# QtCreator .pri file for talas executable rsa
########################################################################

########################################################################
# rsa
rsa_TARGET = rsa

rsa_INCLUDEPATH += \
$${talas_INCLUDEPATH} \
$${talas_bn_INCLUDEPATH} \
$${talas_mp_INCLUDEPATH} \

rsa_DEFINES += \
$${talas_DEFINES} \
$${talas_bn_DEFINES} \
$${talas_mp_DEFINES} \

########################################################################
rsa_HEADERS += \
$${TALAS_SRC}/talas/crypto/rsa/public_keys.hpp \
$${TALAS_SRC}/talas/crypto/rsa/private_keys.hpp \
$${TALAS_SRC}/talas/crypto/rsa/keys.hpp \
\
$${TALAS_SRC}/talas/crypto/rsa/mp/public_key.hpp \
$${TALAS_SRC}/talas/crypto/rsa/mp/private_key.hpp \
$${TALAS_SRC}/talas/crypto/rsa/mp/key.hpp \
\
$${TALAS_SRC}/talas/crypto/rsa/bn/public_key.hpp \
$${TALAS_SRC}/talas/crypto/rsa/bn/private_key.hpp \
$${TALAS_SRC}/talas/crypto/rsa/bn/key.hpp \
\
$${TALAS_SRC}/talas/crypto/rsa/public_key.hpp \
$${TALAS_SRC}/talas/crypto/rsa/private_key.hpp \
$${TALAS_SRC}/talas/crypto/rsa/key.hpp \
\
$${TALAS_SRC}/talas/app/console/rsa/main.hpp \
$${TALAS_SRC}/talas/app/console/rsa/main_opt.hpp \

rsa_SOURCES += \
$${TALAS_SRC}/talas/crypto/rsa/public_keys.cpp \
$${TALAS_SRC}/talas/crypto/rsa/private_keys.cpp \
$${TALAS_SRC}/talas/crypto/rsa/keys.cpp \
\
$${TALAS_SRC}/talas/app/console/rsa/main.cpp \
$${TALAS_SRC}/talas/app/console/rsa/main_opt.cpp \
$${TALAS_SRC}/talas/console/main_main.cpp \

########################################################################
rsa_LIBS += \
$${talas_LIBS} \
$${talas_bn_LIBS} \
$${talas_mp_LIBS} \
