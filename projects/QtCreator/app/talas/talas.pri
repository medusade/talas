########################################################################
# Copyright (c) 1988-2018 $organization$
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
#   File: talas.pri
#
# Author: $author$
#   Date: 11/17/2018, 12/26/2020
#
# QtCreator .pri file for talas executable talas
########################################################################

########################################################################
# talas

# talas_exe TARGET
#
talas_exe_TARGET = talas

# talas_exe INCLUDEPATH
#
talas_exe_INCLUDEPATH += \
$${talas_INCLUDEPATH} \

# talas_exe DEFINES
#
talas_exe_DEFINES += \
$${talas_DEFINES} \
XOS_DEFAULT_LOG_ERROR \

########################################################################
# talas_exe OBJECTIVE_HEADERS
#
#talas_exe_OBJECTIVE_HEADERS += \
#$${TALAS_SRC}/talas/base/Base.hh \

# talas_exe OBJECTIVE_SOURCES
#
#talas_exe_OBJECTIVE_SOURCES += \
#$${TALAS_SRC}/talas/base/Base.mm \

########################################################################
# talas_exe HEADERS
#
talas_exe_HEADERS += \
$${TALAS_SRC}/talas/console/main.hpp \
$${TALAS_SRC}/talas/console/main_opt.hpp \
$${TALAS_SRC}/talas/console/main_main.hpp \
$${TALAS_SRC}/talas/app/console/talas/main_opt.hpp \
$${TALAS_SRC}/talas/app/console/talas/main.hpp \

# talas_exe SOURCES
#
talas_exe_SOURCES += \
$${TALAS_SRC}/talas/console/main_opt.cpp \
$${TALAS_SRC}/talas/console/main_main.cpp \
$${TALAS_SRC}/talas/app/console/talas/main.cpp \

########################################################################
# talas_exe FRAMEWORKS
#
talas_exe_FRAMEWORKS += \
$${talas_FRAMEWORKS} \

# talas_exe LIBS
#
talas_exe_LIBS += \
$${talas_LIBS} \


