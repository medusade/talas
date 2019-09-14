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
#   File: talas.pri
#
# Author: $author$
#   Date: 11/17/2018
#
# QtCreator .pri file for talas
########################################################################
THIS_PKG = ../../../../../..
THIS_PRJ = ../../../../..
THIS_BLD = ../..

OTHER_PKG = ../../../../../../..
OTHER_PRJ = ../../../../../..
OTHER_BLD = ..

THIRDPARTY_NAME = thirdparty
THIRDPARTY_PKG = $${THIS_PKG}/$${THIRDPARTY_NAME}
THIRDPARTY_PRJ = $${THIS_PRJ}/$${THIRDPARTY_NAME}
THIRDPARTY_SRC = $${THIS_PRJ}/src/$${THIRDPARTY_NAME}

########################################################################
# openssl
OPENSSL_VERSION_MAJOR = 0
OPENSSL_VERSION_MINOR = 9
OPENSSL_VERSION_RELEASE = 8zh
OPENSSL_VERSION = $${OPENSSL_VERSION_MAJOR}.$${OPENSSL_VERSION_MINOR}.$${OPENSSL_VERSION_RELEASE}
OPENSSL_NAME = openssl
OPENSSL_GROUP = $${OPENSSL_NAME}
OPENSSL_SOURCE = 
OPENSSL_DIR = $${OPENSSL_GROUP}/$${OPENSSL_NAME}-$${OPENSSL_VERSION}
OPENSSL_PKG_DIR = $${OPENSSL_NAME}
OPENSSL_HOME_BUILD = $${HOME}/build/$${OPENSSL_NAME}
OPENSSL_HOME_BUILD_INCLUDE = $${OPENSSL_HOME_BUILD}/include
OPENSSL_HOME_BUILD_LIB = $${OPENSSL_HOME_BUILD}/lib
OPENSSL_THIRDPARTY_PKG = $${THIRDPARTY_PKG}/$${OPENSSL_DIR}
OPENSSL_THIRDPARTY_PRJ = $${THIRDPARTY_PRJ}/$${OPENSSL_DIR}
OPENSSL_THIRDPARTY_SRC = $${THIRDPARTY_SRC}/$${OPENSSL_PKG_DIR}
OPENSSL_THIRDPARTY_SRC_GROUP = $${OPENSSL_NAME}
OPENSSL_THIRDPARTY_SRC_NAME = $${OPENSSL_NAME}
OPENSSL_THIRDPARTY_SRC_DIR = $${THIRDPARTY_SRC}/$${OPENSSL_THIRDPARTY_SRC_GROUP}/$${OPENSSL_THIRDPARTY_SRC_NAME} 
OPENSSL_PKG = $${OTHER_PKG}/$${OPENSSL_PKG_DIR}
OPENSSL_PRJ = $${OTHER_PRJ}/$${OPENSSL_PKG_DIR}
#OPENSSL_SRC = $${OPENSSL_THIRDPARTY_SRC_DIR}
#OPENSSL_SRC = $${OPENSSL_THIRDPARTY_PKG}/$${OPENSSL_SOURCE}
OPENSSL_SRC = $${OPENSSL_THIRDPARTY_PRJ}/$${OPENSSL_SOURCE}
#OPENSSL_SRC = $${OPENSSL_PKG}/$${OPENSSL_SOURCE}
#OPENSSL_SRC = $${OPENSSL_PRJ}/$${OPENSSL_SOURCE}

# openssl INCLUDEPATH
#
openssl_INCLUDEPATH += \
$${OPENSSL_SRC}/include \
$${OPENSSL_SRC}/crypto \
$${OPENSSL_SRC} \

# openssl DEFINES
#
openssl_DEFINES += \

