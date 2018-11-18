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
# build Gcc Makefile for talas
########################################################################


########################################################################
# bn
#
# pkg-config --cflags --libs bn
#

ifndef USE_HOME_BUILD_bn
USE_HOME_BUILD_bn = no
endif

ifeq ($(USE_HOME_BUILD_bn),yes)
#
# home build bn
#
build_bn_USRDEFINES += \

build_bn_USRINCLUDES += \
-I$(HOME)/build/bn/include \

build_bn_USRCXXFLAGS += \

build_bn_USRLIBDIRS += \
-L$(HOME)/build/bn/lib \

build_bn_LIBS += \
-lbn \

build_bn_FRAMEWORKS += \

else
#
# build bn
#
build_bn_USRDEFINES += \

build_bn_USRINCLUDES += \

build_bn_USRCXXFLAGS += \

build_bn_USRLIBDIRS += \

build_bn_LIBS += \

build_bn_FRAMEWORKS += \

endif

########################################################################
# mp
#
# pkg-config --cflags --libs mp
#

ifndef USE_HOME_BUILD_mp
USE_HOME_BUILD_mp = no
endif

ifeq ($(USE_HOME_BUILD_mp),yes)
#
# home build mp
#
build_mp_USRDEFINES += \

build_mp_USRINCLUDES += \
-I$(HOME)/build/mp/include \

build_mp_USRCXXFLAGS += \

build_mp_USRLIBDIRS += \
-L$(HOME)/build/mp/lib \

build_mp_LIBS += \
-lmp \

build_mp_FRAMEWORKS += \

else
#
# build mp
#
build_mp_USRDEFINES += \

build_mp_USRINCLUDES += \

build_mp_USRCXXFLAGS += \

build_mp_USRLIBDIRS += \

build_mp_LIBS += \

build_mp_FRAMEWORKS += \

endif

########################################################################
# nadir
#
# pkg-config --cflags --libs nadir
#

ifndef USE_HOME_BUILD_nadir
USE_HOME_BUILD_nadir = no
endif

ifeq ($(USE_HOME_BUILD_nadir),yes)
#
# home build nadir
#
build_nadir_USRDEFINES += \

build_nadir_USRINCLUDES += \
-I$(HOME)/build/nadir/include \

build_nadir_USRCXXFLAGS += \

build_nadir_USRLIBDIRS += \
-L$(HOME)/build/nadir/lib \

build_nadir_LIBS += \
-lnadir \

build_nadir_FRAMEWORKS += \

else
#
# build nadir
#
build_nadir_USRDEFINES += \

build_nadir_USRINCLUDES += \

build_nadir_USRCXXFLAGS += \

build_nadir_USRLIBDIRS += \

build_nadir_LIBS += \

build_nadir_FRAMEWORKS += \

endif

########################################################################
# talas

# build talas USRDEFINES
#
build_talas_USRDEFINES += \
${build_bn_USRDEFINES} \
${build_mp_USRDEFINES} \
${build_nadir_USRDEFINES} \


# build talas USRINCLUDES
#
build_talas_USRINCLUDES += \
${build_nadir_USRINCLUDES} \
${build_mp_USRINCLUDES} \
${build_bn_USRINCLUDES} \


# build talas USRCXXFLAGS
#
build_talas_USRCXXFLAGS += \
${build_bn_USRCXXFLAGS} \
${build_mp_USRCXXFLAGS} \
${build_nadir_USRCXXFLAGS} \


# build talas USRLIBDIRS
#
build_talas_USRLIBDIRS += \
${build_nadir_USRLIBDIRS} \
${build_mp_USRLIBDIRS} \
${build_bn_USRLIBDIRS} \


# build talas FRAMEWORKS
#
build_talas_FRAMEWORKS += \
${build_nadir_FRAMEWORKS} \
${build_mp_FRAMEWORKS} \
${build_bn_FRAMEWORKS} \


# build talas LIBS
#
build_talas_LIBS += \
${build_nadir_LIBS} \
${build_mp_LIBS} \
${build_bn_LIBS} \
${build_talas_FRAMEWORKS}


