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
 *  ======== sphenccopy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for SPHENC1COPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the SPHENC1COPY algorithm.
 */
#include <ti/xdais/dm/isphdec1.h>

#ifndef SPHENC1COPY_TI_PRIV_
#define SPHENC1COPY_TI_PRIV_

typedef struct SPHENC1COPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all xDAIS algs */
    XDAS_Int16  frameSize;
    XDAS_Int16  compandingLaw;
    XDAS_Int16  packingType;
    XDAS_Int16  vadSelection;
    XDAS_Int16  codecSelection;
    XDAS_Int16  bitRate;
    XDAS_Int16  mode;
    XDAS_Int16  vadFlag;
    XDAS_Int16  noiseSuppressionMode;
    XDAS_Int16  ttyTddMode;
    XDAS_Int16  dtmfMode;
    XDAS_Int16  dataTransmit;
} SPHENC1COPY_TI_Obj;

extern Int SPHENC1COPY_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int SPHENC1COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int SPHENC1COPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 SPHENC1COPY_TI_process(ISPHENC1_Handle h,
    XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf,
    ISPHENC1_InArgs *inArgs, ISPHENC1_OutArgs *outArgs);

extern XDAS_Int32 SPHENC1COPY_TI_control(ISPHENC1_Handle handle,
    ISPHENC1_Cmd id, ISPHENC1_DynamicParams *dynParams,
    ISPHENC1_Status *status);

#endif
/*
 *  @(#) ti.xdais.dm.examples.sphenc1_copy; 2, 0, 0,122; 5-8-2008 09:06:37; /db/wtree/library/trees/dais-j06x/src/
 */

