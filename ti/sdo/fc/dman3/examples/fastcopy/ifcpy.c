/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== ifcpy.c ========
 *  Default creation parameters for all implementations of the FCPY
 *  module abstract interface. 
 *
 *  These parameters are included by the client of the fcpy algorithm(s), 
 *  and referenced by the algorithms.
 */
#include <std.h>

#include <ifcpy.h>

/*
 *  ======== IFCPY_PARAMS ========
 *  This static initialization defines the default parameters used to
 *  create an instance of a FCPY object.
 */
const IFCPY_Params IFCPY_PARAMS = {
    sizeof(IFCPY_PARAMS),    /* Size of this structure */
    8,                       /* Source Frame length */
    8,                       /* Number of frames for source */
    0,                       /* Stride between frames for source */
    8,                       /* Destination Frame length */
    8,                       /* Number of frames for destination */
    0                        /* Stride between frames for destination */
};



/*
 *  @(#) ti.sdo.fc.dman3.examples.fastcopy; 1,0,0,141; 9-9-2008 23:51:14; /db/atree/library/trees/fc-e20x/src/
 */

