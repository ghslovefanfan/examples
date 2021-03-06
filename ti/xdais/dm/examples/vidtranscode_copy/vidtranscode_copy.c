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
 *  ======== vidtranscode_copy.c ========
 *  Video transcoder "copy" algorithm.
 *
 *  This file contains an implementation of the IVIDTRANSCODE interface
 *  as defined by xDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/ividtranscode.h>

#ifdef __TI_COMPILER_VERSION__
/* xDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(VIDTRANSCODECOPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(VIDTRANSCODECOPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(VIDTRANSCODECOPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(VIDTRANSCODECOPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(VIDTRANSCODECOPY_TI_alloc,   ".text:algAlloc")
#endif

#include "vidtranscode_copy_ti.h"
#include "vidtranscode_copy_ti_priv.h"

/* TODO, need to autogenerate this */
#define VIDTRANSCODE_COPY_VERSIONSTRING "1.00.00.00"

/* Helper definitions */
#define BITSPERBYTE     8       /* number of bits in a byte */

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

extern IALG_Fxns VIDTRANSCODECOPY_TI_IALG;

#define IALGFXNS  \
    &VIDTRANSCODECOPY_TI_IALG,  /* module ID */                         \
    NULL,                       /* activate */                          \
    VIDTRANSCODECOPY_TI_alloc,  /* alloc */                             \
    NULL,                       /* control (NULL => no control ops) */  \
    NULL,                       /* deactivate */                        \
    VIDTRANSCODECOPY_TI_free,   /* free */                              \
    VIDTRANSCODECOPY_TI_initObj,/* init */                              \
    NULL,                       /* moved */                             \
    NULL                        /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== VIDTRANSCODECOPY_TI_IVIDTRANSCODECOPY ========
 *  This structure defines TI's implementation of the IVIDTRANSCODE interface
 *  for the VIDTRANSCODECOPY_TI module.
 */
IVIDTRANSCODE_Fxns VIDTRANSCODECOPY_TI_IVIDTRANSCODECOPY = {
    {IALGFXNS},
    VIDTRANSCODECOPY_TI_process,
    VIDTRANSCODECOPY_TI_control,
};

/*
 *  ======== VIDTRANSCODECOPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the VIDTRANSCODECOPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy xDAIS symbol requirement without any overhead */
asm("_VIDTRANSCODECOPY_TI_IALG .set _VIDTRANSCODECOPY_TI_IVIDTRANSCODECOPY");

#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns VIDTRANSCODECOPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

IVIDTRANSCODE_Params VIDTRANSCODECOPY_TI_PARAMS = {
    sizeof(IVIDTRANSCODE_Params),       /* size */
    1,                                  /* numOutputStreams */
    IVIDEO_MPEG2SP,                     /* formatInput */
    {
        IVIDEO_H264BP,                  /* formatOutput[0] */
        0,                              /* formatOutput[1] - don't care */
    },
        1024,                           /* maxHeightInput */
        1024,                           /* maxWidthInput */
        30000,                          /* maxFrameRateInput */
        10000000,                       /* maxBitRateInput */
    {
        1024,                           /* maxHeightOutput[0] */
        0,                              /* maxHeightOutput[1] - don't care */
    },
    {
        1024,                           /* maxWidthOutput[0] */
        0,                              /* maxWidthOutput[1] - don't care */
    },
    {
        30000,                          /* maxFrameRateOutput[0] */
        0,                              /* maxFrameRateOutput[1] - don't care */
    },
    {
        10000000,                       /* maxBitRateOutput[0] */
        0,                              /* maxBitRateOutput[1] - don't care */
    },
    XDM_BYTE                            /* dataEndianness */
};

/*
 *  ======== VIDTRANSCODECOPY_TI_alloc ========
 */
Int VIDTRANSCODECOPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(VIDTRANSCODECOPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}

/*
 *  ======== VIDTRANSCODECOPY_TI_free ========
 */
Int VIDTRANSCODECOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    return (VIDTRANSCODECOPY_TI_alloc(NULL, NULL, memTab));
}

/*
 *  ======== VIDTRANSCODECOPY_TI_initObj ========
 */
