/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== viddeccopy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for VIDDECCOPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the VIDDECCOPY algorithm.
 */
#ifndef VIDDECCOPY_TI_PRIV_
#define VIDDECCOPY_TI_PRIV_

typedef struct VIDDECCOPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
} VIDDECCOPY_TI_Obj;

extern Int VIDDECCOPY_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int VIDDECCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int VIDDECCOPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 VIDDECCOPY_TI_process(IVIDDEC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDDEC_InArgs *inargs, IVIDDEC_OutArgs *outargs);

extern XDAS_Int32 VIDDECCOPY_TI_control(IVIDDEC_Handle handle,
    IVIDDEC_Cmd id, IVIDDEC_DynamicParams *params, IVIDDEC_Status *status);

#endif
/*
 *  @(#) ti.sdo.ce.examples.codecs.viddec_copy; 1,0,0,131; 9-9-2008 02:03:44; /db/atree/library/trees/ce-h27x/src/
 */

