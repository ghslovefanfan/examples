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
 *  ======== auddec1_copy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for AUDDEC1COPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the AUDDEC1COPY algorithm.
 */
#ifndef AUDDEC1COPY_TI_PRIV_
#define AUDDEC1COPY_TI_PRIV_

typedef struct AUDDEC1COPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
    XDAS_Int32  outputPCMWidth;
    XDAS_Int32  pcmFormat;
    XDAS_Int32  dataEndianness;
} AUDDEC1COPY_TI_Obj;

extern Int AUDDEC1COPY_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int AUDDEC1COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int AUDDEC1COPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 AUDDEC1COPY_TI_process(IAUDDEC1_Handle h,
    XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IAUDDEC1_InArgs *inArgs,
    IAUDDEC1_OutArgs *outArgs);

extern XDAS_Int32 AUDDEC1COPY_TI_control(IAUDDEC1_Handle handle,
    IAUDDEC1_Cmd id, IAUDDEC1_DynamicParams *params, IAUDDEC1_Status *status);

#endif
/*
 *  @(#) ti.xdais.dm.examples.auddec1_copy; 2, 0, 0,118; 5-8-2008 09:05:53; /db/wtree/library/trees/dais-j06x/src/
 */

