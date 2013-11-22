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
 *
 */
function getLibs(prog)
{
    /* No library in this package */
    return ("");
}

/*
 *  ======== close ========
 */
function close()
{
//    print(this.$name + ".close() ...");
    var prog = Program;

    /* If the .alg.useDMA is false, clear the idma3Fxns config param. */
    if (!this.VIDENC1_COPY.alg.useDMA) {
        /* Unseal the readonly config param first.  Use $unseal with care. */
        this.VIDENC1_COPY.$unseal("idma3Fxns");
        this.VIDENC1_COPY.idma3Fxns = null;
        this.VIDENC1_COPY.$seal("idma3Fxns");
    }
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.videnc1_copy; 1,0,0,131; 9-9-2008 02:03:48; /db/atree/library/trees/ce-h27x/src/
 */

