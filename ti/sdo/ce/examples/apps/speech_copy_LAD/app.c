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
 *  ======== app.c ========
 */
#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/speech/sphdec.h>
#include <ti/sdo/ce/speech/sphenc.h>
#include <ti/sdo/ce/trace/gt.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NSAMPLES    1024
#define IFRAMESIZE  (NSAMPLES * sizeof(Int8))  /* raw frame (input) */
#define EFRAMESIZE  (NSAMPLES * sizeof(Int8))  /* encoded frame */
#define OFRAMESIZE  (NSAMPLES * sizeof(Int8))  /* decoded frame (output) */

static XDAS_Int8 *inBuf;
static XDAS_Int8 *encodedBuf;
static XDAS_Int8 *outBuf;

static String progName     = "app";
static String decoderName  = "sphdec_copy";
static String encoderName  = "sphenc_copy";
static String engineName   = "speech_copy";

/*
 * USAGE NOTES: 
 *   1) LAD must be started before executing this app.
 *   2) When invoked with no arguments: in.dat is input file, out.dat is output
 *       file, and there is no delay inserted between frames.
 *   3) When invoked with three arguments: arg1 is input file, arg2 is output
 *      file, and arg3 is the delay (in seconds) to be inserted between frames.
 *      Example:
 *          ./app_remote.x470MV in.dat out2.dat 1
 */
static String usage = "%s: [input-file output-file framedelay]\n";

static Void encode_decode(SPHENC_Handle enc, SPHDEC_Handle dec, FILE *in,
    FILE *out, Int framedelay);

extern GT_Mask curMask;

/*
 *  ======== smain ========
 */
Int smain(Int argc, String argv[])
{
    Engine_Handle ce = NULL;
    SPHDEC_Handle dec = NULL;
    SPHENC_Handle enc = NULL;
    FILE *in = NULL;
    FILE *out = NULL;
    String inFile, outFile;
    Int framedelay = 0;

    if (argc == 1) {
        inFile = "in.dat";
        outFile = "out.dat";
    }
    else if (argc == 4) {
        progName = argv[0];
        inFile = argv[1];
        outFile = argv[2];
        framedelay = atoi(argv[3]);
    }
    else {
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }

    printf( "App-> Application started.\n");

    /* allocate input, encoded, and output buffers */
    inBuf = (XDAS_Int8 *)Memory_contigAlloc(IFRAMESIZE,
        Memory_DEFAULTALIGNMENT);
    encodedBuf = (XDAS_Int8 *)Memory_contigAlloc(EFRAMESIZE,
        Memory_DEFAULTALIGNMENT);
    outBuf = (XDAS_Int8 *)Memory_contigAlloc(OFRAMESIZE,
        Memory_DEFAULTALIGNMENT);

    if ((inBuf == NULL) || (encodedBuf == NULL) || (outBuf == NULL)) {
        goto end;
    }

    /* open file streams for input and output */
    if ((in = fopen(inFile, "rb")) == NULL) {
        printf("App-> ERROR: can't read file %s\n", inFile);
        goto end;
    }
    if ((out = fopen(outFile, "wb")) == NULL) {
        printf("App-> ERROR: can't write to file %s\n", outFile);
        goto end;
    }

    /* reset, load, and start DSP Engine */
    if ((ce = Engine_open(engineName, NULL, NULL)) == NULL) {
        fprintf(stderr, "%s: error: can't open engine %s\n",
            progName, engineName);
        goto end;
    }

    /* allocate and initialize video decoder on the engine */
    dec = SPHDEC_create(ce, decoderName, NULL);
    if (dec == NULL) {
        printf( "App-> ERROR: can't open codec %s\n", decoderName);
        goto end;
    }

    /* allocate and initialize video encoder on the engine */
    enc = SPHENC_create(ce, encoderName, NULL);
    if (enc == NULL) {
        fprintf(stderr, "%s: error: can't open codec %s\n",
            progName, encoderName);
        goto end;
    }

    /* use engine to encode, then decode the data */
    encode_decode(enc, dec, in, out, framedelay);

end:
    /* teardown the codecs */
    if (enc) {
        SPHENC_delete(enc);
    }
    if (dec) {
        SPHDEC_delete(dec);
    }

    /* close the engine */
    if (ce) {
        Engine_close(ce);
    }

    /* close the files */
    if (in) {
        fclose(in);
    }
    if (out) {
        fclose(out);
    }

    /* free buffers */
    if (inBuf) {
        Memory_contigFree(inBuf, IFRAMESIZE);
    }
    if (encodedBuf) {
        Memory_contigFree(encodedBuf, EFRAMESIZE);
    }
    if (outBuf) {
        Memory_contigFree(outBuf, OFRAMESIZE);
    }

    printf("app done.\n");
    return (0);
}

