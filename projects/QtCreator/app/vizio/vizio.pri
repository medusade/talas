########################################################################
# Copyright (c) 1988-2021 $organization$
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
#   File: vizio.pri
#
# Author: $author$
#   Date: 2/25/2021
#
# QtCreator .pri file for talas executable vizio
########################################################################

########################################################################
# vizio

# vizio TARGET
#
vizio_TARGET = vizio

# vizio INCLUDEPATH
#
vizio_INCLUDEPATH += \
$${talas_INCLUDEPATH} \
$${libressl_INCLUDEPATH} \

# vizio DEFINES
#
vizio_DEFINES += \
$${talas_DEFINES} \
$${libressl_DEFINES} \
XOS_DEFAULT_LOG_ERROR \
TALAS_APP_CONSOLE_VIZIO_CLIENT_MAIN_INSTANCE \

########################################################################
# vizio OBJECTIVE_HEADERS
#
#vizio_OBJECTIVE_HEADERS += \
#$${TALAS_SRC}/talas/base/Base.hh \

# vizio OBJECTIVE_SOURCES
#
#vizio_OBJECTIVE_SOURCES += \
#$${TALAS_SRC}/talas/base/Base.mm \

########################################################################
# vizio HEADERS
#
vizio_HEADERS += \
$${LIBRESSL_SRC}/include/openssl/ssl.h \
$${LIBRESSL_SRC}/include/openssl/ssl_cleanup.h \
$${LIBRESSL_SRC}/include/tls.h \
$${LIBRESSL_SRC}/include/tls_cleanup.h \
\
$${TALAS_SRC}/talas/io/reader.hpp \
$${TALAS_SRC}/talas/io/writer.hpp \
$${TALAS_SRC}/talas/io/socket/reader.hpp \
$${TALAS_SRC}/talas/io/socket/writer.hpp \
\
$${TALAS_SRC}/talas/protocol/tls/libressl/libressl.hpp \
$${TALAS_SRC}/talas/protocol/tls/libressl/writer.hpp \
$${TALAS_SRC}/talas/protocol/tls/libressl/reader.hpp \
\
$${TALAS_SRC}/talas/console/main_opt.hpp \
$${TALAS_SRC}/talas/console/main.hpp \
\
$${TALAS_SRC}/talas/app/console/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/main.hpp \
\
$${TALAS_SRC}/talas/app/console/network/base/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/network/base/main.hpp \
$${TALAS_SRC}/talas/app/console/network/client/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/network/client/main.hpp \
\
$${TALAS_SRC}/talas/app/console/protocol/tls/base/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/protocol/tls/base/main.hpp \
$${TALAS_SRC}/talas/app/console/protocol/tls/client/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/protocol/tls/client/main.hpp \
\
$${TALAS_SRC}/talas/app/console/libressl/base/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/libressl/base/main.hpp \
$${TALAS_SRC}/talas/app/console/libressl/client/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/libressl/client/main.hpp \
\
$${TALAS_SRC}/talas/app/console/vizio/base/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/vizio/base/main.hpp \
$${TALAS_SRC}/talas/app/console/vizio/client/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/vizio/client/main.hpp \
\
$${TALAS_SRC}/talas/console/main_main.hpp \

# vizio SOURCES
#
vizio_SOURCES += \
$${LIBRESSL_SRC}/ssl/ssl_err.c \
$${LIBRESSL_SRC}/ssl/ssl_err_cleanup.c \
$${LIBRESSL_SRC}/ssl/ssl_algs.c \
$${LIBRESSL_SRC}/ssl/ssl_algs_cleanup.c \
$${LIBRESSL_SRC}/tls/tls.c \
$${LIBRESSL_SRC}/tls/tls_cleanup.c \
\
$${TALAS_SRC}/talas/app/console/vizio/client/main_opt.cpp \
$${TALAS_SRC}/talas/app/console/vizio/client/main.cpp \
\
$${TALAS_SRC}/talas/console/main_main.cpp \

########################################################################
# vizio FRAMEWORKS
#
vizio_FRAMEWORKS += \
$${talas_FRAMEWORKS} \

# vizio LIBS
#
vizio_LIBS += \
$${talas_libressl_LIBS} \
