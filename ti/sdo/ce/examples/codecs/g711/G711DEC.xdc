/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== G711DEC ========
 *  G711 Decoder specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.speech1.ISPHDEC1, G711DEC declares that it
 *  "is a" xDM 1.0 speech decoder algorithm.
 *
 *  For heterogeneous environments, the Codec Engine will
 *  automatically supply simple stubs and skeletons for transparent
 *  execution of DSP codecs by the GPP.
 *
 *  In addition to declaring the type of the G711 algorithm, we declare
 *  the external symbol required by xDAIS that identifies the algorithms
 *  implementation functions.
 */
metaonly module G711DEC inherits ti.sdo.ce.speech1.ISPHDEC1
{
    /*!
     *  ======== ialgFxns ========
     *  Name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "G711DEC_SUN_IG711DEC";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.g711; 1, 0, 0,131; 9-9-2008 02:02:44; /db/atree/library/trees/ce-h27x/src/
 */

