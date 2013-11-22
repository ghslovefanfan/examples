/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== sphdeccopy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for SPHDECCOPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the SPHDECCOPY algorithm.
 */
#ifndef SPHDECCOPY_TI_PRIV_
#define SPHDECCOPY_TI_PRIV_

typedef struct SPHDECCOPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
} SPHDECCOPY_TI_Obj;

extern Int SPHDECCOPY_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int SPHDECCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int SPHDECCOPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 SPHDECCOPY_TI_process(ISPHDEC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, ISPHDEC_InArgs *inargs, ISPHDEC_OutArgs *outargs);

extern XDAS_Int32 SPHDECCOPY_TI_control(ISPHDEC_Handle handle,
    ISPHDEC_Cmd id, ISPHDEC_DynamicParams *params, ISPHDEC_Status *status);

#endif
/*
 *  @(#) ti.sdo.ce.examples.codecs.sphdec_copy; 1,0,0,132; 9-9-2008 02:03:17; /db/atree/library/trees/ce-h27x/src/
 */

