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
 *  ======== bufres_util.c ========
 *  Utility functions for BUFRES.
 */

#include <xdc/std.h>

#include <ti/bios/include/std.h>

#include <ti/sdo/fc/utils/dbc.h>

#include <ti/sdo/fc/ires/iresman.h>

#include <ti/sdo/fc/rman/examples/bufres_yield/bufres.h>

/*
 *  ======== BUFRES_init ========
 */
IRES_Status BUFRES_init(BUFRES_Params *args)
{
    IRES_Status status;

    /* Returns IRES_OK on success */
    status = BUFRES_MGRFXNS.init((IRESMAN_Params *)args);

    return (status);
}

/*
 *  ======== BUFRES_exit ========
 */
IRES_Status BUFRES_exit()
{
    IRES_Status status = IRES_OK;

    status = BUFRES_MGRFXNS.exit();
    return (status);
}

/*
 *  ======== BUFRES_get ========
 * This function allocates the buffer resource
 */
BUFRES_Handle BUFRES_get(IALG_Handle h, BUFRES_Args *args, Int scratchId,
        IRES_Status *pStatus)
{
    BUFRES_Handle buf;

    buf = (BUFRES_Handle)(BUFRES_MGRFXNS.getHandle(h, (IRES_ProtocolArgs *)args,
                                  scratchId, pStatus));
    return (buf);
}

/*
 *  ======== BUFRES_free ========
 */
IRES_Status BUFRES_free(IALG_Handle h, BUFRES_Handle res, BUFRES_Args *args,
        Int scratchId)
{
    IRES_Status status;

    status = BUFRES_MGRFXNS.freeHandle(h, (IRES_Handle)res,
            (IRES_ProtocolArgs *)args, scratchId);
    return (status);
}

/*
 *  ======== BUFRES_getStaticProps ========
 */
Void BUFRES_getStaticProps(BUFRES_Handle res, BUFRES_Props *props)
{
    (*(IRES_Handle)(res)).getStaticProperties((IRES_Handle)res,
            (IRES_Properties *)props);
}

/*
 *  @(#) ti.sdo.fc.rman.examples.bufres_yield; 1, 0, 0,83; 9-9-2008 23:54:37; /db/atree/library/trees/fc-e20x/src/
 */

