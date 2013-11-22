/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

requires ti.sdo.fc.ires.examples.codecs.auddec1;

/*!
 *  ======== package.xdc ========
 *  Simple Codec Engine compatible audio 1.0 "decoder", wrapping the audio 1.0
 *  decode IRES copy codec distributed with xDAIS. This codec implements the
 *  IRES_Fxns interface.
 *
 *  This codec illustrates the simplest integration into the Codec
 *  Engine.  Only three files are required to integrate into the codec engine:
 *  @p(dlist)
 *      - `package.xdc`
 *          This file is required to declare a name for this package and to
 *          list all codec interfaces available.
 *      - `AUDDEC1_IRES.xdc`
 *          This file specifies a codec (named AUDDEC1_IRES) that is
 *          provided by this package.
 *      - `AUDDEC1_IRES.xs`
 *          This file implements the functions required by the ICodec
 *          interface; these functions enable the codec to describe its
 *          non-functional requirements such as stack size.
 *
 *  Integration into the Codec Engine requires no change to the codecs
 *  libraries.
 */
package ti.sdo.ce.examples.codecs.auddec1_ires {
    module AUDDEC1_IRES;
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.auddec1_ires; 1,0,0,91; 9-9-2008 02:02:28; /db/atree/library/trees/ce-h27x/src/
 */

