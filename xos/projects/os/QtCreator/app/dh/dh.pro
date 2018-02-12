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
#   File: dh.pro
#
# Author: $author$
#   Date: 2/10/2018
#
# QtCreator .pro file for talas executable dh
########################################################################
include(../../../../../build/QtCreator/talas.pri)
include(../../../../QtCreator/talas.pri)
include(../../talas.pri)
include(../../../../QtCreator/app/dh/dh.pri)

TARGET = $${dh_TARGET}

########################################################################
INCLUDEPATH += \
$${dh_INCLUDEPATH} \

DEFINES += \
$${dh_DEFINES} \

########################################################################
HEADERS += \
$${dh_HEADERS} \

SOURCES += \
$${dh_SOURCES} \

########################################################################
LIBS += \
$${dh_LIBS} \