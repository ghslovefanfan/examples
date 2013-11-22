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
 *  Simple xDM 1.00 compatible video "encoder".
 *
 *  This example codec provides a reference for two features of xDM 1.0.  Also,
 *  It implements the IDMA3 interface, using the Framework Components' ACPY3
 *  component to utilize DMA.  (Note the comments in the examples' package.bld,
 *  which describe that this dependency on ACPY3 is determined at build-time,
 *  and the DMA-based "copy" is only built if ACPY3 is found in the system.
 *  More specifically, it is only build if the ti.sdo.fc.acpy3 package is found
 *  on the builder's package path.)
 *
 *  First, it demonstrates a simple implementation of the IVIDENC1 interface.
 *  The implementation of the process() function is a simple memcpy.
 *
 *  The second feature demonstrated is the ability to extend xDM's base
 *  interfaces.  In addition to supporting the base interface, it extends
 *  IVIDENC1_InArgs with a codec-specific IVIDENC1CPY_InArgs.  This "InArgs"
 *  struct defines an additional "maxBytes" field, which enables the
 *  application to limit the number of bytes to copy into the output buffer.
 */
package ti.xdais.dm.examples.videnc1_copy [2, 0, 0] {
    module VIDENC1_COPY;
}
/*
 *  @(#) ti.xdais.dm.examples.videnc1_copy; 2, 0, 0,118; 5-8-2008 09:07:15; /db/wtree/library/trees/dais-j06x/src/
 */

