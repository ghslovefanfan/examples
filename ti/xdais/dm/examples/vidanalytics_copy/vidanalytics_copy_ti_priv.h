/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== vidanalytics_copy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for VIDANALYTICSCOPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the VIDANALYTICSCOPY algorithm.
 */
#include <ti/xdais/dm/ividanalytics.h>

#ifndef VIDANALYTICSCOPY_TI_PRIV_
#define VIDANALYTICSCOPY_TI_PRIV_

typedef struct VIDANALYTICSCOPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
    XDAS_Int32  viewState;
    XDAS_Int32  extendedError;
} VIDANALYTICSCOPY_TI_Obj;

extern Int VIDANALYTICSCOPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[]);

extern Int VIDANALYTICSCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int VIDANALYTICSCOPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 VIDANALYTICSCOPY_TI_process(IVIDANALYTICS_Handle h,
    XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IVIDANALYTICS_InArgs *inArgs,
    IVIDANALYTICS_OutArgs *outArgs);

extern XDAS_Int32 VIDANALYTICSCOPY_TI_control(IVIDANALYTICS_Handle handle,
    IVIDANALYTICS_Cmd id, IVIDANALYTICS_DynamicParams *params,
    IVIDANALYTICS_Status *status);

#endif
/*
 *  @(#) ti.xdais.dm.examples.vidanalytics_copy; 2, 0, 0,27; 5-8-2008 09:06:58; /db/wtree/library/trees/dais-j06x/src/
 */

