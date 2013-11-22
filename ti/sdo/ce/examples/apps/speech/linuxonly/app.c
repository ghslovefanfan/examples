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
 *  ======== app.c ========
 *  Illustrate use of "abstract" speech encoder.
 */
#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/speech1/sphenc1.h>
#include <ti/xdais/xdas.h>

#include <stdio.h>
#include <stdlib.h>

#define BUFALIGN Memory_DEFAULTALIGNMENT

#define NSAMPLES    32
#define IFRAMESIZE  (NSAMPLES * sizeof(Int16))  /* raw frame (input) */
#define OFRAMESIZE  (NSAMPLES * sizeof(Int8))   /* encoded frame (output) */
#define MAXVERSIONSIZE 128

static XDAS_Int8 *inBuf;
static XDAS_Int8 *outBuf;
static XDAS_Int8 *versionBuf;   /* acquire optional version from codec */

static String progName     = "app";
static String codecName    = "sphenc";
static String engineName   = "vcr";

static String usage = "%s: input-file output-file\n";

static Void encode(SPHENC1_Handle enc, FILE *in, FILE *out);

/*
 *  ======== smain ========
 */
Int smain(Int argc, String argv[])
{
    Engine_Handle ce = NULL;
    SPHENC1_Handle enc = NULL;
    FILE *in = NULL;
    FILE *out = NULL;
    String inFile, outFile;

    if (argc <= 1) {
        inFile = "in.dat";
        outFile = "out.dat";
    }
    else if (argc != 3) {
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }
    else {
        progName = argv[0];
        inFile = argv[1];
        outFile = argv[2];
    }

    printf( "App-> Application started.\n");

    /* allocate input, output, and version string buffers */
    inBuf = (XDAS_Int8 *)Memory_contigAlloc(IFRAMESIZE, BUFALIGN);
    outBuf = (XDAS_Int8 *)Memory_contigAlloc(OFRAMESIZE, BUFALIGN);
    versionBuf = (XDAS_Int8 *)Memory_contigAlloc(MAXVERSIONSIZE, BUFALIGN);

    if ((inBuf == NULL) || (outBuf == NULL) || (versionBuf == NULL)) {

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

    /* allocate and initialize speech encoder on engine, with default params */
    enc = SPHENC1_create(ce, codecName, NULL);
    if (enc == NULL) {
        fprintf(stderr, "%s: error: can't open codec %s\n",
            progName, codecName);
        goto end;
    }

    /* use engine to encode data */
    encode(enc, in, out);

end:
    /* teardown the codec */
    if (enc) {
        SPHENC1_delete(enc);
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
    if (outBuf) {
        Memory_contigFree(outBuf, OFRAMESIZE);
    }
    if (versionBuf) {
        Memory_contigFree(versionBuf, MAXVERSIONSIZE);
    }

    printf("app done.\n");
    return (0);
}

/*
 *  ======== encode ========
 */
static Void encode(SPHENC1_Handle enc, FILE *in, FILE *out)
{
    Int                         n;
    XDM1_SingleBufDesc          inBufDesc;
    XDM1_SingleBufDesc          outBufDesc;
    Int32                       status;
    XDAS_Int32                  bufSize = NSAMPLES;

    SPHENC1_InArgs              encInArgs;
    SPHENC1_OutArgs             encOutArgs;
    SPHENC1_DynamicParams       encDynParams;
    SPHENC1_Status              encStatus;

    /* prepare "global" buffer descriptor settings */
    inBufDesc.bufSize = bufSize * sizeof(short);
    outBufDesc.bufSize = bufSize * sizeof(char);

    /* initialize all "sized" fields */
    encInArgs.size    = sizeof(encInArgs);
    encOutArgs.size   = sizeof(encOutArgs);
    encDynParams.size = sizeof(encDynParams);
    encStatus.size    = sizeof(encStatus);
    encStatus.data.buf     = versionBuf;
    encStatus.data.bufSize = MAXVERSIONSIZE;

    status = SPHENC1_control(enc, XDM_GETVERSION, &encDynParams, &encStatus);
    printf("Encoder version:  %s\n",
        (status == SPHENC1_EOK ? ((char *)encStatus.data.buf) : "[unknown]"));

    /*
     * Note that this function is not yet complete.  It's functional, but not
     * a good example to start from - yet.
     */

    /* prepare "global" buffer descriptor settings */
/*    inBufDesc.bufSizes = outBufDesc.bufSizes = */

    encInArgs.size = sizeof(encInArgs);

    /*
     * Read complete frames from in, encode, and write to out.
     */
    for (n = 0; fread(inBuf, IFRAMESIZE, 1, in) == 1; n++) {
        printf("App-> Processing frame %d...\n", n);

        /* prepare "per loop" buffer descriptor settings */
        inBufDesc.buf = inBuf;
        outBufDesc.buf = outBuf;

        /* encode the frame */
        status = SPHENC1_process(enc, &inBufDesc, &outBufDesc, &encInArgs,
            &encOutArgs);

        if (status != SPHENC1_EOK) {
            printf("App-> Encoder frame %d processing FAILED, status = 0x%x, "
                "extendedError = 0x%x\n", n, status, encOutArgs.extendedError);
            break;
        }

        /* write to file */
        fwrite(outBuf, OFRAMESIZE, 1, out);
    }

    printf("%d frames encoded\n", n);
}
/*
 *  @(#) ti.sdo.ce.examples.apps.speech.linuxonly; 1,0,0,134; 9-9-2008 02:01:16; /db/atree/library/trees/ce-h27x/src/
 */

