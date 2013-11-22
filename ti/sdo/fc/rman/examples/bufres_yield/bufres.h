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
 *  ======== bufres.h ========
 *  Buffer resource. This is a very simple example of a resource manager that
 *  implements IRES and IRESMAN interfaces. This resource manager manages a
 *  single buffer that can be shared by multiple algorithms belonging to the
 *  same scratch group (ie, the algorithms don't preempt eachother). An
 *  algorithm can request a chunk of memory with a specified length and
 *  alignment, within this buffer.
 */

#ifndef BUFRES_H_
#define BUFRES_H_

#include <ti/xdais/ires_common.h>
#include <ti/sdo/fc/ires/iresman_protocol.h>
#include <ti/sdo/fc/ires/iresman.h>


#define NUMRES 1 
/*
 *  ======== BUFRES_NAME ========
 *  Name used for this resource.
 */
#define BUFRES_PROTOCOLNAME "ti.sdo.fc.rman.examples.bufres_yield"

/*
 *  ======== BUFRES_PROTOCOLVERSION ======
 *
 */
static IRES_ProtocolRevision BUFRES_PROTOCOLVERSION = {1,0,0};
 
/*
 *  ======== BUFRES_Params ========
 *  Extends IRESMAN_Params. These params are used to initialize the resource.
 */
typedef struct BUFRES_Params {
    IRESMAN_Params iresConfig;

    /* Config params specific to this resource */
    Void      *base;      /* Base address of the buffer to manage */
    UInt32     length;    /* Size of the buffer */
    UInt32     fillValue; /* fillValue to initialize the buffer */   
} BUFRES_Params;

/*
 *  ======== BUFRES_Obj ========
 *  Extension of IRES_Obj. This object holds the state of the logical resource
 *  granted to the algorithm.
 */
typedef struct BUFRES_Obj {
    IRES_Obj        ires;

    /* Fields specific to this resource */
    Void   *base;    /* Base address of assigned memory chunk */
    Int     length;  /* Length of assigned memory chunk */
} BUFRES_Obj;

/*
 *  ======== BUFRES_Args ========
 *  Extends IRES_ProtocolArgs. Used by the algorithm to request this resource.
 */
typedef struct BUFRES_Args {
    IRES_ProtocolArgs iresArgs;

    /* Fields filled in by algorithm when requesting this resource */
    Int    length;  /* Length of buffer requested */
    Int    align;   /* Buffer alignment: 0 (no alignment) or a power of 2 */
} BUFRES_Args;

/*
 *  ======== BUFRES_Props ========
 *  Implementation of IRES_Properties for the buffer resource
 *  
 */
typedef struct BUFRES_Props {
    Int         size;    /* Size of this structure */

    /* Fields specific to this resource */
    Void   *base;    /* Base address of the buffer resource */
    Int     length;  /* Length of the buffer resource */
} BUFRES_Props;

/*
 *  ======== BUFRES_Handle ========
 *  Opaque handle to the BUFRES extension of the IRES_Obj object
 */
typedef struct BUFRES_Obj *BUFRES_Handle;

extern IRESMAN_ConstructFxns BUFRES_REQFXNS;
extern IRESMAN_Fxns BUFRES_MGRFXNS;

#endif /* BUFRES_H_ */

/*
 *  @(#) ti.sdo.fc.rman.examples.bufres_yield; 1, 0, 0,83; 9-9-2008 23:54:37; /db/atree/library/trees/fc-e20x/src/
 */

