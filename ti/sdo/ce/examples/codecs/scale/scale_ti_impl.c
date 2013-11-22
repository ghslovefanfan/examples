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
 *  ======== scale.c ========
 *  "Scale" algorithm.
 *
 *  This file contains an implementation of the IALG interface
 *  required by XDAS.
 */
#include <xdc/std.h>
#include <string.h>


#include "iscale.h"
#include "scale_ti.h"
#include "scale_ti_priv.h"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

extern IALG_Fxns SCALE_TI_IALG;

#define IALGFXNS  \
    &SCALE_TI_IALG,     /* module ID */                         \
    NULL,               /* activate */                          \
    SCALE_TI_alloc,     /* alloc */                             \
    NULL,               /* control (NULL => no control ops) */  \
    NULL,               /* deactivate */                        \
    SCALE_TI_free,      /* free */                              \
    SCALE_TI_initObj,   /* init */                              \
    NULL,               /* moved */                             \
    NULL                /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== SCALE_TI_ISCALE ========
 *  This structure defines TI's implementation of the ISCALE interface
 *  for the SCALE_TI module.
 */
ISCALE_Fxns SCALE_TI_SCALE = {
    {IALGFXNS},
    SCALE_TI_process,
    SCALE_TI_control,
};

/*
 *  ======== SCALE_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the SCALECOPY_TI module.
 */
#ifdef _TI_

asm("_SCALE_TI_IALG .set _SCALE_TI_SCALE");

#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns SCALE_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

/*
 *  ======== SCALE_TI_alloc ========
 */
Int SCALE_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(SCALE_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}

/*
 *  ======== SCALE_TI_free ========
 */
Int SCALE_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    SCALE_TI_alloc(NULL, NULL, memTab);
    return (1);
}

/*
 *  ======== SCALE_TI_initObj ========
 */
Int SCALE_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle p,
    const IALG_Params *algParams)
{
    SCALE_TI_Obj *inst = (SCALE_TI_Obj *)handle;
    ISCALE_Params *params = (ISCALE_Params *)algParams;

    if (params == NULL) {
        inst->scaleFactor = 1; /* default scale is 1 */
    }
    else {
        inst->scaleFactor = params->initialScaleFactor;
    }

    return (IALG_EOK);
}

/*
 *  ======== SCALE_TI_process ========
 */
XDAS_Int32 SCALE_TI_process(ISCALE_Handle handle, XDAS_Int8 *inBuf,
    XDAS_Int8 *outBuf, ISCALE_InArgs *inArgs, ISCALE_OutArgs *outArgs)
{
    XDAS_Int32 i;
    SCALE_TI_Obj *inst = (SCALE_TI_Obj *)handle;

    for (i = 0; i < inArgs->inBufValidBytes; i++) {
        outBuf[i] = inBuf[i] * inst->scaleFactor;
    }

    /* Fill outArgs */
    outArgs->outBufValidBytes = i;

    return (ISCALE_EOK);
}

/*
 *  ======== SCALE_TI_control ========
 */
XDAS_Int32 SCALE_TI_control(ISCALE_Handle handle, ISCALE_Cmd id,
    ISCALE_DynamicParams *params)
{
    XDAS_Int32 retVal;
    SCALE_TI_Obj *inst = (SCALE_TI_Obj *)handle;

    switch (id) {
        case ISCALE_SETPARAMS:
            inst->scaleFactor = params->scaleFactor;

            retVal = ISCALE_EOK;

            break;

        default:
            /* unsupported cmd */
            retVal = ISCALE_EFAIL;

            break;
    }

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.scale; 1,0,0,131; 9-9-2008 02:03:08; /db/atree/library/trees/ce-h27x/src/
 */

