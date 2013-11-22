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
 *  ======== sphdec1_copy.c ========
 *  Speech decoder "copy" algorithm, PCM codec family.
 *
 *  This file contains an implementation of the ISPHDEC1 interface
 *  defined by xDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/isphdec1.h>
#include <ti/xdais/dm/ispeech1_pcm.h>

#ifdef __TI_COMPILER_VERSION__
/* xDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(SPHDEC1COPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(SPHDEC1COPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(SPHDEC1COPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(SPHDEC1COPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(SPHDEC1COPY_TI_alloc,   ".text:algAlloc")
#endif

#include "sphdec1_copy_ti.h"
#include "sphdec1_copy_ti_priv.h"

/* TODO, need to autogenerate this */
#define SPHDEC1_COPY_VERSIONSTRING "1.00.00.0"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

extern IALG_Fxns SPHDEC1COPY_TI_IALG;

#define IALGFXNS  \
    &SPHDEC1COPY_TI_IALG,       /* module ID */                         \
    NULL,                       /* activate */                          \
    SPHDEC1COPY_TI_alloc,       /* alloc */                             \
    NULL,                       /* control (NULL => no control ops) */  \
    NULL,                       /* deactivate */                        \
    SPHDEC1COPY_TI_free,        /* free */                              \
    SPHDEC1COPY_TI_initObj,     /* init */                              \
    NULL,                       /* moved */                             \
    NULL                        /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== SPHDEC1COPY_TI_ISPHDECCOPY ========
 *  This structure defines TI's implementation of the ISPHDEC1 interface
 *  for the SPHDEC1COPY_TI module.
 */
ISPHDEC1_Fxns SPHDEC1COPY_TI_ISPHDEC1COPY = { /* module_vendor_interface */
    {IALGFXNS},
    SPHDEC1COPY_TI_process,
    SPHDEC1COPY_TI_control,
};

/*
 *  ======== SPHDEC1COPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the SPHDEC1COPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy xDAIS symbol requirement without any overhead */
asm("_SPHDEC1COPY_TI_IALG .set _SPHDEC1COPY_TI_ISPHDEC1COPY");

#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns SPHDEC1COPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

ISPHDEC1_Params SPHDEC1COPY_TI_PARAMS = {
    sizeof(ISPHDEC1_Params),
    ISPEECH1_PCM_COMPAND_DEFAULT,
    0,                              /* packingType is a don't care for PCM */
    0,                              /* codecSelect is a don't care for PCM */
    0,                              /* bitRate is a don't care for PCM */
    0,                              /* reserved */
    NULL
};

/*
 *  ======== SPHDEC1COPY_TI_alloc ========
 */
Int SPHDEC1COPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(SPHDEC1COPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}


/*
 *  ======== SPHDEC1COPY_TI_free ========
 */
