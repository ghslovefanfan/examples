/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== IMGDEC_COPY ========
 *  IMGDEC_COPY codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.image.IIMGDEC, IMGDEC_COPY declares that it "is
 *  a" image decoder algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the IMGDEC_COPY algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module IMGDEC_COPY inherits ti.sdo.ce.image.IIMGDEC
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "IMGDECCOPY_TI_IMGDECCOPY";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.imgdec_copy; 1,0,0,132; 9-9-2008 02:02:52; /db/atree/library/trees/ce-h27x/src/
 */

