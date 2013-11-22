/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== audenccopy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for AUDENCCOPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the AUDENCCOPY algorithm.
 */
#ifndef AUDENCCOPY_TI_PRIV_
#define AUDENCCOPY_TI_PRIV_

typedef struct AUDENCCOPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
} AUDENCCOPY_TI_Obj;

extern Int AUDENCCOPY_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int AUDENCCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int AUDENCCOPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 AUDENCCOPY_TI_process(IAUDENC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IAUDENC_InArgs *inargs, IAUDENC_OutArgs *outargs);

extern XDAS_Int32 AUDENCCOPY_TI_control(IAUDENC_Handle handle,
    IAUDENC_Cmd id, IAUDENC_DynamicParams *params, IAUDENC_Status *status);

#endif
/*
 *  @(#) ti.sdo.ce.examples.codecs.audenc_copy; 1,0,0,132; 9-9-2008 02:02:40; /db/atree/library/trees/ce-h27x/src/
 */

