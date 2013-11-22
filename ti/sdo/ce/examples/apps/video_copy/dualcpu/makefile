# 
#  Copyright 2008
#  Texas Instruments Incorporated
#
#  All rights reserved.  Property of Texas Instruments Incorporated
#  Restricted rights to use, duplicate or disclose this code are
#  granted through contract.
# 
#

#
#  ======== makefile ========
#
include ../../../../../../../xdcpaths.mak

all:
%::
ifneq (,$(findstring DM6446,$(DEVICES)))
	$(MAKE) -C evmDM6446 $@
endif	
ifneq (,$(findstring DM6467,$(DEVICES)))
	$(MAKE) -C evmDM6467 $@
endif	
#
#  @(#) ti.sdo.ce.examples.apps.video_copy.dualcpu; 1, 0, 0,133; 9-9-2008 02:01:49; /db/atree/library/trees/ce-h27x/src/
#

