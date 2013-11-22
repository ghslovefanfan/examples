#
#  Copyright 2008 by Texas Instruments Incorporated.
#  
#  All rights reserved. Property of Texas Instruments Incorporated.
#  Restricted rights to use, duplicate or disclose this code are
#  granted through contract.
#  
#

#
#  ======== makefile =======
#  GNUmake-based makefile for linuxonly speech sample app.
#

# This file describes the build for a generic Linux application that
# happens to use Codec Engine. This makefile has special sections to
# accomodate inclusion of the codec engine, while the rest is standard.
# Codec Engine-specific additions are marked with the [CE] tag.

# [CE] define EXAMPLES_ROOTDIR to point to root of <CE/examples> directory
EXAMPLES_ROOTDIR := $(CURDIR)/../../../../../../../..

# [CE] include the file that defines paths to XDC packages and XDC tools
include $(EXAMPLES_ROOTDIR)/xdcpaths.mak

# [CE] add the examples repository to the package path.
# This is necessary because this application's configuration uses the codecs
# in the examples repository
XDC_PATH := $(EXAMPLES_ROOTDIR);$(XDC_PATH)

# The compiler path and name are read from xdcpaths.mak above
CGTOOLS = $(CGTOOLS_MVARM9)

# compiler, linker
CC = $(CGTOOLS)/$(CC_MVARM9)
LD = $(subst gcc,ld,$(CC))

# [CE] Configuro settings.  CONFIGPKG is the basename of your application's
# config script
CONFIGPKG = ceapp

# [CE] Name the xdc target and platform
XDCTARGET = gnu.targets.MVArm9
XDCPLATFORM = ti.platforms.evmDM6446

# [CE] configuro-generated files
COMPILER_FILE = $(CONFIGPKG)/compiler.opt
LINKER_FILE = $(CONFIGPKG)/linker.cmd

# [CE] The path to the configuro utility
CONFIGURO = XDCPATH="$(XDC_PATH)" $(XDC_INSTALL_DIR)/xs xdc.tools.configuro

# [CE] Augment the standard $(CPPFLAGS) variable, adding the
# Configuro-generated compiler file.
CPPFLAGS +=  $(shell cat $(COMPILER_FILE)) -g -Wall -Os

all: configured_CE_subsystem.o

# [CE] The generated linker and compiler files depend on the generated
# config package
$(LINKER_FILE) $(COMPILER_FILE) : $(CONFIGPKG)

# [CE] The generated config package depends on the 2 config scripts
$(CONFIGPKG) : $(CONFIGPKG).cfg
	$(CONFIGURO) -c $(CGTOOLS) -o $(CONFIGPKG) \
		-t $(XDCTARGET) -p $(XDCPLATFORM) \
		$(CONFIGPKG).cfg

# "normal" makefile settings and rules follow, with some additions for CE
# This app consists of the main, codec-engine unrelated main.c file, and
# the codec-engine-using app.c file.
%.o : %.c $(COMPILER_FILE)
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

# [CE] link configured CE-using app and all CE libraries it requires (but no others)
# into a partially linked object file, configured_CE_subsystem.o
# configured_CE_subsystem.o builds with the "-r" switch for partial linking, and
# includes .o and .lib files listed in the configuration-produced $(LINKER_FILE).
configured_CE_subsystem.o: ceapp.o $(LINKER_FILE)
	$(LD) -r -o $@ $^ 

# clean rule; must be a :: rule because CE's xdccfg.mak defines clean::, too
clean:
	rm -rf *.o $(CONFIGPKG)


#
#  @(#) ti.sdo.ce.examples.apps.video_copy.dualcpu_separateconfig; 1,0,0,132; 9-9-2008 02:02:00; /db/atree/library/trees/ce-h27x/src/
#

