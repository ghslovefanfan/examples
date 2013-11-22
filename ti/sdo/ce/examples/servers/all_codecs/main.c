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
 *  @file       ti/sdo/ce/examples/servers/all_codecs/main.c
 */
#include <xdc/std.h>

#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/trace/gt.h>

/* trace info: module name, mask */
static GT_Mask gtMask = {0,0};

/*
 *  ======== main ========
 */
Void main(Int argc, Char *argv[])
{
    /* init Codec Engine */
    CERuntime_init();

    /* init trace */
    GT_init();

    /* create a mask to allow a trace-print welcome message below */
    GT_create(&gtMask, "ti.sdo.ce.examples.servers.all_codecs");

    /* ...and initialize all masks in this module to "on" */
    GT_set("ti.sdo.ce.examples.servers.all_codecs=01234567");

    GT_0trace(gtMask, GT_4CLASS, "main> Welcome to DSP server's main().\n");
}
/*
 *  @(#) ti.sdo.ce.examples.servers.all_codecs; 1,0,0,132; 9-9-2008 02:04:16; /db/atree/library/trees/ce-h27x/src/
 */

