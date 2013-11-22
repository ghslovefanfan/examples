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
 *  ======== videnc1_copy.c ========
 *  Video encoder "copy" algorithm.
 *
 *  This file contains an implementation of the IVIDENC1 interface
 *  as defined by xDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/ividenc1.h>

#ifdef __TI_COMPILER_VERSION__
/* xDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(VIDENC1COPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(VIDENC1COPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(VIDENC1COPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(VIDENC1COPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(VIDENC1COPY_TI_alloc,   ".text:algAlloc")
#endif

#include "videnc1_copy_ti.h"
#include "videnc1_copy_ti_priv.h"

/* TODO, need to autogenerate this */
#define VIDENC1_COPY_VERSIONSTRING "1.00.00.0"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

extern IALG_Fxns VIDENC1COPY_TI_IALG;

#define IALGFXNS  \
    &VIDENC1COPY_TI_IALG,       /* module ID */                         \
    NULL,                       /* activate */                          \
    VIDENC1COPY_TI_alloc,       /* alloc */                             \
    NULL,                       /* control (NULL => no control ops) */  \
    NULL,                       /* deactivate */                        \
    VIDENC1COPY_TI_free,        /* free */                              \
    VIDENC1COPY_TI_initObj,     /* init */                              \
    NULL,                       /* moved */                             \
    NULL                        /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== VIDENC1COPY_TI_IVIDENCCOPY ========
 *  This structure defines TI's implementation of the IVIDENC1 interface
 *  for the VIDENC1COPY_TI module.
 */
IVIDENC1_Fxns VIDENC1COPY_TI_IVIDENC1COPY = {    /* module_vendor_interface */
    {IALGFXNS},
    VIDENC1COPY_TI_process,
    VIDENC1COPY_TI_control,
};

/*
 *  ======== VIDENC1COPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the VIDENC1COPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy xDAIS symbol requirement without any overhead */
asm("_VIDENC1COPY_TI_IALG .set _VIDENC1COPY_TI_IVIDENC1COPY");

#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns VIDENC1COPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

IVIDENC1_Params VIDENC1COPY_TI_PARAMS = {
    sizeof(IVIDENC1_Params),
    0,                              /* encodingPreset - TODO */
    0,                              /* rateControlPreset - TODO */
    1024,                           /* maxHeight */
    1024,                           /* maxWidth */
    30000,                          /* maxFrameRate */
    10000000,                       /* maxBitRate */
    XDM_BYTE,                       /* dataEndianness */
    1,                              /* maxInterFrameInterval */
    XDM_CHROMAFORMAT_DEFAULT,       /* inputChromaFormat */
    IVIDEO_CONTENTTYPE_DEFAULT,     /* inputContentType */
    XDM_CHROMAFORMAT_DEFAULT        /* reconChromaFormat */
};

#ifdef USE_ACPY3

/* Implementation of IDMA3 interface functions & IDMA3_Fxns vtable */
#include <ti/xdais/idma3.h>
#include <ti/sdo/fc/acpy3/acpy3.h>

#define NUM_LOGICAL_CH 1

/*
 *  ======== VIDENC1COPY_TI_dmaChangeChannels ========
 *  Update instance object with new logical channel.
 */
Void VIDENC1COPY_TI_dmaChangeChannels(IALG_Handle handle,
    IDMA3_ChannelRec dmaTab[])
{
    VIDENC1COPY_TI_Obj *videncObj = (Void *)handle;

    videncObj->dmaHandle1D1D8B = dmaTab[0].handle;
}


/*
 *  ======== VIDENC1COPY_TI_dmaGetChannelCnt ========
 *  Return max number of logical channels requested.
 */
Uns VIDENC1COPY_TI_dmaGetChannelCnt(Void)
{
    return (NUM_LOGICAL_CH);
}


/*
 *  ======== VIDENC1COPY_TI_dmaGetChannels ========
 *  Declare DMA resource requirement/holdings.
 */
Uns VIDENC1COPY_TI_dmaGetChannels(IALG_Handle handle, IDMA3_ChannelRec dmaTab[])
{
    VIDENC1COPY_TI_Obj *videncObj = (Void *)handle;
    int i;

    /* Initial values on logical channels */
    dmaTab[0].handle = videncObj->dmaHandle1D1D8B;

    dmaTab[0].numTransfers = 1;
    dmaTab[0].numWaits = 1;

    /*
     * Request logical DMA channels for use with ACPY3
     * AND with environment size obtained from ACPY3 implementation
     * AND with low priority.
     */
    for (i = 0; i < NUM_LOGICAL_CH; i++) {
        dmaTab[i].priority = IDMA3_PRIORITY_LOW;
        dmaTab[i].persistent = FALSE;
        dmaTab[i].protocol = &ACPY3_PROTOCOL;
    }

    return (NUM_LOGICAL_CH);
}


