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
 *  ======== auddec1_ti.h ========
 *  Interface for the audio decoder copy example that uses an example IRES
 *  resource. This example exposes both an IAUDDEC1_Fxns interface and an
 *  IRES_Fxns interface.
 */
#ifndef AUDDEC1_TI_
#define AUDDEC1_TI_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== AUDDEC1_TI_AUDDECIRES ========
 *  Our implementation of the IAUDDEC1 interface
 */
extern IAUDDEC1_Fxns AUDDEC1_TI_AUDDECIRES;

/*
 *  ======== AUDDEC1_TI_IRES ========
 *  Our implementation of the IRES_Fxns interface
 */
extern IRES_Fxns AUDDEC1_TI_IRES;


/*
 *  ======== AUDDEC1_TI_PARAMS ========
 */
extern IAUDDEC1_Params AUDDEC1_TI_PARAMS;


#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.auddec1; 1, 0, 0,81; 9-9-2008 23:52:59; /db/atree/library/trees/fc-e20x/src/
 */

