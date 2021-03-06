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
 *  ======== videnc_copy.c ========
 *  Video Encoder "copy" algorithm.
 *
 *  This file contains an implementation of the deprecated IVIDENC interface
 *  as defined by xDM 0.9.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/ividenc.h>
#include <ti/sdo/ce/trace/gt.h>

#include "videnc_copy_ti.h"
#include "videnc_copy_ti_priv.h"


/* Add for alg of image process by pitou */
#define MR(Y,U,V) (1.164 * (Y - 16) + 1.596 * (V - 128))
#define MG(Y,U,V) (1.164 * (Y - 16) - 0.813 * (V - 128) - 0.391 * (U - 128))
#define MB(Y,U,V) (1.164 * (Y - 16) + 2.018 * (U  - 128))


#define MY(R, G, B) ( 0.257 * R + 0.504 * G + 0.098 * B + 16 )
#define MU(R, G, B) (-0.148 * R - 0.291 * G + 0.439 * B + 128)
#define MV(R, G, B) ( 0.439 * R - 0.368 * G - 0.071 * B + 128)

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

extern IALG_Fxns VIDENCCOPY_TI_IALG;

#define IALGFXNS  \
    &VIDENCCOPY_TI_IALG,        /* module ID */                         \
    VIDENCCOPY_TI_activate,     /* activate */                          \
    VIDENCCOPY_TI_alloc,        /* alloc */                             \
    NULL,                       /* control (NULL => no control ops) */  \
    VIDENCCOPY_TI_deactivate,   /* deactivate */                        \
    VIDENCCOPY_TI_free,         /* free */                              \
    VIDENCCOPY_TI_initObj,      /* init */                              \
    NULL,                       /* moved */                             \
    NULL                        /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== VIDENCCOPY_TI_IVIDENC ========
 *  This structure defines TI's implementation of the IVIDENC interface
 *  for the VIDENCCOPY_TI module.
 */
IVIDENC_Fxns VIDENCCOPY_TI_VIDENCCOPY = {    /* module_vendor_interface */
    {IALGFXNS},
    VIDENCCOPY_TI_process,
    VIDENCCOPY_TI_control,
};

/*
 *  ======== VIDENCCOPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the VIDENCCOPY_TI module.
 */
#ifdef _TI_
/* satisfy xDAIS symbol requirement without any overhead */
asm("_VIDENCCOPY_TI_IALG .set _VIDENCCOPY_TI_VIDENCCOPY");

#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns VIDENCCOPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

/* tracing information */
#define GTNAME "ti.sdo.ce.examples.codecs.videnc_copy"
static GT_Mask curTrace = {NULL,NULL};

#ifdef USE_ACPY3

/* Implementation of IDMA3 interface functions & IDMA3_Fxns vtable */
#include <ti/bios/include/std.h>
#include <ti/xdais/idma3.h>
#include <ti/sdo/fc/acpy3/acpy3.h>

#define NUM_LOGICAL_CH 1

/*
 *  ======== VIDENCCOPY_TI_dmaChangeChannels ========
 *  Update instance object with new logical channel.
 */
Void VIDENCCOPY_TI_dmaChangeChannels(IALG_Handle handle,
    IDMA3_ChannelRec dmaTab[])
{
    VIDENCCOPY_TI_Obj *videncObj = (Void *)handle;

    GT_2trace(curTrace, GT_ENTER,
        "VIDENCCOPY_TI_dmaChangeChannels(0x%x, 0x%x)\n", handle, dmaTab);

    videncObj->dmaHandle1D1D8B = dmaTab[0].handle;
}


/*
 *  ======== VIDENCCOPY_TI_dmaGetChannelCnt ========
 *  Return max number of logical channels requested.
 */
Uns VIDENCCOPY_TI_dmaGetChannelCnt(Void)
{
    GT_0trace(curTrace, GT_ENTER, "VIDENCCOPY_TI_dmaGetChannelCnt()\n");

    return (NUM_LOGICAL_CH);
}


/*
 *  ======== VIDENCCOPY_TI_dmaGetChannels ========
 *  Declare DMA resource requirement/holdings.
 */
