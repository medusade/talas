########################################################################
# Copyright (c) 1988-2014 $organization$
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
#   Date: 11/18/2014
########################################################################
TALAS_PKG = ../../../../..
TALAS_BLD = ../..
TALAS_PRJ = $${TALAS_PKG}
TALAS_BIN = $${TALAS_BLD}/bin
TALAS_LIB = $${TALAS_BLD}/lib
TALAS_SRC = $${TALAS_PKG}/src

CONFIG(debug, debug|release) {
TALAS_CONFIG = Debug
DEFINES += DEBUG_BUILD
} else {
TALAS_CONFIG = Release
DEFINES += RELEASE_BUILD
}

########################################################################
# nadir
NADIR_PKG = $${TALAS_PKG}/../nadir
NADIR_PRJ = $${NADIR_PKG}
NADIR_SRC = $${NADIR_PKG}/src

nadir_INCLUDEPATH += \
$${NADIR_SRC} \

nadir_DEFINES += \

########################################################################
# coral
CORAL_PKG = $${TALAS_PKG}/../coral
CORAL_PRJ = $${CORAL_PKG}
CORAL_SRC = $${CORAL_PKG}/src

coral_INCLUDEPATH += \
$${CORAL_SRC} \

coral_DEFINES += \

########################################################################
# talas
talas_INCLUDEPATH += \
$${TALAS_SRC} \
$${nadir_INCLUDEPATH} \

########################################################################
# talas_bn
talas_bn_INCLUDEPATH += \
$${TALAS_SRC}/thirdparty/openssl/bn \

########################################################################
# talas_mp
talas_mp_INCLUDEPATH += \
$${TALAS_SRC}/thirdparty/gnu/mp \

talas_DEFINES += \
$${nadir_DEFINES} \
