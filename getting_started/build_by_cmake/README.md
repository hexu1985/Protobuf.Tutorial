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


**项目依赖protobuf库：Makefile**

需要指定protobuf库，通过-lprotobuf指定

需要-I指定protobuf头文件的安装路径

需要-L指定protobuf库的安装路径


**项目依赖protobuf库：CMake，通过find_package**

通过find_package查找protobuf（并不需要设置include_directories）

```
find_package(protobuf CONFIG REQUIRED)
```

通过target_link_libraries链接protobuf库（并不需要设置link_directories）

```
target_link_libraries(add_person protobuf::libprotobuf)
```

编译项目需要设置protobuf_DIR路径：

```
$ cmake -H. -Bbuild \
    -DCMAKE_BUILD_TYPE=Debug \
    -Dprotobuf_DIR=~/local/protobuf/lib/cmake/protobuf
$ cmake --build build
```
