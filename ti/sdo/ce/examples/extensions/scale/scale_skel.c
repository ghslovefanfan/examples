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
 *  ======== scale_skel.c ========
 *  This file contains the implemenation of the SKEL interface for
 *  SCALE algorithms.
 *
 *  These functions are the "server-side" of the the stubs defined in
 *  scale_stubs.c
 */
#include <xdc/std.h>
#include <ti/sdo/ce/skel.h>
#include <ti/sdo/ce/osal/Memory.h>

#include "scale.h"
#include "_scale.h"

/*
 *  ======== call ========
 */
static VISA_Status call(VISA_Handle visaHandle, VISA_Msg visaMsg)
{
    _SCALE_Msg *msg  = (_SCALE_Msg *)visaMsg;
    SCALE_Handle handle = (SCALE_Handle)visaHandle;
    XDAS_Int8 *inBuf;
    XDAS_Int8 *outBuf;

    /* perform the requested SCALE operation by parsing message. */
    switch (msg->visa.cmd) {

        case _SCALE_CPROCESS: {
            /* unmarshall inBuf and outBuf */
            inBuf  = msg->cmd.process.inBuf;
            outBuf = msg->cmd.process.outBuf;

            /* invalidate cache for input and output buffers */
            Memory_cacheInv(inBuf, msg->cmd.process.inArgs.inBufSize);
            Memory_cacheInv(outBuf, msg->cmd.process.inArgs.outBufSize);

            /* make the process call */
            msg->visa.status = SCALE_process(handle, inBuf, outBuf,
                &(msg->cmd.process.inArgs), &(msg->cmd.process.outArgs));

            /* flush cache for output buffer */
            Memory_cacheWbInv(outBuf, msg->cmd.process.inArgs.outBufSize);

            /*
             * Note that any changes to individual outBufs[i] values made by
             * the codec will automatically update msg->cmd.process.outBufs
             * as we pass the outBufs array by reference.
             */

            break;
        }

        case _SCALE_CCONTROL: {
            msg->visa.status = SCALE_control(handle, msg->cmd.control.id,
                &(msg->cmd.control.params));

             break;
        }

        default: {
            msg->visa.status = VISA_EFAIL;

            break;
        }
    }
    return (VISA_EOK);
}

/*
 *  ======== SCALE_SKEL ========
 */
SKEL_Fxns SCALE_SKEL = {
    call,
    (SKEL_CREATEFXN)SCALE_create,
    (SKEL_DESTROYFXN)SCALE_delete,
};
/*
 *  @(#) ti.sdo.ce.examples.extensions.scale; 1,0,0,131; 9-9-2008 02:04:04; /db/atree/library/trees/ce-h27x/src/
 */

