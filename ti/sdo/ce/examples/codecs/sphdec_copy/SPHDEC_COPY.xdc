/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== SPHDEC_COPY ========
 *  SPHDEC_COPY codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.speech.ISPHDEC, SPHDEC_COPY declares that it "is
 *  a" speech decoder algorithm.  This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the SPHDEC_COPY algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module SPHDEC_COPY inherits ti.sdo.ce.speech.ISPHDEC
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "SPHDECCOPY_TI_SPHDECCOPY";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.sphdec_copy; 1,0,0,132; 9-9-2008 02:03:16; /db/atree/library/trees/ce-h27x/src/
 */

