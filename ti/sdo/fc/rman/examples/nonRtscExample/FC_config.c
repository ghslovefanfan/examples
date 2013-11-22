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
 *  ======== FC_config.c ========
 *  Configuration for other modules of FC (besides RMAN) being used.
 */

#include <xdc/std.h>
#include <ti/bios/include/std.h>
#include <ti/bios/include/tsk.h>
#include <ti/bios/include/hwi.h>
#include <ti/bios/include/sem.h>


#include <ti/sdo/fc/ires/iresman.h>
#include <ti/sdo/fc/rman/rman.h> 
#include <ti/sdo/fc/ires/vicp/iresman_vicp.h>
#include <ti/sdo/fc/ires/vicp/ires_vicp.h>

#include <ti/sdo/edma3/rm/edma3_rm.h>
#include <ti/sdo/fc/ires/edma3chan/iresman_edma3Chan.h>
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>

#include <ti/sdo/fc/dskt2/dskt2.h>

#include <ti/sdo/fc/edma3/edma3_config.h>
#include <ti/sdo/utils/trace/gt.h>

extern Ptr myMalloc(Int size);
extern Void printfCaller(String fmt, ...);

/* 
 * XDT created scratch size array for DSKT2
 * 
 */ 
far Int SCRATCH_ARRAY = {0};
DSKT2_CacheWBInvFxn DSKT2_cacheWBInvFxn = NULL;

GT_Config _ti_sdo_utils_trace_GT_params = {
    printfCaller,
    NULL,
    NULL,
    NULL,
    myMalloc,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};
GT_Config *GT = &_ti_sdo_utils_trace_GT_params;
/*
 *  @(#) ti.sdo.fc.rman.examples.nonRtscExample; 1, 0, 0,22; 9-9-2008 23:55:03; /db/atree/library/trees/fc-e20x/src/
 */

