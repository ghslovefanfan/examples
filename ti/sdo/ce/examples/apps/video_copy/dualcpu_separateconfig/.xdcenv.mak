#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = ^/../hijacks;^/../imports;/db/toolsrc/library/tools/packages
override XDCROOT = /db/rtree/install/trees/products/xdcprod-h24/product/Linux/xdc_3_00_06
override XDCBUILDCFG = /db/rtree/install/trees/products/xdcprod-h24/product/Linux/xdc_3_00_06/etc/config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = ^/../hijacks;^/../imports;/db/toolsrc/library/tools/packages;/db/rtree/install/trees/products/xdcprod-h24/product/Linux/xdc_3_00_06/packages;../../../../../../..
HOSTOS = Linux
endif
