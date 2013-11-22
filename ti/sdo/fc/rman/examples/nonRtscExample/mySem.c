/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

#include <ti/bios/include/std.h>
#include <ti/sdo/fc/rman/rman.h>

typedef struct Sem_Obj {
    Int sem;
} Sem_Obj;

static Sem_Obj mySem= { 0xC0FFEE };
static Bool pending = FALSE;

/* ARGSUSED */
RMAN_SemHandle mySemCreate(Int key, Int count)
{
    if (1 != count) {
        return NULL;
    }
    mySem.sem = key;
    return (Void *)&mySem; 
}

/* ARGSUSED */
Void mySemDelete(RMAN_SemHandle sem)
{
   mySem.sem = 0xC0FFEE; 
}

/* ARGSUSED */
Int mySemPend(RMAN_SemHandle sem, unsigned int timeout)
{
    if ((sem != &mySem) || (pending != FALSE)) {
        return -1;
    }
    else {
       pending = TRUE; 
    }
        return 0;
}

/* ARGSUSED */
Void mySemPost(RMAN_SemHandle sem) 
{
    pending = FALSE;
}
/*
 *  @(#) ti.sdo.fc.rman.examples.nonRtscExample; 1, 0, 0,22; 9-9-2008 23:55:03; /db/atree/library/trees/fc-e20x/src/
 */

