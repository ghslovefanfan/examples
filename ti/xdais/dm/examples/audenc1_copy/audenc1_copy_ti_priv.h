/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== audenc1_copy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for AUDENC1COPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the AUDENC1COPY algorithm.
 */
#include <ti/xdais/dm/iaudenc1.h>

#ifndef AUDENC1COPY_TI_PRIV_
#define AUDENC1COPY_TI_PRIV_

typedef struct AUDENC1COPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
    XDAS_Int32  bitRate;
    XDAS_Int32  lfeFlag;
    XDAS_Int32  sampleRate;
    XDAS_Int32  channelMode;
    XDAS_Int32  dualMonoMode;
    XDAS_Int32  encMode;
    XDAS_Int32  inputBitsPerSample;
} AUDENC1COPY_TI_Obj;

extern Int AUDENC1COPY_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int AUDENC1COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int AUDENC1COPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 AUDENC1COPY_TI_process(IAUDENC1_Handle h,
    XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IAUDENC1_InArgs *inArgs,
    IAUDENC1_OutArgs *outArgs);

extern XDAS_Int32 AUDENC1COPY_TI_control(IAUDENC1_Handle handle,
    IAUDENC1_Cmd id, IAUDENC1_DynamicParams *params, IAUDENC1_Status *status);

#endif
/*
 *  @(#) ti.xdais.dm.examples.audenc1_copy; 2, 0, 0,118; 5-8-2008 09:06:01; /db/wtree/library/trees/dais-j06x/src/
 */

