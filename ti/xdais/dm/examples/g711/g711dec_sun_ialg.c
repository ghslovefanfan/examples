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
 *  ======== g711dec_sun_ialg.c ========
 *  Implementation of the G711DEC_SUN.h interface; SUN's implementation
 *  of the ISPHDEC1 interface defined by xDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/isphdec1.h>
#include <ti/xdais/dm/ispeech1_pcm.h>

#ifdef __TI_COMPILER_VERSION__
/* xDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(G711DEC_SUN_control, ".text:algControl")
#pragma CODE_SECTION(G711DEC_SUN_decode,  ".text:algProcess")
#pragma CODE_SECTION(G711DEC_SUN_initObj, ".text:algInit")
#pragma CODE_SECTION(G711DEC_SUN_free,    ".text:algFree")
#pragma CODE_SECTION(G711DEC_SUN_alloc,   ".text:algAlloc")
#endif

#include "g711dec_sun.h"
#include "g711_sun_internal.h"
#include "g711dec_sun_priv.h"

/* TODO, need to autogenerate this */
#define G711DEC_SUN_VERSIONSTRING "1.00.00.0"

typedef short (*DecodeFxn)(unsigned char);

/*
 *  ======== G711DEC_SUN_Obj ========
 */
typedef struct G711DEC_SUN_Obj {
    IALG_Obj alg;              /* MUST be first field of all xDAIS inst objs */
    DecodeFxn fxn;             /* dynamically set to u-law or a-law */
    Int frameLen;              /* frame length in samples. */
    XDAS_Int16 compandingLaw;  /* companding setting. */
} G711DEC_SUN_Obj;

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    sizeof(char)
#define MINOUTBUFSIZE   sizeof(short)

extern IALG_Fxns G711DEC_SUN_IALG;

#define IALGFXNS \
    &G711DEC_SUN_IALG,  /* module ID */                         \
    NULL,               /* activate */                          \
    G711DEC_SUN_alloc,  /* algAlloc */                          \
    NULL,               /* control (NULL => no control ops) */  \
    NULL,               /* deactivate */                        \
    G711DEC_SUN_free,   /* free */                              \
    G711DEC_SUN_initObj,/* init */                              \
    NULL,               /* moved */                             \
    NULL                /* numAlloc */

/*
 *  ======== G711DEC_SUN_IG711DEC ========
 *  This structure defines SUN's implementation of the IG711 interface
 *  for the G711DEC_SUN module.
 */
ISPHDEC1_Fxns G711DEC_SUN_IG711DEC = {  /* module_vendor_interface */
    {IALGFXNS},
    G711DEC_SUN_decode,
    G711DEC_SUN_control,
};

/*
 *  ======== G711DEC_SUN_IALG ========
 *  This structure defines SUN's implementation of the IALG interface
 *  for the G711DEC_SUN module.
 */
#ifdef _TI_

asm("_G711DEC_SUN_IALG .set _G711DEC_SUN_IG711DEC");

#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns G711DEC_SUN_IALG = {  /* module_vendor_interface */
    IALGFXNS
};

#endif

ISPHDEC1_Params G711DEC_SUN_PARAMS = {
    sizeof(ISPHDEC1_Params),
    ISPEECH1_PCM_COMPAND_ALAW,  /* a-law companding */
    0,                          /* packingType is a don't care for PCM */
    0,                          /* codecSelection is a don't care for PCM */
    0,                          /* bitRate is a don't care for PCM */
    0,                          /* reserved */
    NULL                        /* tablesPtr isn't supported */
};

/*
 *  ======== G711DEC_SUN_alloc ========
 *  Return a table of memory descriptors that describe the memory needed
 *  to construct a G711DEC_SUN_Obj structure.
 */
Int G711DEC_SUN_alloc(const IALG_Params *g711Params, IALG_Fxns **pf,
    IALG_MemRec memTab[])
{
    /* Request memory for G711 object */
    memTab[0].size = sizeof(G711DEC_SUN_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}


/*
 *  ======== G711DEC_SUN_free ========
 *  Return a table of memory pointers that should be freed.  Note
 *  that this should include *all* memory requested in the
 *  G711DEC_SUN_alloc operation above.
 */
Int G711DEC_SUN_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    Int n;

    n = G711DEC_SUN_alloc(NULL, NULL, memTab);

    return (n);
}


/*
 *  ======== G711DEC_SUN_initObj ========
 *  Initialize the memory allocated on our behalf (including our object).
 */
