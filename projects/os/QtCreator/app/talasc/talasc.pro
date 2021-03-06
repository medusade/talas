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
#   File: talasc.pro
#
# Author: $author$
#   Date: 2/16/2021
#
# QtCreator .pro file for talas executable talasc
########################################################################
include(../../../../../../build/QtCreator/talas.pri)
include(../../../../../build/QtCreator/talas.pri)
include(../../../../QtCreator/talas.pri)
include(../../talas.pri)
include(../../../../QtCreator/app/talasc/talasc.pri)

TARGET = $${talasc_TARGET}

########################################################################
# INCLUDEPATH
#
INCLUDEPATH += \
$${talasc_INCLUDEPATH} \

# DEFINES
# 
DEFINES += \
$${talasc_DEFINES} \

########################################################################
# OBJECTIVE_HEADERS
#
OBJECTIVE_HEADERS += \
$${talasc_OBJECTIVE_HEADERS} \

# OBJECTIVE_SOURCES
#
OBJECTIVE_SOURCES += \
$${talasc_OBJECTIVE_SOURCES} \

########################################################################
# HEADERS
#
HEADERS += \
$${talasc_HEADERS} \
$${talasc_OBJECTIVE_HEADERS} \

# SOURCES
#
SOURCES += \
$${talasc_SOURCES} \

########################################################################
# FRAMEWORKS
#
FRAMEWORKS += \
$${talasc_FRAMEWORKS} \

# LIBS
#
LIBS += \
$${talasc_LIBS} \
$${FRAMEWORKS} \


