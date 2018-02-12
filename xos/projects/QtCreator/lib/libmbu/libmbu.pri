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
#   File: libmbu.pri
#
# Author: $author$
#   Date: 2/11/2018
#
# QtCreator .pri file for etiris library libmbu
########################################################################

########################################################################
# libmbu
libmbu_TARGET = mbu
libmbu_TEMPLATE = lib
libmbu_CONFIG += staticlib

libmbu_INCLUDEPATH += \
$${etiris_INCLUDEPATH} \

libmbu_DEFINES += \
$${etiris_DEFINES} \

########################################################################
libmbu_HEADERS += \
$${ETIRIS_SRC}/generic/mbuint.h \
$${ETIRIS_SRC}/generic/dump.h \
$${ETIRIS_SRC}/generic/dbdump.h \
$${ETIRIS_SRC}/generic/dbprintf.h \

libmbu_SOURCES += \
$${ETIRIS_SRC}/generic/mbuint.c \
$${ETIRIS_SRC}/generic/dump.c \
$${ETIRIS_SRC}/generic/dbdump.c \
$${ETIRIS_SRC}/generic/dbprintf.c \

########################################################################
