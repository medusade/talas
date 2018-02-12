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
# Thirdpary Makefile for openssl
########################################################################

########################################################################
#
# openssl defs
#
########################################################################
OPENSSL_MAKEDIR=$(PWD)

ifndef OPENSSL_UNAME
OPENSSL_UNAME = $(shell uname)
endif

ifndef OPENSSL_OS
ifneq ($(OPENSSL_UNAME), Darwin)
OPENSSL_OS = linux
else
OPENSSL_OS = macosx
endif
endif

#
# openssl version
#
OPENSSL_VERSION_MAJOR = 0
OPENSSL_VERSION_MINOR = 9
OPENSSL_VERSION_RELEASE = 8zh

OPENSSL_VERSION_SEPARATOR = .
OPENSSL_VERSION_MAJOR_SEPARATOR = $(OPENSSL_VERSION_SEPARATOR)
OPENSSL_VERSION_MINOR_SEPARATOR = $(OPENSSL_VERSION_SEPARATOR)

OPENSSL_VERSION_SHORT = $(OPENSSL_VERSION_MAJOR)$(OPENSSL_VERSION_MINOR)$(OPENSSL_VERSION_RELEASE)
OPENSSL_VERSION = $(OPENSSL_VERSION_MAJOR)$(OPENSSL_VERSION_MAJOR_SEPARATOR)$(OPENSSL_VERSION_MINOR)$(OPENSSL_VERSION_MINOR_SEPARATOR)$(OPENSSL_VERSION_RELEASE)

#
# openssl name
#
OPENSSL_NAME_SEPARATOR = -
OPENSSL_NAME_BASE = openssl
OPENSSL_NAME = $(OPENSSL_NAME_BASE)$(OPENSSL_NAME_SEPARATOR)$(OPENSSL_VERSION)
OPENSSL_INSTALL_NAME_SEPARATOR = -
OPENSSL_INSTALL_NAME = $(OPENSSL_NAME_BASE)$(OPENSSL_INSTALL_NAME_SEPARATOR)$(OPENSSL_VERSION)
OPENSSL_DIR = $(OPENSSL_NAME)

#
# openssl archive
#
OPENSSL_ARCHIVED = tar
OPENSSL_COMPRESSED = gz
OPENSSL_ARCHIVE_SEPARATOR = .
OPENSSL_ARCHIVED_SEPARATOR = $(OPENSSL_ARCHIVE_SEPARATOR)
OPENSSL_COMPRESSED_SEPARATOR = $(OPENSSL_ARCHIVE_SEPARATOR)

OPENSSL_EXTRACT_DIR = $(OPENSSL_NAME)
OPENSSL_TGZ_PREFIX = 
OPENSSL_TGZ = $(OPENSSL_NAME)$(OPENSSL_TGZ_PREFIX)$(OPENSSL_ARCHIVED_SEPARATOR)$(OPENSSL_ARCHIVED)$(OPENSSL_COMPRESSED_SEPARATOR)$(OPENSSL_COMPRESSED)
OPENSSL_PATCH_TGZ_PREFIX = $(OPENSSL_NAME_SEPARATOR)patch
OPENSSL_PATCH_TGZ = $(OPENSSL_NAME)$(OPENSSL_PATCH_TGZ_PREFIX)$(OPENSSL_ARCHIVED_SEPARATOR)$(OPENSSL_ARCHIVED)$(OPENSSL_COMPRESSED_SEPARATOR)$(OPENSSL_COMPRESSED)
OPENSSL_DOCS_TGZ_PREFIX = $(OPENSSL_NAME_SEPARATOR)docs
OPENSSL_DOCS_TGZ = $(OPENSSL_NAME)$(OPENSSL_DOCS_TGZ_PREFIX)$(OPENSSL_ARCHIVED_SEPARATOR)$(OPENSSL_ARCHIVED)$(OPENSSL_COMPRESSED_SEPARATOR)$(OPENSSL_COMPRESSED)

