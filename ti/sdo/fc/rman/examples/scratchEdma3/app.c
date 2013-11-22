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
#include <stdio.h>


#include <ti/sdo/fc/edma3/edma3_config.h>
#include <ti/sdo/edma3/rm/edma3_rm.h>

#include <ti/sdo/utils/trace/gt.h>

/* #define MOD_NAME "ti.sdo.fc.rman"*/
#define MOD_NAME "*"
GT_Mask ti_sdo_fc_rman_examples_scratchEdma3_GTMask;

#include <ti/bios/include/mem.h>
/* Arbitrarily chosen to be greater than the number of memory heaps. */
#define MAXMEMSEGMENTS 20
MEM_Stat        memStat[MAXMEMSEGMENTS];

extern EDMA3_RM_InstanceInitConfig DM6467_config;

/*
 * extern declaration 
 */
extern Int smain(Int argc, Char * argv[]);
extern Void _DSKT2_init();

Int main()
{
    Int size = 0;
    IRES_Status status;
    IRESMAN_Edma3ChanParams configParams; 
    Int i = 0;

    GT_set(MOD_NAME "=01234567");
/*
 * Call to _DSKT2_init is required as it leaks memory when DSKT2 is actually . 
 * Call it before you do MEM_stat
 */
    printf("Testing for Memory Leaks\n");
    _DSKT2_init();
    for (i = 0; i < MAXMEMSEGMENTS; i++) {
        if (!MEM_stat(i, &memStat[i])) {
            memStat[i].size =  memStat[i].used = 0;
            memStat[i].length = 0;
        }
    }

    status = RMAN_init(); 
    if (IRES_OK != status) {
        printf("RMAN initialization Failed \n");
        return -1;
    }

    /*
     * Supply initialization information for the EDMA3 RESMAN while registering
     */
    size = sizeof(IRESMAN_Edma3ChanParams);

    configParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
    configParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
    configParams.baseConfig.size = size;

    status = RMAN_register(&IRESMAN_EDMA3CHAN, (IRESMAN_Params *)&configParams);

    if (IRES_OK != status) {
        printf("Protocol Registration Failed \n");
        return -1;
    }

    return 0;
}

/* ARGSUSED - this line tells the compiler to not generate compiler warnings 
 * for unused arguments */ 
Int smain(Int argc, Char * argv[])
{

    Int scratchId1 = 0;
        Int scratchId2 = 0;
    IALG_Status algStatus;
    IALG_Fxns * algFxns = &DUMRES_TI_IALG;
    IRES_Fxns * resFxns = &DUMRES_TI_IRES;
    DUMRES_TI_Handle algHandle1 = NULL; 
    DUMRES_TI_Handle algHandle2 = NULL; 
    EDMA3_RM_Handle rmHandle = NULL;
    EDMA3_RM_ResDesc resObj;

    MEM_Stat stat;
    Bool retVal;
    Int i = 0;
    /*
     * Create 2 instances of the algorithm using "algFxns" 
     */
    algHandle1 = (DUMRES_TI_Handle)DSKT2_createAlg(scratchId1, 
            (IALG_Fxns *)algFxns, NULL,(IALG_Params *)NULL);
    if (algHandle1 == NULL) {
        printf("Alg creation failed for algHandle1\n");
        return -1;
    } 

    algHandle2 = (DUMRES_TI_Handle)DSKT2_createAlg(scratchId2, 
            (IALG_Fxns *)algFxns, NULL,(IALG_Params *)NULL);
    if (algHandle2 == NULL) {
        printf("Alg creation failed for algHandle2\n");
        return -1;
    } 

    /* Assign resources to the algorithm */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)algHandle1,
                resFxns, scratchId1)) {
        GT_0trace(ti_sdo_fc_rman_examples_scratchEdma3_GTMask, GT_7CLASS,
                "Assign Resource Failed \n");
        goto AppEnd1;
    }

    /*
     * Activate the Algorithm
     */
    DSKT2_activateAlg(scratchId1, (IALG_Handle)algHandle1);

    /*
     * Activate All Resources
     */
    RMAN_activateAllResources((IALG_Handle)algHandle1, resFxns, scratchId1);

    /*
     * Use IALG interfaces to do something 
     */
    DSKT2_controlAlg((IALG_Handle)algHandle1, (IALG_Cmd)NULL, &algStatus);
    
    /* Assign resources to the second algorithm */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)algHandle2,
                resFxns, scratchId2)) {
        printf("Assign Resource Failed \n");
        return -1;
    }

    /*
     * Deactivate All Resources
     */
    RMAN_deactivateAllResources((IALG_Handle)algHandle1, resFxns, scratchId1);

    /*
     * Deactivate algorithm 
     */
    DSKT2_deactivateAlg(scratchId1, (IALG_Handle)algHandle1);

    /*
     * Activate the Algorithm
     */
    DSKT2_activateAlg(scratchId2, (IALG_Handle)algHandle2);

    /*
     * Activate All Resources
     */
    RMAN_activateAllResources((IALG_Handle)algHandle2, resFxns, scratchId2);

    /*
     * Free resources assigned to this algorihtm
     */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(algHandle1),
                resFxns, scratchId1)) {
        printf("Free Resource Failed \n");
        return -1;
    }
    
    /* 
     * Acquire the EDMA3 handle first
     */           
    rmHandle = EDMA3_getResourceManager(NULL, -1);
    
    if (NULL == rmHandle) {
        printf("Error obtaining SYSTEM resource Manager Handle \n");
        return (-1);
    }

    resObj.resId = 151; 
    resObj.type = EDMA3_RM_RES_PARAM_SET;
    

    if (EDMA3_RM_SOK != EDMA3_RM_allocResource(rmHandle, &resObj)) {
        printf("Could not allocate this resource, as it is already owned by "
                "the algorithm\n");
    }

    resObj.resId = 256; 
    if (EDMA3_RM_SOK != EDMA3_RM_allocResource(rmHandle, &resObj)) {
        printf("Error, could not allocate resource %d\n"
                "ERROR for 6467, OK for 6446\n", resObj.resId);
    }
    
    if (EDMA3_RM_SOK != EDMA3_releaseResourceManager(NULL, -1)) {
        printf("Error releasing system resource manager handle\n");
    } 

    /*
     * Deactivate All Resources
     */
    RMAN_deactivateAllResources((IALG_Handle)algHandle2, resFxns, scratchId2);

    /*
     * Deactivate algorithm 
     */
    DSKT2_deactivateAlg(scratchId2, (IALG_Handle)algHandle2);

    /*
     * Free resources assigned to this algorihtm
     */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(algHandle2),
                resFxns, scratchId2)) {
        printf("Free Resource Failed \n");
        return -1;
    }

