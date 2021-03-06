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
 *
 */
function getLibs(prog)
{
    /* "mangle" program build attrs into an appropriate directory name */
    var name = "lib/scale_ti.a" + prog.build.target.suffix;

    /* return the library name: name.a<arch> */
    print("    will link with " + this.$name + ":" + name);

    return (name);
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.scale; 1,0,0,131; 9-9-2008 02:03:08; /db/atree/library/trees/ce-h27x/src/
 */

