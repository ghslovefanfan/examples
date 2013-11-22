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
 *  ======== scale_stubs.c ========
 *  These functions are the "app-side" of a "remote" implementation.
 *
 */
#include <xdc/std.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/examples/codecs/scale/iscale.h>
#include <ti/sdo/ce/osal/Memory.h>

#include "scale.h"
#include "_scale.h"

static XDAS_Int32 process(ISCALE_Handle h, XDAS_Int8 *inBuf,
    XDAS_Int8 *outBuf, ISCALE_InArgs *inArgs, ISCALE_OutArgs *outArgs);
static XDAS_Int32 control(ISCALE_Handle h, ISCALE_Cmd id,
    ISCALE_DynamicParams *params);

/*
 * Stubs must implement the interface they "stub" for.  This scale stub
 * proxy's for ISCALE_Fxns, which is IALG + process() and control().
 *
 * Note that the IALG fxns for the stub currently aren't called, so
 * they're all set to NULL.
 */
ISCALE_Fxns SCALE_STUBS = {
    {&SCALE_STUBS, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    process, control,
};

/*
 *  ======== process ========
 *  This is the stub-implementation for the process method
 */
static XDAS_Int32 process(ISCALE_Handle h, XDAS_Int8 *inBuf,
    XDAS_Int8 *outBuf, ISCALE_InArgs *inArgs, ISCALE_OutArgs *outArgs)
{
    XDAS_Int32 retVal;
    VISA_Handle visa = (VISA_Handle)h;
    _SCALE_Msg *msg;

    /* get a message appropriate for this algorithm */
    if ((msg = (_SCALE_Msg *)VISA_allocMsg(visa)) == NULL) {
        return (SCALE_ERUNTIME);
    }

    /* Specify the processing command that the skeleton should do */
    msg->visa.cmd = _SCALE_CPROCESS;

    /* inBuf is a pointer, so we have to convert it */
    msg->cmd.process.inBuf = (XDAS_Int8 *)
        Memory_getBufferPhysicalAddress(inBuf, inArgs->inBufSize, NULL);

    if (msg->cmd.process.inBuf == NULL) {
        retVal = SCALE_ERUNTIME;
        goto exit;
    }

    /* Similarly with outBuf. Note that inArgs and outArgs contain no
     * pointers, so we can simply copy the entire original structure.
     */
    msg->cmd.process.outBuf = (XDAS_Int8 *)
        Memory_getBufferPhysicalAddress(outBuf, inArgs->outBufSize, NULL);

    if (msg->cmd.process.outBuf == NULL) {
        retVal = SCALE_ERUNTIME;
        goto exit;
    }

    /* inArgs has no pointers, so simply copy the struct fields into the msg */
    msg->cmd.process.inArgs = *inArgs;

    /* Note that outArgs is *output* and need not be provided to the skel */

    /* send the message to the skeleton and wait for completion */
    retVal = VISA_call(visa, (VISA_Msg *)&msg);

    /* copy out the outArgs */
    *outArgs = msg->cmd.process.outArgs;

    /* Note that we need not copy inArgs out of the msg. */

    /*
     * Note that we don't have to do any reverse address translation, as the
     * originally provided buffers haven't changed.
     */

exit:
    VISA_freeMsg(visa, (VISA_Msg)msg);

    return (retVal);
}

/*
 *  ======== control ========
 *  This is the stub-implementation for the control method
 */
static XDAS_Int32 control(ISCALE_Handle h, ISCALE_Cmd id,
    ISCALE_DynamicParams *params)
{
    XDAS_Int32 retVal;
    VISA_Handle visa = (VISA_Handle)h;
    _SCALE_Msg *msg;

    /* get a message appropriate for this algorithm */
    if ((msg = (_SCALE_Msg *)VISA_allocMsg(visa)) == NULL) {
        return (SCALE_ERUNTIME);
    }

    /* marshall the command */
    msg->visa.cmd = _SCALE_CCONTROL;

    msg->cmd.control.id = id;

    /* no pointers, just copy the dynamic params struct into the msg */
    msg->cmd.control.params = *params;

    /* send the message to the skeleton and wait for completion */
    retVal = VISA_call(visa, (VISA_Msg *)&msg);

    /* nothing to unmarshall, just free the msg. */
    VISA_freeMsg(visa, (VISA_Msg)msg);

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.examples.extensions.scale; 1,0,0,131; 9-9-2008 02:04:04; /db/atree/library/trees/ce-h27x/src/
 */