/*
 *  ======== VIDENC1COPY_TI_dmaInit ========
 *  Initialize instance object with granted logical channel.
 */
Int VIDENC1COPY_TI_dmaInit(IALG_Handle handle, IDMA3_ChannelRec dmaTab[])
{
    VIDENC1COPY_TI_Obj *videncObj = (Void *)handle;

    videncObj->dmaHandle1D1D8B = dmaTab[0].handle;

    return (IALG_EOK);
}


/*
 *  ======== VIDENC1COPY_TI_IDMA3 ========
 *  This structure defines TI's implementation of the IDMA3 interface
 *  for the VIDENC1COPY_TI module.
 */
IDMA3_Fxns VIDENC1COPY_TI_IDMA3 = {    /* module_vendor_interface */
    &VIDENC1COPY_TI_IALG,              /* IALG functions */
    VIDENC1COPY_TI_dmaChangeChannels,  /* ChangeChannels */
    VIDENC1COPY_TI_dmaGetChannelCnt,   /* GetChannelCnt */
    VIDENC1COPY_TI_dmaGetChannels,     /* GetChannels */
    VIDENC1COPY_TI_dmaInit             /* initialize logical channels */
};

#endif


/*
 *  ======== VIDENC1COPY_TI_alloc ========
 */
Int VIDENC1COPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(VIDENC1COPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}

/*
 *  ======== VIDENC1COPY_TI_free ========
 */
Int VIDENC1COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    return (VIDENC1COPY_TI_alloc(NULL, NULL, memTab));
}

/*
 *  ======== VIDENC1COPY_TI_initObj ========
 */
