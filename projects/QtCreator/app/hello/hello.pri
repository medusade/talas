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
#   File: hello.pri
#
# Author: $author$
#   Date: 9/13/2019
#
# QtCreator .pri file for talas executable hello
########################################################################

########################################################################
# hello

# hello TARGET
#
hello_TARGET = hello

# hello INCLUDEPATH
#
hello_INCLUDEPATH += \
$${talas_INCLUDEPATH} \
$${openssl_INCLUDEPATH} \

# hello DEFINES
#
hello_DEFINES += \
$${talas_DEFINES} \
$${openssl_DEFINES} \

########################################################################
# hello OBJECTIVE_HEADERS
#
#hello_OBJECTIVE_HEADERS += \
#$${TALAS_SRC}/talas/base/Base.hh \

# hello OBJECTIVE_SOURCES
#
#hello_OBJECTIVE_SOURCES += \
#$${TALAS_SRC}/talas/base/Base.mm \

########################################################################
# hello HEADERS
#
hello_HEADERS += \
$${TALAS_SRC}/talas/network/os/sockets.hpp \
\
$${TALAS_SRC}/talas/protocol/tls/server.hpp \
$${TALAS_SRC}/talas/protocol/tls/client.hpp \
$${TALAS_SRC}/talas/protocol/tls/context.hpp \
$${TALAS_SRC}/talas/protocol/tls/connection.hpp \
$${TALAS_SRC}/talas/protocol/tls/version.hpp \
\
$${TALAS_SRC}/talas/protocol/tls/openssl/server.hpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/server_context.hpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/client.hpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/client_context.hpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/connection.hpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/session.hpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/context.hpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/openssl.hpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/bio_rw.hpp \
\
$${TALAS_SRC}/talas/console/main_opt.hpp \
$${TALAS_SRC}/talas/console/main_main.hpp \
\
$${TALAS_SRC}/talas/app/console/hello/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/hello/main.hpp \

# hello SOURCES
#
hello_SOURCES += \
$${TALAS_SRC}/talas/network/os/sockets.cpp \
\
$${TALAS_SRC}/talas/protocol/tls/openssl/server.cpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/server_context.cpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/client.cpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/client_context.cpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/connection.cpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/session.cpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/context.cpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/openssl.cpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/bio_rw.cpp \
$${TALAS_SRC}/talas/protocol/tls/version.cpp \
\
$${TALAS_SRC}/talas/console/main_opt.cpp \
$${TALAS_SRC}/talas/console/main_main.cpp \
\
$${TALAS_SRC}/talas/app/console/hello/main.cpp \

########################################################################
# hello FRAMEWORKS
#
hello_FRAMEWORKS += \
$${talas_FRAMEWORKS} \

# hello LIBS
#
hello_LIBS += \
$${talas_openssl_LIBS} \


