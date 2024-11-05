cmake -Hcmake -Bbuild \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_INSTALL_PREFIX=~/local/protobuf
VERBOSE=1 cmake --build build --parallel 4 --target install
