/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== getLibs ========
 */
function getLibs() 
{
    return (null);
}

/*
 *  ======== getSects ========
 */
function getSects() {
    if (prog.name.search("bufres_test") != -1) {
        return ("ti/sdo/fc/rman/examples/bufres_yield/bufres_test.xdt");
    }
    else {
        return (null);
    }
}

/*
 *  @(#) ti.sdo.fc.rman.examples.bufres_yield; 1, 0, 0,83; 9-9-2008 23:54:37; /db/atree/library/trees/fc-e20x/src/
 */

