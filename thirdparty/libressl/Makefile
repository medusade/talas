########################################################################
# Copyright (c) 1988-2017 $organization$
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
#   Date: 12/22/2017
#
# Thirdpary Makefile for libressl
########################################################################

########################################################################
#
# libressl defs
#
########################################################################
LIBRESSL_MAKEDIR=$(PWD)

ifndef LIBRESSL_UNAME
LIBRESSL_UNAME = $(shell uname)
endif

ifndef LIBRESSL_OS
ifneq ($(LIBRESSL_UNAME), Darwin)
LIBRESSL_OS = linux
else
LIBRESSL_OS = macosx
endif
endif

#
# libressl version
#
ifeq ($(VERSION),253)
LIBRESSL_VERSION_MAJOR = 2
LIBRESSL_VERSION_MINOR = 5
LIBRESSL_VERSION_RELEASE = 3
else
LIBRESSL_VERSION_MAJOR = 2
LIBRESSL_VERSION_MINOR = 5
LIBRESSL_VERSION_RELEASE = 1
endif

LIBRESSL_VERSION_SEPARATOR = .
LIBRESSL_VERSION_MAJOR_SEPARATOR = $(LIBRESSL_VERSION_SEPARATOR)
LIBRESSL_VERSION_MINOR_SEPARATOR = $(LIBRESSL_VERSION_SEPARATOR)

LIBRESSL_VERSION_SHORT = $(LIBRESSL_VERSION_MAJOR)$(LIBRESSL_VERSION_MINOR)$(LIBRESSL_VERSION_RELEASE)
LIBRESSL_VERSION = $(LIBRESSL_VERSION_MAJOR)$(LIBRESSL_VERSION_MAJOR_SEPARATOR)$(LIBRESSL_VERSION_MINOR)$(LIBRESSL_VERSION_MINOR_SEPARATOR)$(LIBRESSL_VERSION_RELEASE)

#
# libressl name
#
LIBRESSL_NAME_SEPARATOR = -
LIBRESSL_NAME_BASE = libressl
LIBRESSL_NAME = $(LIBRESSL_NAME_BASE)$(LIBRESSL_NAME_SEPARATOR)$(LIBRESSL_VERSION)
LIBRESSL_INSTALL_NAME_SEPARATOR = -
LIBRESSL_INSTALL_NAME = $(LIBRESSL_NAME_BASE)$(LIBRESSL_INSTALL_NAME_SEPARATOR)$(LIBRESSL_VERSION)
LIBRESSL_DIR = $(LIBRESSL_NAME)

#
# libressl archive
#
LIBRESSL_ARCHIVED = tar
LIBRESSL_COMPRESSED = gz
LIBRESSL_ARCHIVE_SEPARATOR = .
LIBRESSL_ARCHIVED_SEPARATOR = $(LIBRESSL_ARCHIVE_SEPARATOR)
LIBRESSL_COMPRESSED_SEPARATOR = $(LIBRESSL_ARCHIVE_SEPARATOR)

LIBRESSL_EXTRACT_DIR = $(LIBRESSL_NAME)
LIBRESSL_TGZ_PREFIX = 
LIBRESSL_TGZ = $(LIBRESSL_NAME)$(LIBRESSL_TGZ_PREFIX)$(LIBRESSL_ARCHIVED_SEPARATOR)$(LIBRESSL_ARCHIVED)$(LIBRESSL_COMPRESSED_SEPARATOR)$(LIBRESSL_COMPRESSED)
LIBRESSL_PATCH_TGZ_PREFIX = $(LIBRESSL_NAME_SEPARATOR)modified
LIBRESSL_PATCH_TGZ = $(LIBRESSL_NAME)$(LIBRESSL_PATCH_TGZ_PREFIX)$(LIBRESSL_ARCHIVED_SEPARATOR)$(LIBRESSL_ARCHIVED)$(LIBRESSL_COMPRESSED_SEPARATOR)$(LIBRESSL_COMPRESSED)
LIBRESSL_DOCS_TGZ_PREFIX = $(LIBRESSL_NAME_SEPARATOR)docs
LIBRESSL_DOCS_TGZ = $(LIBRESSL_NAME)$(LIBRESSL_DOCS_TGZ_PREFIX)$(LIBRESSL_ARCHIVED_SEPARATOR)$(LIBRESSL_ARCHIVED)$(LIBRESSL_COMPRESSED_SEPARATOR)$(LIBRESSL_COMPRESSED)

