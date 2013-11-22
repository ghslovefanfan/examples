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
 *  ======== g711dec_sun_priv.h ========
 *  Internal vendor specific (TI) interface header for G711DEC
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the G711 algorithm.
 */
#ifndef ti_xdais_dm_examples_g711_G711DEC_TI_PRIV_
#define ti_xdais_dm_examples_g711_G711DEC_TI_PRIV_

extern Int G711DEC_SUN_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int G711DEC_SUN_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int G711DEC_SUN_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 G711DEC_SUN_decode(ISPHDEC1_Handle h,
    XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf,
    ISPHDEC1_InArgs *inArgs, ISPHDEC1_OutArgs *outArgs);

extern XDAS_Int32 G711DEC_SUN_control(ISPHDEC1_Handle handle,
    ISPHDEC1_Cmd id, ISPHDEC1_DynamicParams *dynParams,
    ISPHDEC1_Status *status);

#endif
/*
 *  @(#) ti.xdais.dm.examples.g711; 1, 0, 0,131; 5-8-2008 09:06:05; /db/wtree/library/trees/dais-j06x/src/
 */

