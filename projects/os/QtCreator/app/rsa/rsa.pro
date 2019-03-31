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
#   File: rsa.pro
#
# Author: $author$
#   Date: 3/25/2019
#
# QtCreator .pro file for talas executable rsa
########################################################################
include(../../../../../build/QtCreator/talas.pri)
include(../../../../QtCreator/talas.pri)
include(../../talas.pri)
include(../../../../QtCreator/app/rsa/rsa.pri)

TARGET = $${rsa_TARGET}

########################################################################
# INCLUDEPATH
#
INCLUDEPATH += \
$${rsa_INCLUDEPATH} \

# DEFINES
# 
DEFINES += \
$${rsa_DEFINES} \

########################################################################
# OBJECTIVE_HEADERS
#
OBJECTIVE_HEADERS += \
$${rsa_OBJECTIVE_HEADERS} \

# OBJECTIVE_SOURCES
#
OBJECTIVE_SOURCES += \
$${rsa_OBJECTIVE_SOURCES} \

########################################################################
# HEADERS
#
HEADERS += \
$${rsa_HEADERS} \
$${OBJECTIVE_HEADERS} \

# SOURCES
#
SOURCES += \
$${rsa_SOURCES} \

########################################################################
# FRAMEWORKS
#
FRAMEWORKS += \
$${rsa_FRAMEWORKS} \

# LIBS
#
LIBS += \
$${rsa_LIBS} \
$${FRAMEWORKS} \


