########################################################################
# Copyright (c) 1988-2015 $organization$
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
#   File: libmp.pri
#
# Author: $author$
#   Date: 4/23/2015
########################################################################

libmp_INCLUDEPATH += \
$${mp_INCLUDEPATH} \

libmp_DEFINES += \
$${mp_DEFINES} \

libmp_HEADERS += \

libmp_SOURCES += \
$${mp_SRC}/extract-double.c \
$${mp_SRC}/insert-double.c \
$${mp_SRC}/memory.c \
$${mp_SRC}/mp_bpl.c \
$${mp_SRC}/mp_clz_tab.c \
$${mp_SRC}/mp_set_fns.c \
$${mp_SRC}/stack-alloc.c \
$${mp_SRC}/version.c \

libmp_LIBS += \
-L$${NADIR_LIB}/libmpz \
-lmpz \
-L$${NADIR_LIB}/libmpn \
-lmpn \

unused = \
-L$${NADIR_LIB}/libmp \
-lmp \

