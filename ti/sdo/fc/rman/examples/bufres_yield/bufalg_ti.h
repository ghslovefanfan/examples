/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== bufalg_ti.h ========
 *  Interface for the BUFALG_TI module; TI's implementation 
 *  of the IBUFALG interface.
 */

#ifndef BUFALG_TI_
#define BUFALG_TI_

#include <ti/xdais/ialg.h>
#include <ti/xdais/ires.h>
#include "ibufalg.h"

typedef struct BUFALG_TI_Obj *BUFALG_TI_Handle;

/*
 *  ======== BUFALG_TI_IALG ========
 *  TI's implementation of the IALG interface for BUFALG
 */
extern IALG_Fxns BUFALG_TI_IALG;

/*
 *  ======== BUFALG_TI_IBUFALG ========
 *  TI's implementation of the IBUFALG interface
 */
extern IBUFALG_Fxns BUFALG_TI_IBUFALG;

/*
 *  ======== BUFALG_TI_IRES ========
 *  IRES function table
 */
extern IRES_Fxns BUFALG_TI_IRES;

#endif  /* BUFALG_TI_ */
/*
 *  @(#) ti.sdo.fc.rman.examples.bufres_yield; 1, 0, 0,83; 9-9-2008 23:54:37; /db/atree/library/trees/fc-e20x/src/
 */

