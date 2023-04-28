### Protobuf 数据类型和编码总结

**Protobuf 的数据类型**
以下是一个 Protobuf 数据类型和其他编程语言的数据类型的映射关系表。

| Protobuf Type | 说明                 | C++ Type | Java Type  | Python Type[2] | Go Type |
| ------------- | -------------------- | -------- | ---------- | -------------- | ------- |
| float         | 固定4个字节          | float    | float      | float          | float32 |
| double        | 固定8个字节          | double   | double     | float          | float64 |
| int32         | varint编码           | int32    | int        | int            | int32   |
| uint32        | varint编码           | uint32   | int        | int/long       | uint32  |
| uint64        | varint编码           | uint64   | long       | int/long       | uint64  |
| sint32        | zigzag 和 varint编码 | int32    | int        | int            | int32   |
| sint64        | zigzag 和 varint编码 | int64    | long       | int/long       | int64   |
| fixed32       | 固定4个字节          | uint32   | int        | int            | uint32  |
| fixed64       | 固定8个字节          | uint64   | long       | int/long       | uint64  |
| sfixed32      | 固定4个字节          | int32    | int        | int            | int32   |
| sfixed64      | 固定8个字节          | int64    | long       | int/long       | int64   |
| bool          | 固定一个字节         | bool     | boolean    | bool           | bool    |
| string        | Lenth-Delimited      | uint64   | String     | str/unicode    | string  |
| bytes         | Lenth-Delimited      | string   | ByteString | str            | []byte  |
| bytes         | Lenth-Delimited      | string   | ByteString | str            | []byte  |

**Protobuf 编码方法**

protobuf包含的编码类型包括

| wire-type | 名称             | 说明              | 类型                                                         |
| --------- | ---------------- | ----------------- | ------------------------------------------------------------ |
| 0         | Varint           | 可变长整形        | 非ZigZag编码类型：int32, uint32, int64, uint64, bool, enum； ZigZag编码类型：sint32, sint64 |
| 1         | 64-bits          | 固定8个字节大小   | fixed64, sfixed64, double                                    |
| 2         | Length-delimited | Length + Body方式 | string, bytes, embedding message, packed repeated fields     |
| 3         | Start group      | 已被弃用          | group start (deprecated)                                     |
| 4         | End group        | 已被弃用          | group end (deprecated)                                       |
| 5         | 32-bits          | 固定4个字节大小   | fixed32, sfixed32, float                                     |
