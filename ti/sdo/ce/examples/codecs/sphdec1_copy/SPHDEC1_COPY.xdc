/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== SPHDEC1_COPY ========
 *  SPHDEC1_COPY codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.speech1.ISPHDEC1, SPHDEC1_COPY declares that it "is
 *  a" speech decoder algorithm.  This allows the Codec Engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the SPHDEC1_COPY algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module SPHDEC1_COPY inherits ti.sdo.ce.speech1.ISPHDEC1
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "SPHDEC1COPY_TI_ISPHDEC1COPY";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.sphdec1_copy; 1, 0, 0,131; 9-9-2008 02:03:12; /db/atree/library/trees/ce-h27x/src/
 */

