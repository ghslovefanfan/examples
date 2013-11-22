/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== imgdec1_copy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for IMGDEC1COPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the IMGDEC1COPY algorithm.
 */
#include <ti/xdais/dm/iimgdec1.h>

#ifndef IMGDEC1COPY_TI_PRIV_
#define IMGDEC1COPY_TI_PRIV_

typedef struct IMGDEC1COPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
    XDAS_Int32  outputChromaFormat;
} IMGDEC1COPY_TI_Obj;

extern Int IMGDEC1COPY_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int IMGDEC1COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int IMGDEC1COPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 IMGDEC1COPY_TI_process(IIMGDEC1_Handle h,
    XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IIMGDEC1_InArgs *inArgs,
    IIMGDEC1_OutArgs *outArgs);

extern XDAS_Int32 IMGDEC1COPY_TI_control(IIMGDEC1_Handle handle,
    IIMGDEC1_Cmd id, IIMGDEC1_DynamicParams *params, IIMGDEC1_Status *status);

#endif
/*
 *  @(#) ti.xdais.dm.examples.imgdec1_copy; 2, 0, 0,118; 5-8-2008 09:06:09; /db/wtree/library/trees/dais-j06x/src/
 */

