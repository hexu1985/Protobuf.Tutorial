### Non-varint编码数字类型

Non-arint编码数字类型一般是指固定长度的整型类型和浮点数类型

**fixed32/sfixed32/fixed64/sfixed64**
fixed32/fixed64 分别对应 C++ 类型的 uint32_t 和 uint64_t，sfixed32/sfixed64 分别对应 C++ 类型的 int32_t 和 int64_t。  
没有经过任何编码，分别使用固定的 4 个字节 和 8 个字节表示该值。

sfixed32/sfixed64 也是分别使用了固定 4 个字节 和 8 个字节表示该值，只不过先经过 ZigZag 编码然后再存储。

**float/double**
float 是使用固定 4 个字节来表示浮点数，double 是使用固定 8 个字节来表示浮点数。

有时候我们可以灵活一点，不一定需要用浮点数的类型类表示浮点数，比如有这样一个需求：使用一个字段来表示分数，满分一分，
有效值扩展到小数点后 2 位小数（如：99.98分），如果使用 float 编码结果为 5 个字节（Tag 1个字节 + 固定 4 个字节）。

我们换一种思路，把分数转换成整型（如：9998），选型为 int32，那么使用的是 Varint 编码，最后的结果只需 3 个字节。

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
    t1.set_i32(9998);     //field_number = 1, wire_type = 0 (varint)
    t1.set_f32(99.98);    //field_number = 12, wire_type = 5 (float)
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
08 8e 4e 65 c3 f5 c7 42
```

分析结果:
```
08 8e 4e        |__ i32
65 c3 f5 c7 42  |__ f32
```
