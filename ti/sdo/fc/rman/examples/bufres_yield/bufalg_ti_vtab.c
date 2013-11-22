/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== bufalg_ti_vtab.c ========
 *  Definition of BUFALG_TI_IBUFALG.  
 *
 *  Since IBUFALG derives from IALG,we also define the sym
 *  BUFALG_TI_IALG, TI's implementation of the IALG interface.
 */

#include <xdc/std.h>

#include "ibufalg.h"
#include "bufalg_ti.h"
#include "bufalg_ti_priv.h"

#define IALGFXNS \
    &BUFALG_TI_IALG,        /* module ID */                     \
    BUFALG_TI_activate,     /* activate */                      \
    BUFALG_TI_alloc,        /* algAlloc */                      \
    BUFALG_TI_control,      /* control ops */                   \
    BUFALG_TI_deactivate,   /* deactivate */                    \
    BUFALG_TI_free,         /* free */                          \
    BUFALG_TI_initObj,      /* init */                          \
    NULL,                   /* moved (NULL => not suported) */  \
    BUFALG_TI_numAlloc      /* numAlloc (NULL => IALG_DEFMEMRECS) */\


/*
 *  ======== BUFALG_TI_IBUFALG ========
 *  This structure defines TI's implementation of the IBUFALG interface
 *  for the BUFALG_TI module.
 */
IBUFALG_Fxns BUFALG_TI_IBUFALG = {    /* module_vendor_interface */
    IALGFXNS,
    BUFALG_TI_useBufs
};

/*
 *  ======== BUFALG_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the BUFALG_TI module.
 */
asm("_BUFALG_TI_IALG .set _BUFALG_TI_IBUFALG");
/*
 *  @(#) ti.sdo.fc.rman.examples.bufres_yield; 1, 0, 0,83; 9-9-2008 23:54:37; /db/atree/library/trees/fc-e20x/src/
 */

