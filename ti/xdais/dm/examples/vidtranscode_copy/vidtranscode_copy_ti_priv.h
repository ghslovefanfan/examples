/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== vidtranscode_copy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for VIDTRANSCODECOPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the VIDTRANSCODECOPY algorithm.
 */
#include <ti/xdais/dm/ividtranscode.h>

#ifndef VIDTRANSCODECOPY_TI_PRIV_
#define VIDTRANSCODECOPY_TI_PRIV_

typedef struct VIDTRANSCODECOPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
} VIDTRANSCODECOPY_TI_Obj;

extern Int VIDTRANSCODECOPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[]);

extern Int VIDTRANSCODECOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int VIDTRANSCODECOPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 VIDTRANSCODECOPY_TI_process(IVIDTRANSCODE_Handle h,
    XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDTRANSCODE_InArgs *inArgs,
    IVIDTRANSCODE_OutArgs *outArgs);

extern XDAS_Int32 VIDTRANSCODECOPY_TI_control(IVIDTRANSCODE_Handle handle,
    IVIDTRANSCODE_Cmd id, IVIDTRANSCODE_DynamicParams *params,
    IVIDTRANSCODE_Status *status);

#endif
/*
 *  @(#) ti.xdais.dm.examples.vidtranscode_copy; 2, 0, 0,45; 5-8-2008 09:07:33; /db/wtree/library/trees/dais-j06x/src/
 */

