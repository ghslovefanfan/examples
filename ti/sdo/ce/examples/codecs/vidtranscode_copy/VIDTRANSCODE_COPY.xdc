/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== VIDTRANSCODE_COPY ========
 *  VIDTRANSCODE_COPY codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.vidtranscode.IVIDTRANSCODE, VIDTRANSCODE_COPY
 *  declares that it "is a" video transcoder algorithm.  This allows the Codec
 *  Engine to automatically supply simple stubs and skeletons for
 *  transparent execution of DSP codecs by the GPP.
 *
 *  In addition to declaring the type of the VIDTRANSCODE_COPY algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module VIDTRANSCODE_COPY inherits ti.sdo.ce.vidtranscode.IVIDTRANSCODE
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns =
        "VIDTRANSCODECOPY_TI_IVIDTRANSCODECOPY";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.vidtranscode_copy; 1,0,0,100; 9-9-2008 02:03:56; /db/atree/library/trees/ce-h27x/src/
 */