#
# libressl extract
#
ifeq ($(LIBRESSL_ARCHIVED),tar)
ifeq ($(LIBRESSL_COMPRESSED),gz)
LIBRESSL_TAR_UNCOMPRESS = z
LIBRESSL_TAR_COMPRESS = z
else
ifeq ($(LIBRESSL_COMPRESSED),bz2)
LIBRESSL_TAR_UNCOMPRESS = j
LIBRESSL_TAR_COMPRESS = j
else
ifeq ($(LIBRESSL_COMPRESSED),xz)
LIBRESSL_TAR_UNCOMPRESS = J
LIBRESSL_TAR_COMPRESS = J
else
endif
endif
endif
LIBRESSL_LIST = tar -tv$(LIBRESSL_TAR_UNCOMPRESS)f
LIBRESSL_EXTRACT = tar -x$(LIBRESSL_TAR_UNCOMPRESS)f
LIBRESSL_ARCHIVE = tar -cv$(LIBRESSL_TAR_COMPRESS)f
else
ifeq ($(LIBRESSL_ARCHIVED),zip)
LIBRESSL_LIST = unzip -l
LIBRESSL_EXTRACT = unzip
LIBRESSL_ARCHIVE = zip
else
LIBRESSL_LIST = echo unable to list
LIBRESSL_EXTRACT = echo unable to extract
LIBRESSL_ARCHIVE = echo unable to archive
endif
endif

LIBRESSL_LIST_TGZ = $(LIBRESSL_LIST) $(LIBRESSL_TGZ)
LIBRESSL_EXTRACT_TGZ = $(LIBRESSL_EXTRACT) $(LIBRESSL_TGZ)
LIBRESSL_TOUCH_EXTRACT = touch $(LIBRESSL_DIR)
LIBRESSL_REMOVE_DIR = $(LIBRESSL_REMOVE) $(LIBRESSL_DIR)

LIBRESSL_LIST_PATCH = $(LIBRESSL_LIST)
LIBRESSL_EXTRACT_PATCH = $(LIBRESSL_EXTRACT)
LIBRESSL_LIST_PATCH_TGZ = $(LIBRESSL_LIST_PATCH) $(LIBRESSL_PATCH_TGZ)
LIBRESSL_EXTRACT_PATCH_TGZ = $(LIBRESSL_EXTRACT_PATCH) $(LIBRESSL_PATCH_TGZ)

LIBRESSL_LIST_DOCS = $(LIBRESSL_LIST)
LIBRESSL_EXTRACT_DOCS = $(LIBRESSL_EXTRACT)
LIBRESSL_LIST_DOCS_TGZ = $(LIBRESSL_LIST_DOCS) $(LIBRESSL_DOCS_TGZ)
LIBRESSL_EXTRACT_DOCS_TGZ = $(LIBRESSL_EXTRACT_DOCS) $(LIBRESSL_DOCS_TGZ) -C$(LIBRESSL_DOCS_PREFIX)

#
# libressl build
#
LIBRESSL_BUILD = $(HOME)/build
LIBRESSL_PREFIX = $(LIBRESSL_BUILD)/$(LIBRESSL_INSTALL_NAME)
LIBRESSL_EXEC_PREFIX = $(LIBRESSL_PREFIX)
LIBRESSL_CONF_PREFIX = $(LIBRESSL_PREFIX)
LIBRESSL_DOCS_PREFIX = $(LIBRESSL_PREFIX)
LIBRESSL_LINK_NAME = $(LIBRESSL_BUILD)/$(LIBRESSL_NAME_BASE)

LIBRESSL_MKDIR = mkdir -p
LIBRESSL_REMOVE = rm -r -f

LIBRESSL_MAKE_DIR = $(LIBRESSL_DIR)
LIBRESSL_MAKE_PUSHD = pushd $(LIBRESSL_MAKE_DIR)
LIBRESSL_MAKE = make

#
# libressl configure
#
ifneq ($(LIBRESSL_UNAME), Darwin)
LIBRESSL_CONFIGURE_UNAME = --disable-shared
else
LIBRESSL_CONFIGURE_UNAME = --disable-shared
endif
LIBRESSL_CONFIGURE_CONFIGURE = ./configure
LIBRESSL_CONFIGURE_HELP = $(LIBRESSL_CONFIGURE_CONFIGURE) --help
LIBRESSL_CONFIGURE_PUSHD = pushd $(LIBRESSL_MAKE_DIR)
LIBRESSL_CONFIGURE = $(LIBRESSL_CONFIGURE_CONFIGURE) \
$(LIBRESSL_CONFIGURE_UNAME) --prefix=$(LIBRESSL_PREFIX) --exec_prefix=$(LIBRESSL_EXEC_PREFIX)

#
# libressl help
#
LIBRESSL_HELP = $(LIBRESSL_CONFIGURE_HELP)