Int VIDTRANSCODECOPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle p, const IALG_Params *algParams)
{
    const IVIDTRANSCODE_Params *params = (IVIDTRANSCODE_Params *)algParams;

    /*
     * In lieu of xDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &VIDTRANSCODECOPY_TI_PARAMS;
    }

    return (IALG_EOK);
}

/*
 *  ======== VIDTRANSCODECOPY_TI_process ========
 */
XDAS_Int32 VIDTRANSCODECOPY_TI_process(IVIDTRANSCODE_Handle h,
    XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDTRANSCODE_InArgs *inArgs,
    IVIDTRANSCODE_OutArgs *outArgs)
{
    XDAS_Int32 numInBytes;

    /* validate arguments - this codec only supports "base" xDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
        (outArgs->size != sizeof(*outArgs))) {

        outArgs->extendedError = XDM_UNSUPPORTEDPARAM;

        return (IVIDTRANSCODE_EUNSUPPORTED);
    }

    /* validate that there's at least a single inBuf and outBuf */
    if ((inBufs->numBufs < 1) || (outBufs->numBufs < 1)) {

        outArgs->extendedError = XDM_UNSUPPORTEDPARAM;

        return (IVIDTRANSCODE_EFAIL);
    }

    numInBytes = inArgs->numBytes;

    /*
     * Sanity check that inBufs->descs[0].bufSize is really capable of holding
     * numInBytes bytes of data, and that outBufs->bufSizes[0]
     * can hold the 'transcoded' data.
     */
    if ((inBufs->descs[0].bufSize < inArgs->numBytes) ||
        (outBufs->bufSizes[0] < MINOUTBUFSIZE)){

        /* inBuf is smaller than provided data(!) or "too small" outBuf */
        outArgs->extendedError = XDM_UNSUPPORTEDPARAM;

        return (IVIDTRANSCODE_EFAIL);
    }

    /* everything looks good, do the 'transcode', set outArgs and return */
    memcpy(outBufs->bufs[0], inBufs->descs[0].buf, numInBytes);

    /* report _how_ we accessed the input buffer */
    XDM_CLEARACCESSMODE_WRITE(inBufs->descs[0].accessMask);
    XDM_SETACCESSMODE_READ(inBufs->descs[0].accessMask);


    /* outArgs->bytesConsumed reports the total number of bytes decoded */
    outArgs->bitsConsumed = numInBytes * BITSPERBYTE;

    outArgs->bitsGenerated[0] = outArgs->bitsConsumed;
    outArgs->bitsGenerated[1] = 0;

    outArgs->decodedPictureType = IVIDEO_I_PICTURE;  /* Simple for now */
    outArgs->decodedPictureStructure = IVIDEO_INTERLACED_FRAME;

    outArgs->encodedPictureType[0] = IVIDEO_I_PICTURE;
    outArgs->encodedPictureType[1] = IVIDEO_NA_PICTURE;

    outArgs->encodedPictureStructure[0] = IVIDEO_INTERLACED_FRAME;
    outArgs->encodedPictureStructure[1] = IVIDEO_CONTENTTYPE_NA;

    outArgs->decodedHeight = 1;  /* one pixel high */
    outArgs->decodedWidth = numInBytes;  /* numInBytes wide */

    outArgs->outputID[0] = inArgs->inputID;
    outArgs->outputID[1] = 0;  /* invalid ID */

    outArgs->inputFrameSkipTranscodeFlag[0] = XDAS_FALSE;
    outArgs->inputFrameSkipTranscodeFlag[1] = XDAS_TRUE;  /* don't care */

    outArgs->encodedBuf[0].buf = outBufs->bufs[0];
    outArgs->encodedBuf[0].bufSize = outBufs->bufSizes[0];

    /* initialize the accessMask, then indicate how we accessed it */
    outArgs->encodedBuf[0].accessMask = 0;
    XDM_SETACCESSMODE_WRITE(outArgs->encodedBuf[0].accessMask);

    outArgs->outBufsInUseFlag = XDAS_FALSE;

    return (IVIDTRANSCODE_EOK);
}

/*
 *  ======== VIDTRANSCODECOPY_TI_control ========
 */
XDAS_Int32 VIDTRANSCODECOPY_TI_control(IVIDTRANSCODE_Handle handle,
    IVIDTRANSCODE_Cmd id, IVIDTRANSCODE_DynamicParams *dynParams,
    IVIDTRANSCODE_Status *status)
{
    XDAS_Int32 retVal;

    /* validate arguments - this codec only supports "base" xDM. */
    if ((dynParams->size != sizeof(*dynParams)) ||
        (status->size != sizeof(*status))) {

        return (IVIDTRANSCODE_EUNSUPPORTED);
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

            retVal = IVIDTRANSCODE_EOK;
            break;

        case XDM_SETPARAMS:
            retVal = IVIDTRANSCODE_EOK;
            break;

        case XDM_SETDEFAULT:
            retVal = IVIDTRANSCODE_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = IVIDTRANSCODE_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.buf != NULL) &&
                (status->data.bufSize >=
                    strlen(VIDTRANSCODE_COPY_VERSIONSTRING))) {

                strncpy((char *)status->data.buf,
                    VIDTRANSCODE_COPY_VERSIONSTRING,
                    strlen(VIDTRANSCODE_COPY_VERSIONSTRING));

                /* null terminate the string */
                status->data.buf[strlen(VIDTRANSCODE_COPY_VERSIONSTRING)] =
                    '\0';

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(status->data.accessMask);

                retVal = IVIDTRANSCODE_EOK;
            }
            else {
                retVal = IVIDTRANSCODE_EFAIL;
            }

            break;

        default:
            /* unsupported cmd */
            retVal = IVIDTRANSCODE_EFAIL;
            break;
    }

    return (retVal);
}
/*
 *  @(#) ti.xdais.dm.examples.vidtranscode_copy; 2, 0, 0,45; 5-8-2008 09:07:33; /db/wtree/library/trees/dais-j06x/src/
 */

