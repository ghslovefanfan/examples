/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== imgdeccopy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for IMGDECCOPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the IMGDECCOPY algorithm.
 */
#ifndef IMGDECCOPY_TI_PRIV_
#define IMGDECCOPY_TI_PRIV_

typedef struct IMGDECCOPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
} IMGDECCOPY_TI_Obj;

extern Int IMGDECCOPY_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int IMGDECCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int IMGDECCOPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 IMGDECCOPY_TI_process(IIMGDEC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IIMGDEC_InArgs *inargs, IIMGDEC_OutArgs *outargs);

extern XDAS_Int32 IMGDECCOPY_TI_control(IIMGDEC_Handle handle,
    IIMGDEC_Cmd id, IIMGDEC_DynamicParams *params, IIMGDEC_Status *status);

#endif
/*
 *  @(#) ti.sdo.ce.examples.codecs.imgdec_copy; 1,0,0,132; 9-9-2008 02:02:52; /db/atree/library/trees/ce-h27x/src/
 */

