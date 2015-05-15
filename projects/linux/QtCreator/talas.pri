########################################################################
# Copyright (c) 1988-2014 $organization$
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
#   Date: 12/7/2014
########################################################################

QMAKE_CXXFLAGS += -std=c++11

########################################################################
# xos
XOS_BLD = ../$${XOS_PKG}/build/linux/QtCreator/Debug
XOS_LIB = $${XOS_BLD}/lib

########################################################################
# talas
talas_LIBS += \
-L$${TALAS_LIB}/libtalas \
-ltalas \
-L$${TALAS_LIB}/libbn \
-lbn \
-L$${TALAS_LIB}/libmpz \
-lmpz \
-L$${TALAS_LIB}/libmpn \
-lmpn \
-L$${TALAS_LIB}/libmp \
-lmp \
-L$${XOS_LIB}/libxosnadir \
-lxosnadir \
-lpthread \
-ldl \
-lrt \

