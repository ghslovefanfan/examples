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
 *  ======== bufres_util.h ========
 *  Utility functions for BUFRES resource manager functions.
 */

#ifndef BUFRES_UTIL_H_
#define BUFRES_UTIL_H_

#include <ti/sdo/fc/ires/iresman.h>

extern IRES_Status BUFRES_init(BUFRES_Params *args);
extern IRES_Status BUFRES_exit();
extern BUFRES_Handle BUFRES_get(IALG_Handle h, BUFRES_Args *args, Int scratchId,
        IRES_Status *pStatus);
extern IRES_Status BUFRES_free(IALG_Handle h, BUFRES_Handle res, BUFRES_Args *args,
        Int scratchId);
extern Void BUFRES_getStaticProps(BUFRES_Handle res, BUFRES_Props *props);


#endif /* BUFRES_UTIL_H_ */

/*
 *  @(#) ti.sdo.fc.rman.examples.bufres_yield; 1, 0, 0,83; 9-9-2008 23:54:37; /db/atree/library/trees/fc-e20x/src/
 */

