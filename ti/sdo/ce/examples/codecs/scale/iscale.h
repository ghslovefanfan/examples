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
 *  ======== iscale.h ========
 *  The scale interface.
 */

#ifndef codecs_scale_ISCALE_H_
#define codecs_scale_ISCALE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/xdas.h>
#include <ti/xdais/ialg.h>

#define ISCALE_EOK      0
#define ISCALE_EFAIL    -1
#define ISCALE_ERUNTIME -2

/**
 *  @brief      This must be the first field of all ISCALE instance objects.
 */
typedef struct ISCALE_Obj {
    struct ISCALE_Fxns *fxns;
} ISCALE_Obj;

/**
 *  @brief      Opaque handle to an ISCALE object.
 */
typedef struct ISCALE_Obj *ISCALE_Handle;


typedef struct ISCALE_Params {
    XDAS_Int32 size;                /* size of this structure, in bytes */
    XDAS_Int32 initialScaleFactor;  /* default scaling factor */
} ISCALE_Params;

typedef struct ISCALE_InArgs {
    XDAS_Int32 inBufSize;
    XDAS_Int32 outBufSize;
    XDAS_Int32 inBufValidBytes;
} ISCALE_InArgs;

typedef struct ISCALE_OutArgs {
    XDAS_Int32 outBufValidBytes;
} ISCALE_OutArgs;

typedef IALG_Cmd ISCALE_Cmd;

#define ISCALE_SETPARAMS 0       /* only cmd we support */

typedef struct ISCALE_DynamicParams {
    XDAS_Int32 scaleFactor;     /* we only scale up */
} ISCALE_DynamicParams;

typedef struct ISCALE_Fxns{
    IALG_Fxns   ialg;
    XDAS_Int32 (*process)(ISCALE_Handle handle, XDAS_Int8 *inBuf,
        XDAS_Int8 *outBuf, ISCALE_InArgs *inArgs, ISCALE_OutArgs *outArgs);
    XDAS_Int32 (*control)(ISCALE_Handle handle, ISCALE_Cmd id,
        ISCALE_DynamicParams *params);
} ISCALE_Fxns;


#ifdef __cplusplus
}
#endif

/*@}*/  /* ingroup */

#endif
/*
 *  @(#) ti.sdo.ce.examples.codecs.scale; 1,0,0,131; 9-9-2008 02:03:08; /db/atree/library/trees/ce-h27x/src/
 */

