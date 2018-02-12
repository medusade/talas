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
#   File: etiris.pri
#
# Author: $author$
#   Date: 2/11/2018
#
# QtCreator .pri file for etiris
########################################################################

OTHER_PKG = ../../../../../../..
OTHER_PRJ = ../../../../../..
OTHER_BLD = ..

THIRDPARTY_NAME = thirdparty
THIRDPARTY_PKG = $${OTHER_PKG}/$${THIRDPARTY_NAME}
THIRDPARTY_PRJ = $${OTHER_PRJ}/$${THIRDPARTY_NAME}
THIRDPARTY_SRC = $${OTHER_PRJ}/src/$${THIRDPARTY_NAME}

########################################################################
# etiris
FRAMEWORK_NAME = etiris

ETIRIS_PKG = ../../../../..
ETIRIS_BLD = ../..

ETIRIS_PRJ = $${ETIRIS_PKG}
ETIRIS_BIN = $${ETIRIS_BLD}/bin
ETIRIS_LIB = $${ETIRIS_BLD}/lib
#ETIRIS_SRC = $${ETIRIS_PKG}/src
ETIRIS_SRC = $${THIRDPARTY_SRC}/$${FRAMEWORK_NAME}

CONFIG(debug, debug|release) {
BUILD_CONFIG = Debug
etiris_DEFINES += DEBUG_BUILD
etiris_DEFINES += DBPRINTF
} else {
BUILD_CONFIG = Release
etiris_DEFINES += RELEASE_BUILD
}

# INCLUDEPATH
#
etiris_INCLUDEPATH += \
$${ETIRIS_SRC}/generic \
$${ETIRIS_SRC} \
$${build_etiris_INCLUDEPATH} \

# DEFINES
#
etiris_DEFINES += \
$${build_etiris_DEFINES} \

# LIBS
#
etiris_LIBS += \
-L$${ETIRIS_LIB}/lib$${FRAMEWORK_NAME} \
-l$${FRAMEWORK_NAME} \
