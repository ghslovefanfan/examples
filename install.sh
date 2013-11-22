#!/bin/sh


WORKGROUP=/opt/dvsdk_1_40_02_33
CE_INSTALL_DIR=$WORKGROUP/codec_engine_2_10_02
XDC_INSTALL_DIR=$WORKGROUP/xdc_3_00_06
BIOS_INSTALL_DIR=$WORKGROUP/bios_5_32_01
XDAIS_INSTALL_DIR=$WORKGROUP/xdais_6_10_01
DSPLINK_INSTALL_DIR=$WORKGROUP/dsplink-davinci-v1.50-prebuilt
CMEM_INSTALL_DIR=$WORKGROUP/cmem_2_10
FC_INSTALL_DIR=$WORKGROUP/framework_components_2_10_02
BIOSUTILS_INSTALL_DIR=$WORKGROUP/biosutils_1_01_00

ROOT=$CE_INSTALL_DIR/examples/ti/sdo/ce/examples/
DESTDIR=/$DESTDIR

echo "step 0: make clean --------------------->"
if [ "$1" = clean ];then
	make -C $ROOT/codecs/videnc_copy/ clean
	make -C $ROOT/codecs/viddec_copy/ clean
	make -C $ROOT/servers/video_copy/evmDM6467/ clean
	make -C $ROOT/apps/video_copy/dualcpu/evmDM6467 clean
fi
echo "step 1: make codecs --------------------->"
cd $ROOT/codecs/videnc_copy/ && make
cd $ROOT/codecs/viddec_copy/ && make
echo "step 2: make servers --------------------->"
cd $ROOT/servers/video_copy/evmDM6467/ && make
echo "step 3: make apps --------------------->"
cd $ROOT/apps/video_copy/dualcpu/evmDM6467 && make

echo "step 4: Installing video_copy to /opt/nfs/opt/dm6467/video_copy"
rm $DESTDIR/dm6467/video_copy -rf
mkdir /$DESTDIR/dm6467/video_copy -p
cp $ROOT/servers/video_copy/evmDM6467/video_copy.x64P $DESTDIR/dm6467/video_copy/
cp $ROOT/apps/video_copy/dualcpu/evmDM6467/app.out $DESTDIR/dm6467/video_copy
cp $ROOT/apps/video_copy/dualcpu/evmDM6467/in.dat $DESTDIR/dm6467/video_copy

#cp /opt/dvsdk_1_40_02_33/codec_engine_2_10_02/examples/apps/system_files/davinci/DM6467/*.ko $DESTDIR/dm6467/video_copy/
cp $CE_INSTALL_DIR/examples/apps/system_files/davinci/DM6467/*.sh $DESTDIR/dm6467/video_copy/
cp $DSPLINK_INSTALL_DIR/packages/dsplink/gpp/export/BIN/Linux/Davinci/DM6467/RELEASE/dsplinkk.ko  $DESTDIR/dm6467/video_copy/
cp $CMEM_INSTALL_DIR/packages/ti/sdo/linuxutils/cmem/src/module/cmemk.ko $DESTDIR/dm6467/video_copy/

echo "ls /opt/nfs/opt/dm6467/video_copy"
chmod 777 $DESTDIR/dm6467/video_copy
ls $DESTDIR/dm6467/video_copy
