/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== ceapp.c ========
 *  The CodecEngine-using part of the Linux application, separated from the
 *  rest of the Linux app to simplify the interface towards the rest of
 *  the main app. CodecEngine API and especially APIs for individual codecs
 *  are much more capable than what we need for simple (dummy) audio
 *  encode/decode.
 */

/* include various CodecEngine header files */
#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/audio/auddec.h>
#include <ti/sdo/ce/audio/audenc.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/CERuntime.h>

#include <ti/sdo/ce/trace/gt.h>

/* define names of codecs to use */
static String decoderName  = "auddec_copy";
static String encoderName  = "audenc_copy";
static String engineName   = "audio_copy";

/*  define handles to the CodecEngine and codecs to be used across ceapp_*
 *  function calls; we are not reentrant.
 */
Engine_Handle ceHandle  = NULL;
AUDDEC_Handle decHandle = NULL;
AUDENC_Handle encHandle = NULL;

/*
 *  ======== traceDump ========
 *  dump contents of DSP trace -- this is a "pull" trace dumping: we read
 *  DSP's trace log whenever we think there might be something there.
 */
static void traceDump(Engine_Handle ceHandle)
{
    Int count;

    GT_disable(); /* temporarily disable tracing for this thread */
    count = Engine_fwriteTrace(ceHandle, "[DSP] ", stdout);
    GT_enable();

    if (count == -1) {
        printf("CEapp-> ERROR: can't read trace from server\n");
    }
}

/*
 *  ======== ceapp_init ========
 */
int ceapp_init()
{
    int status = -1;    /* nonzero means failure */

    /* initialize Codec Engine runtime first */
    CERuntime_init();

    /* reset, load, and start DSP Engine */
    if ((ceHandle = Engine_open(engineName, NULL, NULL)) == NULL) {
        printf("CEapp-> ERROR: can't open engine %s\n", engineName);
        goto init_end;
    }

    /*  dump contents of DSP trace -- this is a "pull" trace dumping: we read
     *  DSP's trace log whenever we think there might be something there.
     */
    traceDump(ceHandle);

    /* allocate and initialize audio encoder on the engine */
    encHandle = AUDENC_create(ceHandle, encoderName, NULL);
    if (encHandle == NULL) {
        printf("CEapp-> ERROR: can't open codec %s\n", encoderName);
        goto init_end;
    }
    traceDump(ceHandle);

    /* allocate and initialize audio decoder on the engine */
    decHandle = AUDDEC_create(ceHandle, decoderName, NULL);
    if (decHandle == NULL) {
        printf("CEapp-> ERROR: can't open codec %s\n", decoderName);
        goto init_end;
    }
    traceDump(ceHandle);

    status = 0;     /* success */

init_end:

    return status;
}


/*
 *  ======== ceapp_allocContigBuf ========
 */
char *ceapp_allocContigBuf(int bufSize, char *description)
{
    char *buf;

    printf("CEapp-> Allocating contiguous buffer for '%s' of size %d...\n",
            description, bufSize);

    buf = (char *)Memory_contigAlloc(bufSize, Memory_DEFAULTALIGNMENT);

    if (buf == NULL) {
        printf("CEapp-> ERROR: Failed to allocate contiguous memory block.\n");
    }

    return buf;
}


/*
 *  ======== ceapp_validateBufSizes ========
 */
int ceapp_validateBufSizes(int inBufSize, int encodedBufSize, int outBufSize)
{
    AUDDEC_DynamicParams  decDynParams;
    AUDENC_DynamicParams  encDynParams;
    AUDENC_Status         encStatus;
    AUDDEC_Status         decStatus;

    Int32                 status;
    int                   retval = -1;      /* nonzero means failure */

    /*
     * Query the encoder and decoder.
     * This app expects the encoder to provide 1 buf in and get 1 buf out,
     * and the buf sizes of the in and out buffer must be able to handle
     * NSAMPLES bytes of data.
     */
    encStatus.size = sizeof(encStatus);
    encDynParams.size = sizeof(encDynParams);

    status = AUDENC_control(encHandle, XDM_GETSTATUS, &encDynParams,
        &encStatus);

    if (status != AUDENC_EOK) {
        printf("CEapp-> Audio Encoder control FAILED, status = %ld\n", status);
        goto validate_end;
    }
    traceDump(ceHandle);

    /* Validate this encoder codec will meet our buffer requirements */
    if((encStatus.bufInfo.minNumInBufs     > 1)         ||
        (encStatus.bufInfo.minInBufSize[0]  > inBufSize) ||
        (encStatus.bufInfo.minNumOutBufs    > 1)         ||
        (encStatus.bufInfo.minOutBufSize[0] > encodedBufSize)) {
        printf("CEapp-> ERROR: encoder does not meet buffer requirements.\n");
        goto validate_end;
    }
    traceDump(ceHandle);

    decStatus.size = sizeof(decStatus);
    decDynParams.size = sizeof(decDynParams);

    status = AUDDEC_control(decHandle, XDM_GETSTATUS, &decDynParams,
        &decStatus);
    if (status != AUDDEC_EOK) {
        printf("CEapp-> Audio Decoder control FAILED, status = %ld\n", status);
        goto validate_end;
    }
    traceDump(ceHandle);

    /* Validate this decoder codec will meet our buffer requirements */
    if((decStatus.bufInfo.minNumInBufs     > 1)              ||
        (decStatus.bufInfo.minInBufSize[0]  > encodedBufSize) ||
        (decStatus.bufInfo.minNumOutBufs    > 1)              ||
        (decStatus.bufInfo.minOutBufSize[0] > outBufSize)) {
        printf("CEapp-> ERROR: decoder does not meet buffer requirements.\n");
        goto validate_end;
    }
    traceDump(ceHandle);

    retval = 0; /* success */

validate_end:

    return (retval);

}


