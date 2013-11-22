/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 * ======== app.c ========
 */

#include <xdc/std.h>

#include <ti/bios/include/std.h>
#include <ti/bios/include/tsk.h>
#include <ti/bios/include/sys.h>

#include <ti/sdo/fc/dskt2/dskt2.h>
#include <ti/sdo/fc/ires/iresman.h>
#include <ti/sdo/fc/rman/rman.h> 
#include <ti/sdo/fc/ires/hdvicp/iresman_hdvicp.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>

#include <stdio.h>
#include <stdlib.h>

#include "ires_algorithm.h"

#include <ti/sdo/utils/trace/gt.h>
GT_Mask ti_sdo_fc_rman_examples_hdvicp;

#define NUMTASKS 12 
#define MAXTASKS 12 
#define MODNAME "ti.sdo.fc.rman.examples.hdvicp"
#define RMAN_PARAMS_TABLE_SIZE 2        /* Size of RMAN table */

/*
 * Declaration of DSKT2 functions for use in configuring RMAN
 */ 
extern Bool DSKT2_allocPersistent(IALG_MemRec *memTab, Int numRecs);
extern Void DSKT2_freePersistent(IALG_MemRec *memTab, Int numRecs);

/*
 * Declaration of RMAN's yield function to configure RMAN   
 */ 
extern void RMAN_yield(IRES_YieldResourceType resource,
        IRES_YieldContextHandle algYieldContext, IRES_YieldArgs yieldArgs);

/*
 *  ======== ScratchTskAttrs ========
 */
typedef struct ScratchTskAttrs {
    Int         priority;       /* Priority of task */
    Int         scratchId;      /* Scratch group in which to create the task */
    IRES_HDVICP_RequestType id[NUM_RESOURCES]; 
    Int         yieldFlag;
} ScratchTskAttrs;

/*
 * heapId in which to create the tasks 
 */
extern Int EXTMEM_HEAP;

/*
 * Tasks 
 */
extern Int smain(Int argc, Char * argv[]);
extern Int rmanTask(Arg scratchId, Arg resourceId,  Arg priority, Arg taskId, 
        Arg yieldFlag);
extern Void myIdle();

/* Scratch task parameters */
static ScratchTskAttrs attrsTable[MAXTASKS] = {
    /* priority,    scratchGroup    resources                       yieldFlag */
    12,              1,      {IRES_HDVICP_ID_0,         IRES_HDVICP_ID_1},   1,
    13,              1,      {IRES_HDVICP_ID_ANY,       IRES_HDVICP_ID_ANY}, 0,
        13,              1,      {IRES_HDVICP_ID_ANY,   IRES_HDVICP_ID_ANY}, 0,
        13,              1,      {IRES_HDVICP_ID_ANY,   IRES_HDVICP_ID_ANY}, 0,
        13,              1,      {IRES_HDVICP_ID_ANY,   IRES_HDVICP_ID_ANY}, 0,
        13,              1,      {IRES_HDVICP_ID_ANY,   IRES_HDVICP_ID_ANY}, 0,
        13,              1,      {IRES_HDVICP_ID_ANY,   IRES_HDVICP_ID_ANY}, 0,
    12,              1,      {IRES_HDVICP_ID_ANY,       IRES_HDVICP_ID_ANY}, 1,
        13,              1,      {IRES_HDVICP_ID_ANY,   IRES_HDVICP_ID_ANY}, 0,
    12,              1,      {IRES_HDVICP_ID_ANY,       IRES_HDVICP_ID_ANY}, 1,
        13,              1,      {IRES_HDVICP_ID_ANY,   IRES_HDVICP_ID_ANY}, 0,
    12,              1,      {IRES_HDVICP_ID_0,         IRES_HDVICP_ID_1},   1,
/*
    13,              1,      {IRES_HDVICP_ID_1,         IRES_HDVICP_ID_ANY}, 1,
    13,              3,      {IRES_HDVICP_ID_0,         IRES_HDVICP_ID_ANY}, 0,
    14,              3,      {IRES_HDVICP_ID_1,         IRES_HDVICP_ID_ANY}, 1,
        13,                              3,      {IRES_HDVICP_ID_1,             IRES_HDVICP_ID_ANY}, 1
 */
};

