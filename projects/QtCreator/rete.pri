########################################################################
# Copyright (c) 1988-2017 $organization$
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
#   File: rete.pri
#
# Author: $author$
#   Date: 2/15/2017
########################################################################

########################################################################
# patrona
PATRONA_PKG = $${TALAS_PKG}/../patrona
PATRONA_PRJ = $${PATRONA_PKG}
PATRONA_SRC = $${PATRONA_PKG}/src

patrona_INCLUDEPATH += \
$${PATRONA_SRC} \

patrona_DEFINES += \

patrona_LIBS += \

########################################################################
# crono
CRONO_PKG = $${TALAS_PKG}/../crono
CRONO_PRJ = $${CRONO_PKG}
CRONO_SRC = $${CRONO_PKG}/src

crono_INCLUDEPATH += \
$${CRONO_SRC} \

crono_DEFINES += \

crono_LIBS += \

########################################################################
# rete
RETE_PKG = $${TALAS_PKG}/../rete
RETE_PRJ = $${RETE_PKG}
RETE_SRC = $${RETE_PKG}/src

rete_INCLUDEPATH += \
$${RETE_SRC} \
$${crono_INCLUDEPATH} \
$${patrona_INCLUDEPATH} \

rete_DEFINES += \

rete_LIBS += \
