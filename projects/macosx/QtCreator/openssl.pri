########################################################################
# Copyright (c) 1988-2015 $organization$
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
#   File: openssl.pri
#
# Author: $author$
#   Date: 12/25/2015
########################################################################
OPENSSL_GROUP = thirdparty/openssl/
OPENSSL_VERSION = openssl-0.9.8zh
OPENSSL_DIR = $${OPENSSL_GROUP}$${OPENSSL_VERSION}
OPENSSL_SRC = $${TALAS_PKG}/$${OPENSSL_DIR}
OPENSSL_BLD = $${TALAS_PKG}/../$${OPENSSL_DIR}
OPENSSL_INC = $${OPENSSL_SRC}/include

HOME = Users/jboyd

########################################################################
# openssl
home_openssl_INCLUDEPATH += $${HOME}/build/openssl/include
home_openssl_LIBPATH += -L$${HOME}/build/openssl/lib

build_openssl_INCLUDEPATH += \
$${OPENSSL_INC} $${OPENSSL_SRC}/crypto $${OPENSSL_SRC}
build_openssl_LIBPATH += -L$${OPENSSL_SRC}

########################################################################
openssl_INCLUDEPATH += \
$${build_openssl_INCLUDEPATH} \

openssl_DEFINES += \

openssl_LIBS += \
$${build_openssl_LIBPATH} \
-lssl \
-lcrypto \