#
# openssl extract
#
ifeq ($(OPENSSL_ARCHIVED),tar)
ifeq ($(OPENSSL_COMPRESSED),gz)
OPENSSL_TAR_UNCOMPRESS = z
OPENSSL_TAR_COMPRESS = z
else
ifeq ($(OPENSSL_COMPRESSED),bz2)
OPENSSL_TAR_UNCOMPRESS = j
OPENSSL_TAR_COMPRESS = j
else
ifeq ($(OPENSSL_COMPRESSED),xz)
OPENSSL_TAR_UNCOMPRESS = J
OPENSSL_TAR_COMPRESS = J
else
endif
endif
endif
OPENSSL_LIST = tar -tv$(OPENSSL_TAR_UNCOMPRESS)f
OPENSSL_EXTRACT = tar -x$(OPENSSL_TAR_UNCOMPRESS)f
OPENSSL_ARCHIVE = tar -cv$(OPENSSL_TAR_COMPRESS)f
else
ifeq ($(OPENSSL_ARCHIVED),zip)
OPENSSL_LIST = unzip -l
OPENSSL_EXTRACT = unzip
OPENSSL_ARCHIVE = zip
else
OPENSSL_LIST = echo unable to list
OPENSSL_EXTRACT = echo unable to extract
OPENSSL_ARCHIVE = echo unable to archive
endif
endif

OPENSSL_LIST_TGZ = $(OPENSSL_LIST) $(OPENSSL_TGZ)
OPENSSL_EXTRACT_TGZ = $(OPENSSL_EXTRACT) $(OPENSSL_TGZ)
OPENSSL_TOUCH_EXTRACT = touch $(OPENSSL_DIR)
OPENSSL_REMOVE_DIR = $(OPENSSL_REMOVE) $(OPENSSL_DIR)

OPENSSL_LIST_PATCH = $(OPENSSL_LIST)
OPENSSL_EXTRACT_PATCH = $(OPENSSL_EXTRACT)
OPENSSL_LIST_PATCH_TGZ = $(OPENSSL_LIST_PATCH) $(OPENSSL_PATCH_TGZ)
OPENSSL_EXTRACT_PATCH_TGZ = $(OPENSSL_EXTRACT_PATCH) $(OPENSSL_PATCH_TGZ)

OPENSSL_LIST_DOCS = $(OPENSSL_LIST)
OPENSSL_EXTRACT_DOCS = $(OPENSSL_EXTRACT)
OPENSSL_LIST_DOCS_TGZ = $(OPENSSL_LIST_DOCS) $(OPENSSL_DOCS_TGZ)
OPENSSL_EXTRACT_DOCS_TGZ = $(OPENSSL_EXTRACT_DOCS) $(OPENSSL_DOCS_TGZ) -C$(OPENSSL_DOCS_PREFIX)

#
# openssl build
#
OPENSSL_BUILD = $(HOME)/build
OPENSSL_PREFIX = $(OPENSSL_BUILD)/$(OPENSSL_INSTALL_NAME)
OPENSSL_EXEC_PREFIX = $(OPENSSL_PREFIX)
OPENSSL_CONF_PREFIX = $(OPENSSL_PREFIX)
OPENSSL_DOCS_PREFIX = $(OPENSSL_PREFIX)
OPENSSL_LINK_NAME = $(OPENSSL_BUILD)/$(OPENSSL_NAME_BASE)

OPENSSL_MKDIR = mkdir -p
OPENSSL_REMOVE = rm -r -f

OPENSSL_MAKE_DIR = $(OPENSSL_DIR)
OPENSSL_MAKE_PUSHD = pushd $(OPENSSL_MAKE_DIR)
OPENSSL_MAKE = make

#
# openssl configure
#
ifneq ($(OPENSSL_UNAME), Darwin)
OPENSSL_CONFIGURE_CONFIGURE = ./config
OPENSSL_CONFIGURE_UNAME = -g
else
OPENSSL_CONFIGURE_CONFIGURE = ./Configure darwin64-x86_64-cc
OPENSSL_CONFIGURE_UNAME = -g
endif
OPENSSL_CONFIGURE_HELP = $(OPENSSL_CONFIGURE_CONFIGURE) --help
OPENSSL_CONFIGURE_PUSHD = pushd $(OPENSSL_MAKE_DIR)
OPENSSL_CONFIGURE = $(OPENSSL_CONFIGURE_CONFIGURE) \
$(OPENSSL_CONFIGURE_UNAME) --prefix=$(OPENSSL_PREFIX) 

