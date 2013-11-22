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
 *  ======== sphenc_copy.c ========
 *  Speech Encoder "copy" algorithm.
 *
 *  This file contains an implementation of the IALG interface
 *  required by XDAS.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/isphenc.h>
#include <ti/sdo/ce/trace/gt.h>

#include "sphenc_copy_ti.h"
#include "sphenc_copy_ti_priv.h"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

extern IALG_Fxns SPHENCCOPY_TI_IALG;

#define IALGFXNS  \
    &SPHENCCOPY_TI_IALG,/* module ID */                         \
    NULL,               /* activate */                          \
    SPHENCCOPY_TI_alloc,/* alloc */                             \
    NULL,               /* control (NULL => no control ops) */  \
    NULL,               /* deactivate */                        \
    SPHENCCOPY_TI_free, /* free */                              \
    SPHENCCOPY_TI_initObj, /* init */                              \
    NULL,               /* moved */                             \
    NULL                /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== SPHENCCOPY_TI_ISPHENC ========
 *  This structure defines TI's implementation of the ISPHENC interface
 *  for the SPHENCCOPY_TI module.
 */
ISPHENC_Fxns SPHENCCOPY_TI_SPHENCCOPY = {    /* module_vendor_interface */
    {IALGFXNS},
    SPHENCCOPY_TI_process,
    SPHENCCOPY_TI_control,
};

/*
 *  ======== SPHENC_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the SPHENCCOPY_TI module.
 */
#ifdef _TI_

asm("_SPHENCCOPY_TI_IALG .set _SPHENCCOPY_TI_SPHENCCOPY");

#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns SPHENCCOPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

/* tracing information */
#define GTNAME "ti.sdo.ce.examples.codecs.sphenc_copy"
static GT_Mask curTrace = {NULL,NULL};

/*
 *  ======== SPHENCCOPY_TI_alloc ========
 */
Int SPHENCCOPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    if (curTrace.modName == NULL) {   /* initialize GT (tracing) */
        GT_create(&curTrace, GTNAME);
    }

    GT_3trace(curTrace, GT_ENTER, "SPHENCCOPY_TI_alloc(0x%lx, 0x%lx, 0x%lx)\n",
        algParams, pf, memTab);

    /* Request memory for my object */
    memTab[0].size = sizeof(SPHENCCOPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}


/*
 *  ======== SPHENCCOPY_TI_free ========
 */
Int SPHENCCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    GT_2trace(curTrace, GT_ENTER, "SPHENCCOPY_TI_free(0x%lx, 0x%lx)\n",
        handle, memTab);

    SPHENCCOPY_TI_alloc(NULL, NULL, memTab);
    return (1);
}


/*
 *  ======== SPHENCCOPY_TI_initObj ========
 */
Int SPHENCCOPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle p,
    const IALG_Params *algParams)
{
    GT_4trace(curTrace, GT_ENTER,
        "SPHENCCOPY_TI_initObj(0x%lx, 0x%lx, 0x%lx, 0x%lx)\n",
        handle, memTab, p, algParams);

    return (IALG_EOK);
}


/*
 *  ======== SPHENCCOPY_TI_process ========
 */
XDAS_Int32 SPHENCCOPY_TI_process(ISPHENC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs)
{
    XDAS_Int32 curBuf;
    XDAS_Int32 minSamples;

    GT_5trace(curTrace, GT_ENTER,
        "SPHENCCOPY_TI_process(0x%lx, 0x%lx, 0x%lx, 0x%lx, 0x%lx)\n",
        h, inBufs, outBufs, inArgs, outArgs);

    /* validate arguments - this codec only supports "base" xDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
        (outArgs->size != sizeof(*outArgs))) {

        GT_2trace(curTrace, GT_ENTER, "SPHENCCOPY_TI_process, unsupported size "
            "(0x%lx, 0x%lx)\n", inArgs->size, outArgs->size);

        return (ISPHENC_EFAIL);
    }

    outArgs->outbufferSize = 0;

    /*
     * A couple constraints for this simple "copy" codec:
     *    - Speech encoding presumes a single input buffer, so only one input
     *      buffer will be encoded, regardless of inBufs->numBufs.
     *    - Given a different size of an input and output buffers, only
     *      encode (i.e., copy) the lesser of the sizes.
     */

    for (curBuf = 0; (curBuf < inBufs->numBufs) &&
        (curBuf < outBufs->numBufs); curBuf++) {

        /* there's an available in and out buffer, how many samples? */
        minSamples = inBufs->bufSizes[curBuf] < outBufs->bufSizes[curBuf] ?
            inBufs->bufSizes[curBuf] : outBufs->bufSizes[curBuf];

        /* process the data: read input, produce output */
        memcpy(outBufs->bufs[curBuf], inBufs->bufs[curBuf], minSamples);

        GT_1trace(curTrace, GT_2CLASS, "SPHENCCOPY_TI_process> "
            "Processed %d bytes.\n", minSamples);
        outArgs->outbufferSize += minSamples;
    }

    /* Fill out the rest of the outArgs struct */
    outArgs->frameType = 0;    /* TODO */
    outArgs->rate = 0;   /* TODO */

    return (ISPHENC_EOK);
}


/*
 *  ======== SPHENCCOPY_TI_control ========
 */
XDAS_Int32 SPHENCCOPY_TI_control(ISPHENC_Handle handle, ISPHENC_Cmd id,
    ISPHENC_DynamicParams *params, ISPHENC_Status *status)
{
    XDAS_Int32 retVal;

    GT_4trace(curTrace, GT_ENTER,
        "SPHENCCOPY_TI_control(0x%lx, 0x%lx, 0x%lx, 0x%lx)\n",
        handle, id, params, status);

    /* validate arguments - this codec only supports "base" xDM. */
    if ((params->size != sizeof(*params)) ||
        (status->size != sizeof(*status))) {

        GT_2trace(curTrace, GT_ENTER, "SPHENCCOPY_TI_control, unsupported size "
            "(0x%lx, 0x%lx)\n", params->size, status->size);

        return (ISPHENC_EFAIL);
    }

    switch (id) {
        case XDM_GETSTATUS:
            status->frameSize = 0;  /* TODO */
            status->bitRate = 0; /* TODO */
            status->mode = 0; /* TODO */
            status->vadFlag = 0; /* TODO */
            status->noiseSuppressionMode = 0;  /* TODO */
            status->ttyTddMode = 0;  /* TODO */
            status->dtmfMode = 0;  /* TODO */
            status->dataTransmit = 0;  /* TODO */
            status->homingMode = 0;  /* TODO */

            /* Note, intentionally no break here so we fill in bufInfo, too */

        case XDM_GETBUFINFO:
            status->extendedError = 0;

            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = ISPHENC_EOK;

            break;

        case XDM_SETPARAMS:
        case XDM_SETDEFAULT:
        case XDM_RESET:
        case XDM_FLUSH:
            /* TODO - for now just return success. */

            retVal = ISPHENC_EOK;
            break;

        default:
            /* unsupported cmd */
            retVal = ISPHENC_EFAIL;

            break;
    }

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.sphenc_copy; 1,0,0,132; 9-9-2008 02:03:25; /db/atree/library/trees/ce-h27x/src/
 */

