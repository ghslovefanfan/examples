/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== bufalg_ti_priv.h ========
 *
 *  Private internal vendor specific interface.
 *
 */

#ifndef BUFALG_TI_PRIV_
#define BUFALG_TI_PRIV_

#include <std.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/ires.h>

#include "ibufalg.h"
#include <ti/sdo/fc/rman/examples/bufres_yield/bufres.h>

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

#define NUMALLOC 1          /* Number of buffers to allocate for the alg*/
#define MAXBUFSIZE 0x1000   /* Maximum context that can be stored in the 
                               persistent buffer */ 

/*
 * ======== BUFALG_TI_CtxtArgs ========
 * Structure of the context that will be saved and restored, during yield
 */

typedef struct BUFALG_TI_CtxtArgs {
    Int num;                    /* Indicates number of scratch buffers used */
    Int size[NUMRES];           /* size of the buffers filled up */
} BUFALG_TI_CtxtArgs;
/*
 *  ======== BUFALG_TI_Obj ========
 */
typedef struct BUFALG_TI_Obj {
    IALG_Obj        alg;               /* Alogorithm handle */
    BUFRES_Handle   res[NUMRES];       /* Resource used by the alg */
    UInt32 *        algBuf[NUMRES];    /* Algorithm's persistent Buffers*/
    Bool            resActive[NUMRES]; /* Is the resource active? */
    BUFRES_Args     args[NUMRES];      /* args for each resource */
    IRES_YieldFxn   yieldFxn;
    IRES_YieldArgs  yieldArgs;
    IRES_YieldContext yieldContext;        //TODO: Does every algorithm object 
    BUFALG_TI_CtxtArgs  contextArgs;           //      need these  
} BUFALG_TI_Obj;


/* IALG Function Declarations */
extern Void BUFALG_TI_activate(IALG_Handle);

extern Int BUFALG_TI_alloc(const IALG_Params *, struct IALG_Fxns **,
        IALG_MemRec *);

extern Int BUFALG_TI_control(IALG_Handle, IALG_Cmd, IALG_Status *);

extern Void BUFALG_TI_deactivate(IALG_Handle);

extern Int BUFALG_TI_free(IALG_Handle, IALG_MemRec *);

extern Int BUFALG_TI_initObj(IALG_Handle, const IALG_MemRec *, IALG_Handle,
        const IALG_Params *);

extern Void BUFALG_TI_moved(IALG_Handle, const IALG_MemRec *, IALG_Handle,
        const IALG_Params *);

extern Int BUFALG_TI_numAlloc(Void);

extern Int BUFALG_TI_useBufs(IBUFALG_Handle handle, UInt32 fillValue, 
        Int taskId);

#ifdef _cplusplus
}
#endif /* _cplusplus */

#endif /* BUFALG_TI_PRIV_ */
/*
 *  @(#) ti.sdo.fc.rman.examples.bufres_yield; 1, 0, 0,83; 9-9-2008 23:54:37; /db/atree/library/trees/fc-e20x/src/
 */