#
# openssl help
#
OPENSSL_HELP = $(OPENSSL_CONFIGURE_HELP)

########################################################################
#
# rules
#
########################################################################

all: build

again: unextract build

test: test-openssl

install-links: install-openssl-links

install-docs: install-openssl-docs

install-prefix: install-openssl-prefix

install: install-openssl

build: build-openssl

clean: clean-openssl

configed: configed-$(OPENSSL_DIR)

config: config-$(OPENSSL_DIR)

help: help-openssl

list-docs: list-openssl-docs

list-patch: list-openssl-patch

extract-patch: extract-openssl-patch

list: list-openssl

extract: extract-openssl

unextract: unextract-openssl

archive: archive-openssl

linked: openssl-linked

prefixed: openssl-prefixed

archived: openssl-archived

extracted: openssl-extracted

########################################################################
#
# openssl rules
#
########################################################################

#
# Test openssl
#
test-openssl:
	@($(OPENSSL_MAKE_PUSHD);\
	  (($(OPENSSL_MAKE) test) || (exit 1));\
	  popd)

#
# Install openssl
#
install-openssl: configed-$(OPENSSL_DIR)
	@(echo Installing $(OPENSSL_DIR)...;\
	  $(OPENSSL_MAKE_PUSHD);\
	  (($(OPENSSL_MAKE) install) || (exit 1)) && \
	  ((touch $(OPENSSL_MAKEDIR)/configed-$(OPENSSL_DIR)) || (exit 1));\
	  popd)
	  
#
# Build openssl
#
build-openssl: configed-$(OPENSSL_DIR)
	@(echo Building $(OPENSSL_DIR)...;\
	  $(OPENSSL_MAKE_PUSHD);\
	  (($(OPENSSL_MAKE)) || (exit 1)) && \
	  ((touch $(OPENSSL_MAKEDIR)/configed-$(OPENSSL_DIR)) || (exit 1));\
	  popd)
	  
#
# Clean openssl
#
clean-openssl: configed-$(OPENSSL_DIR)
	@(echo Cleaning $(OPENSSL_DIR)...;\
	  $(OPENSSL_MAKE_PUSHD);\
	  (($(OPENSSL_MAKE) clean) || (exit 1)) && \
	  ((touch $(OPENSSL_MAKEDIR)/configed-$(OPENSSL_DIR)) || (exit 1));\
	  popd)
	  
#
# Config openssl
#
config-$(OPENSSL_DIR): unconfig-$(OPENSSL_DIR) configed-$(OPENSSL_DIR)

unconfig-$(OPENSSL_DIR):
	@(rm -f configed-$(OPENSSL_DIR))

configed-$(OPENSSL_DIR): $(OPENSSL_DIR)
	@(echo Configing $(OPENSSL_DIR)...;\
	  $(OPENSSL_CONFIGURE_PUSHD);\
	  (($(OPENSSL_CONFIGURE)) || (exit 1)) && \
	  ((touch $(OPENSSL_DIR)) || (exit 1)) && \
	  ((touch $(OPENSSL_MAKEDIR)/configed-$(OPENSSL_DIR)) || (exit 1));\
	  popd)

#
# Help openssl
#
help-openssl: $(OPENSSL_DIR)
	@($(OPENSSL_CONFIGURE_PUSHD);\
	  (($(OPENSSL_HELP)) || (exit 1));\
	  popd)

#
# List openssl Docs
#
list-openssl-docs: $(OPENSSL_DOCS_TGZ)
	@(echo Listing $(OPENSSL_DOCS_TGZ)...;\
	  (($(OPENSSL_LIST_DOCS_TGZ)) || (exit 1)))

#
# Install openssl Docs
#
install-openssl-docs: $(OPENSSL_DOCS_PREFIX)
	@(echo Extracting $(OPENSSL_DOCS_TGZ)...;\
	  (($(OPENSSL_EXTRACT_DOCS_TGZ)) || (exit 1)))

#
# List openssl Patch
#
list-openssl-patch: $(OPENSSL_PATCH_TGZ)
	@(echo Listing $(OPENSSL_PATCH_TGZ)...;\
	  (($(OPENSSL_LIST_PATCH_TGZ)) || (exit 1)))

