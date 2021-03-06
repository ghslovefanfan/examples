/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== viddec1_copy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for VIDDEC1COPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the VIDDEC1COPY algorithm.
 */
#include <ti/xdais/dm/ividdec1.h>

#ifndef VIDDEC1COPY_TI_PRIV_
#define VIDDEC1COPY_TI_PRIV_

typedef struct VIDDEC1COPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
    XDAS_Int32  outputChromaFormat;
} VIDDEC1COPY_TI_Obj;

extern Int VIDDEC1COPY_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int VIDDEC1COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int VIDDEC1COPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 VIDDEC1COPY_TI_process(IVIDDEC1_Handle h,
    XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDDEC1_InArgs *inArgs,
    IVIDDEC1_OutArgs *outArgs);

extern XDAS_Int32 VIDDEC1COPY_TI_control(IVIDDEC1_Handle handle,
    IVIDDEC1_Cmd id, IVIDDEC1_DynamicParams *params, IVIDDEC1_Status *status);

#endif
/*
 *  @(#) ti.xdais.dm.examples.viddec1_copy; 2, 0, 0,118; 5-8-2008 09:07:03; /db/wtree/library/trees/dais-j06x/src/
 */

