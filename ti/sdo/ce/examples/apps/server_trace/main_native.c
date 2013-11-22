/* 
 *  Copyright 2008
 *  Texas Instruments Incorporated
 *
 *  All rights reserved.  Property of Texas Instruments Incorporated
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 * 
 */
/*
 *  ======== main_native.c ========
 */
#include <xdc/std.h>
#include <ti/sdo/ce/CERuntime.h>

extern Int smain(Int argc, String argv[]);

/*
 *  ======== main ========
 */
Int main(Int argc, String argv[])
{
    CERuntime_init();

    return (smain(argc, argv));
}

/*
 *  @(#) ti.sdo.ce.examples.apps.server_trace; 1,0,0,89; 9-9-2008 02:01:09; /db/atree/library/trees/ce-h27x/src/
 */

