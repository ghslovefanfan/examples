/* 
 *  Copyright 2008
 *  Texas Instruments Incorporated
 *
 *  All rights reserved.  Property of Texas Instruments Incorporated
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 * 
 */
/*
 *  ======== auddeccopy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for AUDDECCOPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the AUDDECCOPY algorithm.
 */
#ifndef AUDDECCOPY_TI_PRIV_
#define AUDDECCOPY_TI_PRIV_

typedef struct AUDDECCOPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
} AUDDECCOPY_TI_Obj;

extern Int AUDDECCOPY_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int AUDDECCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int AUDDECCOPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 AUDDECCOPY_TI_process(IAUDDEC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IAUDDEC_InArgs *inargs, IAUDDEC_OutArgs *outargs);

extern XDAS_Int32 AUDDECCOPY_TI_control(IAUDDEC_Handle handle,
    IAUDDEC_Cmd id, IAUDDEC_DynamicParams *params, IAUDDEC_Status *status);

#endif
/*
 *  @(#) ti.xdais.dm.examples.auddec_copy; 2, 0, 0,136; 5-8-2008 09:05:57; /db/wtree/library/trees/dais-j06x/src/
 */