/*
 *  ======== ceapp_encodeBuf ========
 */
int ceapp_encodeBuf(char *inBuf,      int inBufSize,
                     char *encodedBuf, int encodedBufSize)
{
    /* declare codec I/O buffer descriptors for the codec's process() func. */
    XDM_BufDesc      inBufDesc;
    XDM_BufDesc      encodedBufDesc;

    /* declare in and out argument descriptors for process() */
    AUDENC_InArgs    encoderInArgs;
    AUDENC_OutArgs   encoderOutArgs;

    /* declare arrays describing I/O buffers and their sizes */
    XDAS_Int8*       inBufs         [ XDM_MAX_IO_BUFFERS ];
    XDAS_Int32       inBufSizes     [ XDM_MAX_IO_BUFFERS ];
    XDAS_Int8*       encodedBufs    [ XDM_MAX_IO_BUFFERS ];
    XDAS_Int32       encodedBufSizes[ XDM_MAX_IO_BUFFERS ];

    Int32            status;
    int              retval = -1;      /* nonzero means failure */

    /* define the arrays describing I/O buffers and their sizes */
    inBufs[0]          = inBuf;
    inBufSizes[0]      = inBufSize;
    encodedBufs[0]     = encodedBuf;
    encodedBufSizes[0] = encodedBufSize;

    /* define I/O buffer descriptors using lengths and addrs of arrays above */
    inBufDesc.numBufs       = 1;
    inBufDesc.bufs          = inBufs;
    inBufDesc.bufSizes      = inBufSizes;
    encodedBufDesc.numBufs  = 1;
    encodedBufDesc.bufs     = encodedBufs;
    encodedBufDesc.bufSizes = encodedBufSizes;

    /* fill in the input arguments structure; we have nothing for this case */
    encoderInArgs.size = sizeof(encoderInArgs);
    encoderOutArgs.size = sizeof(encoderOutArgs);

    /* encode the frame, pass addrs of the structures we populated above */
    status = AUDENC_process(encHandle, &inBufDesc, &encodedBufDesc,
        &encoderInArgs, &encoderOutArgs);
    traceDump(ceHandle);

    if (status == AUDENC_EOK) {
        retval = 0;
    }
    else {
        printf("CEapp-> AUDENC_process() failed, status=%ld\n", status);
    }

    return retval;
}


/*
 *  ======== ceapp_decodeBuf ========
 */
int ceapp_decodeBuf(char *encodedBuf, int encodedBufSize,
                     char *outBuf,     int outBufSize)
{
    /* declare codec I/O buffer descriptors for the codec's process() func. */
    XDM_BufDesc      encodedBufDesc;
    XDM_BufDesc      outBufDesc;

    /* declare in and out argument descriptors for process() */
    AUDDEC_InArgs    decoderInArgs;
    AUDDEC_OutArgs   decoderOutArgs;

    Int32            status;
    int              retval = -1;      /* nonzero means failure */

    /* declare arrays describing I/O buffers and their sizes */
    XDAS_Int8*       encodedBufs    [ XDM_MAX_IO_BUFFERS ];
    XDAS_Int32       encodedBufSizes[ XDM_MAX_IO_BUFFERS ];
    XDAS_Int8*       outBufs        [ XDM_MAX_IO_BUFFERS ];
    XDAS_Int32       outBufSizes    [ XDM_MAX_IO_BUFFERS ];

    /* define the arrays describing I/O buffers and their sizes */
    encodedBufs[0]      = encodedBuf;
    encodedBufSizes[0]  = encodedBufSize;
    outBufs[0]          = outBuf;
    outBufSizes[0]      = outBufSize;

    /* define I/O buffer descriptors using lengths and addrs of arrays above */
    encodedBufDesc.numBufs  = 1;
    encodedBufDesc.bufs     = encodedBufs;
    encodedBufDesc.bufSizes = encodedBufSizes;
    outBufDesc.numBufs      = 1;
    outBufDesc.bufs         = outBufs;
    outBufDesc.bufSizes     = outBufSizes;

    /* fill in the input arguments structure */
    decoderInArgs.size = sizeof(decoderInArgs);
    decoderInArgs.numBytes = encodedBufSize;
    decoderOutArgs.size = sizeof(decoderOutArgs);

    /* decode the frame, pass addrs of the structures we populated above */
    status = AUDDEC_process(decHandle, &encodedBufDesc, &outBufDesc,
        &decoderInArgs, &decoderOutArgs);

    traceDump(ceHandle);

    if (status == AUDDEC_EOK) {
        retval = 0;
    }
    else {
        printf("CEapp-> AUDDEC_process() failed, status=%ld\n", status);
    }

    return (retval);
}


/*
 *  ======== ceapp_freeContigBuf ========
 */
void ceapp_freeContigBuf(char *buf, int bufSize)
{
    Memory_contigFree(buf, bufSize);
}


/*
 *  ======== ceapp_exit ========
 */
void ceapp_exit()
{
    /* teardown the codecs and the engine */
    if (encHandle != NULL) {
        AUDENC_delete(encHandle);
        traceDump(ceHandle);
    }
    if (decHandle != NULL) {
        AUDDEC_delete(decHandle);
        traceDump(ceHandle);
    }
    if (ceHandle != NULL) {
        Engine_close(ceHandle);
    }
}
/*
 *  @(#) ti.sdo.ce.examples.apps.audio_copy.dualcpu.evmDM6446; 1, 0, 0,84; 9-9-2008 02:00:32; /db/atree/library/trees/ce-h27x/src/
 */

