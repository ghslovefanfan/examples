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
 *  ======== bufres_test.c ========
 *  Test algorithms using the Buffer Resources.
 */

#include <xdc/std.h>
#include <ti/bios/include/std.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ti/sdo/fc/utils/dbc.h>
#include <ti/sdo/fc/dskt2/dskt2.h>
#include <ti/bios/include/tsk.h>
#include <ti/bios/include/sys.h>
#include <ti/sdo/fc/ires/iresman.h>

#include <ti/sdo/fc/rman/rman.h> 

#include <bufalg_ti.h>
#include <ti/sdo/fc/rman/examples/bufres_yield/bufres.h>
#include <bufres_util.h>

#include <ti/sdo/utils/trace/gt.h>
GT_Mask ti_sdo_fc_rman_examples_bufres_yield_GTMask;
#define MOD_NAME "ti.sdo.fc.rman"
//#define MOD_NAME "*"

#define NUMTASKS 2
#define MAXTASKS 5

/*
 *  ======== ScratchTskAttrs ========
 */
typedef struct ScratchTskAttrs {
    Int         priority;       /* Priority of task */
    Uns         size;           /* Scratch buffer size */
    Uns         fillValue;      /* Value to fill scratch buffer with */
} ScratchTskAttrs;
 

extern far UInt32 BUFMEM_base;
extern far UInt32 BUFMEM_end;
extern Int EXTMEM_HEAP;

extern Int smain(Int argc, Char * argv[]);
extern Int rmanTask(Arg size, Arg fillValue, Arg taskId);
extern Void myIdle();
extern IRESMAN_PersistentAllocFxn DSKT2_allocPersistent;
extern IRESMAN_PersistentFreeFxn  DSKT2_freePersistent;


/* Scratch task parameters */
static ScratchTskAttrs attrsTable[MAXTASKS] = {
    /* priority    scratchSize    fillValue */
    3,             0x80,          0x201,
    3,             0x100,         0x202,
    3,             0x60,          0x203,
    3,             0x100,         0x204,
    4,             0x80,          0x301,
};
static SEM_Handle done = NULL;  /* Gets posted by last task to finish */
static SEM_Handle mutex = NULL; /* Protect DSKT2_createAlg and DSKT2_freeAlg */


/*
 *  ======== main ========
 */
Int main(Int argc, Char * argv[])
{
    IRES_Status        status;  
    BUFRES_Params      resmanConfig;

    GT_set(MOD_NAME "=01234567");
    GT_set("ti.sdo.fc.rman.examples.bufres_yield" "=01234567");
    
    GT_create(&ti_sdo_fc_rman_examples_bufres_yield_GTMask, 
    "ti.sdo.fc.rman.examples.bufres_yield");

    GT_init();

    status = RMAN_init();
    if (IRES_OK != status) {

        GT_0trace(ti_sdo_fc_rman_examples_bufres_yield_GTMask, GT_7CLASS,
        "_main> RMAN initialization Failed \n");

        return -1;
    }
    /*
     *  Initialize the BUFRES resource manager.
     */
    resmanConfig.iresConfig.size = sizeof(BUFRES_Params);
    resmanConfig.iresConfig.allocFxn = DSKT2_allocPersistent;
    resmanConfig.iresConfig.freeFxn = DSKT2_freePersistent;
 
    resmanConfig.base = (Void *)&BUFMEM_base;
    resmanConfig.length = (UInt32)&BUFMEM_end - (UInt32)&BUFMEM_base + 1;
    resmanConfig.fillValue = (UInt32 )0xCAFEC0FE;
    
    status = RMAN_register(&BUFRES_MGRFXNS,(IRESMAN_Params *)&resmanConfig);

    if (IRES_OK != status) {

        GT_0trace(ti_sdo_fc_rman_examples_bufres_yield_GTMask, GT_7CLASS,
        "_main> Protocol Registration Failed \n");

        return -1;
    }
    return 0;
}


/*
 * Idle task can do the cleanup ? 
 */
Void myIdle()
{
    IRES_Status status ;

    /*
     * Unregister the protocol
     */
    if (IRES_OK != RMAN_unregister(&BUFRES_MGRFXNS)) {

        GT_0trace(ti_sdo_fc_rman_examples_bufres_yield_GTMask, GT_7CLASS,
        "_myIdle> Unregister Protocol Failed \n");

        exit(-1);
    }


    status = RMAN_exit();
    if (IRES_OK != status) {

        GT_0trace(ti_sdo_fc_rman_examples_bufres_yield_GTMask, GT_7CLASS,
        "_myIdle> RMAN Exit Failed \n");

        exit(-1);
    }

    exit(0);
}


/*
 *  ======== smain ========
 */
