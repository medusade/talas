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
#   File: talasc.pri
#
# Author: $author$
#   Date: 2/16/2021
#
# QtCreator .pri file for talas executable talasc
########################################################################

########################################################################
# talasc

# talasc TARGET
#
talasc_TARGET = talasc

# talasc INCLUDEPATH
#
talasc_INCLUDEPATH += \
$${talas_INCLUDEPATH} \

# talasc DEFINES
#
talasc_DEFINES += \
$${talas_DEFINES} \
XOS_DEFAULT_LOG_ERROR \
TALAS_APP_CONSOLE_NETWORK_CLIENT_MAIN_INSTANCE \

########################################################################
# talasc OBJECTIVE_HEADERS
#
#talasc_OBJECTIVE_HEADERS += \
#$${TALAS_SRC}/talas/base/Base.hh \

# talasc OBJECTIVE_SOURCES
#
#talasc_OBJECTIVE_SOURCES += \
#$${TALAS_SRC}/talas/base/Base.mm \

########################################################################
# talasc HEADERS
#
talasc_HEADERS += \
$${NADIR_SRC}/xos/base/string.hpp \
$${NADIR_SRC}/xos/io/reader.hpp \
$${NADIR_SRC}/xos/io/writer.hpp \
$${NADIR_SRC}/xos/io/socket/reader.hpp \
$${NADIR_SRC}/xos/io/socket/writer.hpp \
\
$${TALAS_SRC}/talas/base/string.hpp \
$${TALAS_SRC}/talas/io/reader.hpp \
$${TALAS_SRC}/talas/io/writer.hpp \
$${TALAS_SRC}/talas/io/socket/reader.hpp \
$${TALAS_SRC}/talas/io/socket/writer.hpp \
\
$${TALAS_SRC}/talas/console/main.hpp \
$${TALAS_SRC}/talas/app/console/network/base/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/network/base/main.hpp \
$${TALAS_SRC}/talas/app/console/network/client/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/network/client/main.hpp \
\
$${TALAS_SRC}/talas/console/main_main.hpp \

# talasc SOURCES
#
talasc_SOURCES += \
$${TALAS_SRC}/talas/base/string.cpp \
\
$${TALAS_SRC}/talas/io/socket/reader.cpp \
$${TALAS_SRC}/talas/io/socket/writer.cpp \
\
$${TALAS_SRC}/talas/app/console/network/client/main_opt.cpp \
$${TALAS_SRC}/talas/app/console/network/client/main.cpp \
\
$${TALAS_SRC}/talas/console/main_main.cpp \

########################################################################
# talasc FRAMEWORKS
#
talasc_FRAMEWORKS += \
$${talas_FRAMEWORKS} \

# talasc LIBS
#
talasc_LIBS += \
$${talas_LIBS} \


