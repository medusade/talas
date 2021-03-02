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
#   File: httpb.pri
#
# Author: $author$
#   Date: 2/23/2021
#
# QtCreator .pri file for talas executable httpb
########################################################################

########################################################################
# httpb

# httpb TARGET
#
httpb_TARGET = httpb

# httpb INCLUDEPATH
#
httpb_INCLUDEPATH += \
$${talas_INCLUDEPATH} \

# httpb DEFINES
#
httpb_DEFINES += \
$${talas_DEFINES} \
XOS_DEFAULT_LOG_ERROR \
TALAS_APP_CONSOLE_PROTOCOL_HTTP_BASE_MAIN_INSTANCE \

########################################################################
# httpb OBJECTIVE_HEADERS
#
#httpb_OBJECTIVE_HEADERS += \
#$${TALAS_SRC}/talas/base/Base.hh \

# httpb OBJECTIVE_SOURCES
#
#httpb_OBJECTIVE_SOURCES += \
#$${TALAS_SRC}/talas/base/Base.mm \

########################################################################
# httpb HEADERS
#
httpb_HEADERS += \
$${NADIR_SRC}/xos/base/base.hpp \
$${NADIR_SRC}/xos/base/logged.hpp \
$${NADIR_SRC}/xos/base/string.hpp \
$${NADIR_SRC}/xos/io/reader.hpp \
$${NADIR_SRC}/xos/io/writer.hpp \
$${NADIR_SRC}/xos/io/stream.hpp \
$${NADIR_SRC}/xos/io/file/reader.hpp \
$${NADIR_SRC}/xos/io/file/writer.hpp \
$${NADIR_SRC}/xos/io/file/stream.hpp \
$${NADIR_SRC}/xos/io/file/opened.hpp \
$${NADIR_SRC}/xos/io/read/file.hpp \
$${NADIR_SRC}/xos/io/write/file.hpp \
\
$${TALAS_SRC}/talas/protocol/xttp/message/part.hpp \
$${TALAS_SRC}/talas/protocol/xttp/message/line.hpp \
$${TALAS_SRC}/talas/protocol/xttp/message/writer.hpp \
$${TALAS_SRC}/talas/protocol/xttp/message/header/field.hpp \
$${TALAS_SRC}/talas/protocol/xttp/message/header/fields.hpp \
\
$${TALAS_SRC}/talas/protocol/http/message/part.hpp \
$${TALAS_SRC}/talas/protocol/http/content/media/subtype/which.hpp \
$${TALAS_SRC}/talas/protocol/http/content/media/subtype/name.hpp \
$${TALAS_SRC}/talas/protocol/http/content/media/type/which.hpp \
$${TALAS_SRC}/talas/protocol/http/content/media/type/name.hpp \
$${TALAS_SRC}/talas/protocol/http/protocol/which.hpp \
$${TALAS_SRC}/talas/protocol/http/protocol/name.hpp \
$${TALAS_SRC}/talas/protocol/http/protocol/version.hpp \
$${TALAS_SRC}/talas/protocol/http/protocol/identifier.hpp \
\
$${TALAS_SRC}/talas/protocol/xttp/message/header/content/type.hpp \
$${TALAS_SRC}/talas/protocol/xttp/message/header/content/length.hpp \
$${TALAS_SRC}/talas/protocol/xttp/message/body/content.hpp \
$${TALAS_SRC}/talas/protocol/xttp/protocol/name.hpp \
$${TALAS_SRC}/talas/protocol/xttp/protocol/version.hpp \
$${TALAS_SRC}/talas/protocol/xttp/protocol/identifier.hpp \
\
$${TALAS_SRC}/talas/protocol/http/request/method/which.hpp \
$${TALAS_SRC}/talas/protocol/http/request/method/name.hpp \
$${TALAS_SRC}/talas/protocol/http/request/method/nameof.hpp \
$${TALAS_SRC}/talas/protocol/http/request/resource/which.hpp \
$${TALAS_SRC}/talas/protocol/http/request/resource/identifier.hpp \
$${TALAS_SRC}/talas/protocol/http/request/line.hpp \
$${TALAS_SRC}/talas/protocol/http/request/message.hpp \
\
$${TALAS_SRC}/talas/protocol/xttp/request/method.hpp \
$${TALAS_SRC}/talas/protocol/xttp/request/parameters.hpp \
$${TALAS_SRC}/talas/protocol/xttp/request/line.hpp \
$${TALAS_SRC}/talas/protocol/xttp/request/message.hpp \
$${TALAS_SRC}/talas/protocol/xttp/response/status.hpp \
$${TALAS_SRC}/talas/protocol/xttp/response/reason.hpp \
$${TALAS_SRC}/talas/protocol/xttp/response/line.hpp \
$${TALAS_SRC}/talas/protocol/xttp/response/message.hpp \
\
$${TALAS_SRC}/talas/app/console/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/main.hpp \
\
$${TALAS_SRC}/talas/app/console/protocol/http/base/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/protocol/http/base/main.hpp \
\
$${TALAS_SRC}/talas/console/main_main.hpp \

# httpb SOURCES
#
httpb_SOURCES += \
$${TALAS_SRC}/talas/protocol/http/protocol/which.cpp \
$${TALAS_SRC}/talas/protocol/http/protocol/name.cpp \
$${TALAS_SRC}/talas/protocol/http/protocol/version.cpp \
$${TALAS_SRC}/talas/protocol/http/message/part.cpp \
$${TALAS_SRC}/talas/protocol/http/request/method/nameof.cpp \
$${TALAS_SRC}/talas/protocol/http/request/resource/identifier.cpp \
\
$${TALAS_SRC}/talas/protocol/xttp/message/writer.cpp \
$${TALAS_SRC}/talas/protocol/xttp/message/header/field.cpp \
$${TALAS_SRC}/talas/protocol/xttp/message/header/fields.cpp \
$${TALAS_SRC}/talas/protocol/xttp/message/header/content/type.cpp \
$${TALAS_SRC}/talas/protocol/xttp/message/header/content/length.cpp \
$${TALAS_SRC}/talas/protocol/xttp/message/body/content.cpp \
\
$${TALAS_SRC}/talas/protocol/xttp/request/method.cpp \
$${TALAS_SRC}/talas/protocol/xttp/request/parameters.cpp \
\
$${TALAS_SRC}/talas/protocol/xttp/response/status.cpp \
$${TALAS_SRC}/talas/protocol/xttp/response/reason.cpp \
$${TALAS_SRC}/talas/protocol/xttp/response/line.cpp \
$${TALAS_SRC}/talas/protocol/xttp/response/message.hpp \
\
$${TALAS_SRC}/talas/app/console/protocol/http/base/main_opt.cpp \
$${TALAS_SRC}/talas/app/console/protocol/http/base/main.cpp \
\
$${TALAS_SRC}/talas/console/main_main.cpp \

########################################################################
# httpb FRAMEWORKS
#
httpb_FRAMEWORKS += \
$${talas_FRAMEWORKS} \

# httpb LIBS
#
httpb_LIBS += \
$${talas_LIBS} \


