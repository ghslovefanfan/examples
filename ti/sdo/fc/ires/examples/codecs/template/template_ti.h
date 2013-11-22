/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== template_ti.h ========
 *  Interface for the audio decoder copy example that uses an example IRES
 *  resource. This example exposes both an ITEMPLATE_Fxns interface and an
 *  IRES_Fxns interface.
 */
#ifndef TEMPLATE_TI_
#define TEMPLATE_TI_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/sdo/fc/ires/examples/codecs/template/itemplate.h>

/*
 *  ======== TEMPLATE_TI_CODECIRES ========
 *  Our implementation of the ITEMPLATE interface
 */
extern ITEMPLATE_Fxns TEMPLATE_TI_CODECIRES;

/*
 *  ======== TEMPLATE_TI_IRES ========
 *  Our implementation of the IRES_Fxns interface
 */
extern IRES_Fxns TEMPLATE_TI_IRES;


/*
 *  ======== TEMPLATE_TI_PARAMS ========
 */
extern ITEMPLATE_Params TEMPLATE_TI_PARAMS;


#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.template; 1, 0, 0,76; 9-9-2008 23:53:14; /db/atree/library/trees/fc-e20x/src/
 */

