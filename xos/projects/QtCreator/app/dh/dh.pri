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
#   File: dh.pri
#
# Author: $author$
#   Date: 2/10/2018
#
# QtCreator .pri file for talas executable dh
########################################################################

########################################################################
# dh
dh_TARGET = dh

dh_INCLUDEPATH += \
$${talas_INCLUDEPATH} \
$${talas_bn_INCLUDEPATH} \
$${talas_mp_INCLUDEPATH} \
$${talas_mbu_INCLUDEPATH} \

dh_DEFINES += \
$${talas_DEFINES} \
$${talas_mbu_DEFINES} \

########################################################################
dh_HEADERS += \
$${TALAS_SRC}/talas/crypto/dh/mbu/private_key.hpp \
$${TALAS_SRC}/talas/crypto/dh/mbu/public_key.hpp \
$${TALAS_SRC}/talas/crypto/dh/mbu/key.hpp \
$${TALAS_SRC}/talas/crypto/dh/mp/private_key.hpp \
$${TALAS_SRC}/talas/crypto/dh/mp/public_key.hpp \
$${TALAS_SRC}/talas/crypto/dh/mp/key.hpp \
$${TALAS_SRC}/talas/crypto/dh/bn/private_key.hpp \
$${TALAS_SRC}/talas/crypto/dh/bn/public_key.hpp \
$${TALAS_SRC}/talas/crypto/dh/bn/key.hpp \
$${TALAS_SRC}/talas/crypto/dh/private_key.hpp \
$${TALAS_SRC}/talas/crypto/dh/public_key.hpp \
$${TALAS_SRC}/talas/crypto/dh/key.hpp \

dh_SOURCES += \
$${TALAS_SRC}/talas/crypto/dh/bn/private_key.cpp \
$${TALAS_SRC}/talas/crypto/dh/mp/public_key.cpp \
$${TALAS_SRC}/talas/crypto/dh/mp/key.cpp \

########################################################################
dh_HEADERS += \
$${TALAS_SRC}/talas/app/console/dh/main.hpp \
$${TALAS_SRC}/talas/app/console/dh/main_opt.hpp \
$${TALAS_SRC}/talas/console/main.hpp \
$${TALAS_SRC}/talas/console/main_opt.hpp \
$${TALAS_SRC}/talas/console/main_main.hpp \

dh_SOURCES += \
$${TALAS_SRC}/talas/app/console/dh/main.cpp \
$${TALAS_SRC}/talas/app/console/dh/main_opt.cpp \
$${TALAS_SRC}/talas/console/main_main.cpp \

########################################################################
dh_LIBS += \
$${talas_LIBS} \
$${talas_bn_LIBS} \
$${talas_mp_LIBS} \
$${talas_mbu_LIBS} \
