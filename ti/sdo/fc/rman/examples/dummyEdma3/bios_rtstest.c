/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== bios_rtstest.c ========
 *
 *  This file contains implementation of test versions of non-BIOS MEM
 *  MEM_valloc() and MEM_free(). The test versions, MEM_tvalloc() and
 *  MEM_tfree(), take an extra parameter to be used for verification.
 *
 */

#ifdef _RTS_MODE

#include <std.h>
#include <stdlib.h>
#include <stdio.h>

#include <bios_rtstest.h>

#define PTRSIZE sizeof(Void *)

/*
 *  ======== MEM_tfree ========
 *  Test version of MEM_free
 */
Bool MEM_tfree(Int segid, Void * alignBuf, size_t size, Void **pAddr)
{
    LgUns *addrPtr;
    Void *buf;
    Uns remainBytes = 0;

    if ((PTRSIZE - 1) & size) {
        remainBytes = PTRSIZE - ((PTRSIZE - 1) & size);
    }

    addrPtr = (LgUns *)((LgUns)alignBuf + size + remainBytes);
    buf = (Void *)*addrPtr;

    /* This must be the same as the *pAddr set in MEM_tvalloc(). */
    *pAddr = buf;

    free(buf);

    return (TRUE);
}

/*
 *  ======== MEM_tvalloc ========
 *  Test version of MEM_valloc
 */
Void * MEM_tvalloc(Int segid, size_t size, size_t align, Char val,
        Void **pAddr)
{
    Uns     alignSize;
    Uns     alignBytes;
    Uns     remainBytes;
    Void   *buf;
    Void   *alignBuf;
    Uns     tmpAlign;
    LgUns  *addrPtr;


    /*
     *  Must at least align on 32-bit boundary since we're storing the
     *  32-bit address of the malloc'd buffer.
     */
    alignBytes = (align < PTRSIZE) ? PTRSIZE : align;

    /* alignment must be a power of 2 */
    DBC_require((alignBytes & (alignBytes - 1)) == 0);

    /*
     *  We will allocate a buffer larger than "size", to allow for alignment
     *  and to hold the address of the buffer returned by malloc() at the
     *  end of the buffer.
     *  Make size a multiple of 32-bits so it will be easier to find the
     *  address of the buffer returned by malloc(). 
     */
    alignSize = size;
    if ((remainBytes = alignSize & (PTRSIZE - 1)) != 0) {
        /* size is not a multiple of 32-bits */
        alignSize += PTRSIZE - remainBytes;
        remainBytes = PTRSIZE - remainBytes;
    }

    /* Add 32-bits to store pointer of allocated buffer */
    alignSize += PTRSIZE;

    alignSize += alignBytes;
    buf = malloc(alignSize);
    *pAddr = buf;

    tmpAlign = (Uns)buf & (alignBytes - 1);
    if (tmpAlign) {
        alignBuf = (Void *)((Uns)buf + alignBytes - tmpAlign);
    }
    else {
        alignBuf = buf;
    }

    /* Store the malloc'd address for freeing later. */
    addrPtr = (LgUns *)((LgUns)alignBuf + size + remainBytes);
    *addrPtr = (LgUns)buf;

    /* Initialize the aligned buffer with 'val' */
    memset(alignBuf, val, size);

    DBC_ensure(!((LgUns)alignBuf & (alignBytes - 1)));

    return (alignBuf);
}


/*
 *  ======== SYS_abort ========
 */
void SYS_abort(char *s, ...)
{
    printf("*** %s ***\n", s );
    exit(1);
}

#endif

/*
 *  @(#) ti.sdo.fc.rman.examples.dummyEdma3; 1, 0, 0,84; 9-9-2008 23:54:50; /db/atree/library/trees/fc-e20x/src/
 */

