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
#   File: libmpz.pri
#
# Author: $author$
#   Date: 11/17/2018
#
# QtCreator .pri file for talas library libmpz
########################################################################

########################################################################
# libmpz

# libmpz TARGET
#
libmpz_TARGET = mpz
libmpz_TEMPLATE = lib
libmpz_CONFIG += staticlib

# libmpz INCLUDEPATH
#
libmpz_INCLUDEPATH += \
$${talas_INCLUDEPATH} \

# libmpz DEFINES
#
libmpz_DEFINES += \
$${talas_DEFINES} \

########################################################################
# libmpz OBJECTIVE_HEADERS
#
#libmpz_OBJECTIVE_HEADERS += \
#$${TALAS_SRC}/talas/base/Base.hh \

# libmpz OBJECTIVE_SOURCES
#
#libmpz_OBJECTIVE_SOURCES += \
#$${TALAS_SRC}/talas/base/Base.mm \

########################################################################
# libmpz HEADERS
#
libmpz_HEADERS += \
$${MP_SRC}/mpz_lsb.h \
$${MP_SRC}/mpz_msb.h \

# libmpz SOURCES
#
libmpz_SOURCES += \
$${MP_SRC}/mpz/abs.c \
$${MP_SRC}/mpz/add.c \
$${MP_SRC}/mpz/add_ui.c \
$${MP_SRC}/mpz/and.c \
$${MP_SRC}/mpz/array_init.c \
$${MP_SRC}/mpz/cdiv_q.c \
$${MP_SRC}/mpz/cdiv_q_ui.c \
$${MP_SRC}/mpz/cdiv_qr.c \
$${MP_SRC}/mpz/cdiv_qr_ui.c \
$${MP_SRC}/mpz/cdiv_r.c \
$${MP_SRC}/mpz/cdiv_r_ui.c \
$${MP_SRC}/mpz/cdiv_ui.c \
$${MP_SRC}/mpz/clear.c \
$${MP_SRC}/mpz/clrbit.c \
$${MP_SRC}/mpz/cmp.c \
$${MP_SRC}/mpz/cmp_si.c \
$${MP_SRC}/mpz/cmp_ui.c \
$${MP_SRC}/mpz/com.c \
$${MP_SRC}/mpz/divexact.c \
$${MP_SRC}/mpz/fac_ui.c \
$${MP_SRC}/mpz/fdiv_q.c \
$${MP_SRC}/mpz/fdiv_q_2exp.c \
$${MP_SRC}/mpz/fdiv_q_ui.c \
$${MP_SRC}/mpz/fdiv_qr.c \
$${MP_SRC}/mpz/fdiv_qr_ui.c \
$${MP_SRC}/mpz/fdiv_r.c \
$${MP_SRC}/mpz/fdiv_r_2exp.c \
$${MP_SRC}/mpz/fdiv_r_ui.c \
$${MP_SRC}/mpz/fdiv_ui.c \
$${MP_SRC}/mpz/gcd.c \
$${MP_SRC}/mpz/gcd_ui.c \
$${MP_SRC}/mpz/gcdext.c \
$${MP_SRC}/mpz/get_d.c \
$${MP_SRC}/mpz/get_si.c \
$${MP_SRC}/mpz/get_str.c \
$${MP_SRC}/mpz/get_ui.c \
$${MP_SRC}/mpz/getbit.c \
$${MP_SRC}/mpz/getlimbn.c \
$${MP_SRC}/mpz/hamdist.c \
$${MP_SRC}/mpz/init.c \
$${MP_SRC}/mpz/inp_raw.c \
$${MP_SRC}/mpz/inp_str.c \
$${MP_SRC}/mpz/invert.c \
$${MP_SRC}/mpz/ior.c \
$${MP_SRC}/mpz/iset.c \
$${MP_SRC}/mpz/iset_d.c \
$${MP_SRC}/mpz/iset_si.c \
$${MP_SRC}/mpz/iset_str.c \
$${MP_SRC}/mpz/iset_ui.c \
$${MP_SRC}/mpz/jacobi.c \
$${MP_SRC}/mpz/legendre.c \
$${MP_SRC}/mpz/mod.c \
$${MP_SRC}/mpz/mod_inverse.c \
$${MP_SRC}/mpz_lsb.c \
$${MP_SRC}/mpz_msb.c \
$${MP_SRC}/mpz/mul.c \
$${MP_SRC}/mpz/mul_2exp.c \
$${MP_SRC}/mpz/mul_ui.c \
$${MP_SRC}/mpz/neg.c \
$${MP_SRC}/mpz/out_raw.c \
$${MP_SRC}/mpz/out_str.c \
$${MP_SRC}/mpz/perfsqr.c \
$${MP_SRC}/mpz/popcount.c \
$${MP_SRC}/mpz/pow_ui.c \
$${MP_SRC}/mpz/powm.c \
$${MP_SRC}/mpz/powm_ui.c \
$${MP_SRC}/mpz/pprime_p.c \
$${MP_SRC}/mpz/random.c \
$${MP_SRC}/mpz/random2.c \
$${MP_SRC}/mpz/realloc.c \
$${MP_SRC}/mpz/scan0.c \
$${MP_SRC}/mpz/scan1.c \
$${MP_SRC}/mpz/set.c \
$${MP_SRC}/mpz/set_d.c \
$${MP_SRC}/mpz/set_f.c \
$${MP_SRC}/mpz/set_q.c \
$${MP_SRC}/mpz/set_si.c \
$${MP_SRC}/mpz/set_str.c \
$${MP_SRC}/mpz/set_ui.c \
$${MP_SRC}/mpz/setbit.c \
$${MP_SRC}/mpz/size.c \
$${MP_SRC}/mpz/sizeinbase.c \
$${MP_SRC}/mpz/sqrt.c \
$${MP_SRC}/mpz/sqrtrem.c \
$${MP_SRC}/mpz/sub.c \
$${MP_SRC}/mpz/sub_ui.c \
$${MP_SRC}/mpz/tdiv_q.c \
$${MP_SRC}/mpz/tdiv_q_2exp.c \
$${MP_SRC}/mpz/tdiv_q_ui.c \
$${MP_SRC}/mpz/tdiv_qr.c \
$${MP_SRC}/mpz/tdiv_qr_ui.c \
$${MP_SRC}/mpz/tdiv_r.c \
$${MP_SRC}/mpz/tdiv_r_2exp.c \
$${MP_SRC}/mpz/tdiv_r_ui.c \
$${MP_SRC}/mpz/ui_pow_ui.c \

########################################################################



