/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== fcpy_ti_idma3vt.c ========
 *  This file contains the function table definitions for the
 *  IDMA3 interface implemented by the FCPY_TI module.
 */
#include <std.h>

#include <ti/xdais/idma3.h>
#include <fcpy_ti.h>
#include <fcpy_ti_priv.h>

/*
 *  ======== FCPY_TI_IDMA3 ========
 *  This structure defines TI's implementation of the IDMA2 interface
 *  for the FCPY_TI module.
 */
IDMA3_Fxns FCPY_TI_IDMA3 = {      /* module_vendor_interface */
    &FCPY_TI_IALG,              /* IALG functions */    
    FCPY_TI_dmaChangeChannels,  /* ChangeChannels */
    FCPY_TI_dmaGetChannelCnt,   /* GetChannelCnt */
    FCPY_TI_dmaGetChannels,     /* GetChannels */
    FCPY_TI_dmaInit             /* initialize logical channels */
};




/*
 *  @(#) ti.sdo.fc.dman3.examples.fastcopy; 1,0,0,141; 9-9-2008 23:51:14; /db/atree/library/trees/fc-e20x/src/
 */