Int SPHDEC1COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    return(SPHDEC1COPY_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== SPHDEC1COPY_TI_initObj ========
 */
Int SPHDEC1COPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle p, const IALG_Params *algParams)
{
    SPHDEC1COPY_TI_Obj *obj = (SPHDEC1COPY_TI_Obj *)handle;
    const ISPHDEC1_Params *params = (ISPHDEC1_Params *)algParams;

    /*
     * In lieu of xDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &SPHDEC1COPY_TI_PARAMS;
    }

    obj->compandingLaw = params->compandingLaw;
    obj->packingType = params->packingType;
    obj->codecSelection = params->codecSelection;
    obj->postFilter = ISPEECH1_POSTFILTER_DEFAULT;
    obj->bitRate = params->bitRate;

    return (IALG_EOK);
}


/*
 *  ======== SPHDEC1COPY_TI_process ========
 */
XDAS_Int32 SPHDEC1COPY_TI_process(ISPHDEC1_Handle h,
    XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf,
    ISPHDEC1_InArgs *inArgs, ISPHDEC1_OutArgs *outArgs)
{
    XDAS_Int32 numInBytes;

    /* validate arguments - this codec only supports "base" xDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
        (outArgs->size != sizeof(*outArgs))) {

        outArgs->extendedError = XDM_UNSUPPORTEDPARAM;

        return (ISPHDEC1_EUNSUPPORTED);
    }

    /*
     * The number of bytes we can consume is the lesser of the specified
     * number of bytes to decode (inBuf->bufSize) and the size of the
     * buffer that will contain the output (outBuf->bufSize).
     */
    numInBytes = (inBuf->bufSize <= outBuf->bufSize) ?
        inBuf->bufSize : outBuf->bufSize;

    /* process the data: read input, produce output */
    memcpy(outBuf->buf, inBuf->buf, numInBytes);

    /* report _how_ we accessed the 2 data buffers */
    XDM_CLEARACCESSMODE_WRITE(inBuf->accessMask);
    XDM_SETACCESSMODE_READ(inBuf->accessMask);

    XDM_CLEARACCESSMODE_READ(outBuf->accessMask);
    XDM_SETACCESSMODE_WRITE(outBuf->accessMask);

    /* Fill out the rest of the outArgs struct */
    outArgs->dataSize = 0;  /* TBD */
    outArgs->extendedError = 0;

    return (ISPHDEC1_EOK);
}


/*
 *  ======== SPHDEC1COPY_TI_control ========
 */
XDAS_Int32 SPHDEC1COPY_TI_control(ISPHDEC1_Handle handle, ISPHDEC1_Cmd id,
    ISPHDEC1_DynamicParams *dynParams, ISPHDEC1_Status *status)
{
    XDAS_Int32 retVal;
    SPHDEC1COPY_TI_Obj *obj = (SPHDEC1COPY_TI_Obj *)handle;

    /* validate arguments - this codec only supports "base" xDM. */
    if ((dynParams->size != sizeof(*dynParams)) ||
        (status->size != sizeof(*status))) {

        return (ISPHDEC1_EUNSUPPORTED);
    }

    /* initialize for the general case where we don't access the data buffer */
    XDM_CLEARACCESSMODE_READ(status->data.accessMask);
    XDM_CLEARACCESSMODE_WRITE(status->data.accessMask);

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->postFilter = obj->postFilter;
            status->extendedError = 0;
            status->compandingLaw = obj->compandingLaw;
            status->packingType = obj->packingType;
            status->codecSelection = obj->codecSelection;
            status->bitRate = obj->bitRate;

            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = ISPHDEC1_EOK;
            break;

        case XDM_SETPARAMS:
            obj->postFilter = dynParams->postFilter;
            retVal = ISPHDEC1_EOK;
            break;

        case XDM_SETDEFAULT:
            obj->compandingLaw = SPHDEC1COPY_TI_PARAMS.compandingLaw;
            obj->packingType = SPHDEC1COPY_TI_PARAMS.packingType;
            obj->codecSelection = SPHDEC1COPY_TI_PARAMS.codecSelection;
            obj->postFilter = ISPEECH1_POSTFILTER_DEFAULT;

            retVal = ISPHDEC1_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = ISPHDEC1_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.buf != NULL) &&
                (status->data.bufSize >= strlen(SPHDEC1_COPY_VERSIONSTRING))) {
                strncpy((char *)status->data.buf, SPHDEC1_COPY_VERSIONSTRING,
                    strlen(SPHDEC1_COPY_VERSIONSTRING));

                /* null terminate the string */
                status->data.buf[strlen(SPHDEC1_COPY_VERSIONSTRING)] = '\0';

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(status->data.accessMask);

                retVal = ISPHDEC1_EOK;
            }
            else {
                retVal = ISPHDEC1_EFAIL;
            }

            break;

        default:
            /* unsupported cmd */
            retVal = ISPHDEC1_EFAIL;
            break;
    }

    return (retVal);
}
/*
 *  @(#) ti.xdais.dm.examples.sphdec1_copy; 2, 0, 0,130; 5-8-2008 09:06:21; /db/wtree/library/trees/dais-j06x/src/
 */

