#
#  Copyright 2008 by Texas Instruments Incorporated.
#  
#  All rights reserved. Property of Texas Instruments Incorporated.
#  Restricted rights to use, duplicate or disclose this code are
#  granted through contract.
#  
#

include ../../../../../xdcpaths.mak

all:
%::
	echo DEVICES=$(DEVICES)
	$(MAKE) -C speech/dsponly $@
ifneq (,$(findstring DM6446,$(DEVICES)))
	$(MAKE) -C speech/linuxonly $@
endif
	$(MAKE) -C speech_copy $@
	$(MAKE) -C image_copy $@
	$(MAKE) -C video_copy/singlecpu $@
ifeq ($(DEVICES_DAVINCI),1)
	$(MAKE) -C video_copy/dualcpu $@
endif	
ifneq (,$(findstring DM6446,$(DEVICES)))
	$(MAKE) -C video_copy/dualcpu_separateconfig_dll/configured_CE_subsystem $@
	$(MAKE) -C video_copy/dualcpu_separateconfig/configured_CE_subsystem $@
endif
	$(MAKE) -C audio_copy/singlecpu $@
ifeq ($(DEVICES_DAVINCI),1)
	$(MAKE) -C audio_copy/dualcpu $@
endif
	$(MAKE) -C scale $@
ifneq (,$(findstring DM6446,$(DEVICES)))
	$(MAKE) -C server_api_example $@
endif
	$(MAKE) -C server_api_example/audio_server $@
	$(MAKE) -C video2_copy $@
	$(MAKE) -C video1_copy $@
	$(MAKE) -C image1_copy $@
	$(MAKE) -C audio1_copy/sync $@
	$(MAKE) -C audio1_copy/async $@
	$(MAKE) -C audio1_ires $@
	$(MAKE) -C audio1_ires/audio1_ires_server $@
	$(MAKE) -C speech1_copy $@
	$(MAKE) -C vidtranscode $@
	$(MAKE) -C vidanalytics $@
#
#  @(#) ti.sdo.ce.examples.apps; 1,0,0,136; 9-9-2008 02:00:07; /db/atree/library/trees/ce-h27x/src/
#