Int VIDENC1COPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle p, const IALG_Params *algParams)
{
    const IVIDENC1_Params *params = (IVIDENC1_Params *)algParams;

    /*
     * In lieu of xDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &VIDENC1COPY_TI_PARAMS;
    }

    return (IALG_EOK);
}

/*
 *  ======== VIDENC1COPY_TI_process ========
 */
XDAS_Int32 VIDENC1COPY_TI_process(IVIDENC1_Handle h, IVIDEO1_BufDescIn *inBufs,
    XDM_BufDesc *outBufs, IVIDENC1_InArgs *inArgs, IVIDENC1_OutArgs *outArgs)
{
    XDAS_Int32 numInBytes;

#ifdef USE_ACPY3
    const Uint32 maxTransferChunkSize       = 0xffff;
    Uint32       thisTransferChunkSize      = 0x0;
    Uint32       remainingTransferChunkSize;
    Uint32       thisTransferSrcAddr, thisTransferDstAddr;

    ACPY3_Params params;
    VIDENC1COPY_TI_Obj *videncObj = (VIDENC1COPY_TI_Obj *)h;
#endif
    /*
     * Validate arguments - this codec supports "base" xDM and an extended
     * inArgs.
     */
    if (((inArgs->size != sizeof(*inArgs)) &&
            (inArgs->size != sizeof(IVIDENC1CPY_InArgs))) ||
        (outArgs->size != sizeof(*outArgs))) {

        outArgs->extendedError = XDM_UNSUPPORTEDPARAM;

        return (IVIDENC1_EUNSUPPORTED);
    }

    /* validate that there's at least a single inBuf and outBuf */
    if ((inBufs->numBufs < 1) || (outBufs->numBufs < 1)) {
        outArgs->extendedError = XDM_UNSUPPORTEDPARAM;

        return (IVIDENC1_EFAIL);
    }

    /* validate inputID */
    if (inArgs->inputID == 0) {
        outArgs->extendedError = XDM_UNSUPPORTEDPARAM;

        return (IVIDENC1_EFAIL);
    }

    /* there's an available in and out buffer, how many samples? */
    numInBytes = inBufs->bufDesc[0].bufSize < outBufs->bufSizes[0] ?
        inBufs->bufDesc[0].bufSize : outBufs->bufSizes[0];

    /* and honor the extended maxBytes if it was provided */
    if (inArgs->size == sizeof(IVIDENC1CPY_InArgs)) {
        if (numInBytes > ((IVIDENC1CPY_InArgs *)inArgs)->maxBytes) {
            numInBytes = ((IVIDENC1CPY_InArgs *)inArgs)->maxBytes;
        }
    }
#ifdef USE_ACPY3
    /*
     * Activate Channel scratch DMA channels.
     */
    ACPY3_activate(videncObj->dmaHandle1D1D8B);

    thisTransferSrcAddr        = (Uint32)inBufs->bufDesc[0].buf;
    thisTransferDstAddr        = (Uint32)outBufs->bufs[0];
    remainingTransferChunkSize = numInBytes;

    while (remainingTransferChunkSize > 0) {

        if (remainingTransferChunkSize > maxTransferChunkSize) {
           thisTransferChunkSize = maxTransferChunkSize;
        }
        else {
           thisTransferChunkSize = remainingTransferChunkSize;
        }

        /* Configure the logical channel */
        params.transferType = ACPY3_1D1D;
        params.srcAddr      = (void *)thisTransferSrcAddr;
        params.dstAddr      = (void *)thisTransferDstAddr;
        params.elementSize  = thisTransferChunkSize;
        params.numElements  = 1;
        params.waitId       = 0;
        params.numFrames    = 1;

        remainingTransferChunkSize -= thisTransferChunkSize;
        thisTransferSrcAddr += thisTransferChunkSize;
        thisTransferDstAddr += thisTransferChunkSize;

        /* Configure logical dma channel */
        ACPY3_configure(videncObj->dmaHandle1D1D8B, &params, 0);

        /* Use DMA to copy data */
        ACPY3_start(videncObj->dmaHandle1D1D8B);

        /* wait for transfer to finish  */
        ACPY3_wait(videncObj->dmaHandle1D1D8B);
    }

    /*
     * Deactivate Channel scratch DMA channels.
     */
    ACPY3_deactivate(videncObj->dmaHandle1D1D8B);

    /*
     * Because we used DMA, the algo processor didn't accessed either of the
     * 2 data buffers.
     */
    XDM_CLEARACCESSMODE_READ(inBufs->bufDesc[0].accessMask);
    XDM_CLEARACCESSMODE_WRITE(inBufs->bufDesc[0].accessMask);

    XDM_CLEARACCESSMODE_READ(outArgs->encodedBuf.accessMask);
    XDM_CLEARACCESSMODE_WRITE(outArgs->encodedBuf.accessMask);

#else
    /* everything looks good, do the 'encode', set outArgs and return */
    memcpy(outBufs->bufs[0], inBufs->bufDesc[0].buf, numInBytes);

    /* memcpy read from inBuf and wrote to encodedBuf (in our case, outBuf) */
    XDM_CLEARACCESSMODE_WRITE(inBufs->bufDesc[0].accessMask);
    XDM_SETACCESSMODE_READ(inBufs->bufDesc[0].accessMask);

    XDM_CLEARACCESSMODE_READ(outArgs->encodedBuf.accessMask);
    XDM_SETACCESSMODE_WRITE(outArgs->encodedBuf.accessMask);
#endif

    /* outArgs->bytesGenerated reports the total number of bytes encoded */
    outArgs->bytesGenerated = numInBytes;

    /* report that the encoded data is in outArgs->encodedBuf */
    outArgs->encodedBuf.buf = outBufs->bufs[0];
    outArgs->encodedBuf.bufSize = outBufs->bufSizes[0];

    /* Fill out the rest of the outArgs struct */
    outArgs->extendedError = 0;
    outArgs->encodedFrameType = 0;     /* TODO */
    outArgs->inputFrameSkip = IVIDEO_FRAME_ENCODED;
    outArgs->outputID = inArgs->inputID;

    /* TODO - add support for reconBufs */
    outArgs->reconBufs.numBufs = 0;

    return (IVIDENC1_EOK);
}

/*
 *  ======== VIDENC1COPY_TI_control ========
 */
XDAS_Int32 VIDENC1COPY_TI_control(IVIDENC1_Handle handle, IVIDENC1_Cmd id,
    IVIDENC1_DynamicParams *params, IVIDENC1_Status *status)
{
    XDAS_Int32 retVal;

    /* validate arguments - this codec only supports "base" xDM. */
    if ((params->size != sizeof(*params)) ||
        (status->size != sizeof(*status))) {

        return (IVIDENC1_EUNSUPPORTED);
    }

    /* initialize for the general case where we don't access the data buffer */
    XDM_CLEARACCESSMODE_READ(status->data.accessMask);
    XDM_CLEARACCESSMODE_WRITE(status->data.accessMask);

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->extendedError = 0;

            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = IVIDENC1_EOK;
            break;

        case XDM_SETPARAMS:
            retVal = IVIDENC1_EOK;
            break;

        case XDM_SETDEFAULT:
            retVal = IVIDENC1_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = IVIDENC1_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.buf != NULL) &&
                (status->data.bufSize >= strlen(VIDENC1_COPY_VERSIONSTRING))) {
                strncpy((char *)status->data.buf, VIDENC1_COPY_VERSIONSTRING,
                    strlen(VIDENC1_COPY_VERSIONSTRING));

                /* null terminate the string */
                status->data.buf[strlen(VIDENC1_COPY_VERSIONSTRING)] = '\0';

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(status->data.accessMask);

                retVal = IVIDENC1_EOK;
            }
            else {
                retVal = IVIDENC1_EFAIL;
            }

            break;

        default:
            /* unsupported cmd */
            retVal = IVIDENC1_EUNSUPPORTED;

            break;
    }

    return (retVal);
}
/*
 *  @(#) ti.xdais.dm.examples.videnc1_copy; 2, 0, 0,118; 5-8-2008 09:07:15; /db/wtree/library/trees/dais-j06x/src/
 */

