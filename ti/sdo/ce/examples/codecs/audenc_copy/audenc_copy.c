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
 *  ======== audenc_copy.c ========
 *  Audio Encoder "copy" algorithm.
 *
 *  This file contains an implementation of the IALG interface
 *  required by XDAS.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/iaudenc.h>
#include <ti/sdo/ce/trace/gt.h>

#include "audenc_copy_ti.h"
#include "audenc_copy_ti_priv.h"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

extern IALG_Fxns AUDENCCOPY_TI_IALG;

#define IALGFXNS  \
    &AUDENCCOPY_TI_IALG,/* module ID */                         \
    NULL,               /* activate */                          \
    AUDENCCOPY_TI_alloc,/* alloc */                             \
    NULL,               /* control (NULL => no control ops) */  \
    NULL,               /* deactivate */                        \
    AUDENCCOPY_TI_free, /* free */                              \
    AUDENCCOPY_TI_initObj, /* init */                              \
    NULL,               /* moved */                             \
    NULL                /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== AUDENCCOPY_TI_IAUDENC ========
 *  This structure defines TI's implementation of the IAUDENC interface
 *  for the AUDENCCOPY_TI module.
 */
IAUDENC_Fxns AUDENCCOPY_TI_AUDENCCOPY = {    /* module_vendor_interface */
    {IALGFXNS},
    AUDENCCOPY_TI_process,
    AUDENCCOPY_TI_control,
};

/*
 *  ======== AUDENC_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the AUDENCCOPY_TI module.
 */
#ifdef _TI_

asm("_AUDENCCOPY_TI_IALG .set _AUDENCCOPY_TI_AUDENCCOPY");

#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns AUDENCCOPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

/* tracing information */
#define GTNAME "ti.sdo.ce.examples.codecs.audenc_copy"
static GT_Mask curTrace = {NULL,NULL};

/*
 *  ======== AUDENCCOPY_TI_alloc ========
 */
Int AUDENCCOPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    if (curTrace.modName == NULL) {   /* initialize GT (tracing) */
        GT_create(&curTrace, GTNAME);
    }

    GT_3trace(curTrace, GT_ENTER, "AUDENCCOPY_TI_alloc(0x%lx, 0x%lx, 0x%lx)\n",
        algParams, pf, memTab);

    /* Request memory for my object */
    memTab[0].size = sizeof(AUDENCCOPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}


/*
 *  ======== AUDENCCOPY_TI_free ========
 */
Int AUDENCCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    GT_2trace(curTrace, GT_ENTER, "AUDENCCOPY_TI_free(0x%lx, 0x%lx)\n",
        handle, memTab);

    AUDENCCOPY_TI_alloc(NULL, NULL, memTab);
    return (1);
}


/*
 *  ======== AUDENCCOPY_TI_initObj ========
 */
Int AUDENCCOPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle p,
    const IALG_Params *algParams)
{
    GT_4trace(curTrace, GT_ENTER,
        "AUDENCCOPY_TI_initObj(0x%lx, 0x%lx, 0x%lx, 0x%lx)\n",
        handle, memTab, p, algParams);

    return (IALG_EOK);
}


/*
 *  ======== AUDENCCOPY_TI_process ========
 */
XDAS_Int32 AUDENCCOPY_TI_process(IAUDENC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IAUDENC_InArgs *inArgs, IAUDENC_OutArgs *outArgs)
{
    XDAS_Int32 curBuf;
    XDAS_Int32 minSamples;

    GT_5trace(curTrace, GT_ENTER,
        "AUDENCCOPY_TI_process(0x%lx, 0x%lx, 0x%lx, 0x%lx, 0x%lx)\n",
        h, inBufs, outBufs, inArgs, outArgs);

    /* validate arguments - this codec only supports "base" xDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
        (outArgs->size != sizeof(*outArgs))) {

        GT_2trace(curTrace, GT_ENTER, "AUDENCCOPY_TI_process, unsupported size "
            "(0x%lx, 0x%lx)\n", inArgs->size, outArgs->size);

        return (IAUDENC_EFAIL);
    }

    /* outargs->outputBufferSize reports the total number of bytes generated */
    outArgs->bytesGenerated = 0;

    for (curBuf = 0; (curBuf < inBufs->numBufs) &&
        (curBuf < outBufs->numBufs); curBuf++) {

        /* there's an available in and out buffer, how many samples? */
        minSamples = inBufs->bufSizes[curBuf] < outBufs->bufSizes[curBuf] ?
            inBufs->bufSizes[curBuf] : outBufs->bufSizes[curBuf];

        /* process the data: read input, produce output */
        memcpy(outBufs->bufs[curBuf], inBufs->bufs[curBuf], minSamples);

        GT_1trace(curTrace, GT_2CLASS, "AUDENCCOPY_TI_process> "
            "Processed %d bytes.\n", minSamples );

        outArgs->bytesGenerated += minSamples;
    }

    /* Fill out the rest of the outArgs struct */
    outArgs->extendedError = 0;

    return (IAUDENC_EOK);
}


/*
 *  ======== AUDENCCOPY_TI_control ========
 */
XDAS_Int32 AUDENCCOPY_TI_control(IAUDENC_Handle handle, IAUDENC_Cmd id,
    IAUDENC_DynamicParams *params, IAUDENC_Status *status)
{
    XDAS_Int32 retVal;

    GT_4trace(curTrace, GT_ENTER,
        "AUDENCCOPY_TI_control(0x%lx, 0x%lx, 0x%lx, 0x%lx)\n",
        handle, id, params, status);

    /* validate arguments - this codec only supports "base" xDM. */
    if ((params->size != sizeof(*params)) ||
        (status->size != sizeof(*status))) {

        GT_2trace(curTrace, GT_ENTER, "AUDENCCOPY_TI_control, unsupported size "
            "(0x%lx, 0x%lx)\n", params->size, status->size);

        return (IAUDENC_EFAIL);
    }

    switch (id) {
        case XDM_GETSTATUS:
            status->extendedError = 0;

            status->frameLen = 0;  /* TODO */

            /* Note, intentionally no break here so we fill in bufInfo, too */

        case XDM_GETBUFINFO:
            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = IAUDENC_EOK;

            break;

        case XDM_SETPARAMS:
        case XDM_SETDEFAULT:
        case XDM_RESET:
        case XDM_FLUSH:
            /* TODO - for now just return success. */

            retVal = IAUDENC_EOK;
            break;

        default:
            /* unsupported cmd */
            retVal = IAUDENC_EFAIL;

            break;
    }

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.audenc_copy; 1,0,0,132; 9-9-2008 02:02:40; /db/atree/library/trees/ce-h27x/src/
 */

