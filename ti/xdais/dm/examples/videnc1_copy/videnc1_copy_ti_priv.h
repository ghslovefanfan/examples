/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== videnc1_copy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for VIDENC1COPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the VIDENC1COPY algorithm.
 */
#ifndef VIDENC1COPY_TI_PRIV_
#define VIDENC1COPY_TI_PRIV_

#ifdef USE_ACPY3
#include <ti/xdais/idma3.h>
#endif

typedef struct VIDENC1COPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
#ifdef USE_ACPY3
    IDMA3_Handle dmaHandle1D1D8B;  /* DMA logical channel for 1D to 1D xfers */
#endif
} VIDENC1COPY_TI_Obj;

extern Int VIDENC1COPY_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int VIDENC1COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int VIDENC1COPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 VIDENC1COPY_TI_process(IVIDENC1_Handle h,
    IVIDEO1_BufDescIn *inBufs, XDM_BufDesc *outBufs, IVIDENC1_InArgs *inArgs,
    IVIDENC1_OutArgs *outArgs);

extern XDAS_Int32 VIDENC1COPY_TI_control(IVIDENC1_Handle handle,
    IVIDENC1_Cmd id, IVIDENC1_DynamicParams *params, IVIDENC1_Status *status);

#endif
/*
 *  @(#) ti.xdais.dm.examples.videnc1_copy; 2, 0, 0,118; 5-8-2008 09:07:15; /db/wtree/library/trees/dais-j06x/src/
 */

