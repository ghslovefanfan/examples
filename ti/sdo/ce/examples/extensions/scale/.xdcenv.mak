#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /db/atree/library/trees/ce-h27x/src/codec_engine_2_10_02/examples/ti/sdo/ce/examples/extensions/scale/../../../../../..;/db/atree/library/trees/ce-h27x/src/codec_engine_2_10_02/cetools/packages;/db/atree/library/trees/ce-h27x/src/codec_engine_2_10_02/packages;/home/xlibrary/trees/sabios/sabios-i05/product/Linux/bios_5_32_01/packages
override XDCROOT = /db/rtree/install/trees/products/xdcprod-h24/product/Linux/xdc_3_00_06
override XDCBUILDCFG = /db/atree/library/trees/ce-h27x/src/codec_engine_2_10_02/packages/config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /db/atree/library/trees/ce-h27x/src/codec_engine_2_10_02/examples/ti/sdo/ce/examples/extensions/scale/../../../../../..;/db/atree/library/trees/ce-h27x/src/codec_engine_2_10_02/cetools/packages;/db/atree/library/trees/ce-h27x/src/codec_engine_2_10_02/packages;/home/xlibrary/trees/sabios/sabios-i05/product/Linux/bios_5_32_01/packages;/db/rtree/install/trees/products/xdcprod-h24/product/Linux/xdc_3_00_06/packages;../../../../../..
HOSTOS = Linux
endif
