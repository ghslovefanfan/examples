/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== VIDDEC_COPY ========
 *  VIDDEC_COPY codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video.IVIDDEC, VIDDEC_COPY declares that it "is
 *  a" video decoder algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the VIDDEC_COPY algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module VIDDEC_COPY inherits ti.sdo.ce.video.IVIDDEC
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "VIDDECCOPY_TI_VIDDECCOPY";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.viddec_copy; 1,0,0,131; 9-9-2008 02:03:44; /db/atree/library/trees/ce-h27x/src/
 */

