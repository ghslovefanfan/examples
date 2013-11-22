/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== VIDENC_COPY ========
 *  VIDENC_COPY codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video.IVIDENC, VIDENC_COPY declares that it "is
 *  a" video encoder algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the VIDENC_COPY algorithm, we declare the
 *  external symbol required by xDAIS that identifies the algorithms
 *  implementation functions.
 */
metaonly module VIDENC_COPY inherits ti.sdo.ce.video.IVIDENC
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "VIDENCCOPY_TI_VIDENCCOPY";

    /*!
     *  ======== idma3Fxns ========
     *  Name of xDAIS alg IDMA3 Interface function table.
     *
     *  Note that this is used only if .useDMA is set to true.  If
     *  .useDMA is false (the default), this idma3Fxns config param is
     *  set to NULL during the package's close phase.
     */
    override readonly config String idma3Fxns = "VIDENCCOPY_TI_IDMA3";

    /*!
     *  ======== useDMA ========
     *  This config flag can be used to enable the DMA performance enhancments
     *  available for <i>some</i> targets this codec supports (e.g. C64P).
     *
     *  If you set this to true, this package will test whether DMA is
     *  available for the requested target.  If it's not available, a warning
     *  will be printed, and the codec will fall back to using the copy
     *  based version.
     */
    config Bool useDMA = false;
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.videnc_copy; 1,0,0,132; 9-9-2008 02:03:52; /db/atree/library/trees/ce-h27x/src/
 */

