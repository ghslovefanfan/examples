## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: linker.cmd

linker.cmd: \
  package/cfg/video_copy_x64P.o64P \
  package/cfg/video_copy_x64Pcfg.o64P \
  package/cfg/video_copy_x64Pcfg_c.o64P \
  package/cfg/video_copy_x64P.xdl
	$(SED) 's"^\"\(package/cfg/video_copy_x64Pcfg.cmd\)\"$""\"/opt/dvsdk_1_40_02_33/codec_engine_2_10_02/examples/ti/sdo/ce/examples/servers/video_copy/evmDM6467/video_copy/\1\""' package/cfg/video_copy_x64P.xdl > $@
