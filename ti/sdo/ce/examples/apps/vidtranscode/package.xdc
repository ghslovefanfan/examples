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
 *  Codec Engine transcode example which utilizes codecs that
 *  implement the xDM video transcode interface.
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
 *      - `main_BIOS.c` and `main_native.c`
 *          The execution runtime-specific entry point for this executable.
 *          This isolates any runtime-specific startup code from the generic
 *          application.
 */
package ti.sdo.ce.examples.apps.vidtranscode {
}
/*
 *  @(#) ti.sdo.ce.examples.apps.vidtranscode; 1,0,0,96; 9-9-2008 02:02:13; /db/atree/library/trees/ce-h27x/src/
 */

