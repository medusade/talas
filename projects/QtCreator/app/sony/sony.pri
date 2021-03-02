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
#   File: sony.pri
#
# Author: $author$
#   Date: 2/20/2021
#
# QtCreator .pri file for talas executable sony
########################################################################

########################################################################
# sony

# sony TARGET
#
sony_TARGET = sony

# sony INCLUDEPATH
#
sony_INCLUDEPATH += \
$${talas_INCLUDEPATH} \

# sony DEFINES
#
sony_DEFINES += \
$${talas_DEFINES} \
XOS_DEFAULT_LOG_ERROR \
TALAS_APP_CONSOLE_SONY_CLIENT_MAIN_INSTANCE \

########################################################################
# sony OBJECTIVE_HEADERS
#
#sony_OBJECTIVE_HEADERS += \
#$${TALAS_SRC}/talas/base/Base.hh \

# sony OBJECTIVE_SOURCES
#
#sony_OBJECTIVE_SOURCES += \
#$${TALAS_SRC}/talas/base/Base.mm \

########################################################################
# sony HEADERS
#
sony_HEADERS += \
$${NADIR_SRC}/xos/io/socket/reader.hpp \
$${NADIR_SRC}/xos/io/socket/writer.hpp \
\
$${TALAS_SRC}/talas/base/string.hpp \
$${TALAS_SRC}/talas/base/exception.hpp \
$${TALAS_SRC}/talas/io/reader.hpp \
$${TALAS_SRC}/talas/io/writer.hpp \
$${TALAS_SRC}/talas/io/file.hpp \
$${TALAS_SRC}/talas/io/socket/reader.hpp \
$${TALAS_SRC}/talas/io/socket/writer.hpp \
\
$${TALAS_SRC}/talas/console/main.hpp \
$${TALAS_SRC}/talas/app/console/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/main.hpp \
$${TALAS_SRC}/talas/app/console/network/base/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/network/base/main.hpp \
$${TALAS_SRC}/talas/app/console/network/client/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/network/client/main.hpp \
\
$${TALAS_SRC}/talas/app/console/sony/client/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/sony/client/main.hpp \
\
$${TALAS_SRC}/talas/console/main_main.hpp \

# sony SOURCES
#
sony_SOURCES += \
$${NADIR_SRC}/xos/io/file/stream.cpp \
\
$${TALAS_SRC}/talas/base/string.cpp \
$${TALAS_SRC}/talas/base/exception.cpp \
$${TALAS_SRC}/talas/io/file.cpp \
\
$${TALAS_SRC}/talas/io/socket/reader.cpp \
\
$${TALAS_SRC}/talas/app/console/sony/client/main_opt.cpp \
$${TALAS_SRC}/talas/app/console/sony/client/main.cpp \
\
$${TALAS_SRC}/talas/console/main_main.cpp \

########################################################################
# sony FRAMEWORKS
#
sony_FRAMEWORKS += \
$${talas_FRAMEWORKS} \

# sony LIBS
#
sony_LIBS += \
$${talas_LIBS} \

########################################################################
# NO Qt
QT -= gui core

