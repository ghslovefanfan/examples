/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== VIDANALYTICS_COPY ========
 *  VIDANALYTICS_COPY codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 *  By inheriting ti.sdo.ce.vidanalytics.IVIDANALYTICS, this
 *  VIDANALYTICS_COPY Module declares that it "is a" video analytics
 *  algorithm.  For environments where this codec will be served by a
 *  Codec Server, this inheritance enables the Codec Engine to
 *  automatically supply simple stubs and skeletons for transparent
 *  execution of this codec.
 *
 *  In addition to declaring the type of the VIDANALYTICS_COPY algorithm, we
 *  declare the external symbol required by xDAIS that identifies the
 *  algorithms implementation functions.
 */
metaonly module VIDANALYTICS_COPY inherits ti.sdo.ce.vidanalytics.IVIDANALYTICS
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns =
        "VIDANALYTICSCOPY_TI_IVIDANALYTICSCOPY";
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.vidanalytics_copy; 1,0,0,82; 9-9-2008 02:03:32; /db/atree/library/trees/ce-h27x/src/
 */