########################################################################
#
# rules
#
########################################################################

all: build

again: unextract build

test: test-libressl

install-links: install-libressl-links

install-docs: install-libressl-docs

install-prefix: install-libressl-prefix

install: install-libressl

build: build-libressl

clean: clean-libressl

configed: configed-$(LIBRESSL_DIR)

config: config-$(LIBRESSL_DIR)

help: help-libressl

list-docs: list-libressl-docs

list-patch: list-libressl-patch

extract-patch: extract-libressl-patch

list: list-libressl

extract: extract-libressl

unextract: unextract-libressl

archive: archive-libressl

linked: libressl-linked

prefixed: libressl-prefixed

archived: libressl-archived

extracted: libressl-extracted

########################################################################
#
# libressl rules
#
########################################################################

#
# Test libressl
#
test-libressl:
	@($(LIBRESSL_MAKE_PUSHD);\
	  (($(LIBRESSL_MAKE) test) || (exit 1));\
	  popd)

#
# Install libressl
#
install-libressl: configed-$(LIBRESSL_DIR) patched-$(LIBRESSL_DIR)
	@(echo Installing $(LIBRESSL_DIR)...;\
	  $(LIBRESSL_MAKE_PUSHD);\
	  (($(LIBRESSL_MAKE) install) || (exit 1)) && \
	  ((touch $(LIBRESSL_MAKEDIR)/configed-$(LIBRESSL_DIR)) || (exit 1));\
	  popd)
	  
#
# Build libressl
#
build-libressl: configed-$(LIBRESSL_DIR) patched-$(LIBRESSL_DIR)
	@(echo Building $(LIBRESSL_DIR)...;\
	  $(LIBRESSL_MAKE_PUSHD);\
	  (($(LIBRESSL_MAKE)) || (exit 1)) && \
	  ((touch $(LIBRESSL_MAKEDIR)/configed-$(LIBRESSL_DIR)) || (exit 1));\
	  popd)
	  
#
# Clean libressl
#
clean-libressl: configed-$(LIBRESSL_DIR) patched-$(LIBRESSL_DIR)
	@(echo Cleaning $(LIBRESSL_DIR)...;\
	  $(LIBRESSL_MAKE_PUSHD);\
	  (($(LIBRESSL_MAKE) clean) || (exit 1)) && \
	  ((touch $(LIBRESSL_MAKEDIR)/configed-$(LIBRESSL_DIR)) || (exit 1));\
	  popd)
	  
#
# Config libressl
#
config-$(LIBRESSL_DIR): unconfig-$(LIBRESSL_DIR) configed-$(LIBRESSL_DIR)

unconfig-$(LIBRESSL_DIR):
	@(rm -f configed-$(LIBRESSL_DIR))

configed-$(LIBRESSL_DIR): $(LIBRESSL_DIR)
	@(echo Configing $(LIBRESSL_DIR)...;\
	  $(LIBRESSL_CONFIGURE_PUSHD);\
	  (($(LIBRESSL_CONFIGURE)) || (exit 1)) && \
	  ((touch $(LIBRESSL_DIR)) || (exit 1)) && \
	  ((touch $(LIBRESSL_MAKEDIR)/configed-$(LIBRESSL_DIR)) || (exit 1));\
	  popd)

#
# Patch libressl
#
patch-$(LIBRESSL_DIR): unpatch-$(LIBRESSL_DIR) patched-$(LIBRESSL_DIR)

unpatch-$(LIBRESSL_DIR):
	@(rm -f patched-$(LIBRESSL_DIR))

patched-$(LIBRESSL_DIR): $(LIBRESSL_DIR)
	@(echo Extracting $(LIBRESSL_PATCH_TGZ)...;\
	  (($(LIBRESSL_EXTRACT_PATCH_TGZ)) || (exit 1)) && \
	  ((touch $(LIBRESSL_MAKEDIR)/patched-$(LIBRESSL_DIR)) || (exit 1)))

#
# Help libressl
#
help-libressl:
	@($(LIBRESSL_CONFIGURE_PUSHD);\
	  (($(LIBRESSL_HELP)) || (exit 1));\
	  popd)

#
# List libressl Docs
#
list-libressl-docs: $(LIBRESSL_DOCS_TGZ)
	@(echo Listing $(LIBRESSL_DOCS_TGZ)...;\
	  (($(LIBRESSL_LIST_DOCS_TGZ)) || (exit 1)))

#
# Install libressl Docs
#
install-libressl-docs: $(LIBRESSL_DOCS_PREFIX)
	@(echo Extracting $(LIBRESSL_DOCS_TGZ)...;\
	  (($(LIBRESSL_EXTRACT_DOCS_TGZ)) || (exit 1)))

