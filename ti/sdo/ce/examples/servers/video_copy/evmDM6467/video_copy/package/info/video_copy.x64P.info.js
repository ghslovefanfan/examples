{
    "server algorithms": {
        "programName": "video_copy.x64P",
        "algs": [
            {
                "mod": "ti.sdo.ce.examples.codecs.viddec_copy.VIDDEC_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.viddec_copy",
                "rpcProtocolVersion": 3,
                "ialgFxns": "VIDDECCOPY_TI_VIDDECCOPY",
                "threadAttrs": {
                    "priority": 2,
                },
                "groupId": 0,
                "serverFxns": "VIDDEC_SKEL",
                "stubFxns": "VIDDEC_STUBS",
                "name": "viddec_copy",
                "pkgVersion": [
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.videnc_copy.VIDENC_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.videnc_copy",
                "rpcProtocolVersion": 3,
                "idma3Fxns": "VIDENCCOPY_TI_IDMA3",
                "ialgFxns": "VIDENCCOPY_TI_VIDENCCOPY",
                "threadAttrs": {
                    "priority": 2,
                },
                "groupId": 0,
                "serverFxns": "VIDENC_SKEL",
                "stubFxns": "VIDENC_STUBS",
                "name": "videnc_copy",
                "pkgVersion": [
                ],
            },
        ],
    },
    "DSP memory map": [
        [
            "DDR2",
            {
                "addr": 0x8FA00000,
                "type": "main",
                "size": 0x00400000,
            },
        ],
        [
            "RESET_VECTOR",
            {
                "addr": 0x8FF00000,
                "type": "reset",
                "size": 128,
            },
        ],
        [
            "DDRALGHEAP",
            {
                "addr": 0x88000000,
                "type": "other",
                "size": 0x07A00000,
            },
        ],
        [
            "DSPLINKMEM",
            {
                "addr": 0x8FE00000,
                "type": "link",
                "size": 0x00100000,
            },
        ],
    ],
}
