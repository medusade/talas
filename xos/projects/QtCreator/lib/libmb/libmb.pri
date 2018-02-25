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
#   File: libmb.pri
#
# Author: $author$
#   Date: 2/25/2018
#
# QtCreator .pri file for talas library libmb
########################################################################

########################################################################
# libmb
libmb_TARGET = mb
libmb_TEMPLATE = lib
libmb_CONFIG += staticlib

libmb_INCLUDEPATH += \
$${talas_INCLUDEPATH} \
$${talas_mb_INCLUDEPATH} \
$${talas_mbu_INCLUDEPATH} \

libmb_DEFINES += \
$${talas_DEFINES} \
$${talas_mb_DEFINES} \
$${talas_mbu_DEFINES} \

########################################################################
libmb_HEADERS += \
$${MB_SRC}/mbu_msb.h \
$${MB_SRC}/mbu.h \

libmb_SOURCES += \
$${MB_SRC}/mbu_msb.c \
$${MB_SRC}/mbu.c \

########################################################################




