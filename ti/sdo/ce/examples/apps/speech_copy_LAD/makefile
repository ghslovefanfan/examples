#
#  ======== makefile ========
#  GNUmake-based makefile.
#

# include the files that defines XDC package, paths and build rules
EXAMPLES_ROOTDIR := $(CURDIR)/../../../../../..

include $(EXAMPLES_ROOTDIR)/xdcpaths.mak

# add the examples directory itself to the list of paths to packages
XDC_PATH := $(EXAMPLES_ROOTDIR);$(XDC_PATH)

include $(EXAMPLES_ROOTDIR)/buildutils/xdcrules.mak
