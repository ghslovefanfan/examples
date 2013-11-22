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
 *  ======== sphdec1_copy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for SPHDEC1COPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the SPHDEC1COPY algorithm.
 */
#include <ti/xdais/dm/isphdec1.h>

#ifndef ti_xdais_dm_examples_sphdec1_copy_SPHDEC1COPY_TI_PRIV_
#define ti_xdais_dm_examples_sphdec1_copy_SPHDEC1COPY_TI_PRIV_

typedef struct SPHDEC1COPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all xDAIS algs */
    XDAS_Int16  compandingLaw;
    XDAS_Int16  packingType;
    XDAS_Int16  codecSelection;
    XDAS_Int16  postFilter;
    XDAS_Int16  bitRate;
} SPHDEC1COPY_TI_Obj;

extern Int SPHDEC1COPY_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int SPHDEC1COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int SPHDEC1COPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 SPHDEC1COPY_TI_process(ISPHDEC1_Handle h,
    XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf,
    ISPHDEC1_InArgs *inArgs, ISPHDEC1_OutArgs *outArgs);

extern XDAS_Int32 SPHDEC1COPY_TI_control(ISPHDEC1_Handle handle,
    ISPHDEC1_Cmd id, ISPHDEC1_DynamicParams *dynParams,
    ISPHDEC1_Status *status);

#endif
/*
 *  @(#) ti.xdais.dm.examples.sphdec1_copy; 2, 0, 0,130; 5-8-2008 09:06:21; /db/wtree/library/trees/dais-j06x/src/
 */

