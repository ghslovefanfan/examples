/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

#include <xdc/std.h>
#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/dskt2/dskt2.h>
#include <ti/sdo/fc/ires/iresman.h>
#include <ti/sdo/fc/ires/vicp/iresman_vicp.h>
#include <ires_algorithm.h>
#include <stdio.h>


/*
 * extern declaration 
 */
extern Int smain(Int argc, Char * argv[]);


/*
 * global declarations
 */

IRESMAN_VicpParams configParams = {
    0,      /* Size of this structure */
            /*
             * RMAN_PERSISTENTALLOCFXN,
             * RMAN_PERSISTENTFREEFXN,
             */
    NULL,
    NULL,
};

void main()
{
}

/* ARGSUSED - this line tells the compiler to not generate compiler warnings 
 * for unused arguments */ 
Int smain(Int argc, Char * argv[])
{

    IRES_Status status;
    Int size = 0;
    Int scratchId = 2;
    IALG_Status algStatus;
    IALG_Fxns * algFxns = &DUMRES_TI_IALG;
    IRES_Fxns * resFxns = &DUMRES_TI_IRES;
    DUMRES_TI_Handle dumHandle = NULL; 


    status = RMAN_init(); 
    if (IRES_OK != status) {
        printf("RMAN initialization Failed \n");
        return -1;
    }

    /*
     * Create an instance of the algorithm using "algFxns" 
     */
    dumHandle = (DUMRES_TI_Handle)DSKT2_createAlg(scratchId, 
            (IALG_Fxns *)algFxns, NULL,(IALG_Params *)NULL);
    if (dumHandle == NULL) {
        printf("Alg creation failed \n");
        return -1;
    } 

    /*
     * Supply initialization information for the RESMAN while registering
     */
    size = sizeof(IRESMAN_VicpParams);

    configParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
    configParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
    configParams.baseConfig.size = size;

    /* Register the VICP protocol/resource manager with the 
     * generic resource manager */

    status = RMAN_register(&IRESMAN_VICP, (IRESMAN_Params *)&configParams);

    if (IRES_OK != status) {
        printf("Protocol Registration Failed \n");
        return -1;
    }

    /* Create an instance of an algorithm that implements IALG and IRES_Fxns */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)dumHandle,
                resFxns,scratchId)) {
        printf("Assign Resource Failed \n");
        return -1;
    }


    /*
     * Activate the Algorithm
     */
    DSKT2_activateAlg(scratchId, (IALG_Handle)dumHandle);

    /*
     * Activate All Resources
     */
    RMAN_activateAllResources((IALG_Handle)dumHandle, resFxns, -1);

    /*
     * Use IALG interfaces to do something 
     */
    DSKT2_controlAlg((IALG_Handle)dumHandle, (IALG_Cmd)NULL, &algStatus);
    
    /*
     * Deactivate All Resources
     */
    RMAN_deactivateAllResources((IALG_Handle)dumHandle, resFxns, -1);

    /*
     * Deactivate algorithm 
     */
    DSKT2_deactivateAlg(scratchId, (IALG_Handle)dumHandle);

    /*
     * Free resources assigned to this algorihtm
     */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(dumHandle),
                resFxns, -1)) {
        printf("Free Resource Failed \n");
        return -1;
    }

    /*
     * Free instance of the algorithm created
     */
    DSKT2_freeAlg(scratchId, (IALG_Handle)dumHandle);

    /*
     * Unregister the protocol
     */
    if (IRES_OK != RMAN_unregister(&IRESMAN_VICP)) {
            printf("Unregister Protocol Failed \n");
            return -1;
    }

    RMAN_exit();

    return 0;
}
/*
 *  @(#) ti.sdo.fc.rman.examples.vicp; 1, 0, 0,80; 9-9-2008 23:55:35; /db/atree/library/trees/fc-e20x/src/
 */

