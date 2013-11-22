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
 *  ======== auddec1_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for AUDDEC1
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the AUDDEC1 algorithm.
 */
#ifndef AUDDEC1_TI_PRIV_
#define AUDDEC1_TI_PRIV_


#include <ti/xdais/ires.h>

/* Header file for the buffer resource (BUFRES) used in this example. */
#include <ti/sdo/fc/ires/bufres/bufres.h>

typedef struct AUDDEC1_TI_Obj {
    IALG_Obj       alg;            /* MUST be first field of all XDAS algs */
    XDAS_Int32     outputPCMWidth;
    XDAS_Int32     pcmFormat;
    XDAS_Int32     dataEndianness;

    /* IRES stuff */
    BUFRES_Handle  bufres;         /* Handle to an IRES resource buffer */
    XDAS_Bool      resActive;      /* Is the resource active? */
    BUFRES_Args    args;           /* Args used to allocate buffer resource */
    IRES_YieldFxn  yieldFxn;
    IRES_YieldArgs yieldArgs;
} AUDDEC1_TI_Obj;

extern Void AUDDEC1_TI_activate(IALG_Handle handle);

extern Int AUDDEC1_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Void AUDDEC1_TI_deactivate(IALG_Handle handle);

extern Int AUDDEC1_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int AUDDEC1_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
        IALG_Handle parent, const IALG_Params *algParams);

extern XDAS_Int32 AUDDEC1_TI_process(IAUDDEC1_Handle h, XDM1_BufDesc *inBufs,
        XDM1_BufDesc *outBufs, IAUDDEC1_InArgs *inArgs,
        IAUDDEC1_OutArgs *outArgs);

extern XDAS_Int32 AUDDEC1_TI_control(IAUDDEC1_Handle handle, IAUDDEC1_Cmd id,
        IAUDDEC1_DynamicParams *params, IAUDDEC1_Status *status);

#endif /* AUDDEC1_TI_PRIV_ */
/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.auddec1; 1, 0, 0,81; 9-9-2008 23:52:59; /db/atree/library/trees/fc-e20x/src/
 */

