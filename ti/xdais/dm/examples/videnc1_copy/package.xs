/* 
 *  Copyright 2008
 *  Texas Instruments Incorporated
 *
 *  All rights reserved.  Property of Texas Instruments Incorporated
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
     * Note that this package demonstrates several different ways to
     * build, including CCS projects, GNU makefiles and XDC Builds.
     * The location of the libraries, however are always in the same place.
     * As a result, this getLibs function is relatively simple.
     */

    if (this.profile == "debug") {
        if (this.VIDENC1_COPY.useDMA == true) {
            name = "lib/debug/videnc1_copy_dma.a"+ prog.build.target.suffix;
        }
        else {
            name = "lib/debug/videnc1_copy.a" + prog.build.target.suffix;
        }
    }
    else {
        if (this.VIDENC1_COPY.useDMA == true) {
            name = "lib/videnc1_copy_dma.a"+ prog.build.target.suffix;
        }
        else {
            name = "lib/videnc1_copy.a" + prog.build.target.suffix;
        }
    }

    /* and dump a helpful breadcrumb */
    print("    will link with " + this.$name + ":" + name);

    return (name);
}


/*
 *  ======== Package.close ========
 *  Close this package.
 */
function close()
{
    print(this.$name + ".close() ...");

    if (this.VIDENC1_COPY.useDMA == true) {
        /* declare that this package has a dependency on ACPY3. */
//        print("    ... loading ACPY3 module");
        xdc.useModule('ti.sdo.fc.acpy3.ACPY3');
    }
}
/*
 *  @(#) ti.xdais.dm.examples.videnc1_copy; 2, 0, 0,118; 5-8-2008 09:07:15; /db/wtree/library/trees/dais-j06x/src/
 */