AppEnd1:
    /*
     * Free instance of the algorithm created
     */
    DSKT2_freeAlg(scratchId1, (IALG_Handle)algHandle1);

    /*
     * Free instance of the algorithm created
     */
    DSKT2_freeAlg(scratchId2, (IALG_Handle)algHandle2);

    /*
     * Unregister the protocol
     */
    if (IRES_OK != RMAN_unregister(&IRESMAN_EDMA3CHAN)) {
            printf("Unregister Protocol Failed \n");
            return -1;
    }
    for (i = 0; i < MAXMEMSEGMENTS; i++) {
        retVal = MEM_stat(i, &stat);
        if (!retVal) {
            GT_assert(ti_sdo_fc_rman_examples_scratchEdma3_GTMask, 
                    memStat[i].size == 0);
        }
        else {
            if (memStat[i].used != stat.used) {
                GT_3trace(ti_sdo_fc_rman_examples_scratchEdma3_GTMask,
                        GT_7CLASS, "MEM seg [%d]: orig used = 0x%x, "
                        "curr used = 0x%x", i, memStat[i].used, 
                        stat.used);
                return (-1);
            }
        }
    }

        RMAN_exit();

    return (0);
}


/*
#define DMA_CHANNEL_TO_EVENT_MAPPING_0          (0x30FF1FF0u)
#define DMA_CHANNEL_TO_EVENT_MAPPING_1          (0x003F07FFu)
*/
#define DMA_CHANNEL_TO_EVENT_MAPPING_0          (0x0)
#define DMA_CHANNEL_TO_EVENT_MAPPING_1          (0x0)

EDMA3_RM_InstanceInitConfig DM6467_config = 
          {
            /* Resources owned by Region 1 */
            /* ownPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u,
            0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
            0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
            0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu},

            /* ownDmaChannels */
            {0xCF00E00Fu, 0xFF00F800u},

            /* ownQdmaChannels */
            {0x0000007Fu},

            /* ownTccs */
/*             {0xCF00E00Fu, 0xFF00F800u},*/
            {0xC0FF10F0u, 0xFF00F800u},

            /* Resources reserved by Region 1 */
            /* resvdPaRAMSets */
            {0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u,
            0x0u, 0x0u, 0x0u, 0x0u},

            /* resvdDmaChannels */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},

            /* resvdQdmaChannels */
            {0x0u},

            /* resvdTccs */
            {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},
          };
/*
 *  @(#) ti.sdo.fc.rman.examples.scratchEdma3; 1, 0, 0,38; 9-9-2008 23:55:22; /db/atree/library/trees/fc-e20x/src/
 */

