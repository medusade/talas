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
#   File: rsa.pri
#
# Author: $author$
#   Date: 3/25/2019
#
# QtCreator .pri file for talas executable rsa
########################################################################

########################################################################
# rsa

# rsa TARGET
#
rsa_TARGET = rsa

# rsa INCLUDEPATH
#
rsa_INCLUDEPATH += \
$${talas_INCLUDEPATH} \

# rsa DEFINES
#
rsa_DEFINES += \
$${talas_DEFINES} \

########################################################################
# rsa OBJECTIVE_HEADERS
#
#rsa_OBJECTIVE_HEADERS += \
#$${TALAS_SRC}/talas/base/Base.hh \

# rsa OBJECTIVE_SOURCES
#
#rsa_OBJECTIVE_SOURCES += \
#$${TALAS_SRC}/talas/base/Base.mm \

########################################################################
# rsa HEADERS
#
rsa_HEADERS += \
$${TALAS_SRC}/talas/io/asn1/reader_events.hpp \
$${TALAS_SRC}/talas/io/asn1/reader.hpp \
\
$${TALAS_SRC}/talas/app/console/rsa/private_key.hpp \
$${TALAS_SRC}/talas/app/console/rsa/public_key.hpp \
$${TALAS_SRC}/talas/app/console/rsa/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/rsa/main.hpp \
$${TALAS_SRC}/talas/console/main_main.hpp \

# rsa SOURCES
#
rsa_SOURCES += \
$${TALAS_SRC}/talas/io/asn1/reader_events.cpp \
$${TALAS_SRC}/talas/io/asn1/reader.cpp \
\
$${TALAS_SRC}/talas/app/console/rsa/private_key.cpp \
$${TALAS_SRC}/talas/app/console/rsa/public_key.cpp \
$${TALAS_SRC}/talas/app/console/rsa/main_opt.cpp \
$${TALAS_SRC}/talas/app/console/rsa/main.cpp \
$${TALAS_SRC}/talas/console/main_main.cpp \

########################################################################
# rsa FRAMEWORKS
#
rsa_FRAMEWORKS += \
$${talas_FRAMEWORKS} \

# rsa LIBS
#
rsa_LIBS += \
$${talas_LIBS} \