Uns VIDENCCOPY_TI_dmaGetChannels(IALG_Handle handle, IDMA3_ChannelRec dmaTab[])
{
    VIDENCCOPY_TI_Obj *videncObj = (Void *)handle;
    int i;

    GT_2trace(curTrace, GT_ENTER,
        "VIDENCCOPY_TI_dmaGetChannels(0x%x, 0x%x)\n", handle, dmaTab);

    /* Initial values on logical channels */
    dmaTab[0].handle = videncObj->dmaHandle1D1D8B;

    dmaTab[0].numTransfers = 1;
    dmaTab[0].numWaits = 1;

    /*
     * Request logical DMA channels for use with ACPY3
     * AND with environment size obtained from ACPY3 implementation
     * AND with low priority.
     */
    for (i = 0; i < NUM_LOGICAL_CH; i++) {
        dmaTab[i].priority = IDMA3_PRIORITY_LOW;
        dmaTab[i].persistent = FALSE;
        dmaTab[i].protocol = &ACPY3_PROTOCOL;
    }

    return (NUM_LOGICAL_CH);
}


/*
 *  ======== VIDENCCOPY_TI_dmaInit ========
 *  Initialize instance object with granted logical channel.
 */
Int VIDENCCOPY_TI_dmaInit(IALG_Handle handle, IDMA3_ChannelRec dmaTab[])
{
    VIDENCCOPY_TI_Obj *videncObj = (Void *)handle;

    GT_2trace(curTrace, GT_ENTER, "VIDENCCOPY_TI_dmaInit(0x%x, 0x%x)\n",
        handle, dmaTab);

    videncObj->dmaHandle1D1D8B = dmaTab[0].handle;

    return (IALG_EOK);
}


/*
 *  ======== VIDENCCOPY_TI_IDMA3 ========
 *  This structure defines TI's implementation of the IDMA3 interface
 *  for the VIDENCCOPY_TI module.
 */
IDMA3_Fxns VIDENCCOPY_TI_IDMA3 = {      /* module_vendor_interface */
    &VIDENCCOPY_TI_IALG,              /* IALG functions */
    VIDENCCOPY_TI_dmaChangeChannels,  /* ChangeChannels */
    VIDENCCOPY_TI_dmaGetChannelCnt,   /* GetChannelCnt */
    VIDENCCOPY_TI_dmaGetChannels,     /* GetChannels */
    VIDENCCOPY_TI_dmaInit             /* initialize logical channels */
};

#endif

/*
 *  ======== VIDENCCOPY_TI_activate ========
 */
Void VIDENCCOPY_TI_activate(IALG_Handle handle)
{
    GT_1trace(curTrace, GT_ENTER, "VIDENCCOPY_TI_activate(0x%x)\n", handle);
}


/*
 *  ======== VIDENCCOPY_TI_deactivate ========
 */
Void VIDENCCOPY_TI_deactivate(IALG_Handle handle)
{
    GT_1trace(curTrace, GT_ENTER, "VIDENCCOPY_TI_deactivate(0x%x)\n", handle);
}


/*
 *  ======== VIDENCCOPY_TI_alloc ========
 */
Int VIDENCCOPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    if (curTrace.modName == NULL) {   /* initialize GT (tracing) */
        GT_create(&curTrace, GTNAME);
    }

    GT_3trace(curTrace, GT_ENTER, "VIDENCCOPY_TI_alloc(0x%x, 0x%x, 0x%x)\n",
        algParams, pf, memTab);

    /* Request memory for my object */
    memTab[0].size = sizeof(VIDENCCOPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;
	
	/* Add for alg of image process by pitou */
    memTab[1].size = sizeof(IplImage);
    memTab[1].alignment = 0;
    memTab[1].space = IALG_EXTERNAL;
    memTab[1].attrs = IALG_PERSIST;
	
    memTab[2].size = 720 * 576 *3 * sizeof(XDAS_UInt8);
    memTab[2].alignment = 0;
    memTab[2].space = IALG_EXTERNAL;
    memTab[2].attrs = IALG_SCRATCH;	
	/* Add for alg of image process by pitou */
    return (3);
}


/*
 *  ======== VIDENCCOPY_TI_free ========
 */
