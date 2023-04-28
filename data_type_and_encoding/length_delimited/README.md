### Lenght-delimited编码

这种编码很容易理解，就是 length + body 的方式，使用一个 Varint 类型表示 length，然后 length 的后面接着 length 个字节的内容。

以示例代码为例:

```
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
    mytest::Test t1;
    t1.set_str("string"); //field_number = 14, wire_type = 5 (varint)
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
72 06 73 74 72 69 6e 67
 r  .  s  t  r  i  n  g
```

分析结果:
```
72 06 73 74 72 69 6e 67
|  |  s  t  r  i  n  g
|  |  |__|__|__|__|__|__ body 的 ASCII 码
|  |__ length = 6 = 0x06
|__ Tag (field-number << 3 | wire-type) = (14 << 3 | 5) = 114 = 0x72
```
