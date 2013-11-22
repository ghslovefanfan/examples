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
 */
#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/examples/extensions/scale/scale.h>
#include <ti/sdo/ce/trace/gt.h>

#include <stdio.h>
#include <stdlib.h>

#define NSAMPLES    1024
#define IFRAMESIZE  (NSAMPLES * sizeof(Int8))  /* raw frame (input) */
#define OFRAMESIZE  (NSAMPLES * sizeof(Int8))  /* scaled frame (output) */

#define APP_SCALEFACTOR 2

static XDAS_Int8 *inBuf;
static XDAS_Int8 *outBuf;

static String progName     = "app";
static String scaleName    = "scale";
static String engineName   = "scale";

static String usage = "%s: input-file output-file\n";

static Void scale(SCALE_Handle algo, FILE *in, FILE *out);

extern GT_Mask curMask;

/*
 *  ======== smain ========
 */
Int smain(Int argc, String argv[])
{
    Engine_Handle ce = NULL;
    SCALE_Handle codec = NULL;
    SCALE_Params params;
    FILE *in = NULL;
    FILE *out = NULL;
    String inFile, outFile;

    if (argc <= 1) {
        inFile = "../in.dat";
        outFile = "../out.dat";
    }
    else if (argc == 3) {
        progName = argv[0];
        inFile = argv[1];
        outFile = argv[2];
    }
    else {
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }

    printf("App-> Application started.\n");

    /* allocate input, encoded, and output buffers */
    inBuf = (XDAS_Int8 *)Memory_contigAlloc(IFRAMESIZE,
        Memory_DEFAULTALIGNMENT);
    outBuf = (XDAS_Int8 *)Memory_contigAlloc(OFRAMESIZE,
        Memory_DEFAULTALIGNMENT);

    if ((inBuf == NULL) || (outBuf == NULL)) {
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

    /* initialize scale factor */
    params.size = sizeof(SCALE_Params);
    params.initialScaleFactor = APP_SCALEFACTOR;

    /* allocate and initialize scale algo on the engine */
    codec = SCALE_create(ce, scaleName, &params);
    if (codec == NULL) {
        printf( "App-> ERROR: can't open codec %s\n", scaleName);
        goto end;
    }

    /* use engine to encode, then decode the data */
    scale(codec, in, out);

end:
    /* teardown the codec */
    if (codec) {
        SCALE_delete(codec);
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

    printf("app done.\n");
    return (0);
}

/*
 *  ======== scale ========
 */
static Void scale(SCALE_Handle codec, FILE *in, FILE *out)
{
    Int                         n;
    Int32                       status;

    SCALE_InArgs                scaleInArgs;
    SCALE_OutArgs               scaleOutArgs;

    /*
     * Read complete frames from in, encode, decode, and write to out.
     */
    for (n = 0; fread(inBuf, IFRAMESIZE, 1, in) == 1; n++) {
        printf("App-> Processing frame %d...\n", n);

        scaleInArgs.inBufSize = IFRAMESIZE;
        scaleInArgs.outBufSize = OFRAMESIZE;
        scaleInArgs.inBufValidBytes = IFRAMESIZE;

        /* scale the frame */
        status = SCALE_process(codec, inBuf, outBuf, &scaleInArgs,
            &scaleOutArgs);

        GT_2trace(curMask, GT_2CLASS, "App-> Scaled frame %d (0x%x)\n",
            n, status);

        if (status == SCALE_EOK) {
            GT_1trace(curMask, GT_2CLASS, "\toutArgs:  (0x%x)\n",
                scaleOutArgs.outBufValidBytes);
        }
        else {
            /* failure, exit the processing loop */
            break;
        }

        /* write to file */
        fwrite(outBuf, OFRAMESIZE, 1, out);
    }

    printf("%d frames scaled\n", n);
}
/*
 *  @(#) ti.sdo.ce.examples.apps.scale; 1,0,0,135; 9-9-2008 02:00:58; /db/atree/library/trees/ce-h27x/src/
 */

