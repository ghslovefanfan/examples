/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== imgenc1copy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for IMGENC1COPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the IMGENC1COPY algorithm.
 */
#ifndef IMGENC1COPY_TI_PRIV_
#define IMGENC1COPY_TI_PRIV_

typedef struct IMGENC1COPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
} IMGENC1COPY_TI_Obj;

extern Int IMGENC1COPY_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int IMGENC1COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int IMGENC1COPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 IMGENC1COPY_TI_process(IIMGENC1_Handle h,
    XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IIMGENC1_InArgs *inArgs,
    IIMGENC1_OutArgs *outArgs);

extern XDAS_Int32 IMGENC1COPY_TI_control(IIMGENC1_Handle handle,
    IIMGENC1_Cmd id, IIMGENC1_DynamicParams *params, IIMGENC1_Status *status);

#endif
/*
 *  @(#) ti.xdais.dm.examples.imgenc1_copy; 2, 0, 0,118; 5-8-2008 09:06:15; /db/wtree/library/trees/dais-j06x/src/
 */

