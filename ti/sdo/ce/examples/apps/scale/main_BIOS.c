/* 
 *  Copyright 2008
 *  Texas Instruments Incorporated
 *
 *  All rights reserved.  Property of Texas Instruments Incorporated
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 * 
 */
/**
 *  @file       ti/sdo/ce/examples/apps/scale/main_BIOS.c
 *
 *  @brief      This is a BIOS main() routine
 */
#include <xdc/std.h>
#include <ti/bios/include/std.h>

#include <tsk.h>
#include <sys.h>
#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/trace/gt.h>

#include <smain.h>

/* trace info: module name, mask */
GT_Mask curMask = {0,0};

static String taskName = "scale";

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

    CERuntime_init();

    GT_create(&curMask, "ZZ");

    /* Enable all trace for this "ZZ" module */
    GT_set("ZZ=01234567");

    GT_0trace(curMask, GT_2CLASS, "main> Welcome to app's main().\n");

    if (TSK_create((Fxn)smain, &attrs, argc, argv) == NULL) {
        SYS_abort("main: failed to create smain thread.");
    }

    return (0);
}

/*
 *  @(#) ti.sdo.ce.examples.apps.scale; 1,0,0,135; 9-9-2008 02:00:58; /db/atree/library/trees/ce-h27x/src/
 */

