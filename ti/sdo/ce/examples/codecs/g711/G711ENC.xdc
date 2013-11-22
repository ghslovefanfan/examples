/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== G711ENC ========
 *  G711 Encoder specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.speech.ISPHENC, G711ENC declares that it "is a"
 *  speech encoder algorithm. This allows the codec engine to automatically
 *  supply simple stubs and skeletons for transparent execution of DSP
 *  codecs by the GPP.
 *
 *  In addition to declaring the type of the G711 algorithm, we declare
 *  the external symbol required by xDAIS that identifies the algorithms
 *  implementation functions.
 */
metaonly module G711ENC inherits ti.sdo.ce.speech1.ISPHENC1
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "G711ENC_SUN_IG711ENC";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.g711; 1, 0, 0,131; 9-9-2008 02:02:44; /db/atree/library/trees/ce-h27x/src/
 */

