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
 *  ======== auddec_copy.c ========
 *  Audio decoder "copy" algorithm.
 *
 *  This file contains an implementation of the IAUDDEC interface
 *  defined by xDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/iauddec.h>

#ifdef __TI_COMPILER_VERSION__
/* xDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(AUDDECCOPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(AUDDECCOPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(AUDDECCOPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(AUDDECCOPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(AUDDECCOPY_TI_alloc,   ".text:algAlloc")
#endif

#include "auddec_copy_ti.h"
#include "auddec_copy_ti_priv.h"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

extern IALG_Fxns AUDDECCOPY_TI_IALG;

#define IALGFXNS  \
    &AUDDECCOPY_TI_IALG,/* module ID */                         \
    NULL,               /* activate */                          \
    AUDDECCOPY_TI_alloc,/* alloc */                             \
    NULL,               /* control (NULL => no control ops) */  \
    NULL,               /* deactivate */                        \
    AUDDECCOPY_TI_free, /* free */                              \
    AUDDECCOPY_TI_initObj, /* init */                              \
    NULL,               /* moved */                             \
    NULL                /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== AUDDECCOPY_TI_AUDDECCOPY ========
 *  This structure defines TI's implementation of the IAUDDEC interface
 *  for the AUDDECCOPY_TI module.
 */
IAUDDEC_Fxns AUDDECCOPY_TI_IAUDDECCOPY = {    /* module_vendor_interface */
    {IALGFXNS},
    AUDDECCOPY_TI_process,
    AUDDECCOPY_TI_control,
};

/*
 *  ======== AUDDECCOPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the AUDDECCOPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__

asm("_AUDDECCOPY_TI_IALG .set _AUDDECCOPY_TI_IAUDDECCOPY");

#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns AUDDECCOPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

/*
 *  ======== AUDDECCOPY_TI_alloc ========
 */
Int AUDDECCOPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(AUDDECCOPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}

/*
 *  ======== AUDDECCOPY_TI_free ========
 */
Int AUDDECCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    return (AUDDECCOPY_TI_alloc(NULL, NULL, memTab));
}

/*
 *  ======== AUDDECCOPY_TI_initObj ========
 */
Int AUDDECCOPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle p, const IALG_Params *algParams)
{
    return (IALG_EOK);
}

/*
 *  ======== AUDDECCOPY_TI_process ========
 */
XDAS_Int32 AUDDECCOPY_TI_process(IAUDDEC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IAUDDEC_InArgs *inArgs, IAUDDEC_OutArgs *outArgs)
{
    /* validate arguments - this codec only supports "base" xDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
        (outArgs->size != sizeof(*outArgs))) {

        outArgs->extendedError = XDM_UNSUPPORTEDPARAM;

        return (IAUDDEC_EFAIL);
    }

    /* validate that there's at least a single inBuf and outBuf */
    if ((inBufs->numBufs < 1) || (outBufs->numBufs < 1)) {

        outArgs->extendedError = XDM_UNSUPPORTEDPARAM;

        return (IAUDDEC_EFAIL);
    }

    /*
     * The number of bytes we can consume is the lesser of the specified
     * number of bytes to decode (inArgs->numBytes) and the size of the
     * buffer that will contain the output (outBufs->bufSizes[0]).
     */
    outArgs->bytesConsumed = (inArgs->numBytes <= outBufs->bufSizes[0]) ?
        inArgs->numBytes : outBufs->bufSizes[0];

    /* process the data: read input, produce output */
    memcpy(outBufs->bufs[0], inBufs->bufs[0], outArgs->bytesConsumed);

    /* Fill out the rest of the outArgs struct */
    outArgs->extendedError = 0;

    return (IAUDDEC_EOK);
}

/*
 *  ======== AUDDECCOPY_TI_control ========
 */
XDAS_Int32 AUDDECCOPY_TI_control(IAUDDEC_Handle handle, IAUDDEC_Cmd id,
    IAUDDEC_DynamicParams *params, IAUDDEC_Status *status)
{
    XDAS_Int32 retVal;

    /* validate arguments - this codec only supports "base" xDM. */
    if ((params->size != sizeof(*params)) ||
        (status->size != sizeof(*status))) {

        return (IAUDDEC_EFAIL);
    }

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->extendedError = 0;
            status->bitRate = 0;  /* TODO */
            status->sampleRate = 0;  /* TODO */
            status->numChannels = 0;  /* TODO */
            status->numLFEChannels = 0;  /* TODO */
            status->outputFormat = 0;  /* TODO */
            status->autoPosition = 0;  /* TODO */
            status->fastFwdLen = 0;  /* TODO */
            status->frameLen = 0;  /* TODO */
            status->outputBitsPerSample = 0;  /* TODO */
            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = IAUDDEC_EOK;

            break;

        case XDM_SETPARAMS:
        case XDM_SETDEFAULT:
            /* Not really supported, TBD.  But, we return success anyway... */
            retVal = IAUDDEC_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = IAUDDEC_EOK;
            break;

        default:
            /* unsupported cmd */
            retVal = IAUDDEC_EFAIL;

            break;
    }

    return (retVal);
}
/*
 *  @(#) ti.xdais.dm.examples.auddec_copy; 2, 0, 0,136; 5-8-2008 09:05:57; /db/wtree/library/trees/dais-j06x/src/
 */