Int VIDENCCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
	/* Add for alg of image process by pitou */
	VIDENCCOPY_TI_Obj *videncObj = (VIDENCCOPY_TI_Obj *)handle;
		
    GT_2trace(curTrace, GT_ENTER, "VIDENCCOPY_TI_free(0x%lx, 0x%lx)\n",
        handle, memTab);
        	
    VIDENCCOPY_TI_alloc(NULL, NULL, memTab);
	/* Add for alg of image process by pitou */
	memTab[0].base = handle;
	memTab[1].base = videncObj->img;
	memTab[1].size = sizeof(IplImage);
	memTab[2].base = videncObj->pRGB;
	memTab[2].size = 720 * 576 * 3 * sizeof(XDAS_UInt8);	
	/* Add for alg of image process by pitou */
    return (3);
}


/*
 *  ======== VIDENCCOPY_TI_initObj ========
 */
Int VIDENCCOPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle p,
    const IALG_Params *algParams)
{
	
	VIDENCCOPY_TI_Obj *videncObj = (VIDENCCOPY_TI_Obj *)handle;
    GT_4trace(curTrace, GT_ENTER,
        "VIDENCCOPY_TI_initObj(0x%x, 0x%x, 0x%x, 0x%x)\n", handle, memTab,
        p, algParams);
	
	/* Add for alg of image process by pitou */
	videncObj->img = memTab[1].base;
	videncObj->pRGB = memTab[2].base;
	
    return (IALG_EOK);
}


/*
 *  ======== VIDENCCOPY_TI_process ========
 */
