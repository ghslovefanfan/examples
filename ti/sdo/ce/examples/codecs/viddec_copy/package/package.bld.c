#define _concat(p,n) p ## n
#define myPrefixedVar(p,n) _concat(p,n)

/* create a string that can be used at runtime */
char * myPrefixedVar(__xdc_PKGPREFIX, _versionString) = "0, 0, 0";

/* create numeric array that can be used at runtime */
float myPrefixedVar(__xdc_PKGPREFIX, _versionNumArray)[] = {0, 0, 0};

/* create a string that will be reported by vers utility */
char * myPrefixedVar(__xdc_PKGPREFIX, _whatString) = "@(#) ti.sdo.ce.examples.codecs.viddec_copy" \
                             "; version 0, 0, 0" \
                             "; /opt/dvsdk_1_40_02_33/codec_engine_2_10_02/examples/" \
                             "; " __DATE__ " " __TIME__;