/* ARGSUSED */
Int smain(Int argc, Char * argv[])
{
    TSK_Handle tsk;
    TSK_Attrs attrs = TSK_ATTRS;
    Int i;

    done = SEM_create(0, NULL);
    mutex = SEM_create(1, NULL);

    if ((done == NULL) || (mutex == NULL)) {

        GT_0trace(ti_sdo_fc_rman_examples_bufres_yield_GTMask, GT_7CLASS,
        "_smain> Semaphore creation failed\n");

        SYS_abort("Sem create failed \n");
    }

/*
 * Do I care about this ? 
 */
    attrs.stackseg = EXTMEM_HEAP;

    for (i = 0; i < NUMTASKS; i++) {

        attrs.priority = attrsTable[i].priority;
        tsk = TSK_create((Fxn)rmanTask, &attrs, 
                (Arg)(attrsTable[i].size), (Arg)(attrsTable[i].fillValue), 
                (Arg)(i +1));
        if (tsk == NULL) {

            GT_1trace(ti_sdo_fc_rman_examples_bufres_yield_GTMask, GT_7CLASS,
            "_smain> TSK_create of task %d failed\n", i+1);

            SYS_abort("TSK_create() of task %d failed\n",i+1); 
        }
    }

    for (i=0; i < NUMTASKS; i++) {
        SEM_pend(done, SYS_FOREVER);
    }
 
    SEM_delete(mutex);
    SEM_delete(done);

    GT_0trace(ti_sdo_fc_rman_examples_bufres_yield_GTMask, GT_4CLASS,
    "_smain> TEST COMPLETED\n");

    return 0;
}

Int rmanTask(Arg size, Arg fillValue, Arg taskId) 
{

    IBUFALG_Handle     alg;
    IBUFALG_Fxns       fxns = BUFALG_TI_IBUFALG;  /* IALG implementation ? */ 
    IRES_Fxns          iresFxns = BUFALG_TI_IRES; /* IRES implementation */
    Int                scratchId = 1;


    /*
     * Create an instance of the algorithm using "algFxns"
     */

    GT_2trace(ti_sdo_fc_rman_examples_bufres_yield_GTMask, GT_4CLASS,
    "_smain> Task Id %d fillValue 0x%x \n",taskId, fillValue );


    SEM_pend(mutex, SYS_FOREVER);
    alg = (IBUFALG_Handle)DSKT2_createAlg(scratchId,
            (IALG_Fxns *)&fxns, NULL,(IALG_Params *)NULL);
    if (alg == NULL) {

        GT_0trace(ti_sdo_fc_rman_examples_bufres_yield_GTMask, GT_7CLASS,
        "_smain> Alg creation failed\n");

        return -1;
    }  
    SEM_post(mutex);
    /* Assign resources to the algorithm */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)alg, &iresFxns,
            scratchId)) {

        GT_3trace(ti_sdo_fc_rman_examples_bufres_yield_GTMask, GT_7CLASS,
        "_smain> Assign resources failed for alg 0x%x, scratchId %d "
        "IRES interface 0x%x\n", alg, scratchId, iresFxns );

        return -1;
    } 

    DSKT2_activateAlg(scratchId, (IALG_Handle)alg);

    /*
     * Activate All Resources
     */
    RMAN_activateAllResources((IALG_Handle)alg, &iresFxns, scratchId);
  
    alg->fxns->useBufs(alg, fillValue, taskId);

    /*
     * Deactivate All Resources
     */
    RMAN_deactivateAllResources((IALG_Handle)alg, &iresFxns, scratchId);
 
    /*
     * Deactivate algorithm
     */
    DSKT2_deactivateAlg(scratchId, (IALG_Handle)alg);
 
    /*
     * Free resources assigned to this algorihtm
     */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(alg), &iresFxns, 
            scratchId)){

        GT_3trace(ti_sdo_fc_rman_examples_bufres_yield_GTMask, GT_7CLASS,
        "_smain> Free resources failed for alg 0x%x, scratchId %d "
        "IRES interface 0x%x\n", alg, scratchId, iresFxns );

        return -1;
    }
 
    /*
     * Free instance of the algorithm created
     */
    SEM_pend(mutex, SYS_FOREVER);
    DSKT2_freeAlg(scratchId, (IALG_Handle)alg);    
    SEM_post(mutex);

    SEM_post(done);

    GT_1trace(ti_sdo_fc_rman_examples_bufres_yield_GTMask, GT_4CLASS,
    "_smain> Completed task %d\n", taskId); 

    return 0;
}

/*
 *  @(#) ti.sdo.fc.rman.examples.bufres_yield; 1, 0, 0,83; 9-9-2008 23:54:37; /db/atree/library/trees/fc-e20x/src/
 */

