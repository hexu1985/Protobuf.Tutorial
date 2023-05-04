### submessage编码

submessage - embedding message，也就是 message 中某个字段的类型是一个 message 的类型，使用了 Length-delimited 编码方式。

以示例代码为例:

```cpp
#include <cstdio>
#include <iostream>

#include "test.pb.h"

//输出十六进制编码
static void dump_hexstring(const std::string& tag, const std::string& data) {
    printf("%s:\n", tag.c_str());
    for (size_t i = 0; i < data.size(); ++i) {
        printf("%02x ", (unsigned char)data[i]);
    }
    printf("\n\n");
}

static void test_1() {
    mytest::Test t1;
    t1.mutable_test()->set_i32(1);  //field_number = 18, wire_type = 2 (Length-delimited)
    std::string buf;
    t1.SerializeToString(&buf);
    dump_hexstring("==== test_1 ====", buf);
}

int main() {
    test_1();
    return 0;
}
```

编译和执行结果：

```
==== test_1 ====:
92 01 02 08 01
```

分析结果：

```
92 01   |__ Tag
02      |__ Length
08 01   |__ Data, SubTest值, 08 -> Tag, 01 -> 值
```
