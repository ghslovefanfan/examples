/* 
 *  Copyright 2008
 *  Texas Instruments Incorporated
 *
 *  All rights reserved.  Property of Texas Instruments Incorporated
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 * 
 */
#include <xdc/std.h>
#include <ti/bios/include/std.h>

#include <tsk.h>
#include <sys.h>
#include <ti/sdo/ce/CERuntime.h>

extern Int smain(Int argc, String argv[]);

static String taskName = "speech";

/*
 *  ======== main ========
 */
Int main(Int argc, String argv[])
{
    TSK_Attrs attrs = TSK_ATTRS;
    attrs.stacksize = 6 * 1024;
    attrs.name = taskName;

    CERuntime_init();

    if (TSK_create((Fxn)smain, &attrs, argc, argv) == NULL) {
        SYS_abort("main: failed to create smain thread.");
    }

    return (0);
}

/*
 *  @(#) ti.sdo.ce.examples.apps.speech.dsponly; 1,0,0,134; 9-9-2008 02:01:13; /db/atree/library/trees/ce-h27x/src/
 */

