/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== AUDENC1_COPY ========
 *  AUDENC1_COPY codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.audio1.IAUDENC1, AUDENC1_COPY declares
 *  that it "is a" audio 1.0 encoder algorithm.  This allows the Codec
 *  Engine to automatically supply simple stubs and skeletons for
 *  transparent execution of DSP codecs by the GPP.
 *
 *  In addition to declaring the type of the AUDENC1_COPY algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module AUDENC1_COPY inherits ti.sdo.ce.audio1.IAUDENC1
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "AUDENC1COPY_TI_IAUDENC1COPY";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.audenc1_copy; 1,0,0,131; 9-9-2008 02:02:36; /db/atree/library/trees/ce-h27x/src/
 */

