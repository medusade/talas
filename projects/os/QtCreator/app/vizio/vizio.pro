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
#   File: vizio.pro
#
# Author: $author$
#   Date: 2/25/2021
#
# QtCreator .pro file for talas executable vizio
########################################################################
include(../../../../../../build/QtCreator/talas.pri)
include(../../../../../build/QtCreator/talas.pri)
include(../../../../QtCreator/talas.pri)
include(../../talas.pri)
include(../../../../QtCreator/app/vizio/vizio.pri)

TARGET = $${vizio_TARGET}

########################################################################
# INCLUDEPATH
#
INCLUDEPATH += \
$${vizio_INCLUDEPATH} \

# DEFINES
# 
DEFINES += \
$${vizio_DEFINES} \

########################################################################
# OBJECTIVE_HEADERS
#
OBJECTIVE_HEADERS += \
$${vizio_OBJECTIVE_HEADERS} \

# OBJECTIVE_SOURCES
#
OBJECTIVE_SOURCES += \
$${vizio_OBJECTIVE_SOURCES} \

########################################################################
# HEADERS
#
HEADERS += \
$${vizio_HEADERS} \
$${vizio_OBJECTIVE_HEADERS} \

# SOURCES
#
SOURCES += \
$${vizio_SOURCES} \

########################################################################
# FRAMEWORKS
#
FRAMEWORKS += \
$${vizio_FRAMEWORKS} \

# LIBS
#
LIBS += \
$${vizio_LIBS} \
$${FRAMEWORKS} \


