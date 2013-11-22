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
 *  ======== sphenc1_copy.c ========
 *  Speech encoder "copy" algorithm, PCM codec family.
 *
 *  This file contains an implementation of the ISPHENC1 interface
 *  defined by xDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/isphenc1.h>
#include <ti/xdais/dm/ispeech1_pcm.h>

#ifdef __TI_COMPILER_VERSION__
/* xDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(SPHENC1COPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(SPHENC1COPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(SPHENC1COPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(SPHENC1COPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(SPHENC1COPY_TI_alloc,   ".text:algAlloc")
#endif

#include "sphenc1_copy_ti.h"
#include "sphenc1_copy_ti_priv.h"

/* TODO, need to autogenerate this */
#define SPHENC1_COPY_VERSIONSTRING "1.00.00.0"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

extern IALG_Fxns SPHENC1COPY_TI_IALG;

#define IALGFXNS  \
    &SPHENC1COPY_TI_IALG,       /* module ID */                         \
    NULL,                       /* activate */                          \
    SPHENC1COPY_TI_alloc,       /* alloc */                             \
    NULL,                       /* control (NULL => no control ops) */  \
    NULL,                       /* deactivate */                        \
    SPHENC1COPY_TI_free,        /* free */                              \
    SPHENC1COPY_TI_initObj,     /* init */                              \
    NULL,                       /* moved */                             \
    NULL                        /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== SPHENC1COPY_TI_ISPHENCCOPY ========
 *  This structure defines TI's implementation of the ISPHENC1 interface
 *  for the SPHENC1COPY_TI module.
 */
ISPHENC1_Fxns SPHENC1COPY_TI_ISPHENC1COPY = { /* module_vendor_interface */
    {IALGFXNS},
    SPHENC1COPY_TI_process,
    SPHENC1COPY_TI_control,
};

/*
 *  ======== SPHENC1COPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the SPHENC1COPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy xDAIS symbol requirement without any overhead */
asm("_SPHENC1COPY_TI_IALG .set _SPHENC1COPY_TI_ISPHENC1COPY");

#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns SPHENC1COPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

ISPHENC1_Params SPHENC1COPY_TI_PARAMS = {
    sizeof(ISPHENC1_Params),
    0,                          /* frameSize isn't relevant for copy codecs */
    ISPEECH1_PCM_COMPAND_DEFAULT,
    0,                          /* packingType is a don't care for PCM */
    0,                          /* vadSelection is a don't care for PCM */
    0,                          /* codecSelection is a don't care for PCM */
    0,                          /* bitRate is a don't care for PCM */
    0,                          /* reserved */
    NULL
};

/*
 *  ======== SPHENC1COPY_TI_alloc ========
 */
Int SPHENC1COPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(SPHENC1COPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}


/*
 *  ======== SPHENC1COPY_TI_free ========
 */
Int SPHENC1COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    return (SPHENC1COPY_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== SPHENC1COPY_TI_initObj ========
 */
Int SPHENC1COPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle p, const IALG_Params *algParams)
{
    SPHENC1COPY_TI_Obj *obj = (SPHENC1COPY_TI_Obj *)handle;
    const ISPHENC1_Params *params = (ISPHENC1_Params *)algParams;

    /*
     * In lieu of xDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &SPHENC1COPY_TI_PARAMS;
    }

    obj->frameSize = params->frameSize;
    obj->compandingLaw = params->compandingLaw;
    obj->packingType = params->packingType;         /* doesn't matter for PCM */
    obj->vadSelection = params->vadSelection;       /* doesn't matter for PCM */
    obj->codecSelection = params->codecSelection;   /* doesn't matter for PCM */
    obj->bitRate = params->bitRate;                 /* doesn't matter for PCM */

    obj->mode = 0;                                  /* doesn't matter for PCM */
    obj->vadFlag = ISPEECH1_VADFLAG_DEFAULT;
    obj->noiseSuppressionMode = 0;                  /* doesn't matter for PCM */
    obj->ttyTddMode = 0;                            /* doesn't matter for PCM */
    obj->dtmfMode = 0;                              /* doesn't matter for PCM */
    obj->dataTransmit = 0;                          /* doesn't matter for PCM */

    return (IALG_EOK);
}


/*
 *  ======== SPHENC1COPY_TI_process ========
 */
