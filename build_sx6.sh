#!/bin/bash
#
# This file requires ENV_PATH_GCC and ENV_PATH_SYSROOT path variables to be set.
# User can either set them manually, or create an "env_paths.vf6" file
# to set them automatically before each run.

if [ $# -lt 1 ] || [ $# -gt 2 ]; then
	echo "Calling sequence: $0 BOARD [VARIANT]"
	exit 1
fi
BOARD=$1
PADFILE=pad.tmp

[ -f $PADFILE ] && rm $PADFILE

if [ $# -eq 2 ]; then
	VARIANT=$2
	CONFIG=${BOARD}_${VARIANT}_config
	OUTPUT=u-boot-${VARIANT}.${BOARD}
else
	VARIANT=""
	CONFIG=${BOARD}_config
	OUTPUT=u-boot.${BOARD}
fi

case $VARIANT in
	* ) touch $PADFILE ;;
esac


[ -f env_paths.sx6 ] && source env_paths.sx6

export PATH=$PATH:$ENV_PATH_GCC
export CROSS_COMPILE=arm-poky-linux-gnueabi-
export CC="${CROSS_COMPILE}gcc --sysroot=$ENV_PATH_SYSROOT"

make clean
make distclean
make CC="$CC" $CONFIG
make CC="$CC" V=1 u-boot.imx

cat $PADFILE u-boot.imx > $OUTPUT
rm $PADFILE
