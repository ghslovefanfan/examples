#
#  Copyright 2008 by Texas Instruments Incorporated.
#  
#  All rights reserved. Property of Texas Instruments Incorporated.
#  Restricted rights to use, duplicate or disclose this code are
#  granted through contract.
#  
#

#
#  ======== makefile ========
#  GNUmake-based makefile.
#

# This file describes the build for a Codec Engine Server.  This makefile has
# special sections to accomodate inclusion of the Codec Engine, while the rest
# is standard GNU make.  Codec Engine-specific additions are marked with
# the [CE] tag.

# [CE] define EXAMPLES_ROOTDIR to point to root of <CE/examples> directory
EXAMPLES_ROOTDIR := $(CURDIR)/../../../../../../..

# [CE] include the file that defines paths to XDC packages and XDC tools
include $(EXAMPLES_ROOTDIR)/xdcpaths.mak

# [CE] name of the server executable
SERVER_EXE := video_copy.x64P

# [CE] name of the server release package
SERVER_PKG := ti.sdo.ce.examples.servers.video_copy.evmDM6446

SERVER_PKG_ARCHIVE := $(subst .,_,$(SERVER_PKG)).tar

# add the examples repository to the package path.
# This is necessary because this server's configuration uses the codecs
# in the examples repository
XDC_PATH := $(EXAMPLES_ROOTDIR);$(XDC_PATH)

# The compiler path and name are read from xdcpaths.mak above
CGTOOLS = $(CGTOOLS_C64P)

# compiler, linker
CC   = $(CGTOOLS)/$(CC_C64P)
LINK = $(subst cl6x,lnk6x,$(CC))

# [CE] Configuro settings.  CONFIGPKG is the basename of your application's
# config script
CONFIGPKG = video_copy

# [CE] Name the xdc target and platform
XDCTARGET = ti.targets.C64P
XDCPLATFORM = ti.platforms.evmDM6446

# [CE] configuro-generated files
COMPILER_FILE = $(CONFIGPKG)/compiler.opt
LINKER_FILE = $(CONFIGPKG)/linker.cmd

# [CE] The path to the configuro utility
CONFIGURO = XDCPATH="$(XDC_PATH)" $(XDC_INSTALL_DIR)/xs xdc.tools.configuro

# [CE] Augment the standard $(CFLAGS) variable, adding the
# Configuro-generated compiler file.
CFLAGS = -@ $(COMPILER_FILE)

# final executable
all: $(SERVER_PKG_ARCHIVE)

# [CE] The generated linker and compiler files depend on the generated
# config package
$(LINKER_FILE) $(COMPILER_FILE) : $(CONFIGPKG)

# [CE] The generated config package depends on the 2 config scripts
$(CONFIGPKG) : $(CONFIGPKG).cfg $(CONFIGPKG).tcf
	$(CONFIGURO) -c $(CGTOOLS) -o $(CONFIGPKG) \
		-t $(XDCTARGET) -p $(XDCPLATFORM) \
                --tcf $(CONFIGPKG).cfg

# "normal" makefile settings and rules follow.
%.obj : %.c $(COMPILER_FILE)
	$(CC) $(CFLAGS) -c $<


# app.out, in addition to its standard stuff, must specify the
# auto-generated $(LINKER_FILE)
$(SERVER_EXE): main.obj $(LINKER_FILE)
	$(LINK) -o $@ -c $^
#	@cp $(CONFIGPKG)/$@.info.js .
	

# create server release package and archive it; the package 
# contains the executable and some meta-info files
# This non-standard build step is necessary to support app config scripts
# which want to use Engine.createFromServer()
$(SERVER_PKG_ARCHIVE): $(SERVER_EXE)
	@echo "Creating server release:"
	@rm -rf package package.*
	@echo "package $(SERVER_PKG) {}" > package.xdc
	@echo "Pkg.otherFiles = ['./$(SERVER_EXE)','./$(SERVER_EXE).DataSheet.html','package/info']" > package.bld
	@mkdir package ; cp -R $(CONFIGPKG)/package/info package ; cp package/info/*DataSheet.html .
	@$(XDC_INSTALL_DIR)/xdc XDCPATH="$(XDC_PATH)" release
	@rm -f package.bld package.mak .[idle]*

# clean rule
clean:
	rm -rf $(SERVER_EXE) $(SERVER_PKG_ARCHIVE) *.obj package package.* *DataSheet.html $(CONFIGPKG)
#
#  @(#) ti.sdo.ce.examples.servers.video_copy.evmDM6446; 1, 0, 0,81; 9-9-2008 02:04:27; /db/atree/library/trees/ce-h27x/src/
#

