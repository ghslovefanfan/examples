/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== package.xs ========
 *    Implementation of the xdc.IPackage interface.
 */

/*
 *  ======== Package.getLibs ========
 *  Determine the name of the library to use, based on the program
 *  configuration (prog).
 */
function getLibs(prog)
{
    var name = "";

    /*
     * Note that we did a check in close() to ensure .useDMA is only set
     * if we have a library that supports it (e.g. C64P).
     */
    if (this.VIDENC_COPY.useDMA) {
        name = "lib/videnc_copy_dma.a" + prog.build.target.suffix;
    } else {
        name = "lib/videnc_copy.a" + prog.build.target.suffix;
    }

    /* return the library name: name.a<arch> */
    print("    will link with " + this.$name + ":" + name);

    return (name);
}


/*
 *  ======== Package.close ========
 *  Close this package; optionally (re)set other config parameters in the
 *  model
 */
function close()
{
    print(this.$name + ".close() ...");
    var prog = Program;

    /*
     * If we're not on a 64, and .useDMA is set, we're "smart" and reset
     * the .useDMA to false, printing an appropriate warning.
     */
    if ((prog.build.target.suffix.match("64") == null) &&
        (this.VIDENC_COPY.useDMA)) {

        print("Warning.  The " + this.$name + " package doesn't have a " +
            "library which supports DMA for the " + prog.build.target.name +
            " target.  Setting .useDMA to \"false\".");
        this.VIDENC_COPY.useDMA = false;
    }

    /* If the .useDMA is false, clear the idma3Fxns config param. */
    if (!this.VIDENC_COPY.useDMA) {
        /* Unseal the readonly config param first.  Use $unseal with care. */
        this.VIDENC_COPY.$unseal("idma3Fxns");
        this.VIDENC_COPY.idma3Fxns = null;
        this.VIDENC_COPY.$seal("idma3Fxns");
    }
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.videnc_copy; 1,0,0,132; 9-9-2008 02:03:52; /db/atree/library/trees/ce-h27x/src/
 */

