### any类型

> 源文件: include/google/protobuf/any.proto

```
syntax = "proto3";

package google.protobuf;

option csharp_namespace = "Google.Protobuf.WellKnownTypes";
option go_package = "google.golang.org/protobuf/types/known/anypb";
option java_package = "com.google.protobuf";
option java_outer_classname = "AnyProto";
option java_multiple_files = true;
option objc_class_prefix = "GPB";

message Any {
  string type_url = 1;
  bytes value = 2;
}
```

去掉注释之后，也就一个 message，type_url 用来存储类型描述信息，value 用来存储序列化（ C++ 是SerializeToString 函数）之后的字符串。


以示例代码为例:

```cpp
#include <cstdio>
#include <iostream>

#include "test.pb.h"

//输出十六进制编码
static void dump_hexstring(const std::string& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        printf("%02x ", (unsigned char)data[i]);
    }
    printf("\n");
}

//输出ASCII编码
static void dump_asciistring(const std::string& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        printf(" %c ", ((data[i] > 31) && (data[i] < 128)) ? data[i] : '.');
    }
    printf("\n");
}

static void test_1() {
    mytest::SubTest st1;
    st1.set_i32(1);
    mytest::Test t1;
    t1.mutable_any()->PackFrom(st1);  //field_number = 21, wire_type = 2 (Lenth-Delimited)
    //std::cout << t1.any().type_url() << std::endl;
    std::string buf;
    t1.SerializeToString(&buf);
    printf("==== test_1 ====\n");
    dump_hexstring(buf);
    dump_asciistring(buf);
}

int main() {
    test_1();
    return 0;
}
```

编译和执行结果：

```
==== test_1 ====
aa 01 28 0a 22 74 79 70 65 2e 67 6f 6f 67 6c 65 61 70 69 73 2e 63 6f 6d 2f 6d 79 74 65 73 74 2e 53 75 62 54 65 73 74 12 02 08 01
 .  .  (  .  "  t  y  p  e  .  g  o  o  g  l  e  a  p  i  s  .  c  o  m  /  m  y  t  e  s  t  .  S  u  b  T  e  s  t  .  .  .  .
```

分析结果:

```
aa 01           |__ Tag
28              |__ Length (40个字符)
0a 22 74 79 70 65 2e 67 6f 6f 67 6c 65 61 70 69 73 2e 63 6f 6d 2f 6d 79 74 65 73 74 2e 53 75 62 54 65 73 74  |__ 第一个字段（string type_url）
12 02 08 01     |__ 第二个字段（bytes value = 2）

第一个字段（string type_url）：
0a              |__ Tag
22              |__ Length (34个字符)
74 79 70 65 2e 67 6f 6f 67 6c 65 61 70 69 73 2e 63 6f 6d 2f 6d 79 74 65 73 74 2e 53 75 62 54 65 73 74        |__ 字符串的ASCCII码（以下是对应的字符）
 t  y  p  e  .  g  o  o  g  l  e  a  p  i  s  .  c  o  m  /  m  y  t  e  s  t  .  S  u  b  T  e  s  t

第二个字段（bytes value = 2）：
12              |__ Tag
02              |__ Length
08 01           |__ mytest::SubTest的编码: 08 -> Tag, 01 -> 值
```

> 注: Any 使用到了reflecttion（反射）功能，C++ 编译链接时不能使用 -lprotobuf-lite，而要使用 -lprotobuf。
