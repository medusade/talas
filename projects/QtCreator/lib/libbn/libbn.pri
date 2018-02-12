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
#   File: libbn.pri
#
# Author: $author$
#   Date: 4/23/2015
########################################################################

libbn_TARGET = bn
libbn_TEMPLATE = lib
libbn_CONFIG += staticlib

libbn_INCLUDEPATH += \
$${bn_INCLUDEPATH} \

libbn_DEFINES += \
$${bn_DEFINES} \

########################################################################
libbn_HEADERS += \

libbn_SOURCES += \
$${bn_SRC}/bn_add.c \
$${bn_SRC}/bn_blind.c \
$${bn_SRC}/bn_div.c \
$${bn_SRC}/bn_exp.c \
$${bn_SRC}/bn_gcd.c \
$${bn_SRC}/bn_lib.c \
$${bn_SRC}/bn_mod.c \
$${bn_SRC}/bn_mont.c \
$${bn_SRC}/bn_mpi.c \
$${bn_SRC}/bn_lsb.c \
$${bn_SRC}/bn_msb.c \
$${bn_SRC}/bn_mul.c \
$${bn_SRC}/bn_mulw.c \
$${bn_SRC}/bn_prime.c \
$${bn_SRC}/bn_randm.c \
$${bn_SRC}/bn_recp.c \
$${bn_SRC}/bn_shift.c \
$${bn_SRC}/bn_sqr.c \
$${bn_SRC}/bn_sub.c \
$${bn_SRC}/bn_word.c \

########################################################################
libbn_LIBS += \
-L$${NADIR_LIB}/libbn \
-lbn \
