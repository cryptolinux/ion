#!/bin/bash
# Copyright (c) 2019 The Ion developers
# copy this file to root of ion folder and run it to
# How to use: run from ion run 
#
#    ./contrib/debian/build-dpkg.sh
#
#    You can pass one variable, as example if you want
#    want to ignore missing dependencies:
#    
#    ./contrib/debian/build-dpkg.sh -d
#
BUILD_ROOT=/tmp/build-root/ioncore;
mkdir -p $BUILD_ROOT;
cp -r -f . $BUILD_ROOT;
cd $BUILD_ROOT;
dpkg-buildpackage -b -rfakeroot -us -uc ${1};