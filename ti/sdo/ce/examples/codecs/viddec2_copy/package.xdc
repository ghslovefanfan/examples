/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

requires ti.xdais.dm.examples.viddec2_copy;

/*!
 *  ======== package.xdc ========
 *  Simple Codec Engine compatible IVIDDEC2 "decoder", wrapping the video2_copy
 *  codec distributed with xDAIS.
 *
 *  This codec illustrates the simplest integration into the Codec
 *  Engine.  Only three files are required to integrate into the codec engine:
 *  @p(dlist)
 *      - `package.xdc`
 *          This file is required to declare a name for this package and to
 *          list all codec interfaces available.
 *      - `VIDDEC2_COPY.xdc`
 *          This file specifies a codec (named VIDDEC2_COPY) that is
 *          provided by this package.
 *      - `VIDDEC2_COPY.xs`
 *          This file implements the functions required by the ICodec
 *          interface; these functions enable the codec to describe its
 *          non-functional requirements such as stack size.
 *
 *  Integration into the Codec Engine requires no change to the codecs
 *  libraries.
 */
package ti.sdo.ce.examples.codecs.viddec2_copy {
    module VIDDEC2_COPY;
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.viddec2_copy; 1,0,0,45; 9-9-2008 02:03:40; /db/atree/library/trees/ce-h27x/src/
 */