Int G711DEC_SUN_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle p, const IALG_Params *algParams)
{
    G711DEC_SUN_Obj *g711Dec = (Void *)handle;
    const ISPHDEC1_Params *params = (ISPHDEC1_Params *)algParams;
    Int status = IALG_EOK;

    /*
     * In lieu of xDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &G711DEC_SUN_PARAMS;
    }

    switch (params->compandingLaw) {
        case ISPEECH1_PCM_COMPAND_ALAW:
            g711Dec->fxn = G711_SUN_alaw2linear;
            g711Dec->compandingLaw = ISPEECH1_PCM_COMPAND_ALAW;
            break;

        case ISPEECH1_PCM_COMPAND_ULAW:
            g711Dec->fxn = G711_SUN_ulaw2linear;
            g711Dec->compandingLaw = ISPEECH1_PCM_COMPAND_ULAW;
            break;

        default:
            status = IALG_EFAIL;
            break;
    }
    
    return (status);
}


/*
 *  ======== G711DEC_SUN_decode ========
 *
 *  G711DEC_SUN_decode - implements ISPHDEC1::process() function.
 */
XDAS_Int32 G711DEC_SUN_decode(ISPHDEC1_Handle handle,
    XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf,
    ISPHDEC1_InArgs *inArgs, ISPHDEC1_OutArgs *outArgs)
{
    G711DEC_SUN_Obj *g711Dec = (Void *)handle;
    Int i;

    short * out        = (short *)outBuf->buf;
    unsigned char * in = (unsigned char *)inBuf->buf;

    Int frameLen = inBuf->bufSize;

    /* validate arguments - this codec only supports "base" xDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
        (outArgs->size != sizeof(*outArgs))) {

        outArgs->extendedError = XDM_UNSUPPORTEDPARAM;

        return (ISPHDEC1_EUNSUPPORTED);
    }

    /* validate arguments - outBuf needs to be big enough to hold output */
    if (outBuf->bufSize < (frameLen * sizeof(char))) {
        outArgs->extendedError = XDM_INSUFFICIENTDATA;

        return (ISPHDEC1_EFAIL);
    }

    /* process the data: read input, produce output */
    for (i = 0; i < frameLen; i++) {
        *out++ = g711Dec->fxn(*in++);
    }

    /* report how large, in 8-bit bytes, the decoded outBuf buffer is */
    outBuf->bufSize = frameLen * sizeof(short);

    /* report _how_ we accessed the 2 data buffers */
    XDM_CLEARACCESSMODE_WRITE(inBuf->accessMask);
    XDM_SETACCESSMODE_READ(inBuf->accessMask);

    XDM_CLEARACCESSMODE_READ(outBuf->accessMask);
    XDM_SETACCESSMODE_WRITE(outBuf->accessMask);

    /* Fill out the rest of the outArgs struct */
    outArgs->dataSize = 0;   /* not used in PCM codecs */
    outArgs->extendedError = 0;

    return (ISPHDEC1_EOK);
}


/*
 *  ======== G711DEC_SUN_control ========
 */
XDAS_Int32 G711DEC_SUN_control(ISPHDEC1_Handle handle, ISPHDEC1_Cmd id,
    ISPHDEC1_DynamicParams *dynParams, ISPHDEC1_Status *status)
{
    XDAS_Int32 retVal;
    G711DEC_SUN_Obj *obj = (G711DEC_SUN_Obj *)handle;

    /* validate arguments - this codec only supports "base" xDM. */
    if ((dynParams->size != sizeof(*dynParams)) ||
        (status->size != sizeof(*status))) {

        if ((status->size) >= sizeof(*status)) {
            /* yeah, it may be extended, but if it's "big enough" set the bit */
            XDM_SETUNSUPPORTEDPARAM(status->extendedError);
        }
        return (ISPHDEC1_EUNSUPPORTED);
    }

    /* Think positive... */
    status->extendedError = 0;

    /* initialize for the general case where we don't access the data buffer */
    XDM_CLEARACCESSMODE_READ(status->data.accessMask);
    XDM_CLEARACCESSMODE_WRITE(status->data.accessMask);

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->postFilter = ISPEECH1_POSTFILTER_OFF;
            status->compandingLaw = obj->compandingLaw;

            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = ISPHDEC1_EOK;

            break;

        case XDM_SETPARAMS:
            if (dynParams->postFilter == ISPEECH1_POSTFILTER_ON) {
                retVal = ISPHDEC1_EUNSUPPORTED;
            }
            else {
                retVal = ISPHDEC1_EOK;
            }
            break;

        case XDM_SETDEFAULT:
            obj->fxn = G711_SUN_alaw2linear;
            obj->compandingLaw = ISPEECH1_PCM_COMPAND_ALAW;

            retVal = ISPHDEC1_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = ISPHDEC1_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.buf != NULL) &&
                (status->data.bufSize >= strlen(G711DEC_SUN_VERSIONSTRING))) {
                strncpy((char *)status->data.buf, G711DEC_SUN_VERSIONSTRING,
                    strlen(G711DEC_SUN_VERSIONSTRING));

                /* null terminate the string */
                status->data.buf[strlen(G711DEC_SUN_VERSIONSTRING)] = '\0';

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
 *  @(#) ti.xdais.dm.examples.g711; 1, 0, 0,131; 5-8-2008 09:06:05; /db/wtree/library/trees/dais-j06x/src/
 */

