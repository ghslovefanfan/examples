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
 *  ======== videnc1_copy_ti.h ========
 */
#ifndef ti_xdais_dm_examples_videnc1_copy_VIDENC1_COPY_TI_
#define ti_xdais_dm_examples_videnc1_copy_VIDENC1_COPY_TI_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== VIDENC1COPY_TI_IVIDENCCOPY ========
 *  Our implementation of the IVIDENC1 interface
 */
extern IVIDENC1_Fxns VIDENC1COPY_TI_IVIDENC1COPY;
extern IALG_Fxns VIDENC1COPY_TI_IALG;

/*
 *  ======== IVIDENC1CPY_InArgs ========
 *  This codec extends IVIDENC1_InArgs with a codec-specific "maxBytes" field.
 */
typedef struct IVIDENC1CPY_InArgs {
    IVIDENC1_InArgs videnc1InArgs;
    XDAS_Int32      maxBytes;    /* Maximum number of bytes to copy. */
} IVIDENC1CPY_InArgs;

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.xdais.dm.examples.videnc1_copy; 2, 0, 0,118; 5-8-2008 09:07:15; /db/wtree/library/trees/dais-j06x/src/
 */

