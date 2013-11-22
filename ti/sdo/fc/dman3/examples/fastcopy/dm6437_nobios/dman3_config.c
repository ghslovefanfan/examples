/* --COPYRIGHT--
 *  Copyright $(CPYYEAR)
 *  $(COMPANY_NAME)
 *
 *  All rights reserved.  Property of $(COMPANY_NAME)
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 * --/COPYRIGHT--
 */

/*
 *  ======== dman3_config.c ========
 *  Configuration for DMAN3 Parameters 
 */
#include <std.h>
#include <ti/sdo/fc/dman3/dman3.h>

static Uns CFG_QDMA_CHANNELS[4] = { 0, 1, 2, 3};
#define DMAN3MAXQDMACHANNELS 8;
#define DMAN3NUMQDMACHANNELS 4;

extern int L1DHEAP; /* Heap Label for L1DRAM memory allocation */
extern int EXTMEMHEAP; /* Heap Label for external memory allocation */

#define DMAN3HEAPINTERNAL L1DHEAP;
#define DMAN3HEAPEXTERNAL EXTMEMHEAP;
#define DMAN3PARAMBASEINDEX 78;
#define DMAN3NUMPARAMENTRIES 48;
#define DMAN3TCCALLOCATIONMASKH 0xffffffff;
#define DMAN3TCCALLOCATIONMASKL 0x0;
#define DMAN3QDMACHANNELS CFG_QDMA_CHANNELS;

fastcopy_dman3_config()
{
    DMAN3_PARAMS.heapInternal = DMAN3HEAPINTERNAL;
    DMAN3_PARAMS.heapExternal = DMAN3HEAPEXTERNAL;

    DMAN3_PARAMS.paRamBaseIndex = DMAN3PARAMBASEINDEX;
    DMAN3_PARAMS.numPaRamEntries = DMAN3NUMPARAMENTRIES;
    DMAN3_PARAMS.tccAllocationMaskH = DMAN3TCCALLOCATIONMASKH;
    DMAN3_PARAMS.tccAllocationMaskL = DMAN3TCCALLOCATIONMASKL;
    DMAN3_PARAMS.qdmaChannels = CFG_QDMA_CHANNELS;
    DMAN3_PARAMS.maxQdmaChannels = DMAN3MAXQDMACHANNELS;
    DMAN3_PARAMS.numQdmaChannels = DMAN3NUMQDMACHANNELS;
}