static SEM_Handle done = NULL;  /* Gets posted by last task to finish */
static SEM_Handle mutex = NULL; /* Protect DSKT2_createAlg and DSKT2_freeAlg */
/*
 * extern declaration 
 */
extern Int smain(Int argc, Char * argv[]);

IRESMAN_HdVicpParams configParams = {
    0,      /* Size of this structure */
            /*
             * RMAN_PERSISTENTALLOCFXN,
             * RMAN_PERSISTENTFREEFXN,
             */
    NULL,
    NULL,
    2,      /* Number of resources to manage */
    NULL,   /* Rsvd for future use */ 
};

Int main()
{
    IRES_Status status;
    Int size = 0;

    GT_init();
    GT_create(&ti_sdo_fc_rman_examples_hdvicp,"ti.sdo.fc.rman.examples.hdvicp");
        GT_set(MODNAME "=01234567");
        GT_set("ti.sdo.fc.rman" "=4567");
        GT_set("ti.sdo.fc.dskt2" "=67");
/*      GT_set("ti.sdo.fc.dskt2" "=01234567");*/

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_main> Enter \n");

    /* Modify RMAN_PARAMS structure as required */
    RMAN_PARAMS.numRegistries = RMAN_PARAMS_TABLE_SIZE;
    RMAN_PARAMS.allocFxn = DSKT2_allocPersistent;
    RMAN_PARAMS.freeFxn = DSKT2_freePersistent;
    RMAN_PARAMS.yieldFxn = RMAN_yield;
    RMAN_PARAMS.yieldSamePriority = TRUE;

    status = RMAN_init(); 

    if (IRES_OK != status) {

        GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_main> RMAN "
                "Initialization failed \n");
        return -1;
    }

    /*
     * Supply initialization information for the RESMAN while registering
     */
    size = sizeof(IRESMAN_HdVicpParams);

    configParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
    configParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
    configParams.baseConfig.size = size;

    /* Register the HDVICP protocol/resource manager with the 
     * generic resource manager */

    status = RMAN_register(&IRESMAN_HDVICP, (IRESMAN_Params *)&configParams);

    if (IRES_OK != status) {
        GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_main> Protocol "
                "Initialization failed \n");
        return -1;
    }


    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_main> Exit \n");

    return 0;
}

/*
 *  ======== myIdle ========
 *  Idle task cleans up afterwards
 */
Void myIdle()
{
    IRES_Status status ;

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_myIdle> Enter \n");
    /*
     * Unregister the protocol
     */
    if (IRES_OK != RMAN_unregister(&IRESMAN_HDVICP)) {

        GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_myIdle> "
            "Unregister protocol failed \n");

        exit(-1);
    }


    status = RMAN_exit();
    if (IRES_OK != status) {

        GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_myIdle> " 
            "RMAN exit failed \n");

        exit(-1);
    }

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_myIdle> Exit \n");

    exit(0);
}

/*
 *  ======== smain ========
 */
/* ARGSUSED */
/* ARGSUSED - this line tells the compiler to not generate compiler warnings 
 * for unused arguments */ 
Int smain(Int argc, Char * argv[])
{
    TSK_Handle tsk;
    TSK_Attrs attrs = TSK_ATTRS;
    Int i;

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_smain> Enter \n");

    done = SEM_create(0, NULL);
    mutex = SEM_create(1, NULL);

    if ((done == NULL) || (mutex == NULL)) {

        SYS_abort("Sem create failed \n");
    }

/*
 * Do I care about this ? 
 */
    attrs.stackseg = EXTMEM_HEAP;

/*
 * Use a bigger stack size when printing out trace 
 */
    attrs.stacksize = 0x1000;

    for (i = 0; i < NUMTASKS; i++) {

        attrs.priority = attrsTable[i].priority;
        tsk = TSK_create((Fxn)rmanTask, &attrs, 
                                (Arg)(attrsTable[i].scratchId),
                                (Arg)(&(attrsTable[i].id)),
                                (Arg)(attrsTable[i].priority),
                (Arg)(i +1),
                (Arg)(attrsTable[i].yieldFlag));
        if (tsk == NULL) {

            GT_1trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_rman> " 
                "Task #%d create failed \n",i);

            SYS_abort("TSK_create() of task %d failed\n",i+1); 
        }
    }

    for (i=0; i < NUMTASKS; i++) {
        SEM_pend(done, SYS_FOREVER);
    }

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_4CLASS, "_smain> "
    "TEST PASSED \n");

    SEM_delete(mutex);
    SEM_delete(done);

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_smain> Exit \n");

    return 0;
}


