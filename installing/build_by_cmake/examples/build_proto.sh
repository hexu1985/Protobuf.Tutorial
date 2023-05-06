#!/bin/bash

current_file_path=$(cd `dirname ${BASH_SOURCE[0]}` && pwd)
SRC_DIR=${current_file_path}
DST_DIR=${current_file_path}

mkdir -p $DST_DIR
protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/addressbook.proto
