/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== videnccopy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for VIDENCCOPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the VIDENCCOPY algorithm.
 */
#ifndef VIDENCCOPY_TI_PRIV_
#define VIDENCCOPY_TI_PRIV_

#ifdef USE_ACPY3
#include <ti/bios/include/std.h>
#include <ti/xdais/idma3.h>
#endif

/* Add for alg of image process by pitou */
#include "cv.h"
extern Void VIDENCCOPY_TI_RGB_2_YUV422( XDAS_UInt8* pRGB, XDAS_UInt8* pYUV, XDAS_Int32 height, XDAS_Int32 width);
extern Void VIDENCCOPY_TI_YUV422_2_RGB( XDAS_UInt8* pYUV, XDAS_UInt8* pRGB, XDAS_Int32 height, XDAS_Int32 width);

typedef struct VIDENCCOPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
	/* Add for alg of image process by pitou */
	IplImage     *img;
	XDAS_UInt8   *pRGB;
#ifdef USE_ACPY3
    IDMA3_Handle dmaHandle1D1D8B;  /* DMA logical channel for 1D to 1D xfers */
#endif
} VIDENCCOPY_TI_Obj;

extern Void VIDENCCOPY_TI_activate(IALG_Handle handle);

extern Int VIDENCCOPY_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Void VIDENCCOPY_TI_deactivate(IALG_Handle handle);

extern Int VIDENCCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int VIDENCCOPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 VIDENCCOPY_TI_process(IVIDENC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDENC_InArgs *inargs, IVIDENC_OutArgs *outargs);

extern XDAS_Int32 VIDENCCOPY_TI_control(IVIDENC_Handle handle,
    IVIDENC_Cmd id, IVIDENC_DynamicParams *params, IVIDENC_Status *status);
	
#endif

/*
 *  @(#) ti.sdo.ce.examples.codecs.videnc_copy; 1,0,0,132; 9-9-2008 02:03:52; /db/atree/library/trees/ce-h27x/src/
 */