/*
 *  ======== encode_decode ========
 */
static Void encode_decode(SPHENC_Handle enc, SPHDEC_Handle dec, FILE *in,
    FILE *out, Int framedelay)
{
    Int                         n;
    XDM_BufDesc                 inBufDesc;
    XDM_BufDesc                 encodedBufDesc;
    XDM_BufDesc                 outBufDesc;
    Int32                       status;
    XDAS_Int32                  bufSizes = NSAMPLES;

    SPHDEC_InArgs               decInArgs;
    SPHDEC_OutArgs              decOutArgs;
    SPHDEC_DynamicParams        decDynParams;
    SPHDEC_Status               decStatus;

    SPHENC_InArgs               encInArgs;
    SPHENC_OutArgs              encOutArgs;
    SPHENC_DynamicParams        encDynParams;
    SPHENC_Status               encStatus;

    /* prepare "global" buffer descriptor settings */
    inBufDesc.numBufs = encodedBufDesc.numBufs = outBufDesc.numBufs = 1;
    inBufDesc.bufSizes = encodedBufDesc.bufSizes = outBufDesc.bufSizes =
        &bufSizes;

    encInArgs.size = sizeof(encInArgs);
    decInArgs.size = sizeof(decInArgs);
    encOutArgs.size = sizeof(encOutArgs);
    decOutArgs.size = sizeof(decOutArgs);
    encDynParams.size = sizeof(encDynParams);
    decDynParams.size = sizeof(decDynParams);
    encStatus.size = sizeof(encStatus);
    decStatus.size = sizeof(decStatus);

    /*
     * Query the encoder and decoder.
     * This app expects the encoder to provide 1 buf in and get 1 buf out,
     * and the buf sizes of the in and out buffer must be able to handle
     * NSAMPLES bytes of data.
     */
    status = SPHENC_control(enc, XDM_GETSTATUS, &encDynParams,
        &encStatus);
    if (status != SPHENC_EOK) {
        /* failure, report error and exit */
        printf("encode control status = %ld\n", status);
        return;
    }

    /* Validate this encoder codec will meet our buffer requirements */
    if ((inBufDesc.numBufs < encStatus.bufInfo.minNumInBufs) ||
        (IFRAMESIZE < encStatus.bufInfo.minInBufSize[0]) ||
        (encodedBufDesc.numBufs < encStatus.bufInfo.minNumOutBufs) ||
        (EFRAMESIZE < encStatus.bufInfo.minOutBufSize[0])) {

        /* failure, report error and exit */
        printf("Error:  encoder codec feature conflict\n");
        return;
    }

    status = SPHDEC_control(dec, XDM_GETSTATUS, &decDynParams,
        &decStatus);
    if (status != SPHDEC_EOK) {
        /* failure, report error and exit */
        printf("decode control status = %ld\n", status);
        return;
    }

    /* Validate this decoder codec will meet our buffer requirements */
    if ((encodedBufDesc.numBufs < decStatus.bufInfo.minNumInBufs) ||
        (EFRAMESIZE < decStatus.bufInfo.minInBufSize[0]) ||
        (outBufDesc.numBufs < decStatus.bufInfo.minNumOutBufs) ||
        (OFRAMESIZE < decStatus.bufInfo.minOutBufSize[0])) {

        /* failure, report error and exit */
        printf("App-> ERROR: decoder does not meet buffer requirements.\n");
        return;
    }

    /*
     * Read complete frames from in, encode, decode, and write to out.
     */
    for (n = 0; fread(inBuf, IFRAMESIZE, 1, in) == 1; n++) {
        XDAS_Int8 *src     = inBuf;
        XDAS_Int8 *encoded = encodedBuf;
        XDAS_Int8 *dst     = outBuf;

        printf("App-> Processing frame %d...\n", n);

        /* prepare "per loop" buffer descriptor settings */
        inBufDesc.bufs = &src;
        encodedBufDesc.bufs = &encoded;
        outBufDesc.bufs = &dst;

        /* encode the frame */
        status = SPHENC_process(enc, &inBufDesc, &encodedBufDesc, &encInArgs,
            &encOutArgs);

        if (status != SPHENC_EOK) {
            printf("App-> Encoder frame %d processing FAILED, status = %ld\n",
                    n, status);
        }

        /* decode the frame */
        status = SPHDEC_process(dec, &encodedBufDesc, &outBufDesc, &decInArgs,
           &decOutArgs);

        if (status != SPHDEC_EOK) {
            printf("frame %d: decode status = %ld\n", n, status);
        }

        /* write to file */
        fwrite(dst, OFRAMESIZE, 1, out);
 
        /* sleep optional number of seconds between frames */
        sleep(framedelay);
    }

    printf("%d frames encoded/decoded\n", n);
}
