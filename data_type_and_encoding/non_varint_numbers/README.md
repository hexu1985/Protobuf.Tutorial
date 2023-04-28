### Non-varint编码数字类型

Non-arint编码数字类型一般是指固定长度的整型类型和浮点数类型

**fixed32/sfixed32/fixed64/sfixed64**
fixed32/fixed64 分别对应 C++ 类型的 uint32_t 和 uint64_t，sfixed32/sfixed64 分别对应 C++ 类型的 int32_t 和 int64_t。  
没有经过任何编码，分别使用固定的 4 个字节 和 8 个字节表示该值。

sfixed32/sfixed64 也是分别使用了固定 4 个字节 和 8 个字节表示该值，只不过先经过 ZigZag 编码然后再存储。

**float/double**
float 是使用固定 4 个字节来表示浮点数，double 是使用固定 8 个字节来表示浮点数。


