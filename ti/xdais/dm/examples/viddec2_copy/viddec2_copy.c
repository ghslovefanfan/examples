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
 *  ======== viddec2_copy.c ========
 *  Video decoder "copy" algorithm.
 *
 *  This file contains an implementation of the IALG interface
 *  required by xDAIS.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/ividdec2.h>

#ifdef __TI_COMPILER_VERSION__
/* xDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(VIDDEC2COPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(VIDDEC2COPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(VIDDEC2COPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(VIDDEC2COPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(VIDDEC2COPY_TI_alloc,   ".text:algAlloc")
#endif

#include "viddec2_copy_ti.h"
#include "viddec2_copy_ti_priv.h"

/* TODO, need to autogenerate this */
#define VIDDEC2_COPY_VERSIONSTRING "1.00.00.0"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

extern IALG_Fxns VIDDEC2COPY_TI_IALG;

#define IALGFXNS  \
    &VIDDEC2COPY_TI_IALG,/* module ID */                         \
    NULL,               /* activate */                          \
    VIDDEC2COPY_TI_alloc,/* alloc */                             \
    NULL,               /* control (NULL => no control ops) */  \
    NULL,               /* deactivate */                        \
    VIDDEC2COPY_TI_free, /* free */                              \
    VIDDEC2COPY_TI_initObj, /* init */                              \
    NULL,               /* moved */                             \
    NULL                /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== VIDDEC2COPY_TI_IVIDDECCOPY ========
 *  This structure defines TI's implementation of the IVIDDEC2 interface
 *  for the VIDDEC2COPY_TI module.
 */
IVIDDEC2_Fxns VIDDEC2COPY_TI_IVIDDEC2COPY = {    /* module_vendor_interface */
    {IALGFXNS},
    VIDDEC2COPY_TI_process,
    VIDDEC2COPY_TI_control,
};

/*
 *  ======== VIDDEC2COPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the VIDDEC2COPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy xDAIS symbol requirement without any overhead */
asm("_VIDDEC2COPY_TI_IALG .set _VIDDEC2COPY_TI_IVIDDEC2COPY");

#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns VIDDEC2COPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

IVIDDEC2_Params VIDDEC2COPY_TI_PARAMS = {
    sizeof(IVIDDEC2_Params),
    1024,                           /* maxHeight */
    1024,                           /* maxWidth */
    30000,                          /* maxFrameRate */
    10000000,                       /* maxBitRate */
    XDM_BYTE,                       /* dataEndianness */
    XDM_CHROMAFORMAT_DEFAULT        /* forceChromaFormat */
};

/*
 *  ======== VIDDEC2COPY_TI_alloc ========
 */
Int VIDDEC2COPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(VIDDEC2COPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}


/*
 *  ======== VIDDEC2COPY_TI_free ========
 */
