/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== SCALE_TI ========
 *  SCALE_TI codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.examples.extensions.scale.ISCALE, SCALE_TI
 *  declares that it "is a" scaling algorithm.
 *
 *  In addition to declaring the type of the SCALE algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithm's implementation functions.
 */
metaonly module SCALE_TI inherits ti.sdo.ce.examples.extensions.scale.ISCALE
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "SCALE_TI_SCALE";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.scale; 1,0,0,131; 9-9-2008 02:03:08; /db/atree/library/trees/ce-h27x/src/
 */

