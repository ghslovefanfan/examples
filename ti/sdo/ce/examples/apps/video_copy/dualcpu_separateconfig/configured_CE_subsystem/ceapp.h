/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

#ifndef _CEAPP_H_
#define _CEAPP_H_

/* API for the Codec-Engine-using subsystem, that hides Codec Engine API from
 * its users
 */

extern int   ceapp_init();            /* initialize the ceapp module */

extern char *ceapp_allocContigBuf(    /* allocate physically contiguous */
                int   bufSize,        /*   buffer of given size; description */
                char *bufDescription  /*   is used only for print */
                );
                
extern int   ceapp_validateBufSizes(  /* confirm that the enc/dec codecs */
                int inBufSize,        /*   support these buffer sizes */
                int encodedBufSize,   /*   for the raw input video, encoded */
                int outBufSize        /*   video data, and decoded output */
                );
                
extern int   ceapp_encodeBuf(         /* encode raw video data in inBuf */
                char *inBuf,          /*   and store result in encodedBuf */
                int   inBufSize,
                char *encodedBuf,
                int   encodedBufSize
                );
                
extern int   ceapp_decodeBuf(         /* decode data from encodedBuf and */
                char *encodedBuf,     /*   store resulting raw data in outBuf */
                int   encodedBufSize,
                char *outBuf,
                int   outBufSize
                );
                
extern void  ceapp_freeContigBuf(     /* free the contiguous buffer */
                char *buf,
                int   bufSize
                );
                
extern void  ceapp_exit();            /* exit the ceapp module */


#endif /* _CEAPP_H_ */

/*
 *  @(#) ti.sdo.ce.examples.apps.video_copy.dualcpu_separateconfig; 1,0,0,132; 9-9-2008 02:02:00; /db/atree/library/trees/ce-h27x/src/
 */

