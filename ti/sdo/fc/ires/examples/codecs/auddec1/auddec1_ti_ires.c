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
 *  ======== auddec1_ti_ires.c ========
 *  Audio decoder "copy" algorithm's implementation of IRES_Fxns.
 */

#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/iauddec1.h>

#include <ti/xdais/ialg.h>
#include <ti/xdais/ires.h>

/* Header file for the buffer resource (BUFRES) used in this example. */
#include <ti/sdo/fc/ires/bufres/bufres.h>

#include "auddec1_ti.h"
#include "auddec1_ti_priv.h"

/* IRES Function Declarations */
static IRES_Status AUDDEC1_TI_activateRes(IALG_Handle handle, IRES_Handle res);
static IRES_Status AUDDEC1_TI_activateAllRes(IALG_Handle handle);
static IRES_Status AUDDEC1_TI_deactivateRes(IALG_Handle h, IRES_Handle res);
static IRES_Status AUDDEC1_TI_deactivateAllRes(IALG_Handle handle);
static Int32 AUDDEC1_TI_numResources(IALG_Handle handle);
static IRES_Status AUDDEC1_TI_getResources(IALG_Handle handle,
        IRES_ResourceDescriptor *desc);
static IRES_Status AUDDEC1_TI_initResources(IALG_Handle h,
        IRES_ResourceDescriptor * desc, IRES_YieldFxn  yieldFxn,
        IRES_YieldArgs yieldArgs);
static IRES_Status AUDDEC1_TI_deInitResources(IALG_Handle h,
        IRES_ResourceDescriptor *desc);
static IRES_Status AUDDEC1_TI_reInitResources(IALG_Handle handle,
        IRES_ResourceDescriptor *desc, IRES_YieldFxn  yieldFxn,
        IRES_YieldArgs yieldArgs);

/*
 *  ======== AUDDEC1_TI_IRES ========
 */
IRES_Fxns AUDDEC1_TI_IRES = {
    &AUDDEC1_TI_IRES,
    AUDDEC1_TI_getResources,
    AUDDEC1_TI_numResources,
    AUDDEC1_TI_initResources,
    AUDDEC1_TI_reInitResources,
    AUDDEC1_TI_deInitResources,
    AUDDEC1_TI_activateRes,
    AUDDEC1_TI_activateAllRes,
    AUDDEC1_TI_deactivateRes,
    AUDDEC1_TI_deactivateAllRes
};


/*
 *  ======== AUDDEC1_TI_activateAllRes ========
 */
static IRES_Status AUDDEC1_TI_activateAllRes(IALG_Handle handle)
{
    AUDDEC1_TI_Obj  *alg = (AUDDEC1_TI_Obj *)handle;
    IRES_Status      status;

    /* Activate all resources - this example has only one. */
    status = AUDDEC1_TI_activateRes(handle, (IRES_Handle)alg->bufres);
    if (status != IRES_OK) {
        return (status);
    }

    return (IRES_OK);
}

/*
 *  ======== AUDDEC1_TI_activateRes ========
 */
static IRES_Status AUDDEC1_TI_activateRes(IALG_Handle handle, IRES_Handle res)
{
    AUDDEC1_TI_Obj  *alg = (AUDDEC1_TI_Obj *)handle;
    BUFRES_Handle    bufres = (BUFRES_Handle)res;
    Int              i;

    /* Check that res = alg->bufres */
    if (res != (IRES_Handle)(alg->bufres)) {
        return (IRES_EFAIL);
    }

    if (alg->resActive == FALSE) {
        /*
         *  Add code here to do any necessary initialization of the buffer
         *  resource before starting to use it.
         */
        for (i = 0; i < bufres->length / sizeof(Int); i++) {
            ((Int *)(bufres->base))[i] = 0xac;
        }

        /* Set the resource to active state */
        alg->resActive = TRUE;
        return (IRES_OK);
    }
    else {
        /* The resource was already active */
        return (IRES_EFAIL);
    }
}

/*
 *  ======== AUDDEC1_TI_deactivateAllRes ========
 */
