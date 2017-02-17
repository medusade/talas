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

########################################################################
talas_openssl_HEADERS += \
$${OPENSSL_SRC}/crypto/bio/bio.h \

talas_openssl_SOURCES += \
$${OPENSSL_SRC}/crypto/bio/bio_lib.c \

########################################################################
talas_openssl_HEADERS += \
$${TALAS_SRC}/talas/protocol/tls/openssl/bio_rw.hpp \
$${TALAS_SRC}/talas/network/os/sockets.hpp \

talas_openssl_SOURCES += \
$${TALAS_SRC}/talas/protocol/tls/openssl/bio_rw.cpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/openssl.cpp \
$${TALAS_SRC}/talas/network/os/sockets.cpp \

########################################################################
talas_openssl_HEADERS += \
$${TALAS_SRC}/talas/app/console/openssl/main.hpp \
$${TALAS_SRC}/talas/app/console/openssl/main_opt.hpp \
$${TALAS_SRC}/talas/console/main.hpp \
$${TALAS_SRC}/talas/console/main_opt.hpp \
$${TALAS_SRC}/talas/console/main_main.hpp \
$${TALAS_SRC}/talas/base/base.hpp \

talas_openssl_SOURCES += \
$${TALAS_SRC}/talas/app/console/openssl/main.cpp \
$${TALAS_SRC}/talas/console/main_opt.cpp \
$${TALAS_SRC}/talas/console/main_main.cpp \

########################################################################
_talas_openssl_HEADERS += \

_talas_openssl_SOURCES += \