Int VIDDEC2COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    return (VIDDEC2COPY_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== VIDDEC2COPY_TI_initObj ========
 */
Int VIDDEC2COPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle p, const IALG_Params *algParams)
{
    VIDDEC2COPY_TI_Obj *obj = (VIDDEC2COPY_TI_Obj *)handle;
    const IVIDDEC2_Params *params = (IVIDDEC2_Params *)algParams;

    /*
     * In lieu of xDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &VIDDEC2COPY_TI_PARAMS;
    }

    obj->outputChromaFormat = params->forceChromaFormat;

    return (IALG_EOK);
}


/*
 *  ======== VIDDEC2COPY_TI_process ========
 */
XDAS_Int32 VIDDEC2COPY_TI_process(IVIDDEC2_Handle h, XDM1_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDDEC2_InArgs *inArgs, IVIDDEC2_OutArgs *outArgs)
{
    XDAS_Int32 numInBytes;

    /* validate arguments - this codec only supports "base" xDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
        (outArgs->size != sizeof(*outArgs))) {

        outArgs->decodedBufs.extendedError = XDM_UNSUPPORTEDPARAM;

        return (IVIDDEC2_EUNSUPPORTED);
    }

    /* validate that there's at least a single inBuf and outBuf */
    if ((inBufs->numBufs < 1) || (outBufs->numBufs < 1)) {

        outArgs->decodedBufs.extendedError = XDM_UNSUPPORTEDPARAM;

        return (IVIDDEC2_EFAIL);
    }

    numInBytes = inArgs->numBytes;

    /*
     * Sanity check that inBufs->descs[0].bufSize is really capable of holding
     * numInBytes bytes of data, and that outBufs->bufSizes[0]
     * can hold the 'encoded' data.
     */
    if ((inBufs->descs[0].bufSize < inArgs->numBytes) ||
        (outBufs->bufSizes[0] < MINOUTBUFSIZE)){

        /* inBuf is smaller than provided data(!) or "too small" outBuf */
        outArgs->decodedBufs.extendedError = XDM_UNSUPPORTEDPARAM;

        return (IVIDDEC2_EFAIL);
    }

    /* everything looks good, do the 'encode', set outArgs and return */
    memcpy(outBufs->bufs[0], inBufs->descs[0].buf, numInBytes);

    /* report _how_ we accessed the input buffer */
    XDM_CLEARACCESSMODE_WRITE(inBufs->descs[0].accessMask);
    XDM_SETACCESSMODE_READ(inBufs->descs[0].accessMask);


    /* outArgs->bytesConsumed reports the total number of bytes decoded */
    outArgs->bytesConsumed = numInBytes;

    /* Fill out the rest of the outArgs struct */
    outArgs->outputID[0] = inArgs->inputID;
    outArgs->outputID[1] = 0;  /* end of array - invalid ID */

    outArgs->decodedBufs.numBufs = 1;
    outArgs->decodedBufs.frameWidth = numInBytes; /* minBytes wide */
    outArgs->decodedBufs.frameHeight = 1;       /* one pixel high */
    outArgs->decodedBufs.framePitch = 0;        /* TODO */

    outArgs->decodedBufs.bufDesc[0].buf = outBufs->bufs[0];
    outArgs->decodedBufs.bufDesc[0].bufSize = outBufs->bufSizes[0];

    /* initialize the accessMask, then indicate how we accessed it */
    outArgs->decodedBufs.bufDesc[0].accessMask = 0;
    XDM_SETACCESSMODE_WRITE(outArgs->decodedBufs.bufDesc[0].accessMask);

    outArgs->decodedBufs.extendedError = 0;
    outArgs->decodedBufs.frameType = 0;         /* TODO */
    outArgs->decodedBufs.topFieldFirstFlag = XDAS_FALSE;  /* TODO */
    outArgs->decodedBufs.repeatFirstFieldFlag = XDAS_FALSE;  /* TODO */
    outArgs->decodedBufs.frameStatus = IVIDEO_FRAME_NOERROR;
    outArgs->decodedBufs.repeatFrame = 0;  /* TODO */
    outArgs->decodedBufs.contentType = IVIDEO_PROGRESSIVE;
    outArgs->decodedBufs.chromaFormat = XDM_CHROMAFORMAT_DEFAULT;

    /* Single display buf equivalent to the decoded buf above */
    outArgs->displayBufs[0] = outArgs->decodedBufs;
    outArgs->displayBufs[1].numBufs = 0;   /* end of array */

    /* MB data support is TBD */
    outArgs->outputMbDataID = 0;  /* invalid ID */
    outArgs->mbDataBuf.buf = NULL;  /* important, set to NULL if no MB Data! */

    outArgs->freeBufID[0] = inArgs->inputID;  /* release the only outBuf */
    outArgs->freeBufID[1] = 0; /* end of array - invalid ID */
    outArgs->outBufsInUseFlag = XDAS_FALSE;

    return (IVIDDEC2_EOK);
}


/*
 *  ======== VIDDEC2COPY_TI_control ========
 */
XDAS_Int32 VIDDEC2COPY_TI_control(IVIDDEC2_Handle handle, IVIDDEC2_Cmd id,
    IVIDDEC2_DynamicParams *dynParams, IVIDDEC2_Status *status)
{
    XDAS_Int32 retVal;
    VIDDEC2COPY_TI_Obj *obj = (VIDDEC2COPY_TI_Obj *)handle;

    /* validate arguments - this codec only supports "base" xDM. */
    if ((dynParams->size != sizeof(*dynParams)) ||
        (status->size != sizeof(*status))) {

        return (IVIDDEC2_EUNSUPPORTED);
    }

    /* initialize for the general case where we don't access the data buffer */
    XDM_CLEARACCESSMODE_READ(status->data.accessMask);
    XDM_CLEARACCESSMODE_WRITE(status->data.accessMask);

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->extendedError = 0;
            status->outputHeight = 0;  /* TODO */
            status->outputWidth = 0;  /* TODO */
            status->frameRate = 0;  /* TODO */
            status->bitRate = 0;  /* TODO */
            status->contentType = 0;  /* TODO */
            status->outputChromaFormat = obj->outputChromaFormat;

            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = IVIDDEC2_EOK;
            break;

        case XDM_SETPARAMS:
            retVal = IVIDDEC2_EOK;
            break;

        case XDM_SETDEFAULT:
            obj->outputChromaFormat = VIDDEC2COPY_TI_PARAMS.forceChromaFormat;

            retVal = IVIDDEC2_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = IVIDDEC2_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.buf != NULL) &&
                (status->data.bufSize >= strlen(VIDDEC2_COPY_VERSIONSTRING))) {
                strncpy((char *)status->data.buf, VIDDEC2_COPY_VERSIONSTRING,
                    strlen(VIDDEC2_COPY_VERSIONSTRING));

                /* null terminate the string */
                status->data.buf[strlen(VIDDEC2_COPY_VERSIONSTRING)] = '\0';

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(status->data.accessMask);

                retVal = IVIDDEC2_EOK;
            }
            else {
                retVal = IVIDDEC2_EFAIL;
            }

            break;

        default:
            /* unsupported cmd */
            retVal = IVIDDEC2_EFAIL;

            break;
    }

    return (retVal);
}
/*
 *  @(#) ti.xdais.dm.examples.viddec2_copy; 2, 0, 0,21; 5-8-2008 09:07:08; /db/wtree/library/trees/dais-j06x/src/
 */