########################################################################
# libressl
LIBRESSL_VERSION_MAJOR = 2
LIBRESSL_VERSION_MINOR = 5
LIBRESSL_VERSION_RELEASE = 3
LIBRESSL_VERSION = $${LIBRESSL_VERSION_MAJOR}.$${LIBRESSL_VERSION_MINOR}.$${LIBRESSL_VERSION_RELEASE}
LIBRESSL_NAME = libressl
LIBRESSL_GROUP = $${LIBRESSL_NAME}
LIBRESSL_SOURCE = 
LIBRESSL_DIR = $${LIBRESSL_GROUP}/$${LIBRESSL_NAME}-$${LIBRESSL_VERSION}
LIBRESSL_PKG_DIR = $${LIBRESSL_NAME}
LIBRESSL_HOME_BUILD = $${HOME}/build/$${LIBRESSL_NAME}-$${LIBRESSL_VERSION}
LIBRESSL_HOME_BUILD_INCLUDE = $${LIBRESSL_HOME_BUILD}/include
LIBRESSL_HOME_BUILD_LIB = $${LIBRESSL_HOME_BUILD}/lib
LIBRESSL_THIRDPARTY_PKG = $${THIRDPARTY_PKG}/$${LIBRESSL_DIR}
LIBRESSL_THIRDPARTY_PRJ = $${THIRDPARTY_PRJ}/$${LIBRESSL_DIR}
LIBRESSL_THIRDPARTY_SRC = $${THIRDPARTY_SRC}/$${LIBRESSL_PKG_DIR}
LIBRESSL_THIRDPARTY_SRC_GROUP = $${LIBRESSL_NAME}
LIBRESSL_THIRDPARTY_SRC_NAME = $${LIBRESSL_NAME}
LIBRESSL_THIRDPARTY_SRC_DIR = $${THIRDPARTY_SRC}/$${LIBRESSL_THIRDPARTY_SRC_GROUP}/$${LIBRESSL_THIRDPARTY_SRC_NAME} 
LIBRESSL_PKG = $${OTHER_PKG}/$${LIBRESSL_PKG_DIR}
LIBRESSL_PRJ = $${OTHER_PRJ}/$${LIBRESSL_PKG_DIR}
#LIBRESSL_SRC = $${LIBRESSL_THIRDPARTY_SRC_DIR}
#LIBRESSL_SRC = $${LIBRESSL_THIRDPARTY_PKG}/$${LIBRESSL_SOURCE}
LIBRESSL_SRC = $${LIBRESSL_THIRDPARTY_PRJ}/$${LIBRESSL_SOURCE}
#LIBRESSL_SRC = $${LIBRESSL_PKG}/$${LIBRESSL_SOURCE}
#LIBRESSL_SRC = $${LIBRESSL_PRJ}/$${LIBRESSL_SOURCE}

# libressl INCLUDEPATH
#
libressl_INCLUDEPATH += \
$${LIBRESSL_SRC}/include \

# libressl DEFINES
#
libressl_DEFINES += \
__BEGIN_HIDDEN_DECLS= \
__END_HIDDEN_DECLS= \

########################################################################
# bn
BN_VERSION_MAJOR = 0
BN_VERSION_MINOR = 0
BN_VERSION_RELEASE = 0
BN_VERSION = $${BN_VERSION_MAJOR}.$${BN_VERSION_MINOR}.$${BN_VERSION_RELEASE}
BN_NAME = bn
BN_GROUP = $${BN_NAME}
BN_DIR = $${BN_GROUP}/$${BN_NAME}-$${BN_VERSION}
BN_HOME_BUILD = $${HOME}/build/$${BN_NAME}
BN_HOME_BUILD_INCLUDE = $${BN_HOME_BUILD}/include
BN_HOME_BUILD_LIB = $${BN_HOME_BUILD}/lib
BN_THIRDPARTY_PKG = $${THIRDPARTY_PKG}/$${BN_DIR}
BN_THIRDPARTY_PRJ = $${THIRDPARTY_PRJ}/$${BN_DIR}
BN_THIRDPARTY_SRC = $${THIRDPARTY_SRC}/$${BN_PKG_DIR}
BN_THIRDPARTY_SRC_GROUP = openssl
BN_THIRDPARTY_SRC_NAME = $${BN_NAME}
BN_THIRDPARTY_SRC_DIR = $${THIRDPARTY_SRC}/$${BN_THIRDPARTY_SRC_GROUP}/$${BN_THIRDPARTY_SRC_NAME} 
BN_PKG_DIR = $${BN_NAME}
BN_PKG = $${OTHER_PKG}/$${BN_PKG_DIR}
BN_PRJ = $${OTHER_PRJ}/$${BN_PKG_DIR}
BN_SRC = $${BN_THIRDPARTY_SRC_DIR}
#BN_SRC = $${BN_THIRDPARTY_PKG}/src
#BN_SRC = $${BN_THIRDPARTY_PRJ}/src
#BN_SRC = $${BN_PKG}/src
#BN_SRC = $${BN_PRJ}/src

