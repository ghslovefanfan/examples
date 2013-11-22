/* 
 *  Copyright 2008
 *  Texas Instruments Incorporated
 *
 *  All rights reserved.  Property of Texas Instruments Incorporated
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 * 
 */
/**
 *  @file       ires_algorithm.h 
 *
 *  @brief      Definitions for dummy implementation of the IRES interfaces 
 *              by an algorithm  
 *
 */

#include <ti/xdais/ires.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>

#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_rman_examples_hdvicp;

/*
 * @brief  Number of resources the algorithm will request 
 */
#define NUM_RESOURCES   2

/*
 * @brief  Number of memory resources required by IALG implementation 
 */
#define NUM_ALLOC       1

/*
 * @brief   IRES interface of the algorithm object
 */
extern IRES_Fxns DUMALG_TI_IRES;

/*
 * @brief   IALG interface of the algorithm object
 */
extern IALG_Fxns DUMALG_TI_IALG;

/*
 * Context args structure for the HDVICP resource object 
 */
typedef struct BUFALG_TI_CtxtArgs {
    Int size; 
} BUFALG_TI_CtxtArgs;

/*
 *  Extension of the IALG object for the HDVICP object 
 */
typedef struct DUMALG_TI_Obj {
    IALG_Obj                    alg;
    IRES_HDVICP_Handle          resourceHandles[NUM_RESOURCES]; 
    short                       resourceState[NUM_RESOURCES]; 
    IRES_HDVICP_ProtocolArgs    protocolArgs[NUM_RESOURCES];
    short                       paRamArray[512];
    IRES_YieldFxn               yieldFxn;
    IRES_YieldArgs              yieldArgs;
    IRES_YieldContext           yieldContext;
    BUFALG_TI_CtxtArgs          contextArgs;
    IRES_HDVICP_RequestType     hdvicp[NUM_RESOURCES];
    Int                         yieldFlag;
    Int                         taskId;
} DUMALG_TI_Obj;

/*
 * Handle to the IALG HDVICP object 
 */
typedef DUMALG_TI_Obj * DUMALG_TI_Handle;

/*
 * Creation paramters for the DUMALG object
 */
typedef struct IDUMALG_Params {
    Int                         size;
    IRES_HDVICP_RequestType     hdvicp[NUM_RESOURCES];
    Int                         yieldFlag;
    Int                         taskId;
} IDUMALG_Params;

/*
 * Paramter values for DUMALG instance objects 
 */
extern IDUMALG_Params IDUMALG_PARAMS;

/*
 * This structure must be first field of all DUMALG instance objects  
 */
typedef struct IDUMALG_Obj {
    struct IDUMALG_Fxns         *fxns;
} IDUMALG_Obj;

typedef IDUMALG_Obj * IDUMALG_Handle;

/*
 * Defines the full set of operations that can be performed on the DUMALG object
 */
typedef struct IDUMALG_Fxns {
    IALG_Fxns                   alg;
    Int                         (* useHDVICP)(IDUMALG_Handle handle,
                                        unsigned int Id);
} IDUMALG_Fxns;

/*
 * Defines TI's implementation of the IDUMALG interface 
 */
extern IDUMALG_Fxns DUMALG_TI_IDUMALG;

Int DUMALG_TI_useHDVICP( IDUMALG_Handle handle, unsigned int Id);
/*
 *  @(#) ti.sdo.fc.rman.examples.nonRtscExample; 1, 0, 0,22; 9-9-2008 23:55:03; /db/atree/library/trees/fc-e20x/src/
 */

