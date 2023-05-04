### map类型

map 的底层实现是哈希表。类似 C++ 语言中的 unordered_map。

map 使用了 Length-delimited 编码方式。

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
    //field_number = 17, wire_type = 2 (Length-Delimited)
    t1.mutable_mp()->insert({1, 10});
    t1.mutable_mp()->insert({2, 11});
    t1.mutable_mp()->insert({3, 12});
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
8a 01 04 08 03 10 0c 8a 01 04 08 02 10 0b 8a 01 04 08 01 10 0a 
```

分析结果：

```
 8a 01  04 08 01 10 0a  |__ Key-Value-Group[0]
 |__|   |  |__|  |__|______ Value (10-> Tag (1), 0a -> 值)
    |   |     |____________ Key   (08-> Tag (2), 01 -> 值)
    |   |__________________ Length
    |______________________ Tag

    (1)：10 = 2 << 3 | 0 = 16 = 0x10
         (map的value field-number 固定为 2)
    (2)：08 = 1 << 3 | 0 = 8 = 0x08
         (map的Key field-number 固定为 1)

 8a 01  04 08 02 10 0b  |__ Key-Value-Group[1]
 8a 01  04 08 03 10 0c  |__ Key-Value-Group[2]
```
