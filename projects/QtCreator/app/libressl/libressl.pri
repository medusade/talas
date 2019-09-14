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
#   File: libressl.pri
#
# Author: $author$
#   Date: 9/12/2019
#
# QtCreator .pri file for talas executable libressl
########################################################################

########################################################################
# libressl

# libressl TARGET
#
libressl_exe_TARGET = talas-libressl

# libressl INCLUDEPATH
#
libressl_exe_INCLUDEPATH += \
$${talas_INCLUDEPATH} \
$${libressl_INCLUDEPATH} \

# libressl DEFINES
#
libressl_exe_DEFINES += \
$${talas_DEFINES} \
$${libressl_DEFINES} \

########################################################################
# libressl OBJECTIVE_HEADERS
#
#libressl_exe_OBJECTIVE_HEADERS += \
#$${TALAS_SRC}/talas/base/Base.hh \

# libressl OBJECTIVE_SOURCES
#
#libressl_exe_OBJECTIVE_SOURCES += \
#$${TALAS_SRC}/talas/base/Base.mm \

########################################################################
# libressl HEADERS
#
libressl_exe_HEADERS += \
$${LIBRESSL_SRC}/include/openssl/ssl.h \
$${LIBRESSL_SRC}/include/openssl/ssl_cleanup.h \
$${LIBRESSL_SRC}/include/tls.h \
$${LIBRESSL_SRC}/include/tls_cleanup.h \
\
$${TALAS_SRC}/talas/base/base.hpp \
$${TALAS_SRC}/talas/network/os/sockets.hpp \
$${TALAS_SRC}/talas/protocol/tls/libressl/libressl.hpp \
\
$${TALAS_SRC}/talas/console/main.hpp \
$${TALAS_SRC}/talas/console/main_opt.hpp \
$${TALAS_SRC}/talas/console/main_main.hpp \
\
$${TALAS_SRC}/talas/app/console/libressl/main.hpp \
$${TALAS_SRC}/talas/app/console/libressl/main_opt.hpp \

# libressl SOURCES
#
libressl_exe_SOURCES += \
$${LIBRESSL_SRC}/ssl/ssl_err.c \
$${LIBRESSL_SRC}/ssl/ssl_err_cleanup.c \
$${LIBRESSL_SRC}/ssl/ssl_algs.c \
$${LIBRESSL_SRC}/ssl/ssl_algs_cleanup.c \
$${LIBRESSL_SRC}/tls/tls.c \
$${LIBRESSL_SRC}/tls/tls_cleanup.c \
\
$${TALAS_SRC}/talas/base/base.cpp \
$${TALAS_SRC}/talas/network/os/sockets.cpp \
$${TALAS_SRC}/talas/protocol/tls/libressl/libressl.cpp \
\
$${TALAS_SRC}/talas/console/main_main.cpp \
\
$${TALAS_SRC}/talas/app/console/libressl/main.cpp \

########################################################################
# libressl FRAMEWORKS
#
libressl_exe_FRAMEWORKS += \
$${talas_FRAMEWORKS} \

# libressl LIBS
#
libressl_exe_LIBS += \
$${talas_libressl_LIBS} \


