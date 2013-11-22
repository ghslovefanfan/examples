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
 *  ======== _scale.h ========
 */
#ifndef extensions_scale__SCALE_H_
#define extensions_scale__SCALE_H_

#include <ti/sdo/ce/visa.h>
#include <scale.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _SCALE_CPROCESS        0
#define _SCALE_CCONTROL        1

/* msgq message to decode */
typedef struct {
    VISA_MsgHeader  visa;
    union {
        struct {
            XDAS_Int8           *inBuf;
            XDAS_Int8           *outBuf;
            SCALE_InArgs        inArgs;
            SCALE_OutArgs       outArgs;
        } process;
        struct {
            SCALE_Cmd           id;
            SCALE_DynamicParams params;
        } control;
    } cmd;
} _SCALE_Msg;

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.examples.extensions.scale; 1,0,0,131; 9-9-2008 02:04:04; /db/atree/library/trees/ce-h27x/src/
 */

