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
 *  Codec Engine example application for pulling and optionally saving to files
 *  DSP server trace and LOG data.
 *
 *  This example is built only for the MVArm9 and UCArm9 targets, and requires
 *  the Link Abiter Daemon, (LAD), for shared access of a DSP server.
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
 *      - `remote.cfg`
 *          The XDC configuration file for this executable, when configured
 *          to run "remote" codecs.
 *      - `trace.c`
 *          The primary source file for this executable.
 *      - `main_native.c`
 *          The execution runtime-specific entry point for this executable.
 *          This isolates any runtime-specific startup code from the generic
 *          application.
 */
package ti.sdo.ce.examples.apps.server_trace {
}
/*
 *  @(#) ti.sdo.ce.examples.apps.server_trace; 1,0,0,89; 9-9-2008 02:01:09; /db/atree/library/trees/ce-h27x/src/
 */