XDAS_Int32 VIDENCCOPY_TI_process(IVIDENC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDENC_InArgs *inArgs, IVIDENC_OutArgs *outArgs)
{
    XDAS_Int32 curBuf;
    XDAS_UInt32 minSamples;
	
	VIDENCCOPY_TI_Obj *VIDENC_COPY = (VIDENCCOPY_TI_Obj *)h;
	CvSize size; // pal frame, 422, YUV422 semi-planar
	CvPoint point1, point2; // draw a rectangle in the middle of an image
	CvScalar color;
	
#ifdef USE_ACPY3
    const Uint32 maxTransferChunkSize       = 0xffff;
    Uint32       thisTransferChunkSize      = 0x0;
    Uint32       remainingTransferChunkSize;
    Uint32       thisTransferSrcAddr, thisTransferDstAddr;

    ACPY3_Params params;
    VIDENCCOPY_TI_Obj *videncObj = (VIDENCCOPY_TI_Obj *)h;
#endif

    GT_5trace(curTrace, GT_ENTER, "VIDENCCOPY_TI_process(0x%x, 0x%x, 0x%x, "
        "0x%x, 0x%x)\n", h, inBufs, outBufs, inArgs, outArgs);

    /* validate arguments - this codec only supports "base" xDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
        (outArgs->size != sizeof(*outArgs))) {

        GT_2trace(curTrace, GT_ENTER,
            "VIDENCCOPY_TI_process, unsupported size "
            "(0x%x, 0x%x)\n", inArgs->size, outArgs->size);

        return (IVIDENC_EFAIL);
    }

#ifdef USE_ACPY3
    /*
     * Activate Channel  scratch DMA channels.
     */
    ACPY3_activate(videncObj->dmaHandle1D1D8B);
#endif

    /* outArgs->bytesGenerated reports the total number of bytes generated */
    outArgs->bytesGenerated = 0;

    /*
     * A couple constraints for this simple "copy" codec:
     *    - Video encoding presumes a single input buffer, so only one input
     *      buffer will be encoded, regardless of inBufs->numBufs.
     *    - Given a different size of an input and output buffers, only
     *      encode (i.e., copy) the lesser of the sizes.
     */

    for (curBuf = 0; (curBuf < inBufs->numBufs) &&
        (curBuf < outBufs->numBufs); curBuf++) 
	{

        /* there's an available in and out buffer, how many samples? */
        minSamples = inBufs->bufSizes[curBuf] < outBufs->bufSizes[curBuf] ?
            inBufs->bufSizes[curBuf] : outBufs->bufSizes[curBuf];

#ifdef USE_ACPY3

        thisTransferSrcAddr        = (Uint32)inBufs->bufs[curBuf];
        thisTransferDstAddr        = (Uint32)outBufs->bufs[curBuf];
        remainingTransferChunkSize = minSamples;

        while (remainingTransferChunkSize > 0) {

            if (remainingTransferChunkSize > maxTransferChunkSize) {
               thisTransferChunkSize = maxTransferChunkSize;
            }
            else {
               thisTransferChunkSize = remainingTransferChunkSize;
            }

            /* Configure the logical channel */
            params.transferType = ACPY3_1D1D;
            params.srcAddr      = (void *)thisTransferSrcAddr;
            params.dstAddr      = (void *)thisTransferDstAddr;
            params.elementSize  = thisTransferChunkSize;
            params.numElements  = 1;
            params.waitId       = 0;
            params.numFrames    = 1;

            remainingTransferChunkSize -= thisTransferChunkSize;
            thisTransferSrcAddr += thisTransferChunkSize;
            thisTransferDstAddr += thisTransferChunkSize;

            /* Configure logical dma channel */
            ACPY3_configure(videncObj->dmaHandle1D1D8B, &params, 0);

            /* Use DMA to copy data */
            ACPY3_start(videncObj->dmaHandle1D1D8B);

            /* wait for transfer to finish  */
            ACPY3_wait(videncObj->dmaHandle1D1D8B);
        }
        GT_1trace(curTrace, GT_2CLASS, "VIDENCCOPY_TI_process> "
               "ACPY3 Processed %d bytes.\n", minSamples);
#else
        GT_3trace(curTrace, GT_2CLASS, "VIDENCCOPY_TI_process> "
               "memcpy (0x%x, 0x%x, %d)\n",
               outBufs->bufs[curBuf], inBufs->bufs[curBuf], minSamples);

        /* process the data: read input, produce output */
        //memcpy(outBufs->bufs[curBuf], inBufs->bufs[curBuf], minSamples);
		/* Add for alg of image process by pitou */
		
		color = CV_RGB(0, 255, 0); // green
		size.height = 576;
		size.width = 720;

		point1.x = size.width / 2 - 50;
		point1.y = size.height / 2 - 50;
		point2.x = size.width / 2 + 50;
		point2.y = size.height / 2 + 50;
		
		VIDENCCOPY_TI_YUV422_2_RGB((XDAS_UInt8 *)inBufs->bufs[curBuf], 
									VIDENC_COPY->pRGB, 
									size.height, 
									size.width);
		//pRGB-->img-->add rectangel to img-->convert-->outBufs->bufs[curBuf]
		VIDENCCOPY_TI_cvSetData(VIDENC_COPY->img, VIDENC_COPY->pRGB, size.width * 3);
		VIDENCCOPY_TI_cvRectangle(VIDENC_COPY->img, point1, point2, color, CV_AA, 8, 0);
		
		VIDENCCOPY_TI_RGB_2_YUV422((XDAS_UInt8 *)((VIDENC_COPY->img)->imageData), 
									(XDAS_UInt8 *)outBufs->bufs[curBuf], 
									size.height, 
									size.width);
#endif

        outArgs->bytesGenerated += minSamples;
    }

    /* Fill out the rest of the outArgs struct */
    outArgs->extendedError = 0;
    outArgs->encodedFrameType = 0;    /* TODO */
    outArgs->inputFrameSkip = IVIDEO_FRAME_ENCODED;
    outArgs->reconBufs.numBufs = 0;   /* important: indicate no reconBufs */

    return (IVIDENC_EOK);
}


/*
 *  ======== VIDENCCOPY_TI_control ========
 */
XDAS_Int32 VIDENCCOPY_TI_control(IVIDENC_Handle handle, IVIDENC_Cmd id,
    IVIDENC_DynamicParams *params, IVIDENC_Status *status)
{
    XDAS_Int32 retVal;

    GT_4trace(curTrace, GT_ENTER, "VIDENCCOPY_TI_control(0x%x, 0x%x, 0x%x, "
        "0x%x)\n", handle, id, params, status);

    /* validate arguments - this codec only supports "base" xDM. */
    if ((params->size != sizeof(*params)) ||
        (status->size != sizeof(*status))) {

        GT_2trace(curTrace, GT_ENTER,
            "VIDENCCOPY_TI_control, unsupported size "
            "(0x%x, 0x%x)\n", params->size, status->size);

        return (IVIDENC_EFAIL);
    }

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->extendedError = 0;

            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = IVIDENC_EOK;

            break;

        case XDM_SETPARAMS:
        case XDM_SETDEFAULT:
        case XDM_RESET:
        case XDM_FLUSH:
            /* TODO - for now just return success. */

            retVal = IVIDENC_EOK;
            break;

        default:
            /* unsupported cmd */
            retVal = IVIDENC_EFAIL;

            break;
    }

    return (retVal);
}

