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
#   File: libmpn.pri
#
# Author: $author$
#   Date: 4/23/2015
########################################################################

libmpn_INCLUDEPATH += \
$${mp_INCLUDEPATH} \

libmpn_DEFINES += \
$${mp_DEFINES} \

libmpn_HEADERS += \

libmpn_SOURCES += \
$${mp_SRC}/mpn/generic/add_n.c \
$${mp_SRC}/mpn/generic/addmul_1.c \
$${mp_SRC}/mpn/generic/bdivmod.c \
$${mp_SRC}/mpn/generic/cmp.c \
$${mp_SRC}/mpn/generic/divmod_1.c \
$${mp_SRC}/mpn/generic/divrem.c \
$${mp_SRC}/mpn/generic/divrem_1.c \
$${mp_SRC}/mpn/generic/dump.c \
$${mp_SRC}/mpn/generic/gcd.c \
$${mp_SRC}/mpn/generic/gcd_1.c \
$${mp_SRC}/mpn/generic/gcdext.c \
$${mp_SRC}/mpn/generic/get_str.c \
$${mp_SRC}/mpn/generic/hamdist.c \
$${mp_SRC}/mpn/generic/inlines.c \
$${mp_SRC}/mpn/generic/lshift.c \
$${mp_SRC}/mpn/generic/mod_1.c \
$${mp_SRC}/mpn/mp_bases.c \
$${mp_SRC}/mpn/generic/mul.c \
$${mp_SRC}/mpn/generic/mul_1.c \
$${mp_SRC}/mpn/generic/mul_n.c \
$${mp_SRC}/mpn/generic/perfsqr.c \
$${mp_SRC}/mpn/generic/popcount.c \
$${mp_SRC}/mpn/generic/pre_mod_1.c \
$${mp_SRC}/mpn/generic/random2.c \
$${mp_SRC}/mpn/generic/rshift.c \
$${mp_SRC}/mpn/generic/scan0.c \
$${mp_SRC}/mpn/generic/scan1.c \
$${mp_SRC}/mpn/generic/set_str.c \
$${mp_SRC}/mpn/generic/sqrtrem.c \
$${mp_SRC}/mpn/generic/sub_n.c \
$${mp_SRC}/mpn/generic/submul_1.c \
$${mp_SRC}/mpn/generic/udiv_w_sdiv.c \

libmpn_LIBS += \

