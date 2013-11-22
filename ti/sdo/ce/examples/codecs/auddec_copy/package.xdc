/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

requires ti.xdais.dm.examples.auddec_copy;

/*!
 *  ======== package.xdc ========
 *  Simple Codec Engine compatible audio "decoder", wrapping the audio decode
 *  copy codec distributed with xDAIS.
 *
 *  This codec illustrates the simplest integration into the Codec
 *  Engine.  Only three files are required to integrate into the codec engine:
 *  @p(dlist)
 *      - `package.xdc`
 *          This file is required to declare a name for this package and to
 *          list all codec interfaces available.
 *      - `AUDDEC_COPY.xdc`
 *          This file specifies a codec (named AUDDEC_COPY) that is
 *          provided by this package.
 *      - `AUDDEC_COPY.xs`
 *          This file implements the functions required by the ICodec
 *          interface; these functions enable the codec to describe its
 *          non-functional requirements such as stack size.
 *
 *  Integration into the Codec Engine requires no change to the codecs
 *  libraries.
 */
package ti.sdo.ce.examples.codecs.auddec_copy {
    module AUDDEC_COPY;
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.auddec_copy; 1,0,0,131; 9-9-2008 02:02:32; /db/atree/library/trees/ce-h27x/src/
 */

