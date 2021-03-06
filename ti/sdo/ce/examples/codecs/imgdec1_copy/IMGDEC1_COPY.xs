/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== IMGDEC1_COPY.xs ========
 *  This file implements the functions specified in the ti.sdo.ce.ICodec
 *  interface.  These functions enable the configuration tool to validate
 *  user supplied configuration parameters (e.g., stack size for the
 *  thread running this codec).
 */

var verbose = false;   /* set to true to enable verbose output during config */

/*
 *  ======== getStackSize ========
 */
function getStackSize(prog)
{
    if (verbose) {
        print("getting stack size for " + this.$name
            + " built for the target " + prog.build.target.$name
            + ", running on platform " +  prog.platformName);
    }

    return (2048);
}

/*
 *  ======== getDaramScratchSize ========
 */
function getDaramScratchSize(prog)
{
    if (verbose) {
        print("getting DARAM scratch size for " + this.$name
            + " built for the target " + prog.build.target.$name
            + ", running on platform " +  prog.platformName);
    }

    return (0);
}

/*
 *  ======== getSaramScratchSize ========
 */
function getSaramScratchSize(prog)
{
    if (verbose) {
        print("getting SARAM scratch size for " + this.$name
            + " built for the target " + prog.build.target.$name
            + ", running on platform " +  prog.platformName);
    }

    return (0);
}

/*
 *  @(#) ti.sdo.ce.examples.codecs.imgdec1_copy; 1,0,0,131; 9-9-2008 02:02:48; /db/atree/library/trees/ce-h27x/src/
 */

