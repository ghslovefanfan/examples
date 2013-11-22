/*!
 *  ======== package.xdc ========
 *  Codec Engine encode-decode example which utilizes speech codecs that
 *  implement the 0.9 xDM speech interfaces.
 *
 *  This example is a modified version of the general speech_copy example, 
 *  built specifically for the MVArm9 and UCArm9 targets, which uses the Link 
 *  Abiter Daemon, (LAD), for shared access of a DSP server.
 *
 *  This example builds using the XDC build tools, and is portable to
 *  several execution environments.  The following files are
 *  included in this package:
 *  @p(dlist)
 *	- `package.xdc`
 *	    This file is required to declare a globally unique name for this
 *	    package.
 *	- `package.bld`
 *	    This file is the build script describing the application to the
 *	    XDC built tools.
 *	- `makefile`
 *	    A usability makefile wrapper around the XDC build tools.
 *	- `remote.cfg`
 *	    The XDC configuration file for this executable, when configured
 *	    to run "remote" codecs.  This is the typical configuration for
 *	    multiple processor execution environments.
 *	- `app.c`
 *	    The primary source file for this executable.
 *	- `main_native.c`
 *	    The execution runtime-specific entry point for this executable.
 *	    This isolates any runtime-specific startup code from the generic
 *	    application.
 */
package ti.sdo.ce.examples.apps.speech_copy_LAD [1, 0, 0] {
}
