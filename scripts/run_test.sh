#! /usr/bin/bash

ROOT_DIR=$(dirname "${0}")/..

rm -rf $ROOT_DIR/build
mkdir $ROOT_DIR/build

cd $ROOT_DIR/build
cmake ..
make -j$(nproc)
ctest --output-on-failure
