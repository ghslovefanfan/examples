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
 *  ======== main.c ========
 */
#include <xdc/std.h>

#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/trace/gt.h>

extern Int smain(Int argc, String argv[]);

/* trace info: module name, mask */
#define MOD_NAME "ti.sdo.ce.examples.apps.video_copy.singlecpu"
GT_Mask curMask = {0,0};

/*
 *  ======== main ========
 */
Int main(Int argc, String argv[])
{
    /* init Codec Engine */
    CERuntime_init();

    /* init trace */
    GT_init();

    /* create a mask to allow a trace-print welcome message below */
    GT_create(&curMask, MOD_NAME);

    /* Enable all trace for this module */
    GT_set(MOD_NAME "=01234567");

    GT_0trace(curMask, GT_2CLASS, "main> " MOD_NAME "\n");

    return (smain(argc, argv));
}
/*
 *  @(#) ti.sdo.ce.examples.apps.video_copy.singlecpu; 1,0,0,132; 9-9-2008 02:02:09; /db/atree/library/trees/ce-h27x/src/
 */

