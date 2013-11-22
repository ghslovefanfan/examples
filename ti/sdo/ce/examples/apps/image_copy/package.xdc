/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== package.xdc ========
 *  Codec Engine encode-decode example which utilizes image codecs that
 *  implement the 0.9 xDM image interfaces.
 *
 *  This example builds using the XDC build tools, and is portable to
 *  several execution environments.  The following files are
 *  included in this package:
 *  @p(dlist)
 *      - `package.xdc`
 *          This file is required to declare a globally unique name for this
 *          package.
 *      - `package.bld`
 *          This file is the build script describing the application to the
 *          XDC built tools.
 *      - `makefile`
 *          A usability makefile wrapper around the XDC build tools.
 *      - `local.cfg`
 *          The XDC configuration file for this executable, when configured
 *          to run "local" codecs.  This is the typical configuration for
 *          single processor excution environments.
 *      - `local.tcf`
 *          The BIOS configuration file for this executable.  This file is
 *          only necessary when building for a BIOS runtime environment.
 *          It's base name must match that of the XDC config file.
 *      - `remote.cfg`
 *          The XDC configuration file for this executable, when configured
 *          to run "remote" codecs.  This is the typical configuration for
 *          multiple processor excution environments.
 *      - `app.c`
 *          The primary source file for this executable.
 *      - `main.c` and `main_native.c`
 *          The execution runtime-specific entry point for this executable.
 *          This isolates any runtime-specific startup code from the generic
 *          application.
 */
package ti.sdo.ce.examples.apps.image_copy {
}
/*
 *  @(#) ti.sdo.ce.examples.apps.image_copy; 1,0,0,135; 9-9-2008 02:00:49; /db/atree/library/trees/ce-h27x/src/
 */

