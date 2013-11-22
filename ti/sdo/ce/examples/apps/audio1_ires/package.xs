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
 *  ======== close ========
 */
function close()
{
    if (prog.name.search("app_local") != -1) {
        xdc.loadPackage('ti.sdo.fc.ires.bufres');
    }
}

/*
 *  ======== getSects ========
 */
function getSects() {
    if (prog.name.search("app_local") != -1) {
        return ("ti/sdo/ce/examples/apps/audio1_ires/local.xdt");
    }
    else {
        return (null);
    }
}

/*
 *  @(#) ti.sdo.ce.examples.apps.audio1_ires; 1,0,0,96; 9-9-2008 02:00:21; /db/atree/library/trees/ce-h27x/src/
 */

