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
#   File: dsa.pri
#
# Author: $author$
#   Date: 2/25/2018
#
# QtCreator .pri file for talas executable dsa
########################################################################

########################################################################
# dsa
dsa_TARGET = dsa

dsa_INCLUDEPATH += \
$${talas_INCLUDEPATH} \
$${talas_bn_INCLUDEPATH} \
$${talas_mp_INCLUDEPATH} \
$${talas_mb_INCLUDEPATH} \

dsa_DEFINES += \
$${talas_DEFINES} \

########################################################################
dsa_HEADERS += \
$${TALAS_SRC}/talas/crypto/dsa/mp/public_key.hpp \
$${TALAS_SRC}/talas/crypto/dsa/mp/private_key.hpp \
$${TALAS_SRC}/talas/crypto/dsa/mp/key.hpp \
\
$${TALAS_SRC}/talas/crypto/dsa/bn/public_key.hpp \
$${TALAS_SRC}/talas/crypto/dsa/bn/private_key.hpp \
$${TALAS_SRC}/talas/crypto/dsa/bn/key.hpp \
\
$${TALAS_SRC}/talas/crypto/dsa/public_key.hpp \
$${TALAS_SRC}/talas/crypto/dsa/private_key.hpp \
$${TALAS_SRC}/talas/crypto/dsa/key.hpp \
\
$${TALAS_SRC}/talas/app/console/dsa/main.hpp \
$${TALAS_SRC}/talas/app/console/dsa/main_opt.hpp \

dsa_SOURCES += \
$${TALAS_SRC}/talas/crypto/dsa/mp/public_key.cpp \
$${TALAS_SRC}/talas/crypto/dsa/mp/private_key.cpp \
$${TALAS_SRC}/talas/crypto/dsa/mp/key.cpp \
\
$${TALAS_SRC}/talas/app/console/dsa/main.cpp \
$${TALAS_SRC}/talas/app/console/dsa/main_opt.cpp \
$${TALAS_SRC}/talas/console/main_main.cpp \

########################################################################
dsa_LIBS += \
$${talas_LIBS} \
$${talas_bn_LIBS} \
$${talas_mp_LIBS} \
