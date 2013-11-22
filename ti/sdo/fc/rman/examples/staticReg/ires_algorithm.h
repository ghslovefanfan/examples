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
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>

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
extern IRES_Fxns DUMRES_TI_IRES;

/*
 * @brief   IALG interface of the algorithm object
 */
extern IALG_Fxns DUMRES_TI_IALG;

/*
 *  Implementation of the IALG interface for BUFALG
 */
typedef struct DUMRES_TI_Obj {
    IALG_Obj                alg;
    IRES_EDMA3CHAN_Handle   resourceHandles[NUM_RESOURCES]; 
    short                   resourceState[NUM_RESOURCES]; 
    IRES_EDMA3CHAN_ProtocolArgs protocolArgs[NUM_RESOURCES];
    short                   paRamArray[512];
} DUMRES_TI_Obj;

typedef DUMRES_TI_Obj * DUMRES_TI_Handle;
/*
 *  @(#) ti.sdo.fc.rman.examples.staticReg; 1, 0, 0,22; 9-9-2008 23:55:29; /db/atree/library/trees/fc-e20x/src/
 */

