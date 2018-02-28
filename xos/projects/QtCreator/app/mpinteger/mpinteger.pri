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
#   File: mpinteger.pri
#
# Author: $author$
#   Date: 2/26/2018
#
# QtCreator .pri file for talas executable mpinteger
########################################################################

########################################################################
# mpinteger
mpinteger_TARGET = mpinteger

mpinteger_INCLUDEPATH += \
$${talas_INCLUDEPATH} \
$${talas_bn_INCLUDEPATH} \
$${talas_mp_INCLUDEPATH} \
$${talas_mpinteger_INCLUDEPATH} \

mpinteger_DEFINES += \
$${talas_DEFINES} \
$${talas_bn_DEFINES} \
$${talas_mp_DEFINES} \
$${talas_mpinteger_DEFINES} \

########################################################################
mpinteger_HEADERS += \
$${MPINTEGER_SRC}/mp/unsigned_integers.hpp \
$${MPINTEGER_SRC}/mp/mp/unsigned_integer.hpp \
$${MPINTEGER_SRC}/mp/bn/unsigned_integer.hpp \
$${MPINTEGER_SRC}/mp/unsigned_integer.hpp \
$${MPINTEGER_SRC}/base/base.hpp \

mpinteger_SOURCES += \
$${MPINTEGER_SRC}/mp/unsigned_integers.cpp \
$${MPINTEGER_SRC}/base/base.cpp \

########################################################################
mpinteger_HEADERS += \
$${TALAS_SRC}/talas/app/console/mpinteger/main.hpp \
$${TALAS_SRC}/talas/crypto/console/mpinteger/main_opt.hpp \
$${TALAS_SRC}/talas/console/main.hpp \
$${TALAS_SRC}/talas/console/main_opt.hpp \
$${TALAS_SRC}/talas/console/main_main.hpp \

mpinteger_SOURCES += \
$${TALAS_SRC}/talas/app/console/mpinteger/main.cpp \
$${TALAS_SRC}/talas/crypto/console/mpinteger/main_opt.cpp \
$${TALAS_SRC}/talas/console/main_main.cpp \

########################################################################
mpinteger_LIBS += \
$${talas_LIBS} \
$${talas_bn_LIBS} \
$${talas_mp_LIBS} \
