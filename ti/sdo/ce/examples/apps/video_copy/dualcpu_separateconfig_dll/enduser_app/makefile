#
#  Copyright 2008 by Texas Instruments Incorporated.
#  
#  All rights reserved. Property of Texas Instruments Incorporated.
#  Restricted rights to use, duplicate or disclose this code are
#  granted through contract.
#  
#

# location of the configured CE app partially linked object
CONFIGURED_CE_SUBSYSTEM_DLL = ../configured_CE_subsystem/configured_CE_subsystem.so

# [EDIT THIS] path to the MVArm compiler 
CC=/db/toolsrc/library/vendors2005/mvl/arm/mvl4.0/Linux/montavista/pro/devkit/arm/v5t_le/armv5tl-montavista-linuxeabi/bin/gcc \
    -g -Wall -Os

# standard compile rule
%.o : %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<


# link our end-user application object files with the partially linked CE obj
app.out: app.o $(CONFIGURED_CE_SUBSYSTEM_DLL)
	cp -f $(CONFIGURED_CE_SUBSYSTEM_DLL) .
	$(CC) -ldl -g -o $@ app.o -lpthread

all: app.out

clean:
	rm -rf app.out *.o *.so

#
#  @(#) ti.sdo.ce.examples.apps.video_copy.dualcpu_separateconfig_dll; 1,0,0,100; 9-9-2008 02:02:05; /db/atree/library/trees/ce-h27x/src/
#

