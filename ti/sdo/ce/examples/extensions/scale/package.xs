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
 */
function getLibs(prog)
{
    /* "mangle" program build attrs into an appropriate directory name */
    var name = this.profile == "debug" ? "lib/scale_debug" : "lib/scale";

    /* return the library name: name.a<arch> */
    var lib = name + ".a" + prog.build.target.suffix;
    print("    will link with " + this.$name + ":" + lib);

    return (lib);
}
/*
 *  @(#) ti.sdo.ce.examples.extensions.scale; 1,0,0,131; 9-9-2008 02:04:04; /db/atree/library/trees/ce-h27x/src/
 */

