/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== VIDDEC2_COPY ========
 *  VIDDEC2_COPY codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.video2.IVIDDEC2, VIDDEC2_COPY declares that it "is
 *  a" video decoder algorithm.  This allows the Codec Engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the VIDDEC2_COPY algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module VIDDEC2_COPY inherits ti.sdo.ce.video2.IVIDDEC2
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "VIDDEC2COPY_TI_IVIDDEC2COPY";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.viddec2_copy; 1,0,0,45; 9-9-2008 02:03:40; /db/atree/library/trees/ce-h27x/src/
 */

