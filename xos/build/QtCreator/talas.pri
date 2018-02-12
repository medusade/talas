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
# build QtCreator .pri file for talas
########################################################################

########################################################################
# libressl
#
# pkg-config --cflags --libs libressl
#
build_libressl_INCLUDEPATH += \

build_libressl_DEFINES += \

build_libressl_LIBS += \

########################################################################
# openssl
#
# pkg-config --cflags --libs openssl
#
build_openssl_INCLUDEPATH += \

build_openssl_DEFINES += \

build_openssl_LIBS += \

########################################################################
# bn
#
# pkg-config --cflags --libs bn
#
build_bn_INCLUDEPATH += \

build_bn_DEFINES += \

build_bn_LIBS += \

########################################################################
# mp
#
# pkg-config --cflags --libs mp
#
build_mp_INCLUDEPATH += \

build_mp_DEFINES += \

build_mp_LIBS += \

########################################################################
# nadir
#
# pkg-config --cflags --libs nadir
#
build_nadir_INCLUDEPATH += \

build_nadir_DEFINES += \

build_nadir_LIBS += \

########################################################################
# talas
build_talas_INCLUDEPATH += \
$${build_nadir_INCLUDEPATH} \
$${build_mp_INCLUDEPATH} \
$${build_bn_INCLUDEPATH} \
$${build_openssl_INCLUDEPATH} \
$${build_libressl_INCLUDEPATH} \


build_talas_DEFINES += \
$${build_libressl_DEFINES} \
$${build_openssl_DEFINES} \
$${build_bn_DEFINES} \
$${build_mp_DEFINES} \
$${build_nadir_DEFINES} \


build_talas_LIBS += \
$${build_nadir_LIBS} \
$${build_mp_LIBS} \
$${build_bn_LIBS} \
$${build_openssl_LIBS} \
$${build_libressl_LIBS} \


