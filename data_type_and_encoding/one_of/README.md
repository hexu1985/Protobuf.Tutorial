### oneof类型

如果需求有一条包含许多字段的消息，并且最多同时设置一个字段，那么可以使用 oneof 特性来节省内存。

oneof 字段类似于常规字段，除了 oneof 共享内存的所有字段之外，最多可以同时设置一个字段。设置 oneof 的任何成员都会自动清除所有其他成员。
可以使用 case() 或 WhichOneof()方法检查 oneof 中的哪个值被设置(如果有的话)，具体取决于您选择的语言。

oneof 不能使用 repeated 字段。

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
    t1.set_obj_f32(0.1);
    std::cout << "obj_str:" << t1.obj_str() << ", obj_f32:" << t1.obj_f32() << std::endl;
    t1.set_obj_str("string");
    std::cout << "obj_str:" << t1.obj_str() << ", obj_f32:" << t1.obj_f32() << std::endl; // optimize_for = LITE_RUNTIME 时会 crash，因为 obj_f32 被释放掉。
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
obj_str:, obj_f32:0.1
obj_str:string, obj_f32:0
==== test_1 ====
a2 01 06 73 74 72 69 6e 67
 .  .  .  s  t  r  i  n  g
```

分析结果：

```
obj_str:, obj_f32:0.1
obj_str:string, obj_f32:0
| 设置 obj_str 的时候，obj_f32被清空了，
| 操作（触发内存分配如执行set_xxx或者mutable_xxxx函数）
| 任何一个成员的时候，会清空所有其他成员。
==== test_1 ====:
a2 01 06 73 74 72 69 6e 67
|__|  |   s  t  r  i  n  g  ____ 字符串
   |  |_________________________ Length
   |____________________________ Tag
```
