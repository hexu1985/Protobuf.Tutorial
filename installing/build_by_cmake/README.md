### protobuf编译安装与使用

**用cmake编译安装protobuf**

以下命令可以通过cmake编译protobuflib

```
$ git clone https://github.com/protocolbuffers/protobuf.git
$ cd protobuf 
$ cmake -Hcmake -Bbuild \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_INSTALL_PREFIX=~/local/protobuf
$ VERBOSE=1 cmake --build build --parallel 4 --target install
```

如果需要编译动态库，需要增加`BUILD_SHARED_LIBS=ON`

CMAKE_INSTALL_PREFIX指定安装目录前缀，可能需要sudo权限执行install命令

protoc被安装在`${CMAKE_INSTALL_PREFIX}/bin`目录下，需要添加到PATH环境变量

```
$ export PATH=~/local/protobuf/bin/:$PATH
```
