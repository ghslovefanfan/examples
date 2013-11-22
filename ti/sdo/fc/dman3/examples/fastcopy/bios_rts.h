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
 *  ======== bios_rts.h ========
 *
 * This file contains Non-BIOS version of MEM, SYS, HWI, and DBC implementation
 */


#ifndef _BIOS_RTS_
#define _BIOS_RTS_


#include <stdlib.h>

#if DBC_ASSERTS

extern void SYS_abort(char *s, ...);

#define DBC_assert(c) if (!(c)) { \
        SYS_abort("Assertion Failed: file=%s, line=%d.\n", __FILE__, \
        __LINE__); }

#define DBC_require     DBC_assert
#define DBC_ensure      DBC_assert

#else

#define DBC_assert(c)
#define DBC_require(c)
#define DBC_ensure(c)

#endif  /* DBC_ASSERTS */

#define MEM_calloc(segid, size, align) MEM_valloc(segid, size, align, 0)

extern Void * MEM_alloc(Int segid, size_t size, size_t align);
extern Void * MEM_valloc(Int segid, size_t size, size_t align, Char val);
extern Bool MEM_free(Int segid, Void * buf, size_t size);

extern Void TSK_enable(Void);
extern Void TSK_disable(Void);

#endif /* _BIOS_RTS_ */

/*
 *  @(#) ti.sdo.fc.dman3.examples.fastcopy; 1,0,0,141; 9-9-2008 23:51:13; /db/atree/library/trees/fc-e20x/src/
 */

