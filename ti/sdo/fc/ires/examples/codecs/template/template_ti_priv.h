/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== template_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for TEMPLATE
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the TEMPLATE algorithm.
 */
#ifndef TEMPLATE_TI_PRIV_
#define TEMPLATE_TI_PRIV_


#include <ti/xdais/ires.h>

/* Header file for the NULL resource (NULLRES) used in this example. */
#include <ti/sdo/fc/ires/nullresource/ires_nullres.h>

typedef struct TEMPLATE_TI_CtxtArgs {
    Int size;           
} TEMPLATE_TI_CtxtArgs;

typedef struct TEMPLATE_TI_Obj {
    IALG_Obj       alg;            /* MUST be first field of all XDAS algs */

    /* IRES stuff */
    IRES_Handle nullres;
    Bool      resActive;            /* Is the resource active? */
    IRES_YieldFxn  yieldFxn;
    IRES_YieldArgs yieldArgs;
    IRES_YieldContext yieldContext;        
    TEMPLATE_TI_CtxtArgs  contextArgs;
} TEMPLATE_TI_Obj;

extern Int TEMPLATE_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int TEMPLATE_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int TEMPLATE_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
        IALG_Handle parent, const IALG_Params *algParams);

extern Int TEMPLATE_TI_process(ITEMPLATE_Handle h, ITEMPLATE_InArgs *inArgs,
        ITEMPLATE_OutArgs *outArgs);

extern Int TEMPLATE_TI_control(ITEMPLATE_Handle handle, ITEMPLATE_Cmd id,
        ITEMPLATE_DynamicParams *params, ITEMPLATE_Status *status);

#endif /* TEMPLATE_TI_PRIV_ */
/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.template; 1, 0, 0,76; 9-9-2008 23:53:14; /db/atree/library/trees/fc-e20x/src/
 */

