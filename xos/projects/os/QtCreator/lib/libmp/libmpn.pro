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
#   File: libmpn.pro
#
# Author: $author$
#   Date: 2/9/2018
#
# QtCreator .pro file for talas library libmpn
########################################################################
#include(../../../../../build/QtCreator/talas.pri)
#include(../../../../QtCreator/talas.pri)
#include(../../talas.pri)
include(../../../../../build/QtCreator/mp.pri)
include(../../../../QtCreator/mp.pri)
include(../../mp.pri)
include(../../../../QtCreator/lib/libmp/libmpn.pri)

TARGET = $${libmpn_TARGET}
TEMPLATE = $${libmpn_TEMPLATE}
CONFIG += $${libmpn_CONFIG}

########################################################################
INCLUDEPATH += \
$${libmpn_INCLUDEPATH} \

DEFINES += \
$${libmpn_DEFINES} \

########################################################################
HEADERS += \
$${libmpn_HEADERS} \

SOURCES += \
$${libmpn_SOURCES} \

########################################################################


