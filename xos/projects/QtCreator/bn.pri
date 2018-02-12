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
#   File: bn.pri
#
# Author: $author$
#   Date: 2/10/2018
#
# QtCreator .pri file for bn
########################################################################

OTHER_PKG = ../../../../../../..
OTHER_PRJ = ../../../../../..
OTHER_BLD = ..

THIRDPARTY_NAME = thirdparty
THIRDPARTY_PKG = $${OTHER_PKG}/$${THIRDPARTY_NAME}
THIRDPARTY_PRJ = $${OTHER_PRJ}/$${THIRDPARTY_NAME}
THIRDPARTY_SRC = $${OTHER_PRJ}/src/$${THIRDPARTY_NAME}

########################################################################
# bn
FRAMEWORK_GROUP = openssl
FRAMEWORK_NAME = bn

BN_PKG = ../../../../..
BN_BLD = ../..

BN_PRJ = $${BN_PKG}
BN_BIN = $${BN_BLD}/bin
BN_LIB = $${BN_BLD}/lib
#BN_SRC = $${BN_PKG}/src
BN_SRC = $${THIRDPARTY_SRC}/$${FRAMEWORK_GROUP}/$${FRAMEWORK_NAME}

CONFIG(debug, debug|release) {
BUILD_CONFIG = Debug
bn_DEFINES += DEBUG_BUILD
} else {
BUILD_CONFIG = Release
bn_DEFINES += RELEASE_BUILD
}

# INCLUDEPATH
#
bn_INCLUDEPATH += \
$${BN_SRC} \
$${build_bn_INCLUDEPATH} \

# DEFINES
#
bn_DEFINES += \
$${build_bn_DEFINES} \

# LIBS
#
bn_LIBS += \
-L$${BN_LIB}/lib$${FRAMEWORK_NAME} \
-l$${FRAMEWORK_NAME} \