XDAS_Int32 SPHENC1COPY_TI_process(ISPHENC1_Handle h,
    XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf,
    ISPHENC1_InArgs *inArgs, ISPHENC1_OutArgs *outArgs)
{
    int  numBytes;

    /* validate arguments - this codec only supports "base" xDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
        (outArgs->size != sizeof(*outArgs))) {

        outArgs->extendedError = XDM_UNSUPPORTEDPARAM;

        return (ISPHENC1_EUNSUPPORTED);
    }

    /*
     * The number of bytes we can encode is the lesser of the specified
     * number of bytes to encode (inBuf->bufSize) and the size of the
     * buffer that will contain the output (outBuf->bufSize).
     */
    numBytes = (inBuf->bufSize <= outBuf->bufSize) ?
        inBuf->bufSize : outBuf->bufSize;

    /* process the data: read input, produce output */
    memcpy(outBuf->buf, inBuf->buf, numBytes);

    /* report _how_ we accessed the 2 data buffers */
    XDM_CLEARACCESSMODE_WRITE(inBuf->accessMask);
    XDM_SETACCESSMODE_READ(inBuf->accessMask);

    XDM_CLEARACCESSMODE_READ(outBuf->accessMask);
    XDM_SETACCESSMODE_WRITE(outBuf->accessMask);

    /* Fill out the rest of the outArgs struct */
    outArgs->frameType = ISPHENC1_FTYPE_SPEECH;
    outArgs->extendedError = 0;

    return (ISPHENC1_EOK);
}


/*
 *  ======== SPHENC1COPY_TI_control ========
 */
XDAS_Int32 SPHENC1COPY_TI_control(ISPHENC1_Handle handle, ISPHENC1_Cmd id,
    ISPHENC1_DynamicParams *dynParams, ISPHENC1_Status *status)
{
    XDAS_Int32 retVal;
    SPHENC1COPY_TI_Obj *obj = (SPHENC1COPY_TI_Obj *)handle;

    /* validate arguments - this codec only supports "base" xDM. */
    if ((dynParams->size != sizeof(*dynParams)) ||
        (status->size != sizeof(*status))) {

        return (ISPHENC1_EUNSUPPORTED);
    }

    /* initialize for the general case where we don't access the data buffer */
    XDM_CLEARACCESSMODE_READ(status->data.accessMask);
    XDM_CLEARACCESSMODE_WRITE(status->data.accessMask);

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->frameSize = obj->frameSize;
            status->extendedError = 0;
            status->bitRate = obj->bitRate;
            status->mode = obj->mode;
            status->vadFlag = obj->vadFlag;
            status->noiseSuppressionMode = obj->noiseSuppressionMode;
            status->ttyTddMode = obj->ttyTddMode;
            status->dataTransmit = obj->dataTransmit;
            status->compandingLaw = obj->compandingLaw;
            status->packingType = obj->packingType;
            status->vadSelection = obj->vadSelection;
            status->codecSelection = obj->codecSelection;

            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = ISPHENC1_EOK;

            break;

        case XDM_SETPARAMS:
            obj->frameSize = dynParams->frameSize;
            obj->bitRate = dynParams->bitRate;
            obj->mode = dynParams->mode;
            obj->vadFlag = dynParams->vadFlag;
            obj->noiseSuppressionMode = dynParams->noiseSuppressionMode;
            obj->ttyTddMode = dynParams->ttyTddMode;
            obj->dtmfMode = dynParams->dtmfMode;
            obj->dataTransmit = dynParams->dataTransmit;

            retVal = ISPHENC1_EOK;
            break;

        case XDM_SETDEFAULT:
            /* should validate these rather than blindly assign them! */
            obj->frameSize = SPHENC1COPY_TI_PARAMS.frameSize;
            obj->compandingLaw = SPHENC1COPY_TI_PARAMS.compandingLaw;
            obj->packingType = SPHENC1COPY_TI_PARAMS.packingType;
            obj->vadSelection = SPHENC1COPY_TI_PARAMS.vadSelection;
            obj->codecSelection = SPHENC1COPY_TI_PARAMS.codecSelection;

            obj->bitRate = 0;                   /* doesn't matter for PCM */
            obj->mode = 0;                      /* doesn't matter for PCM */
            obj->vadFlag = ISPEECH1_VADFLAG_DEFAULT;
            obj->noiseSuppressionMode = 0;      /* doesn't matter for PCM */
            obj->ttyTddMode = 0;                /* doesn't matter for PCM */
            obj->dtmfMode = 0;                  /* doesn't matter for PCM */
            obj->dataTransmit = 0;              /* doesn't matter for PCM */

            retVal = ISPHENC1_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = ISPHENC1_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.buf != NULL) &&
                (status->data.bufSize >= strlen(SPHENC1_COPY_VERSIONSTRING))) {
                strncpy((char *)status->data.buf, SPHENC1_COPY_VERSIONSTRING,
                    strlen(SPHENC1_COPY_VERSIONSTRING));

                /* null terminate the string */
                status->data.buf[strlen(SPHENC1_COPY_VERSIONSTRING)] = '\0';

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(status->data.accessMask);

                retVal = ISPHENC1_EOK;
            }
            else {
                retVal = ISPHENC1_EFAIL;
            }

            break;

        default:
            /* unsupported cmd */
            retVal = ISPHENC1_EFAIL;

            break;
    }

    return (retVal);
}
/*
 *  @(#) ti.xdais.dm.examples.sphenc1_copy; 2, 0, 0,122; 5-8-2008 09:06:37; /db/wtree/library/trees/dais-j06x/src/
 */

