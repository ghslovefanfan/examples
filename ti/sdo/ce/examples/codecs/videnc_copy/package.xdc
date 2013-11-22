/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== package.xdc ========
 *  Simple Codec Engine compatible video "encoder".
 *
 *  This codec illustrates the simplest integration into the Codec
 *  Engine.  Only three files are required to integrate into the Codec Engine:
 *  @p(dlist)
 *      - `package.xdc`
 *          This file is required to declare a name for this package and to
 *          list all codec interfaces available.
 *      - `VIDENC_COPY.xdc`
 *          This file specifies a codec (named VIDENC_COPY) that is
 *          provided by this package.
 *      - `VIDENC_COPY.xs`
 *          This file implements the functions required by the ICodec
 *          interface; these functions enable the codec to describe its
 *          non-functional requirements such as stack size.
 *
 *  All other files in this package are simply the implementation of the codec
 *  as specified by xDM.  Thus, integration into the Codec Engine requires
 *  no change to the codecs sources.
 */
package ti.sdo.ce.examples.codecs.videnc_copy {
    module VIDENC_COPY;
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.videnc_copy; 1,0,0,132; 9-9-2008 02:03:52; /db/atree/library/trees/ce-h27x/src/
 */

