### repeated编码

repeated 顾名思义，是重复这个字段，其主要是补充数组功能这块的空白，类似于 C++ 语言中的 vector。

repeated 使用了 Length-delimited 的编码方式。先看一下它的序列化模型：

```
[Tag][Length][Data-1][Data-2][Data-3]...[Data-n]
```

我们给出两个例子对比基础类型和复合类性的编码区别：

**测试 - 1**

repeat基础类型

proto文件

```
message Test {
    ...
    repeated int32     vec      =   16;
    ...
}
```

测试代码

```cpp
static void test_1() {
    mytest::Test t1;
    t1.add_vec(1);  //field_number = 16, wire_type = 2 (Length-Delimited)
    t1.add_vec(2);  //field_number = 16, wire_type = 2 (Length-Delimited)
    std::string buf;
    t1.SerializeToString(&buf);
    dump_hexstring("==== test_1 ====", buf);
}
```

编译和执行结果：

```
==== test_1 ====:
82 01 02 01 02
```

分析结果：

```
82 01  |__ Tag
02     |__ Length
01 02  |__ 值 1 和 2
```

**测试 - 2**

repeat复合类型

proto文件

```
//message 是消息体，它就是一个结构体/类
message SubTest {
  int32              i32      =   1;
}

message Test {
    ...
    repeated SubTest   test_vec =   22;
    ...
}
```

编译和执行结果：

```cpp
static void test_2() {
    mytest::Test t2;
    t2.add_test_vec()->set_i32(1);//field_number = 22, wire_type = 2 (Length-Delimited)
    t2.add_test_vec()->set_i32(2);//field_number = 22, wire_type = 2 (Length-Delimited)
    std::string buf;
    t2.SerializeToString(&buf);
    dump_hexstring("==== test_2 ====", buf);
}
```

编译和执行结果：

```
==== test_2 ====:
b2 01 02 08 01 b2 01 02 08 02
```

分析结果:
```
b2 01 02 08 01 //vec[0]
b2 01  |__ Tag
02     |__ Length
08 01  |__ Subtest值, 08-> Tag, 01 -> 值

b2 01 02 08 02 //vec[1]
b2 01  |__ Tag
02     |__ Length
08 02  |__ Subtest值, 08-> Tag, 02 -> 值
```

对比测试1和测试2，我们可以发现，对于SubTest类型（复合类型）的repeated字段，每个 repeated item 都要重复 Tag 和 Length，
如果 repeated 类型是基础类型（比如 Varint） 时，会做 packed 优化（也就是压缩）。

