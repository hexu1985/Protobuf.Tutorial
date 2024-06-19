#!/bin/bash

current_file_path=$(cd `dirname ${BASH_SOURCE[0]}` && pwd)
SRC_DIR=${current_file_path}/proto
DST_DIR=${current_file_path}/

mkdir -p $DST_DIR
protoc --proto_path generated=$SRC_DIR --python_out=$DST_DIR $SRC_DIR/person_info.proto
protoc --proto_path generated=$SRC_DIR --python_out=$DST_DIR $SRC_DIR/person.proto
