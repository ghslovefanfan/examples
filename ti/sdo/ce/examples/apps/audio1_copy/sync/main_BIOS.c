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
/**
 *  @file       ti/sdo/ce/examples/apps/audio1_copy/main_BIOS.c
 *
 *  @brief      This is a BIOS main() routine
 */
#include <xdc/std.h>
#include <ti/bios/include/std.h>

#include <ti/bios/include/tsk.h>
#include <ti/bios/include/sys.h>
#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/trace/gt.h>

#include <smain.h>
#include <stdio.h>

/* trace info: module name, mask */
#define MOD_NAME "ti.sdo.ce.examples.apps.audio1_copy"
GT_Mask curMask = {0,0};

static String taskName = "audio1_copy";

/**
 *  @brief      The BIOS main() entry point.
 *
 *  @remark     The purpose of this function is to create a BIOS worker task
 *              to house our example.
 *
 *  @remark     This is called during BIOS_init, but before the scheduler
 *              has begun running.
 */
Int main(Int argc, String argv[])
{
    TSK_Attrs attrs = TSK_ATTRS;
    attrs.stacksize = 6 * 1024;
    attrs.name = taskName;

    /* init Codec Engine */
    CERuntime_init();

    /* init trace */
    GT_init();

    /* create a mask to allow a trace-print welcome message below */
    GT_create(&curMask, MOD_NAME);

    /* Enable all trace for this module */
    GT_set(MOD_NAME "=01234567");

    GT_setprintf((GT_PrintFxn)printf);

    GT_0trace(curMask, GT_2CLASS, "main> " MOD_NAME "\n");

    if (TSK_create((Fxn)smain, &attrs, argc, argv) == NULL) {
        SYS_abort("main: failed to create smain thread.");
    }

    return (0);
}

/*
 *  @(#) ti.sdo.ce.examples.apps.audio1_copy.sync; 1,0,0,36; 9-9-2008 02:00:16; /db/atree/library/trees/ce-h27x/src/
 */