# INCLUDEPATH
#
#bn_INCLUDEPATH += \
#$${BN_HOME_BUILD_INCLUDE} \

bn_INCLUDEPATH += \
$${BN_SRC} \

# DEFINES
#
bn_DEFINES += \

########################################################################
# mp
MP_VERSION_MAJOR = 0
MP_VERSION_MINOR = 0
MP_VERSION_RELEASE = 0
MP_VERSION = $${MP_VERSION_MAJOR}.$${MP_VERSION_MINOR}.$${MP_VERSION_RELEASE}
MP_NAME = mp
MP_GROUP = $${MP_NAME}
MP_DIR = $${MP_GROUP}/$${MP_NAME}-$${MP_VERSION}
MP_PKG_DIR = $${MP_NAME}
MP_HOME_BUILD = $${HOME}/build/$${MP_NAME}
MP_HOME_BUILD_INCLUDE = $${MP_HOME_BUILD}/include
MP_HOME_BUILD_LIB = $${MP_HOME_BUILD}/lib
MP_THIRDPARTY_PKG = $${THIRDPARTY_PKG}/$${MP_DIR}
MP_THIRDPARTY_PRJ = $${THIRDPARTY_PRJ}/$${MP_DIR}
MP_THIRDPARTY_SRC = $${THIRDPARTY_SRC}/$${MP_PKG_DIR}
MP_THIRDPARTY_SRC_GROUP = gnu
MP_THIRDPARTY_SRC_NAME = $${MP_NAME}
MP_THIRDPARTY_SRC_DIR = $${THIRDPARTY_SRC}/$${MP_THIRDPARTY_SRC_GROUP}/$${MP_THIRDPARTY_SRC_NAME} 
MP_PKG = $${OTHER_PKG}/$${MP_PKG_DIR}
MP_PRJ = $${OTHER_PRJ}/$${MP_PKG_DIR}
MP_SRC = $${MP_THIRDPARTY_SRC_DIR}
#MP_SRC = $${MP_THIRDPARTY_PKG}/src
#MP_SRC = $${MP_THIRDPARTY_PRJ}/src
#MP_SRC = $${MP_PKG}/src
#MP_SRC = $${MP_PRJ}/src

# INCLUDEPATH
#
#mp_INCLUDEPATH += \
#$${MP_HOME_BUILD_INCLUDE} \

mp_INCLUDEPATH += \
$${MP_SRC} \

# DEFINES
#
mp_DEFINES += \
_NO_INLINES \
NO_ASM \

