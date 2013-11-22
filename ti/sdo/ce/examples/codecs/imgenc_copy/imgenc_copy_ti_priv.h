/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== imgenccopy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for IMGENCCOPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the IMGENCCOPY algorithm.
 */
#ifndef IMGENCCOPY_TI_PRIV_
#define IMGENCCOPY_TI_PRIV_

typedef struct IMGENCCOPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
} IMGENCCOPY_TI_Obj;

extern Int IMGENCCOPY_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int IMGENCCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int IMGENCCOPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 IMGENCCOPY_TI_process(IIMGENC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IIMGENC_InArgs *inargs, IIMGENC_OutArgs *outargs);

extern XDAS_Int32 IMGENCCOPY_TI_control(IIMGENC_Handle handle,
    IIMGENC_Cmd id, IIMGENC_DynamicParams *params, IIMGENC_Status *status);

#endif
/*
 *  @(#) ti.sdo.ce.examples.codecs.imgenc_copy; 1,0,0,132; 9-9-2008 02:03:00; /db/atree/library/trees/ce-h27x/src/
 */

