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
#   File: libtalas.pro
#
# Author: $author$
#   Date: 11/18/2014
########################################################################
include(../../../../QtCreator/talas.pri)
include(../../talas.pri)
include(../../../../QtCreator/lib/libtalas/libtalas.pri)

TARGET = $${libtalas_TARGET}
TEMPLATE = $${libtalas_TEMPLATE}
CONFIG += $${libtalas_CONFIG}

########################################################################
INCLUDEPATH += \
$${libtalas_INCLUDEPATH} \

DEFINES += \
$${libtalas_DEFINES} \

########################################################################
HEADERS += \
$${libtalas_HEADERS} \

SOURCES += \
$${libtalas_SOURCES} \

########################################################################
