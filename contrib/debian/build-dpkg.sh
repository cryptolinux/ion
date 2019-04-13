#!/bin/bash
# copy this file to root of ion folder and run it to
BUILD_ROOT=/tmp/build-root/ioncore
mkdir -p $BUILD_ROOT
cp -r -f . $BUILD_ROOT
#mv -f $BUILD_ROOT/contrib/debian $BUILD_ROOT/debian
cd $BUILD_ROOT
dpkg-buildpackage -b -rfakeroot -us -uc