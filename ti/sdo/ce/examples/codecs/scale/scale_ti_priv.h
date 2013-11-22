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
 *  ======== scale_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for SCALE
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the SCALE algorithm.
 */
#ifndef SCALE_TI_PRIV_
#define SCALE_TI_PRIV_

#include <ti/xdais/ialg.h>

typedef struct SCALE_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
    XDAS_Int32  scaleFactor;
} SCALE_TI_Obj;

extern Int SCALE_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int SCALE_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int SCALE_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 SCALE_TI_process(ISCALE_Handle h, XDAS_Int8 *inBuf,
    XDAS_Int8 *outBuf, ISCALE_InArgs *inargs, ISCALE_OutArgs *outargs);

extern XDAS_Int32 SCALE_TI_control(ISCALE_Handle handle,
    ISCALE_Cmd id, ISCALE_DynamicParams *params);

#endif
/*
 *  @(#) ti.sdo.ce.examples.codecs.scale; 1,0,0,131; 9-9-2008 02:03:08; /db/atree/library/trees/ce-h27x/src/
 */