/*
 *  ======== rmanTask ========
 *  
 */
Int rmanTask(Arg scratchId, Arg resourceId,  Arg priority, Arg taskId, 
        Arg yieldFlag)
{

    Int i;
    IALG_Fxns * algFxns = &DUMALG_TI_IALG;
    IRES_Fxns * resFxns = &DUMALG_TI_IRES;
    IDUMALG_Handle dumHandle = NULL; 
    IDUMALG_Params params;

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_rmanTask> Enter \n");

    params.size = sizeof(IDUMALG_Params);

    GT_4trace(ti_sdo_fc_rman_examples_hdvicp, GT_4CLASS, "_rmanTask> "
            "Task #%d: ScratchId %d, Priority %d Yield %d\n",taskId, scratchId,
            priority, yieldFlag);

    params.yieldFlag  = yieldFlag;
    params.taskId = taskId; 

    for (i = 0; i < NUM_RESOURCES; i++) {
        params.hdvicp[i] = *((IRES_HDVICP_RequestType *)resourceId + i);
        GT_1trace(ti_sdo_fc_rman_examples_hdvicp, GT_4CLASS, "_rmanTask> "
        "Requesting resource %d (2 => ANY)\n",(Int)params.hdvicp[i]);
    }
    /*
     * Create an instance of the algorithm using "algFxns" 
     */
    SEM_pend(mutex, SYS_FOREVER);
    dumHandle = (IDUMALG_Handle)DSKT2_createAlg((Int)scratchId, 
            (IALG_Fxns *)algFxns, NULL,(IALG_Params *)&params);
    if (dumHandle == NULL) {
        GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_rmanTask> "
                "Alg creation failed\n");
        return -1;
    } 
    SEM_post(mutex);
    /* Assign resources to the algorithm */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)dumHandle,
                resFxns, scratchId)) {
        GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_rmanTask> "
                "Assign resource failed\n");
        return -1;
    }


    /*
     * Activate the Algorithm
     */
    DSKT2_activateAlg(scratchId, (IALG_Handle)dumHandle);

    /*
     * Activate All Resources
     */
    RMAN_activateAllResources((IALG_Handle)dumHandle, resFxns, scratchId);

    /*
     * Use IALG interfaces to do something 
     */
        dumHandle->fxns->useHDVICP(dumHandle, taskId);
    
    /*
     * Deactivate All Resources
     */
    RMAN_deactivateAllResources((IALG_Handle)dumHandle, resFxns, scratchId);

    /*
     * Deactivate algorithm 
     */
    DSKT2_deactivateAlg(scratchId, (IALG_Handle)dumHandle);

    /*
     * Free resources assigned to this algorihtm
     */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(dumHandle),
                resFxns, scratchId)) {
        GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_rmanTask> "
                "Free resource failed\n");
        return -1;
    }

    /*
     * Free instance of the algorithm created
     */
    SEM_pend(mutex, SYS_FOREVER);
    DSKT2_freeAlg(scratchId, (IALG_Handle)dumHandle);
    SEM_post(mutex);

    SEM_post(done);

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_rmanTask> Exit \n");

    return 0;
}
/*
 *  @(#) ti.sdo.fc.rman.examples.nonRtscExample; 1, 0, 0,22; 9-9-2008 23:55:03; /db/atree/library/trees/fc-e20x/src/
 */

