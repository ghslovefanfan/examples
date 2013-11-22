#
#  Copyright 2008 by Texas Instruments Incorporated.
#  
#  All rights reserved. Property of Texas Instruments Incorporated.
#  Restricted rights to use, duplicate or disclose this code are
#  granted through contract.
#  
#

# location of the configured CE app partially linked object
CONFIGURED_CE_SUBSYSTEM_OBJ = ../configured_CE_subsystem/configured_CE_subsystem.o

# [EDIT THIS] path to the MVArm compiler 
CC=/db/toolsrc/library/vendors2005/mvl/arm/mvl4.0/Linux/montavista/pro/devkit/arm/v5t_le/armv5tl-montavista-linuxeabi/bin/gcc \
    -g -Wall -Os

# standard compile rule
%.o : %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<


# link our end-user application object files with the partially linked CE obj
app.out: app.o $(CONFIGURED_CE_SUBSYSTEM_OBJ)
	$(CC) -g -o $@ app.o $(CONFIGURED_CE_SUBSYSTEM_OBJ) -lpthread 

all: app.out

clean:
	rm -rf app.out *.o 

#
#  @(#) ti.sdo.ce.examples.apps.video_copy.dualcpu_separateconfig; 1,0,0,132; 9-9-2008 02:02:01; /db/atree/library/trees/ce-h27x/src/
#

