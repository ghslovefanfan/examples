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
#include <ti/sdo/fc/ires/edma3chan/iresman_edma3Chan.h>
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ires_algorithm.h>
#include <_edma3lld_dm6467.h>
#include <stdio.h>

#include <ti/sdo/fc/ires/hdvicp/iresman_hdvicp.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>

#include <ti/sdo/utils/trace/gt.h>
#define MOD_NAME "*"
GT_Mask ti_sdo_fc_rman_examples_staticReg_GTMask;

extern Bool DSKT2_allocPersistent(IALG_MemRec *memTab, Int numRecs);

extern Void DSKT2_freePersistent(IALG_MemRec *memTab, Int numRecs);

static IRESMAN_Edma3ChanParams configParams = { sizeof(IRESMAN_Edma3ChanParams),        DSKT2_allocPersistent, DSKT2_freePersistent };

static IRESMAN_Fxns * RMAN_registryEntryArray[] = {&IRESMAN_EDMA3CHAN};  

static IRESMAN_Params * RMAN_registryResmanArgsArray[] = 
        {(IRESMAN_Params *)&configParams};

/*
 * extern declaration 
 */
extern Int smain(Int argc, Char * argv[]);

void main()
{
    GT_set(MOD_NAME "=4567");

/* Statically register entries in RMAN */

    RMAN_numRegistryEntries  = 1;
    RMAN_registryEntries = RMAN_registryEntryArray; 
    RMAN_registryResmanArgs = RMAN_registryResmanArgsArray;
}


/* ARGSUSED - this line tells the compiler to not generate compiler warnings 
 * for unused arguments */ 
Int smain(Int argc, Char * argv[])
{
    IRES_Status status;
    Int scratchId = 1;
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

    /* Create an instance of an algorithm that implements IALG and IRES_Fxns */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)dumHandle,
                resFxns,-1)) {
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

        /* TEMP */
    /* Create an instance of an algorithm that implements IALG and IRES_Fxns */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)dumHandle,
                resFxns,-1)) {
        printf("Assign Resource Failed \n");
        return -1;
    }


    /*
     * Free instance of the algorithm created
     */
    DSKT2_freeAlg(scratchId, (IALG_Handle)dumHandle);

    /*
     * Unregister the protocol
     */
    if (IRES_OK != RMAN_unregister(&IRESMAN_EDMA3CHAN)) {
            printf("Unregister Protocol Failed \n");
            return -1;
    }

    RMAN_exit();

    return 0;
}
/*
 *  @(#) ti.sdo.fc.rman.examples.staticReg; 1, 0, 0,22; 9-9-2008 23:55:29; /db/atree/library/trees/fc-e20x/src/
 */

