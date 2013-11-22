/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== AUDENC_COPY ========
 *  AUDENC_COPY codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.audio.IAUDENC, AUDENC_COPY declares that it "is
 *  a" audio encoder algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the AUDENC_COPY algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module AUDENC_COPY inherits ti.sdo.ce.audio.IAUDENC
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "AUDENCCOPY_TI_AUDENCCOPY";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.audenc_copy; 1,0,0,132; 9-9-2008 02:02:40; /db/atree/library/trees/ce-h27x/src/
 */

