/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

requires ti.xdais.dm.examples.imgdec1_copy;

/*!
 *  ======== package.xdc ========
 *  Simple Codec Engine compatible image 1.0 "decoder", wrapping the image 1.0
 *  decode copy codec distributed with xDAIS.
 *
 *  This codec illustrates the simplest integration into the Codec
 *  Engine.  Only three files are required to integrate into the codec engine:
 *  @p(dlist)
 *      - `package.xdc`
 *          This file is required to declare a name for this package and to
 *          list all codec interfaces available.
 *      - `IMGDEC1_COPY.xdc`
 *          This file specifies a codec (named IMGDEC1_COPY) that is
 *          provided by this package.
 *      - `IMGDEC1_COPY.xs`
 *          This file implements the functions required by the ICodec
 *          interface; these functions enable the codec to describe its
 *          non-functional requirements such as stack size.
 *
 *  Integration into the Codec Engine requires no change to the codecs
 *  libraries.
 */
package ti.sdo.ce.examples.codecs.imgdec1_copy {
    module IMGDEC1_COPY;
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.imgdec1_copy; 1,0,0,131; 9-9-2008 02:02:48; /db/atree/library/trees/ce-h27x/src/
 */