#
# List libressl Patch
#
list-libressl-patch: $(LIBRESSL_PATCH_TGZ)
	@(echo Listing $(LIBRESSL_PATCH_TGZ)...;\
	  (($(LIBRESSL_LIST_PATCH_TGZ)) || (exit 1)))

#
# Extract libressl patch
#
extract-libressl-patch: $(LIBRESSL_DIR)
	@(echo Extracting $(LIBRESSL_PATCH_TGZ)...;\
	  (($(LIBRESSL_EXTRACT_PATCH_TGZ)) || (exit 1)))

#
# List libressl
#
list-libressl: 
	@(echo Listing $(LIBRESSL_TGZ)...;\
	  (($(LIBRESSL_LIST_TGZ)) || (exit 1)))

#
# Extract libressl
#
extract-libressl: unextract-libressl $(LIBRESSL_DIR)

unextract-libressl: unpatch-$(LIBRESSL_DIR) unconfig-$(LIBRESSL_DIR)
	@(echo Removing $(LIBRESSL_DIR)...;\
	  (($(LIBRESSL_REMOVE_DIR)) || (exit 1)))

$(LIBRESSL_DIR): $(LIBRESSL_TGZ)
	@(echo Extracting $(LIBRESSL_TGZ)...;\
	  (($(LIBRESSL_EXTRACT_TGZ)) || (exit 1)) && \
	  (($(LIBRESSL_TOUCH_EXTRACT)) || (exit 1)))
	  
#
# Archive libressl
#
archive-libressl: 
	@(echo Archiving $(LIBRESSL_DIR) to $(LIBRESSL_TGZ)...;\
	  (($(LIBRESSL_ARCHIVE) $(LIBRESSL_TGZ) $(LIBRESSL_DIR)) || (exit 1)))

#
# Install libressl links
#
install-libressl-links: 
	@((echo removing $(LIBRESSL_LINK_NAME)) && \
	  ((rm -f $(LIBRESSL_LINK_NAME)) || (exit 1)) && \
	  (echo Linking $(LIBRESSL_LINK_NAME) "->" $(LIBRESSL_PREFIX)) && \
	  ((ln -s $(LIBRESSL_PREFIX) $(LIBRESSL_LINK_NAME)) || (exit 1)))
	  
#
# libressl linked
#
libressl-linked: 
	@echo link is $(LIBRESSL_LINK_NAME) "->" $(LIBRESSL_PREFIX)
	  
#
# Install libressl prefix
#
install-libressl-prefix: 
	@((echo makeing $(LIBRESSL_PREFIX)) && \
	  ((mkdir -p $(LIBRESSL_PREFIX)) || (exit 1)) && \
	  (echo makeing $(LIBRESSL_EXEC_PREFIX)) && \
	  ((mkdir -p $(LIBRESSL_EXEC_PREFIX)) || (exit 1)))
	  
#
# libressl prefixed
#
libressl-prefixed: 
	@((echo prefix is $(LIBRESSL_PREFIX)) && \
	  (echo exec prefix is $(LIBRESSL_EXEC_PREFIX)) && \
	  (echo conf prefix is $(LIBRESSL_CONF_PREFIX)) && \
	  (echo docs prefix is $(LIBRESSL_DOCS_PREFIX)))
	  
$(LIBRESSL_PREFIX):
	@(echo Makeing Directory $(LIBRESSL_PREFIX)...;\
	  (($(LIBRESSL_MKDIR) $(LIBRESSL_PREFIX)) || (exit 1)))

$(LIBRESSL_EXEC_PREFIX):
	@(echo Makeing Directory $(LIBRESSL_EXEC_PREFIX)...;\
	  (($(LIBRESSL_MKDIR) $(LIBRESSL_EXEC_PREFIX)) || (exit 1)))

$(LIBRESSL_CONF_PREFIX):
	@(echo Makeing Directory $(LIBRESSL_CONF_PREFIX)...;\
	  (($(LIBRESSL_MKDIR) $(LIBRESSL_CONF_PREFIX)) || (exit 1)))

$(LIBRESSL_DOCS_PREFIX):
	@(echo Makeing Directory $(LIBRESSL_DOCS_PREFIX)...;\
	  (($(LIBRESSL_MKDIR) $(LIBRESSL_DOCS_PREFIX)) || (exit 1)))

#
# libressl archived
#
libressl-archived: 
	@(echo $(LIBRESSL_TGZ))
	  
#
# libressl extracted
#
libressl-extracted: 
	@(echo $(LIBRESSL_EXTRACT) $(LIBRESSL_TGZ))




        

