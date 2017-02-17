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

HOME = /Users/jboyd

########################################################################
# libressl
home_libressl_INCLUDEPATH += $${HOME}/build/libressl/include
home_libressl_LIBPATH += $${HOME}/build/libressl/lib

build_libressl_INCLUDEPATH += $${LIBRESSL_INC}
build_libressl_LIBPATH += $${home_libressl_LIBPATH}

libressl_INCLUDEPATH += \
$${build_libressl_INCLUDEPATH} \

libressl_DEFINES += \

libressl_LIBS += \
-L$${build_libressl_LIBPATH} \
-ltls \
-lssl \
-lcrypto \
