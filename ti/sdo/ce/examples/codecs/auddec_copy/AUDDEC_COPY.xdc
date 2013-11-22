/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== AUDDEC_COPY ========
 *  AUDDEC_COPY codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.audio.IAUDDEC, AUDDEC_COPY declares that it "is
 *  a" audio decoder algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the AUDDEC_COPY algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module AUDDEC_COPY inherits ti.sdo.ce.audio.IAUDDEC
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "AUDDECCOPY_TI_IAUDDECCOPY";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.auddec_copy; 1,0,0,131; 9-9-2008 02:02:32; /db/atree/library/trees/ce-h27x/src/
 */

