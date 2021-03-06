########################################################################
# Copyright (c) 1988-2021 $organization$
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
#   File: libresslc.pro
#
# Author: $author$
#   Date: 2/14/2021
#
# QtCreator .pro file for talas executable libresslc
########################################################################
include(../../../../../../build/QtCreator/talas.pri)
include(../../../../../build/QtCreator/talas.pri)
include(../../../../QtCreator/talas.pri)
include(../../talas.pri)
include(../../../../QtCreator/app/libresslc/libresslc.pri)

TARGET = $${libresslc_TARGET}

########################################################################
# INCLUDEPATH
#
INCLUDEPATH += \
$${libresslc_INCLUDEPATH} \

# DEFINES
# 
DEFINES += \
$${libresslc_DEFINES} \

########################################################################
# OBJECTIVE_HEADERS
#
OBJECTIVE_HEADERS += \
$${libresslc_OBJECTIVE_HEADERS} \

# OBJECTIVE_SOURCES
#
OBJECTIVE_SOURCES += \
$${libresslc_OBJECTIVE_SOURCES} \

########################################################################
# HEADERS
#
HEADERS += \
$${libresslc_HEADERS} \
$${libresslc_OBJECTIVE_HEADERS} \

# SOURCES
#
SOURCES += \
$${libresslc_SOURCES} \

########################################################################
# FRAMEWORKS
#
FRAMEWORKS += \
$${libresslc_FRAMEWORKS} \

# LIBS
#
LIBS += \
$${libresslc_LIBS} \
$${FRAMEWORKS} \


