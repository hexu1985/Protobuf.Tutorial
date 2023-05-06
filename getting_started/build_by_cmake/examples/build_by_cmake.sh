#!/usr/bin/env bash

cd `dirname ${BASH_SOURCE[0]}`
cmake -H. -Bbuild \
    -DCMAKE_BUILD_TYPE=Debug \
    -Dprotobuf_DIR=~/local/protobuf/lib/cmake/protobuf
VERBOSE=1 cmake --build build
echo "target dir is build"
