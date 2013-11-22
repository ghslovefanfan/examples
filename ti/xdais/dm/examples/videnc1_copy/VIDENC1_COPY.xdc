/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== VIDENC1_COPY.xdc ========
 */
metaonly module VIDENC1_COPY
{
    /*!
     *  ======== useDMA ========
     *  This config flag can be used to enable DMA in this algorithm.
     *
     *  Note that this feature is not available on all targets this codec
     *  supports.  If you set this to true, this package will test whether DMA
     *  is available for the requested target.  If it's not available, a
     *  warning will be printed, and the codec will fall back to using the
     *  memcpy based implementation.
     */
    config Bool useDMA = false;
}
/*
 *  @(#) ti.xdais.dm.examples.videnc1_copy; 2, 0, 0,118; 5-8-2008 09:07:15; /db/wtree/library/trees/dais-j06x/src/
 */