#
# Extract openssl patch
#
extract-openssl-patch: $(OPENSSL_DIR)
	@(echo Extracting $(OPENSSL_PATCH_TGZ)...;\
	  (($(OPENSSL_EXTRACT_PATCH_TGZ)) || (exit 1)))

#
# List openssl
#
list-openssl: 
	@(echo Listing $(OPENSSL_TGZ)...;\
	  (($(OPENSSL_LIST_TGZ)) || (exit 1)))

#
# Extract openssl
#
extract-openssl: unextract-openssl $(OPENSSL_DIR)

unextract-openssl: unconfig-$(OPENSSL_DIR)
	@(echo Removing $(OPENSSL_DIR)...;\
	  (($(OPENSSL_REMOVE_DIR)) || (exit 1)))

$(OPENSSL_DIR): $(OPENSSL_TGZ)
	@(echo Extracting $(OPENSSL_TGZ)...;\
	  (($(OPENSSL_EXTRACT_TGZ)) || (exit 1)) && \
	  (($(OPENSSL_TOUCH_EXTRACT)) || (exit 1)))
	  
#
# Archive openssl
#
archive-openssl: 
	@(echo Archiving $(OPENSSL_DIR) to $(OPENSSL_TGZ)...;\
	  (($(OPENSSL_ARCHIVE) $(OPENSSL_TGZ) $(OPENSSL_DIR)) || (exit 1)))

#
# Install openssl links
#
install-openssl-links: 
	@((echo removing $(OPENSSL_LINK_NAME)) && \
	  ((rm -f $(OPENSSL_LINK_NAME)) || (exit 1)) && \
	  (echo Linking $(OPENSSL_LINK_NAME) "->" $(OPENSSL_PREFIX)) && \
	  ((ln -s $(OPENSSL_PREFIX) $(OPENSSL_LINK_NAME)) || (exit 1)))
	  
#
# openssl linked
#
openssl-linked: 
	@echo link is $(OPENSSL_LINK_NAME) "->" $(OPENSSL_PREFIX)
	  
#
# Install openssl prefix
#
install-openssl-prefix: 
	@((echo makeing $(OPENSSL_PREFIX)) && \
	  ((mkdir -p $(OPENSSL_PREFIX)) || (exit 1)) && \
	  (echo makeing $(OPENSSL_EXEC_PREFIX)) && \
	  ((mkdir -p $(OPENSSL_EXEC_PREFIX)) || (exit 1)))
	  
#
# openssl prefixed
#
openssl-prefixed: 
	@((echo prefix is $(OPENSSL_PREFIX)) && \
	  (echo exec prefix is $(OPENSSL_EXEC_PREFIX)) && \
	  (echo conf prefix is $(OPENSSL_CONF_PREFIX)) && \
	  (echo docs prefix is $(OPENSSL_DOCS_PREFIX)))
	  
$(OPENSSL_PREFIX):
	@(echo Makeing Directory $(OPENSSL_PREFIX)...;\
	  (($(OPENSSL_MKDIR) $(OPENSSL_PREFIX)) || (exit 1)))

$(OPENSSL_EXEC_PREFIX):
	@(echo Makeing Directory $(OPENSSL_EXEC_PREFIX)...;\
	  (($(OPENSSL_MKDIR) $(OPENSSL_EXEC_PREFIX)) || (exit 1)))

$(OPENSSL_CONF_PREFIX):
	@(echo Makeing Directory $(OPENSSL_CONF_PREFIX)...;\
	  (($(OPENSSL_MKDIR) $(OPENSSL_CONF_PREFIX)) || (exit 1)))

$(OPENSSL_DOCS_PREFIX):
	@(echo Makeing Directory $(OPENSSL_DOCS_PREFIX)...;\
	  (($(OPENSSL_MKDIR) $(OPENSSL_DOCS_PREFIX)) || (exit 1)))

#
# openssl archived
#
openssl-archived: 
	@(echo $(OPENSSL_TGZ))
	  
#
# openssl extracted
#
openssl-extracted: 
	@(echo $(OPENSSL_EXTRACT) $(OPENSSL_TGZ))




        

