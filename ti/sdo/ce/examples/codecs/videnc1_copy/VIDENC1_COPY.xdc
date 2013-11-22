/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== VIDENC1_COPY ========
 *  VIDENC1_COPY codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video1.IVIDENC1, VIDENC1_COPY declares
 *  that it "is a" video 1.0 encoder algorithm.  This allows the Codec
 *  Engine to automatically supply simple stubs and skeletons for
 *  transparent execution of DSP codecs by the GPP.
 *
 *  In addition to declaring the type of the VIDENC1_COPY algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module VIDENC1_COPY inherits ti.sdo.ce.video1.IVIDENC1
{
    /* handle to underlying algorithm's module - for convenience. */
    readonly config ti.xdais.dm.examples.videnc1_copy.VIDENC1_COPY.Module alg =
        ti.xdais.dm.examples.videnc1_copy.VIDENC1_COPY;

    override readonly config String ialgFxns = "VIDENC1COPY_TI_IVIDENC1COPY";

    override readonly config String idma3Fxns = "VIDENC1COPY_TI_IDMA3";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.videnc1_copy; 1,0,0,131; 9-9-2008 02:03:48; /db/atree/library/trees/ce-h27x/src/
 */