static IRES_Status AUDDEC1_TI_deactivateAllRes(IALG_Handle handle) 
{
    AUDDEC1_TI_Obj  *alg = (AUDDEC1_TI_Obj *)handle;
    IRES_Status      status = IRES_OK;

    status = AUDDEC1_TI_deactivateRes(handle, (IRES_Handle)alg->bufres);

    return (status);
}

/*
 *  ======== AUDDEC1_TI_deactivateRes ========
 */
static IRES_Status AUDDEC1_TI_deactivateRes(IALG_Handle h, IRES_Handle res)
{
    AUDDEC1_TI_Obj  *alg = (AUDDEC1_TI_Obj *)h;
    BUFRES_Handle    bufres = (BUFRES_Handle)res;
    Int              i;

    /* Check that res = alg->bufres */
    if (res != (IRES_Handle)(alg->bufres)) {
        return (IRES_EFAIL);
    }

    if (alg->resActive == TRUE) {
        /*
         *  Add code here to do what needs to be done when finished using
         *  this resource
         */
        for (i = 0; i < bufres->length / sizeof(Int); i++) {
            ((Int *)(bufres->base))[i] = 0xdeac;
        }

        alg->resActive = FALSE;
        return (IRES_OK);
    }
    else {
        /* The resource was not found or was already active */
        return (IRES_EFAIL);
    }
}

/*
 *  ======== AUDDEC1_TI_deInitResources ========
 */
static IRES_Status AUDDEC1_TI_deInitResources(IALG_Handle h,
        IRES_ResourceDescriptor *desc)
{
    AUDDEC1_TI_Obj  *alg = (AUDDEC1_TI_Obj *)h;

    alg->resActive = FALSE;

    return (IRES_OK);
}

/*
 *  ======== AUDDEC1_TI_getResources ========
 */
static IRES_Status AUDDEC1_TI_getResources(IALG_Handle h,
        IRES_ResourceDescriptor *desc)
{
    AUDDEC1_TI_Obj  *alg = (AUDDEC1_TI_Obj *)h;

    desc->resourceName = BUFRES_PROTOCOLNAME;
    desc->revision = &BUFRES_PROTOCOLVERSION;
    desc->protocolArgs = (IRES_ProtocolArgs *)&(alg->args);
    desc->protocolArgs->mode = IRES_SCRATCH;

    if (alg != NULL) {
        desc->handle = (IRES_Handle)(alg->bufres);
    }
    else {
        desc->handle = NULL;
    }

    return (IRES_OK);
}

/*
 *  ======== AUDDEC1_TI_initResources ========
 */
static IRES_Status AUDDEC1_TI_initResources(IALG_Handle h,
        IRES_ResourceDescriptor *desc, IRES_YieldFxn  yieldFxn,
        IRES_YieldArgs yieldArgs)
{
    AUDDEC1_TI_Obj  *alg = (AUDDEC1_TI_Obj *)h;

    alg->bufres = (BUFRES_Handle)desc->handle;

    alg->yieldFxn = yieldFxn;
    alg->yieldArgs = yieldArgs;

    return (IRES_OK);
}

/*
 *  ======== AUDDEC1_TI_numResources ========
 */
static Int32 AUDDEC1_TI_numResources(IALG_Handle handle) 
{
    return (1);
}

/*
 *  ======== AUDDEC1_TI_reInitResources ========
 */
static IRES_Status AUDDEC1_TI_reInitResources(IALG_Handle handle,
        IRES_ResourceDescriptor *desc, IRES_YieldFxn  yieldFxn,
        IRES_YieldArgs yieldArgs)
{
    AUDDEC1_TI_Obj  *alg = (AUDDEC1_TI_Obj *)handle;

    alg->yieldFxn = yieldFxn;
    alg->yieldArgs = yieldArgs;
    alg->bufres = (BUFRES_Handle)desc->handle;
    alg->resActive = FALSE;

    return (IRES_OK);
}

/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.auddec1; 1, 0, 0,81; 9-9-2008 23:52:59; /db/atree/library/trees/fc-e20x/src/
 */

