/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== ibufalg.h ========
 *  IBUFALG Interface Header
 *
 */
#ifndef IBUFALG_
#define IBUFALG_

#include <ti/xdais/ialg.h>
#include <ti/xdais/idma2.h>

#define BUFALG_SOK      0
#define BUFALG_EFAIL    -1
#define BUFALG_EMEMORY  -2


/*
 *  ======== IBUFALG_HANDLE ========
 *  This handle is used to reference all BUFALG instance objects
 */
typedef struct IBUFALG_Obj *IBUFALG_Handle;

/*
 *  ======== IBUFALG_Obj ========
 *  This structure must be the first field of all BUFALG instance objects
 */
typedef struct IBUFALG_Obj {
    struct IBUFALG_Fxns *fxns;
} IBUFALG_Obj;

/*
 *  ======== IBUFALG_Cmd ========
 *  The Cmd enumeration defines the control commands for the BUFALG
 *  control method.
 */
typedef enum IBUFALG_Cmd {
    IBUFALG_GET,      /* Get command */
    IBUFALG_SET       /* Set command */
} IBUFALG_Cmd;

/*
 *  ======== IBUFALG_Params ========
 *  This structure defines the creation parameters for all BUFALG objects
 */
typedef struct IBUFALG_Params {
    Int size;           /* must be first field of all params structures */
} IBUFALG_Params;

/*
 *  ======== IBUFALG_PARAMS ========
 *  Default parameter values for BUFALG instance objects
 */
extern IBUFALG_Params IBUFALG_PARAMS;

/*
 *  ======== IBUFALG_Fxns ========
 *  This structure defines all of the operations on BUFALG objects
 */
typedef struct IBUFALG_Fxns {
    IALG_Fxns   ialg;    /* IBUFALG extends IALG */
    Int         (*useBufs)(IBUFALG_Handle handle, unsigned int fillValue, 
            int taskId);
} IBUFALG_Fxns;

#endif  /* IBUFALG_ */
/*
 *  @(#) ti.sdo.fc.rman.examples.bufres_yield; 1, 0, 0,83; 9-9-2008 23:54:37; /db/atree/library/trees/fc-e20x/src/
 */

