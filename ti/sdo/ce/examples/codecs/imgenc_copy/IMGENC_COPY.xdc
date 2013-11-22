/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== IMGENC_COPY ========
 *  IMGENC_COPY codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.image.IIMGENC, IMGENC_COPY declares that it "is
 *  a" image encoder algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the IMGENC_COPY algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module IMGENC_COPY inherits ti.sdo.ce.image.IIMGENC
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "IMGENCCOPY_TI_IMGENCCOPY";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.imgenc_copy; 1,0,0,132; 9-9-2008 02:03:00; /db/atree/library/trees/ce-h27x/src/
 */

