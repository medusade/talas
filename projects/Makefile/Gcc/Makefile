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
#   File: Makefile
#
# Author: $author$
#   Date: 11/18/2018
#
# generic Gcc Makefile for talas
########################################################################

OTHER_VERSION_PKG = ${PKG}
OTHER_DEPENDS_PKG = ${PKG}/..
OTHER_THIRDPARTY_NAME = thirdparty
OTHER_THIRDPARTY_VERSION_PKG = ${OTHER_VERSION_PKG}/${OTHER_THIRDPARTY_NAME}

TALAS_PKG = ${PKG}
TALAS_SRC = ${TALAS_PKG}/src
TALAS_BLD = ${TALAS_PKG}/${BLD}/${BUILD_TYPE}
TALAS_LIB = ${TALAS_BLD}/lib
TALAS_BIN = ${TALAS_BLD}/bin

########################################################################
# bn
BN_VERSION_MAJOR = 0
BN_VERSION_MINOR = 0
BN_VERSION_RELEASE = 0
BN_VERSION = ${BN_VERSION_MAJOR}.${BN_VERSION_MINOR}.${BN_VERSION_RELEASE}
BN_NAME = bn
BN_GROUP = openssl
BN_VERSION_DIR = ${BN_GROUP}/${BN_NAME}-${BN_VERSION}
BN_DEPENDS_DIR = ${BN_NAME}

#BN_PKG = ${OTHER_THIRDPARTY_VERSION_PKG}/${BN_VERSION_DIR}
#BN_PKG = ${OTHER_VERSION_PKG}/${BN_VERSION_DIR}
#BN_PKG = ${OTHER_DEPENDS_PKG}/${BN_DEPENDS_DIR}
BN_PKG = ${TALAS_PKG}
BN_SRC = ${TALAS_SRC}/${OTHER_THIRDPARTY_NAME}/${BN_GROUP}/${BN_NAME}
#BN_SRC = ${BN_PKG}/src/${BN_GROUP}/${BN_NAME}
#BN_SRC = ${BN_PKG}/src
BN_BLD = ${BN_PKG}/${BLD}/${BUILD_TYPE}
BN_LIB = ${BN_BLD}/lib
BN_BIN = ${BN_BLD}/bin

# bn USRDEFINES
#
bn_USRDEFINES += \

# bn USRINCLUDES
#
bn_USRINCLUDES += \
-I${BN_SRC} \

# bn USRCXXFLAGS
#
bn_USRCXXFLAGS += \

# bn USRLIBDIRS
#
bn_USRLIBDIRS += \
-L${BN_LIB} \

# bn LIBS
#
bn_LIBS += \
-lbn \

# bn FRAMEWORKS
#
bn_FRAMEWORKS += \

########################################################################
# mp
MP_VERSION_MAJOR = 0
MP_VERSION_MINOR = 0
MP_VERSION_RELEASE = 0
MP_VERSION = ${MP_VERSION_MAJOR}.${MP_VERSION_MINOR}.${MP_VERSION_RELEASE}
MP_NAME = mp
MP_GROUP = gnu
MP_VERSION_DIR = ${MP_GROUP}/${MP_NAME}-${MP_VERSION}
MP_DEPENDS_DIR = ${MP_NAME}

#MP_PKG = ${OTHER_THIRDPARTY_VERSION_PKG}/${MP_VERSION_DIR}
#MP_PKG = ${OTHER_VERSION_PKG}/${MP_VERSION_DIR}
#MP_PKG = ${OTHER_DEPENDS_PKG}/${MP_DEPENDS_DIR}
MP_PKG = ${TALAS_PKG}
MP_SRC = ${TALAS_SRC}/${OTHER_THIRDPARTY_NAME}/${MP_GROUP}/${MP_NAME}
#MP_SRC = ${MP_PKG}/src/${BN_GROUP}/${BN_NAME}
#MP_SRC = ${MP_PKG}/src
MP_BLD = ${MP_PKG}/${BLD}/${BUILD_TYPE}
MP_LIB = ${MP_BLD}/lib
MP_BIN = ${MP_BLD}/bin

# mp USRDEFINES
#
mp_USRDEFINES += \
-D_NO_INLINES \
-DNO_ASM \

# mp USRINCLUDES
#
mp_USRINCLUDES += \
-I${MP_SRC} \

