/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

requires ti.xdais.dm.examples.g711;

/*!
 *  ======== package.xdc ========
 *  Simple Codec Engine compatible 'wrapper package',
 *  enabling the G.711 encoder and decoder codecs
 *  distributed with xDAIS to be integrated into a Codec Engine-based
 *  system.
 *
 *  This codec illustrates how to provide Codec Engine-specific
 *  packaging around an existing algorithm.  It also demonstrates how
 *  a single codec package can supply more than one codec - in this
 *  case, both the encoder and decoder codecs are supported by this
 *  single codec package.
 *
 *  Five files are required to integrate into the Codec Engine:
 *  @p(dlist)
 *      - `package.xdc`
 *          This file is required to declare a globally unique name
 *          for this package and to list all codec interfaces
 *          available.  This package has two interfaces, G711ENC and
 *          G711DEC.
 *      - `G711ENC.xdc`
 *          This file defines the G711ENC codec, which implements
 *          the ti.sdo.ce.speech1.ISPHENC1 interface.
 *      - `G711ENC.xs`
 *          This file implements the functions required by the ISPHENC1
 *          interface; these functions enable the codec to describe its
 *          non-functional requirements such as stack size.
 *      - `G711DEC.xdc`
 *          This file defines the G711DEC codec, which implements
 *          the ti.sdo.ce.speech1.ISPHDEC1 interface.
 *      - `G711DEC.xs`
 *          This file implements the functions required by the ISPHDEC1
 *          interface; these functions enable the codec to describe its
 *          non-functional requirements such as stack size.
 *
 *  Integration into the Codec Engine requires no change to the codecs
 *  libraries.
 */
package ti.sdo.ce.examples.codecs.g711 [1, 0, 0] {
    module G711ENC;
    module G711DEC;
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.g711; 1, 0, 0,131; 9-9-2008 02:02:44; /db/atree/library/trees/ce-h27x/src/
 */

