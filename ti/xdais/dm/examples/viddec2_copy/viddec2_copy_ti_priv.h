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
 *  ======== viddec2_copy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for VIDDEC2COPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the VIDDEC2COPY algorithm.
 */
#include <ti/xdais/dm/ividdec2.h>

#ifndef VIDDEC2COPY_TI_PRIV_
#define VIDDEC2COPY_TI_PRIV_

typedef struct VIDDEC2COPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
    XDAS_Int32  outputChromaFormat;
} VIDDEC2COPY_TI_Obj;

extern Int VIDDEC2COPY_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int VIDDEC2COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int VIDDEC2COPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 VIDDEC2COPY_TI_process(IVIDDEC2_Handle h,
    XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDDEC2_InArgs *inArgs,
    IVIDDEC2_OutArgs *outArgs);

extern XDAS_Int32 VIDDEC2COPY_TI_control(IVIDDEC2_Handle handle,
    IVIDDEC2_Cmd id, IVIDDEC2_DynamicParams *params, IVIDDEC2_Status *status);

#endif
/*
 *  @(#) ti.xdais.dm.examples.viddec2_copy; 2, 0, 0,21; 5-8-2008 09:07:09; /db/wtree/library/trees/dais-j06x/src/
 */

