/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== ISCALE ========
 *  Scale Codec Configuration interface
 *
 *  All Scale Codec modules must implement this configuration interface.
 */
metaonly interface ISCALE inherits ti.sdo.ce.ICodec
{
    override readonly config String serverFxns = "SCALE_SKEL";
    override readonly config String stubFxns = "SCALE_STUBS";

    override readonly config Int rpcProtocolVersion = 1;
}
/*
 *  @(#) ti.sdo.ce.examples.extensions.scale; 1,0,0,131; 9-9-2008 02:04:04; /db/atree/library/trees/ce-h27x/src/
 */