Void YUV422_2_RGB( XDAS_UInt8* pYUV, XDAS_UInt8* pRGB, XDAS_Int32 height, XDAS_Int32 width)
{

    XDAS_UInt8* pBGR = NULL;

    XDAS_UInt8 R = 0;
    XDAS_UInt8 G = 0;
    XDAS_UInt8 B = 0;

    XDAS_UInt8 Y = 0;
    XDAS_UInt8 U = 0;
    XDAS_UInt8 V = 0;

    double tmp = 0;
	int i,j;
    for ( i = 0; i < height; ++i )
    {
        for ( j = 0; j < width; ++j )
        {
            pBGR = pRGB + i * width * 3 + j * 3;
            Y = *(pYUV + i * width + j);
            if(j % 2 ==0){

                U = *(pYUV + height * width + i * width + j);
                V = *(pYUV + height * width + i * width + j + 1);
            }

            else {

                U = *(pYUV + height * width + i * width + j - 1);
                V = *(pYUV + height * width + i * width + j);
            }

            tmp = MB(Y, U, V);
            tmp = (tmp > 255) ? 255 : tmp;
            tmp = (tmp < 0) ? 0 : tmp;

            B = (XDAS_UInt8)tmp;

            tmp = MG(Y, U, V);
            tmp = (tmp > 255) ? 255 : tmp;
            tmp = (tmp < 0) ? 0 : tmp;

            G = (XDAS_UInt8)tmp;

            tmp = MR(Y, U, V);
            tmp = (tmp > 255) ? 255 : tmp;
            tmp = (tmp < 0) ? 0 : tmp;

            R = (XDAS_UInt8)tmp;

            *pBGR       = B;           
            *(pBGR + 1) = G;       
            *(pBGR + 2) = R;
        }
    }
}


Void RGB_2_YUV422( XDAS_UInt8* pRGB, XDAS_UInt8* pYUV, XDAS_Int32 height, XDAS_Int32 width)
{
    XDAS_UInt8* pBGR = NULL;

    XDAS_UInt8 R = 0;
    XDAS_UInt8 G = 0;
    XDAS_UInt8 B = 0;

    XDAS_UInt8 Y = 0;
    XDAS_UInt8 U = 0;
    XDAS_UInt8 V = 0;
	
    double tmp = 0;
	int i,j;

    for ( i = 0; i < height; ++i )
    {
        for ( j = 0; j < width; ++j )
        {
            pBGR = pRGB + i * width * 3 + j * 3;

            B = *pBGR;
            G = *(pBGR + 1);
            R = *(pBGR + 2);

            tmp = MY(R, G, B);
            tmp = (tmp > 255) ? 255 : tmp;
            tmp = (tmp < 0) ? 0 : tmp;

            Y = (XDAS_UInt8)tmp;

            *(pYUV + i * width + j) = Y;

            if(j % 2 == 0) {
                tmp = MU(R, G, B);
                tmp = (tmp > 255) ? 255 : tmp;
                tmp = (tmp < 0) ? 0 : tmp;
                U = (XDAS_UInt8)tmp;
                *(pYUV + height * width + i * width + j) = U;
            }
            else {

                tmp = MV(R, G, B);
                tmp = (tmp > 255) ? 255 : tmp;
                tmp = (tmp < 0) ? 0 : tmp;
                V = (XDAS_UInt8)tmp;
                *(pYUV + height * width + i * width + j) = V;
            }
        }
    }
}


/*
 *  @(#) ti.sdo.ce.examples.codecs.videnc_copy; 1,0,0,132; 9-9-2008 02:03:52; /db/atree/library/trees/ce-h27x/src/
 */

