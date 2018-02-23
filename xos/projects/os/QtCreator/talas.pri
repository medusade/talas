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
#   Date: 2/9/2018
#
# Os QtCreator .pri file for talas
########################################################################
UNAME = $$system(uname)

contains(UNAME,Darwin) {
TALAS_OS = macosx
} else {
TALAS_OS = linux
}

#CONFIG += c++11
#CONFIG += c++0x

########################################################################
# libressl
LIBRESSL_THIRDPARTY_PKG_BLD = $${LIBRESSL_THIRDPARTY_PKG}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
LIBRESSL_THIRDPARTY_PRJ_BLD = $${LIBRESSL_THIRDPARTY_PRJ}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
LIBRESSL_PKG_BLD = $${OTHER_BLD}/$${LIBRESSL_PKG}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
LIBRESSL_PRJ_BLD = $${OTHER_BLD}/$${LIBRESSL_PRJ}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
#LIBRESSL_LIB = $${LIBRESSL_THIRDPARTY_PKG_BLD}/lib
#LIBRESSL_LIB = $${LIBRESSL_THIRDPARTY_PRJ_BLD}/lib
#LIBRESSL_LIB = $${LIBRESSL_PKG_BLD}/lib
#LIBRESSL_LIB = $${LIBRESSL_PRJ_BLD}/lib

#libressl_LIBS += \
#-L$${LIBRESSL_LIB}/liblibressl \
#$${LIBRESSL_LIB_NAMES} \

########################################################################
# openssl
OPENSSL_THIRDPARTY_PKG_BLD = $${OPENSSL_THIRDPARTY_PKG}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
OPENSSL_THIRDPARTY_PRJ_BLD = $${OPENSSL_THIRDPARTY_PRJ}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
OPENSSL_PKG_BLD = $${OTHER_BLD}/$${OPENSSL_PKG}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
OPENSSL_PRJ_BLD = $${OTHER_BLD}/$${OPENSSL_PRJ}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
#OPENSSL_LIB = $${OPENSSL_THIRDPARTY_PKG_BLD}/lib
#OPENSSL_LIB = $${OPENSSL_THIRDPARTY_PRJ_BLD}/lib
#OPENSSL_LIB = $${OPENSSL_PKG_BLD}/lib
#OPENSSL_LIB = $${OPENSSL_PRJ_BLD}/lib

#openssl_LIBS += \
#-L$${OPENSSL_LIB}/libopenssl \
#$${OPENSSL_LIB_NAMES} \

########################################################################
# bn
BN_THIRDPARTY_PKG_BLD = $${BN_THIRDPARTY_PKG}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
BN_THIRDPARTY_PRJ_BLD = $${BN_THIRDPARTY_PRJ}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
BN_PKG_BLD = $${OTHER_BLD}/$${BN_PKG}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
BN_PRJ_BLD = $${OTHER_BLD}/$${BN_PRJ}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
#BN_LIB = $${BN_THIRDPARTY_PKG_BLD}/lib
#BN_LIB = $${BN_THIRDPARTY_PRJ_BLD}/lib
#BN_LIB = $${BN_PKG_BLD}/lib
#BN_LIB = $${BN_PRJ_BLD}/lib
BN_LIB = $${TALAS_LIB}

bn_LIBS += \
-L$${BN_LIB}/lib$${BN_NAME} \
-l$${BN_NAME} \

########################################################################
# mp
MP_THIRDPARTY_PKG_BLD = $${MP_THIRDPARTY_PKG}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
MP_THIRDPARTY_PRJ_BLD = $${MP_THIRDPARTY_PRJ}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
MP_PKG_BLD = $${OTHER_BLD}/$${MP_PKG}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
MP_PRJ_BLD = $${OTHER_BLD}/$${MP_PRJ}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
#MP_LIB = $${MP_THIRDPARTY_PKG_BLD}/lib
#MP_LIB = $${MP_THIRDPARTY_PRJ_BLD}/lib
#MP_LIB = $${MP_PKG_BLD}/lib
#MP_LIB = $${MP_PRJ_BLD}/lib
MP_LIB = $${TALAS_LIB}

