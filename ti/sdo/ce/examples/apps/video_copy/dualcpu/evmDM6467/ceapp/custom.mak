## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: linker.cmd

linker.cmd: \
  package/cfg/ceapp_x470MV.o470MV \
  package/cfg/ceapp_x470MV.xdl
	$(SED) 's"^\"\(package/cfg/ceapp_x470MVcfg.cmd\)\"$""\"/opt/dvsdk_1_40_02_33/codec_engine_2_10_02/examples/ti/sdo/ce/examples/apps/video_copy/dualcpu/evmDM6467/ceapp/\1\""' package/cfg/ceapp_x470MV.xdl > $@