########################################################################
# nadir
NADIR_VERSION_MAJOR = 0
NADIR_VERSION_MINOR = 0
NADIR_VERSION_RELEASE = 0
NADIR_VERSION = $${NADIR_VERSION_MAJOR}.$${NADIR_VERSION_MINOR}.$${NADIR_VERSION_RELEASE}
NADIR_NAME = nadir
NADIR_GROUP = $${NADIR_NAME}
NADIR_SOURCE = src
NADIR_DIR = $${NADIR_GROUP}/$${NADIR_NAME}-$${NADIR_VERSION}
NADIR_PKG_DIR = $${NADIR_NAME}
NADIR_HOME_BUILD = $${HOME}/build/$${NADIR_NAME}
NADIR_HOME_BUILD_INCLUDE = $${NADIR_HOME_BUILD}/include
NADIR_HOME_BUILD_LIB = $${NADIR_HOME_BUILD}/lib
NADIR_THIRDPARTY_PKG = $${THIRDPARTY_PKG}/$${NADIR_DIR}
NADIR_THIRDPARTY_PRJ = $${THIRDPARTY_PRJ}/$${NADIR_DIR}
NADIR_THIRDPARTY_SRC = $${THIRDPARTY_SRC}/$${NADIR_PKG_DIR}
NADIR_THIRDPARTY_SRC_GROUP = $${NADIR_NAME}
NADIR_THIRDPARTY_SRC_NAME = $${NADIR_NAME}
NADIR_THIRDPARTY_SRC_DIR = $${THIRDPARTY_SRC}/$${NADIR_THIRDPARTY_SRC_GROUP}/$${NADIR_THIRDPARTY_SRC_NAME} 
NADIR_PKG = $${OTHER_PKG}/$${NADIR_PKG_DIR}
NADIR_PRJ = $${OTHER_PRJ}/$${NADIR_PKG_DIR}
#NADIR_SRC = $${NADIR_THIRDPARTY_SRC_DIR}
#NADIR_SRC = $${NADIR_THIRDPARTY_PKG}/$${NADIR_SOURCE}
#NADIR_SRC = $${NADIR_THIRDPARTY_PRJ}/$${NADIR_SOURCE}
#NADIR_SRC = $${NADIR_PKG}/$${NADIR_SOURCE}
NADIR_SRC = $${NADIR_PRJ}/$${NADIR_SOURCE}

# nadir INCLUDEPATH
#
#nadir_INCLUDEPATH += \
#$${NADIR_HOME_BUILD_INCLUDE} \

nadir_INCLUDEPATH += \
$${NADIR_SRC} \

# nadir DEFINES
#
nadir_DEFINES += \

########################################################################
# xosnadir

# xosnadir INCLUDEPATH
#
xosnadir_INCLUDEPATH += \
$${nadir_INCLUDEPATH} \

# xosnadir DEFINES
#
xosnadir_DEFINES += \
$${nadir_DEFINES} \
NO_USE_NADIR_BASE \
NO_USE_XOS_LOGGER_INTERFACE \


########################################################################
# talas
TALAS_NAME = talas
TALAS_SOURCE = src

TALAS_PKG = ../../../../..
TALAS_BLD = ../..

TALAS_PRJ = $${TALAS_PKG}
TALAS_BIN = $${TALAS_BLD}/bin
TALAS_LIB = $${TALAS_BLD}/lib
TALAS_SRC = $${TALAS_PKG}/$${TALAS_SOURCE}

# talas BUILD_CONFIG
#
CONFIG(debug, debug|release) {
BUILD_CONFIG = Debug
talas_DEFINES += DEBUG_BUILD
} else {
BUILD_CONFIG = Release
talas_DEFINES += RELEASE_BUILD
}

# talas INCLUDEPATH
#
talas_INCLUDEPATH += \
$${TALAS_SRC} \
$${xosnadir_INCLUDEPATH} \
$${bn_INCLUDEPATH} \
$${mp_INCLUDEPATH} \
$${build_talas_INCLUDEPATH} \

# talas DEFINES
#
talas_DEFINES += \
$${xosnadir_DEFINES} \
$${bn_DEFINES} \
$${mp_DEFINES} \
$${build_talas_DEFINES} \

# talas LIBS
#
talas_LIBS += \
-L$${TALAS_LIB}/lib$${TALAS_NAME} \
-l$${TALAS_NAME} \