mp_LIBS += \
-L$${MP_LIB}/lib$${MP_NAME} \
-l$${MP_NAME} \
-L$${MP_LIB}/lib$${MP_NAME}n \
-l$${MP_NAME}n \
-L$${MP_LIB}/lib$${MP_NAME}z \
-l$${MP_NAME}z \

########################################################################
# mb
MB_THIRDPARTY_PKG_BLD = $${MB_THIRDPARTY_PKG}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
MB_THIRDPARTY_PRJ_BLD = $${MB_THIRDPARTY_PRJ}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
MB_PKG_BLD = $${OTHER_BLD}/$${MB_PKG}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
MB_PRJ_BLD = $${OTHER_BLD}/$${MB_PRJ}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
#MB_LIB = $${MB_THIRDPARTY_PKG_BLD}/lib
#MB_LIB = $${MB_THIRDPARTY_PRJ_BLD}/lib
#MB_LIB = $${MB_PKG_BLD}/lib
#MB_LIB = $${MB_PRJ_BLD}/lib
MB_LIB = $${TALAS_LIB}

mb_LIBS += \
-L$${MB_LIB}/lib$${MB_NAME} \
-l$${MB_NAME} \

########################################################################
# mbu
MBU_THIRDPARTY_PKG_BLD = $${MBU_THIRDPARTY_PKG}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
MBU_THIRDPARTY_PRJ_BLD = $${MBU_THIRDPARTY_PRJ}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
MBU_PKG_BLD = $${OTHER_BLD}/$${MBU_PKG}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
MBU_PRJ_BLD = $${OTHER_BLD}/$${MBU_PRJ}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
#MBU_LIB = $${MBU_THIRDPARTY_PKG_BLD}/lib
#MBU_LIB = $${MBU_THIRDPARTY_PRJ_BLD}/lib
#MBU_LIB = $${MBU_PKG_BLD}/lib
#MBU_LIB = $${MBU_PRJ_BLD}/lib
MBU_LIB = $${TALAS_LIB}

mbu_LIBS += \
-L$${MBU_LIB}/lib$${MBU_LIB_NAME} \
-l$${MBU_LIB_NAME} \

########################################################################
# nadir
NADIR_THIRDPARTY_PKG_BLD = $${NADIR_THIRDPARTY_PKG}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
NADIR_THIRDPARTY_PRJ_BLD = $${NADIR_THIRDPARTY_PRJ}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
NADIR_PKG_BLD = $${OTHER_BLD}/$${NADIR_PKG}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
NADIR_PRJ_BLD = $${OTHER_BLD}/$${NADIR_PRJ}/build/$${TALAS_OS}/QtCreator/$${BUILD_CONFIG}
#NADIR_LIB = $${NADIR_THIRDPARTY_PKG_BLD}/lib
#NADIR_LIB = $${NADIR_THIRDPARTY_PRJ_BLD}/lib
NADIR_LIB = $${NADIR_PKG_BLD}/lib
#NADIR_LIB = $${NADIR_PRJ_BLD}/lib

nadir_LIBS += \
-L$${NADIR_LIB}/libxos$${NADIR_NAME} \
-lxos$${NADIR_NAME} \

########################################################################
# talas
talas_INCLUDEPATH += \

talas_DEFINES += \

talas_bn_LIBS += \
$${bn_LIBS} \

talas_mp_LIBS += \
$${mp_LIBS} \

talas_mb_LIBS += \
$${mb_LIBS} \

talas_mbu_LIBS += \
$${mbu_LIBS} \

talas_LIBS += \
$${nadir_LIBS} \
$${build_talas_LIBS} \
-lpthread \
-ldl \

contains(TALAS_OS,linux) {
talas_LIBS += \
-lrt
}
