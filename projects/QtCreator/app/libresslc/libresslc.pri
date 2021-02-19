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
#   File: libresslc.pri
#
# Author: $author$
#   Date: 2/14/2021, 2/18/2021
#
# QtCreator .pri file for talas executable libresslc
########################################################################

########################################################################
# libresslc

# libresslc TARGET
#
libresslc_TARGET = libresslc

# libresslc INCLUDEPATH
#
libresslc_INCLUDEPATH += \
$${talas_INCLUDEPATH} \
$${libressl_INCLUDEPATH} \

# libresslc DEFINES
#
libresslc_DEFINES += \
$${talas_DEFINES} \
$${libressl_DEFINES} \
XOS_DEFAULT_LOG_ERROR \
TALAS_APP_CONSOLE_LIBRESSL_CLIENT_MAIN_INSTANCE \

########################################################################
# libresslc OBJECTIVE_HEADERS
#
#libresslc_OBJECTIVE_HEADERS += \
#$${TALAS_SRC}/talas/base/Base.hh \

# libresslc OBJECTIVE_SOURCES
#
#libresslc_OBJECTIVE_SOURCES += \
#$${TALAS_SRC}/talas/base/Base.mm \

########################################################################
# libresslc HEADERS
#
libresslc_HEADERS += \
$${LIBRESSL_SRC}/include/openssl/ssl.h \
$${LIBRESSL_SRC}/include/openssl/ssl_cleanup.h \
$${LIBRESSL_SRC}/include/tls.h \
$${LIBRESSL_SRC}/include/tls_cleanup.h \
\
$${NADIR_SRC}/xos/base/string.hpp \
\
$${NADIR_SRC}/xos/io/reader.hpp \
$${NADIR_SRC}/xos/io/writer.hpp \
$${NADIR_SRC}/xos/io/socket/reader.hpp \
$${NADIR_SRC}/xos/io/socket/writer.hpp \
\
$${TALAS_SRC}/talas/base/string.hpp \
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
$${TALAS_SRC}/talas/console/main_main.hpp \
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

# libresslc SOURCES
#
libresslc_SOURCES += \
$${LIBRESSL_SRC}/ssl/ssl_err.c \
$${LIBRESSL_SRC}/ssl/ssl_err_cleanup.c \
$${LIBRESSL_SRC}/ssl/ssl_algs.c \
$${LIBRESSL_SRC}/ssl/ssl_algs_cleanup.c \
$${LIBRESSL_SRC}/tls/tls.c \
$${LIBRESSL_SRC}/tls/tls_cleanup.c \
\
$${TALAS_SRC}/talas/protocol/tls/libressl/libressl.cpp \
$${TALAS_SRC}/talas/protocol/tls/libressl/writer.cpp \
$${TALAS_SRC}/talas/protocol/tls/libressl/reader.cpp \
\
$${TALAS_SRC}/talas/console/main_main.cpp \
\
$${TALAS_SRC}/talas/app/console/libressl/client/main_opt.cpp \
$${TALAS_SRC}/talas/app/console/libressl/client/main.cpp \

########################################################################
# libresslc FRAMEWORKS
#
libresslc_FRAMEWORKS += \
$${talas_FRAMEWORKS} \

# libresslc LIBS
#
libresslc_LIBS += \
$${talas_libressl_LIBS} \
