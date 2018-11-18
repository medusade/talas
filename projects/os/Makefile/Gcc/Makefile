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
# Os Gcc Makefile for talas subdurs
########################################################################

PKG = ../../../..

MAK = projects/Makefile/Gcc
PRJ = projects/os/Makefile/Gcc
SRC = src

include $(PKG)/$(MAK)/Makedefines

#
# Source subdirs
#
#SRC_DIRS = \
#$(PKG)/$(PRJ)/somedir \
#
SRC_DIRS = \
$(PKG)/$(PRJ)/lib/libbn \
$(PKG)/$(PRJ)/lib/libmp \
$(PKG)/$(PRJ)/lib/libmpn \
$(PKG)/$(PRJ)/lib/libmpz \
$(PKG)/$(PRJ)/lib/libtalas \
$(PKG)/$(PRJ)/app/talas \

include $(PKG)/$(MAK)/Makedirs