# mp USRCXXFLAGS
#
mp_USRCXXFLAGS += \

# mp USRLIBDIRS
#
mp_USRLIBDIRS += \
-L${MP_LIB} \

# mp LIBS
#
mp_LIBS += \
-lmpz \
-lmpn \
-lmp \

# mp FRAMEWORKS
#
mp_FRAMEWORKS += \

########################################################################
# nadir
NADIR_VERSION_MAJOR = 0
NADIR_VERSION_MINOR = 0
NADIR_VERSION_RELEASE = 0
NADIR_VERSION = ${NADIR_VERSION_MAJOR}.${NADIR_VERSION_MINOR}.${NADIR_VERSION_RELEASE}
NADIR_NAME = nadir
NADIR_GROUP = ${NADIR_NAME}
NADIR_VERSION_DIR = ${NADIR_GROUP}/${NADIR_NAME}-${NADIR_VERSION}
NADIR_DEPENDS_DIR = ${NADIR_NAME}

#NADIR_PKG = ${OTHER_THIRDPARTY_VERSION_PKG}/${NADIR_VERSION_DIR}
#NADIR_PKG = ${OTHER_VERSION_PKG}/${NADIR_VERSION_DIR}
NADIR_PKG = ${OTHER_DEPENDS_PKG}/${NADIR_DEPENDS_DIR}
#NADIR_SRC = ${NADIR_PKG}/src/${BN_GROUP}/${BN_NAME}
NADIR_SRC = ${NADIR_PKG}/src
NADIR_BLD = ${NADIR_PKG}/${BLD}/${BUILD_TYPE}
NADIR_LIB = ${NADIR_BLD}/lib
NADIR_BIN = ${NADIR_BLD}/bin

# nadir USRDEFINES
#
nadir_USRDEFINES += \

# nadir USRINCLUDES
#
nadir_USRINCLUDES += \
-I${NADIR_SRC} \

# nadir USRCXXFLAGS
#
nadir_USRCXXFLAGS += \

# nadir USRLIBDIRS
#
nadir_USRLIBDIRS += \
-L${NADIR_LIB} \

# nadir LIBS
#
nadir_LIBS += \
-lnadir \

# nadir FRAMEWORKS
#
nadir_FRAMEWORKS += \

########################################################################
# xosnadir

# xosnadir USRDEFINES
#
xosnadir_USRDEFINES += \
${nadir_USRDEFINES} \
-DNO_USE_NADIR_BASE \
-DNO_USE_XOS_LOGGER_INTERFACE \

# xosnadir USRINCLUDES
#
xosnadir_USRINCLUDES += \
${nadir_USRINCLUDES} \

# xosnadir USRCXXFLAGS
#
xosnadir_USRCXXFLAGS += \
${nadir_USRCXXFLAGS} \

# xosnadir USRLIBDIRS
#
xosnadir_USRLIBDIRS += \
${nadir_USRLIBDIRS} \

# xosnadir LIBS
#
xosnadir_LIBS += \
-lxosnadir \

# xosnadir FRAMEWORKS
#
xosnadir_FRAMEWORKS += \
${nadir FRAMEWORKS} \

########################################################################
# talas

# talas USRDEFINES
#
talas_USRDEFINES += \
${bn_USRDEFINES} \
${mp_USRDEFINES} \
${xosnadir_USRDEFINES} \
${build_talas_USRDEFINES} \

# talas USRINCLUDES
#
talas_USRINCLUDES += \
-I${TALAS_SRC} \
${xosnadir_USRINCLUDES} \
${mp_USRINCLUDES} \
${bn_USRINCLUDES} \
${build_talas_USRINCLUDES} \

# talas USRCXXFLAGS
#
talas_USRCXXFLAGS += \
${bn_USRCXXFLAGS} \
${mp_USRCXXFLAGS} \
${xosnadir_USRCXXFLAGS} \
${build_talas_USRCXXFLAGS} \

# talas USRLIBDIRS
#
talas_USRLIBDIRS += \
-L${TALAS_LIB} \
${xosnadir_USRLIBDIRS} \
${mp_USRLIBDIRS} \
${bn_USRLIBDIRS} \
${build_talas_USRLIBDIRS} \

# talas LIBS
#
talas_LIBS += \
-ltalas \
${xosnadir_LIBS} \
${mp_LIBS} \
${bn_LIBS} \
${build_talas_LIBS} \

########################################################################

