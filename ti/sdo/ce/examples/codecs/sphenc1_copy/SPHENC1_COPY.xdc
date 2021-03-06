/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== SPHENC1_COPY ========
 *  SPHENC1_COPY codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.speech1.ISPHENC1, SPHENC1_COPY declares that it "is
 *  a" speech encoder algorithm.  This allows the Codec Engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the SPHENC1_COPY algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module SPHENC1_COPY inherits ti.sdo.ce.speech1.ISPHENC1
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "SPHENC1COPY_TI_ISPHENC1COPY";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.sphenc1_copy; 1, 0, 0,131; 9-9-2008 02:03:20; /db/atree/library/trees/ce-h27x/src/
 */

