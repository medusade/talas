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
#   File: openssl.pri
#
# Author: $author$
#   Date: 9/13/2019
#
# QtCreator .pri file for talas executable openssl
########################################################################

########################################################################
# openssl

# openssl TARGET
#
openssl_exe_TARGET = talas-openssl

# openssl INCLUDEPATH
#
openssl_exe_INCLUDEPATH += \
$${talas_INCLUDEPATH} \
$${openssl_INCLUDEPATH} \

# openssl DEFINES
#
openssl_exe_DEFINES += \
$${talas_DEFINES} \
$${openssl_DEFINES} \

########################################################################
# openssl OBJECTIVE_HEADERS
#
#openssl_exe_OBJECTIVE_HEADERS += \
#$${TALAS_SRC}/talas/base/Base.hh \

# openssl OBJECTIVE_SOURCES
#
#openssl_exe_OBJECTIVE_SOURCES += \
#$${TALAS_SRC}/talas/base/Base.mm \

########################################################################
# openssl HEADERS
#
openssl_exe_HEADERS += \
$${OPENSSL_SRC}/crypto/bio/bio.h \
\
$${TALAS_SRC}/talas/base/base.hpp \
$${TALAS_SRC}/talas/network/os/sockets.hpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/bio_rw.hpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/openssl.hpp \
\
$${TALAS_SRC}/talas/console/main_opt.hpp \
$${TALAS_SRC}/talas/console/main.hpp \
$${TALAS_SRC}/talas/console/main_main.hpp \
\
$${TALAS_SRC}/talas/app/console/openssl/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/openssl/main.hpp \

# openssl SOURCES
#
openssl_exe_SOURCES += \
$${OPENSSL_SRC}/crypto/bio/bio_lib.c \
\
$${TALAS_SRC}/talas/network/os/sockets.cpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/bio_rw.cpp \
$${TALAS_SRC}/talas/protocol/tls/openssl/openssl.cpp \
\
$${TALAS_SRC}/talas/console/main_main.cpp \
\
$${TALAS_SRC}/talas/app/console/openssl/main_opt.cpp \
$${TALAS_SRC}/talas/app/console/openssl/main.cpp \

########################################################################
# openssl FRAMEWORKS
#
openssl_exe_FRAMEWORKS += \
$${talas_FRAMEWORKS} \

# openssl LIBS
#
openssl_exe_LIBS += \
$${talas_openssl_LIBS} \


