#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /opt/dvsdk_1_40_02_33/codec_engine_2_10_02/examples/ti/sdo/ce/examples/codecs/videnc_copy/../../../../../..;/opt/dvsdk_1_40_02_33/codec_engine_2_10_02/packages;/opt/dvsdk_1_40_02_33/xdais_6_10_01/packages;/opt/dvsdk_1_40_02_33/dsplink-davinci-v1.50-prebuilt/packages;/opt/dvsdk_1_40_02_33/cmem_2_10/packages;/opt/dvsdk_1_40_02_33/framework_components_2_10_02/packages;/opt/dvsdk_1_40_02_33/biosutils_1_01_00/packages;/opt/dvsdk_1_40_02_33/bios_5_32_01/packages
override XDCROOT = /opt/dvsdk_1_40_02_33/xdc_3_00_06
override XDCBUILDCFG = /opt/dvsdk_1_40_02_33/codec_engine_2_10_02/packages/config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /opt/dvsdk_1_40_02_33/codec_engine_2_10_02/examples/ti/sdo/ce/examples/codecs/videnc_copy/../../../../../..;/opt/dvsdk_1_40_02_33/codec_engine_2_10_02/packages;/opt/dvsdk_1_40_02_33/xdais_6_10_01/packages;/opt/dvsdk_1_40_02_33/dsplink-davinci-v1.50-prebuilt/packages;/opt/dvsdk_1_40_02_33/cmem_2_10/packages;/opt/dvsdk_1_40_02_33/framework_components_2_10_02/packages;/opt/dvsdk_1_40_02_33/biosutils_1_01_00/packages;/opt/dvsdk_1_40_02_33/bios_5_32_01/packages;/opt/dvsdk_1_40_02_33/xdc_3_00_06/packages;../../../../../..
HOSTOS = Linux
endif
