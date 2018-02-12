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
#   File: libressl.pri
#
# Author: $author$
#   Date: 2/3/2017
########################################################################
LIBRESSL_PKG = $${TALAS_PKG}/..
LIBRESSL_GROUP = thirdparty/libressl

LIBRESSL_VERSION_MAJOR = 2
LIBRESSL_VERSION_MINOR = 5
LIBRESSL_VERSION_RELEASE = 1
LIBRESSL_VERSION = \
libressl-$${LIBRESSL_VERSION_MAJOR}.$${LIBRESSL_VERSION_MINOR}.$${LIBRESSL_VERSION_RELEASE}

LIBRESSL_DIR = $${LIBRESSL_GROUP}/$${LIBRESSL_VERSION}
LIBRESSL_SRC = $${LIBRESSL_PKG}/$${LIBRESSL_DIR}
LIBRESSL_BLD = $${LIBRESSL_PKG}/../$${LIBRESSL_DIR}
LIBRESSL_INC = $${LIBRESSL_SRC}/include

########################################################################
# libressl
libressl_INCLUDEPATH += \

libressl_DEFINES += \

libressl_LIBS += \
