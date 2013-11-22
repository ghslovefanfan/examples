/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== AUDDEC1_COPY ========
 *  AUDDEC1_COPY codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.audio1.IAUDDEC1, AUDDEC1_COPY declares
 *  that it "is a" audio 1.0 decoder algorithm.  This allows the Codec
 *  Engine to automatically supply simple stubs and skeletons for
 *  transparent execution of DSP codecs by the GPP.
 *
 *  In addition to declaring the type of the AUDDEC1_COPY algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module AUDDEC1_COPY inherits ti.sdo.ce.audio1.IAUDDEC1
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "AUDDEC1COPY_TI_IAUDDEC1COPY";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.auddec1_copy; 1,0,0,132; 9-9-2008 02:02:24; /db/atree/library/trees/ce-h27x/src/
 */

