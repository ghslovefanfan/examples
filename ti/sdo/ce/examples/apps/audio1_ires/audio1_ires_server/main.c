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
 *  @file       ti/sdo/ce/examples/apps/audio1_ires/audio1_ires_server/main.c
 */
#include <xdc/std.h>

#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/trace/gt.h>

#include <ti/xdais/ires.h>
#include <ti/sdo/fc/ires/bufres/bufres.h>
#include <ti/sdo/fc/rman/rman.h>

/* trace info: module name, mask */
static GT_Mask gtMask = {0,0};

/* Defined in linker template file, mark the beginning and end of buffer */
extern far UInt32 BUFMEM_base;
extern far UInt32 BUFMEM_end;

extern IRESMAN_PersistentAllocFxn DSKT2_allocPersistent;
extern IRESMAN_PersistentFreeFxn  DSKT2_freePersistent;

/* Configuration parameters for buffer resource */
static BUFRES_Params config;

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
    GT_create(&gtMask, "audio1_ires_server");

    /* ...and initialize all masks in this module to "on" */
    GT_set("audio1_ires_server=01234567");

    GT_0trace(gtMask, GT_4CLASS, "main> Welcome to DSP server's main().\n");

    /* Configure and register BUFRES resource with RMAN */
    config.iresConfig.size = sizeof(BUFRES_Params);
    config.iresConfig.allocFxn = DSKT2_allocPersistent;
    config.iresConfig.freeFxn = DSKT2_freePersistent;

    config.base = (Void *)&BUFMEM_base;
    config.length = (UInt32)&BUFMEM_end - (UInt32)&BUFMEM_base + 1;

    RMAN_register(&BUFRES_MGRFXNS, (IRESMAN_Params *)&config);
}


/*
 *  @(#) ti.sdo.ce.examples.apps.audio1_ires.audio1_ires_server; 1,0,0,88; 9-9-2008 02:00:24; /db/atree/library/trees/ce-h27x/src/
 */

