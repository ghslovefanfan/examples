/*
 *  Copyright 2008 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== g711_sun.h ========
 */
#ifndef G711_SUN_INTERNAL_
#define G711_SUN_INTERNAL_

/*
 *  ======== linear2alaw ========
 * linear2alaw() - Convert a 16-bit linear PCM value to 8-bit A-law
 *
 * linear2alaw() accepts an 16-bit integer and encodes it as A-law data.
 *
 *              Linear Input Code       Compressed Code
 *      ------------------------        ---------------
 *      0000000wxyza                    000wxyz
 *      0000001wxyza                    001wxyz
 *      000001wxyzab                    010wxyz
 *      00001wxyzabc                    011wxyz
 *      0001wxyzabcd                    100wxyz
 *      001wxyzabcde                    101wxyz
 *      01wxyzabcdef                    110wxyz
 *      1wxyzabcdefg                    111wxyz
 *
 * For further information see John C. Bellamy's Digital Telephony, 1982,
 * John Wiley & Sons, pps 98-111 and 472-476.
 */
extern unsigned char G711_SUN_linear2alaw(short pcm_val); /* 2's complement (16-bit range) */

/*
 *  ======== alaw2linear ========
 * alaw2linear() - Convert an A-law value to 16-bit linear PCM
 *
 */
extern short G711_SUN_alaw2linear(unsigned char a_val);

/*
 *  ======== linear2ulaw ========
 * linear2ulaw() - Convert a linear PCM value to u-law
 *
 * In order to simplify the encoding process, the original linear magnitude
 * is biased by adding 33 which shifts the encoding range from (0 - 8158) to
 * (33 - 8191). The result can be seen in the following encoding table:
 *
 *      Biased Linear Input Code        Compressed Code
 *      ------------------------        ---------------
 *      00000001wxyza                   000wxyz
 *      0000001wxyzab                   001wxyz
 *      000001wxyzabc                   010wxyz
 *      00001wxyzabcd                   011wxyz
 *      0001wxyzabcde                   100wxyz
 *      001wxyzabcdef                   101wxyz
 *      01wxyzabcdefg                   110wxyz
 *      1wxyzabcdefgh                   111wxyz
 *
 * Each biased linear code has a leading 1 which identifies the segment
 * number. The value of the segment number is equal to 7 minus the number
 * of leading 0's. The quantization interval is directly available as the
 * four bits wxyz.  * The trailing bits (a - h) are ignored.
 *
 * Ordinarily the complement of the resulting code word is used for
 * transmission, and so the code word is complemented before it is returned.
 *
 * For further information see John C. Bellamy's Digital Telephony, 1982,
 * John Wiley & Sons, pps 98-111 and 472-476.
 */
extern unsigned char G711_SUN_linear2ulaw(short pcm_val); /* 2's complement (16-bit range) */

/*
 *  ======== ulaw2linear ========
 * ulaw2linear() - Convert a u-law value to 16-bit linear PCM
 *
 * First, a biased linear code is derived from the code word. An unbiased
 * output can then be obtained by subtracting 33 from the biased code.
 *
 * Note that this function expects to be passed the complement of the
 * original code word. This is in keeping with ISDN conventions.
 */
extern short G711_SUN_ulaw2linear(unsigned char u_val);

/*
 *  ======== alaw2ulaw ========
 * A-law to u-law conversion
 */
extern unsigned char G711_SUN_alaw2ulaw(unsigned char aval);

/*
 *  ======== ulaw2alaw ========
 *  u-law to A-law conversion
 */
extern unsigned char G711_SUN_ulaw2alaw(unsigned char uval);

#endif  /* G711_SUN_ */
/*
 *  @(#) ti.xdais.dm.examples.g711; 1, 0, 0,131; 5-8-2008 09:06:05; /db/wtree/library/trees/dais-j06x/src/
 */

