########################################################################
# Copyright (c) 1988-2019 $organization$
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
#   File: libressl.pro
#
# Author: $author$
#   Date: 9/12/2019
#
# QtCreator .pro file for talas executable libressl
########################################################################
include(../../../../../build/QtCreator/talas.pri)
include(../../../../QtCreator/talas.pri)
include(../../talas.pri)
include(../../../../QtCreator/app/libressl/libressl.pri)

TARGET = $${libressl_exe_TARGET}

########################################################################
# INCLUDEPATH
#
INCLUDEPATH += \
$${libressl_exe_INCLUDEPATH} \

# DEFINES
# 
DEFINES += \
$${libressl_exe_DEFINES} \

########################################################################
# OBJECTIVE_HEADERS
#
OBJECTIVE_HEADERS += \
$${libressl_exe_OBJECTIVE_HEADERS} \

# OBJECTIVE_SOURCES
#
SOURCES += \
$${libressl_exe_OBJECTIVE_SOURCES} \

########################################################################
# HEADERS
#
HEADERS += \
$${libressl_exe_HEADERS} \

# SOURCES
#
SOURCES += \
$${libressl_exe_SOURCES} \
$${OBJECTIVE_SOURCES} \

########################################################################
# FRAMEWORKS
#
FRAMEWORKS += \
$${libressl_exe_FRAMEWORKS} \

# LIBS
#
LIBS += \
$${libressl_exe_LIBS} \
$${FRAMEWORKS} \


