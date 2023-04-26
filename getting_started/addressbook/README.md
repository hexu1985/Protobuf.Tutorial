## protobuf tutorial

### 1 protobuf 简介

protobuf (protocol buffer) 是谷歌内部的混合语言数据标准。通过将结构化的数据进行序列化(串行化)，用于通讯协议、数据存储等领域的语言无关、平台无关、可扩展的序列化结构数据格式。

我们说的 protobuf 通常包括下面三点:

- 一种二进制数据交换格式。可以将 C++ 中定义的存储类的内容 与 二进制序列串 相互转换，主要用于数据传输或保存
- 定义了一种源文件，扩展名为 .proto(类比.cpp文件)，使用这种源文件，可以定义存储类的内容
- protobuf有自己的编译器 protoc，可以将 .proto 编译成.cc文件，使之成为一个可以在 C++ 工程中直接使用的类

### 2 定义proto文件

**message 介绍**

message：protobuf中定义一个消息类型是通过关键字message字段指定的，这个关键字类似于C++/Java中的class关键字。  
使用protobuf编译器将proto编译成C++代码之后，每个message都会生成一个名字与之对应的C++类，该类公开继承自google::protobuf::Message。

**message 消息定义**

创建addressbook.proto文件，文件内容如下：

```
// FileName: addressbook.proto
// 通常文件名建议命名格式为 包名.消息名.proto

// 表示正在使用proto2命令
syntax = "proto2";

//包声明，tutorial 也可以声明为二级类型。
//例如a.b，表示a类别下b子类别
package tutorial;

//编译器将生成一个名为person的类
//类的字段信息包括姓名name,编号id,邮箱email，
//以及电话号码phones
message Person {

  optional string name = 1;
  optional int32 id = 2;
  optional string email = 3;

  enum PhoneType {  //电话类型枚举值
    MOBILE = 0;  //手机号
    HOME = 1;    //家庭联系电话
    WORK = 2;    //工作联系电话
  }

  //电话号码phone消息体
  //组成包括号码number、电话类型 type
  message PhoneNumber {
    optional string number = 1;
    optional PhoneType type = 2 [default = HOME];
  }

  repeated PhoneNumber phones = 4;
}


// 通讯录消息体，包括一个Person类的people
message AddressBook {
  repeated Person people = 1;

}
```

**字段解释**

- 包声明
    proto 文件以package声明开头，这有助于防止不同项目之间命名冲突。  
    在C++中，以package声明的文件内容生成的类将放在与包名匹配的namespace中，  
    上面的.proto文件中所有的声明都属于tutorial。

- 字段规则
    + required:消息体中必填字段，不设置会导致编解码异常。
    + optional: 消息体中可选字段，可通过default关键字设置默认值。
    + repeated: 消息体中可重复字段，重复的值的顺序会被保留。其中，proto3默认使用packed方式存储，这样编码方式比较节省内存。

- 标识号
    在消息体的定义中，每个字段都必须要有一个唯一的标识号，标识号是[0,2^29-1]范围内的一个整数。  
    以Person为例，name=1，id=2, email=3, phones=4 中的1-4就是标识号。

- 数据定义
    许多标准的简单数据类型都可以用作message字段类型，包括bool,int32,float,double和string。  
    还可以使用其他message类型作为字段类型在消息体中添加更多结构。  
    在上面的示例中，Person包含PhoneNumber message, 而AddressBook包含Person message。  
    甚至可以定义嵌套在其他message中的message类型。例如，上面的PhoneNumber定义在Person。

- 函数方法
    用message关键字声明的的消息体，允许你检查、操作、读、或写整个消息，  
    包括解析二进制字符串，以及序列化二进制字符串。除此之外，也定义了下列方法：
    ```
    Person:缺省的构造函数。

    ~Person():缺省的析构函数。

    Person(const Person& other):拷贝构造函数。

    Person& operator=(const Person& other):
    赋值 (Assignment ）操作符。

    const UnknownFieldSet& unknown_fields() const:
    返回当解析信息时遇到的未知字段的集合。

    UnknownFieldSet* mutable_unknown_fields():
    返回当前解析信息时遇到的未知字段的集合的一个mutale指针。
    ```

### 3 编译proto文件

可以执行以下protoc命令对.proto文件进行编译，生成对应的c文件。Linux系统通过 help protoc 查看protoc命令的使用详解。
```
$ protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/addressbook.proto
```
命令各个部分的含义:
- `$SRC_DIR`: proto 所在的源目录
- `--cpp_out`: 生成C++代码
- `$DST_DIR`: 生成代码的目标目录
- `$SRC_DIR/addressbook.proto`: 要针对哪个proto文件生成接口

编译完成后，将生成2个文件:
- addressbook.pb.h： 类声明的头文件
- addressbook.pb.cc：类实现

让我们看看一些生成的代码，看看编译器为你创建了哪些类和函数。如果你查看　addressbook.pb.h，  
你会发现你在 addressbook.proto 中指定的每条 message 都有一个对应的类。仔细观察 Person 类，  
你可以看到编译器已为每个字段生成了访问器。例如，对于 name ，id，email 和 phone 字段，你可以使用以下方法：
```cpp
  // accessors -------------------------------------------------------

  // optional string name = 1;
  bool has_name() const;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // optional int32 id = 2;
  bool has_id() const;
  void clear_id();
  static const int kIdFieldNumber = 2;
  ::google::protobuf::int32 id() const;
  void set_id(::google::protobuf::int32 value);

  // optional string email = 3;
  bool has_email() const;
  void clear_email();
  static const int kEmailFieldNumber = 3;
  const ::std::string& email() const;
  void set_email(const ::std::string& value);
  void set_email(const char* value);
  void set_email(const char* value, size_t size);
  ::std::string* mutable_email();
  ::std::string* release_email();
  void set_allocated_email(::std::string* email);

  // repeated .tutorial.Person.PhoneNumber phones = 4;
  int phones_size() const;
  void clear_phones();
  static const int kPhonesFieldNumber = 4;
  const ::tutorial::Person_PhoneNumber& phones(int index) const;
  ::tutorial::Person_PhoneNumber* mutable_phones(int index);
  ::tutorial::Person_PhoneNumber* add_phones();
  ::google::protobuf::RepeatedPtrField< ::tutorial::Person_PhoneNumber >*
      mutable_phones();
  const ::google::protobuf::RepeatedPtrField< ::tutorial::Person_PhoneNumber >&
      phones() const;
```

如你所见，getter 的名称与小写字段完全相同，setter 方法以 set_ 开头。  
每个单数（required 或 optional）字段也有 has_ 方法，如果设置了该字段，则返回 true。  
最后，每个字段都有一个 clear_ 方法，可以将字段重新设置回 empty 状态。  
虽然数字 id 字段只有上面描述的基本访问器集，但是 name 和 email 字段因为是字符串所以有几个额外的方法：  
一个 mutable_ 的 getter，它允许你获得一个指向字符串的直接指针，以及一个额外的 setter。  
请注意，即使尚未设置 email ，也可以调用 mutable_email()；它将自动初始化为空字符串。  
如果在这个例子中你有一个单数的 message 字段，它也会有一个 mutable_ 方法而不是 set_ 方法。

repeated 字段也有一些特殊的方法 - 如果你看一下 repeated phones 字段的相关方法，你会发现你可以：
- 检查 repeated 字段长度（换句话说，与此人关联的电话号码数）
- 使用索引获取指定的电话号码
- 更新指定索引处的现有电话号码
- 在 message 中添加另一个电话号码同时之后也可进行再修改（repeated 的标量类型有一个 add_，而且只允许你传入新值）

**枚举和嵌套类**
生成的代码包含与你的 .proto 枚举对应的 PhoneType 枚举。你可以将此类型称为 Person::PhoneType，  
其值为 Person::MOBILE，Person::HOME 和 Person::WORK（实现细节稍微复杂一些，但你如果仅仅只是使用不需要理解里面的实现原理）。  
编译器还为你生成了一个名为 Person::PhoneNumber 的嵌套类。如果查看代码，可以看到 “真实” 类实际上称为 Person_PhoneNumber，  
但在 Person 中定义的 typedef 允许你将其视为嵌套类。唯一会造成一点差异的情况是，如果你想在另一个文件中前向声明该类，  
你不能在 C ++ 中前向声明嵌套类型，但你可以前向声明 Person_PhoneNumber。

**标准 Message 方法**
每个 message 类还包含许多其他方法，可用于检查或操作整个 message，包括：
- `bool IsInitialized() const;`: 检查是否已设置所有必填 required 字段
- `string DebugString() const;`: 返回 message 的人类可读表达，对调试特别有用
- `void CopyFrom(const Person& from);`: 用给定的 message 的值覆盖 message
- `void Clear();`: 将所有元素清除回 empty 状态

**解析和序列化**
最后，每个 protocol buffer 类都有使用 protocol buffer 二进制格式 读写所选类型 message 的方法。包括：
- `bool SerializeToString(string* output) const;`:序列化消息并将字节存储在给定的字符串中。
    请注意，字节是二进制的，而不是文本;我们只使用 string 类作为方便的容器。
- `bool ParseFromString(const string& data);`: 解析给定字符串到 message
- `bool SerializeToOstream(ostream* output) const;`: 将 message 写入给定的 C++ 的 ostream
- `bool ParseFromIstream(istream* input);`: 解析给定 C++ istream 到 message

### 4 protobuf程序示例

- 写入一个 Message: 参考[add_person.cc](cxx/add_person.cc)和[create_addressbook.cc](cxx/create_addressbook.cc)
- 读取一个 Message: 参考[add_person.cc](cxx/add_person.cc)和[list_people.cc](cxx/list_people.cc)

### 5 扩展一个 Protocol Buffer

在发布使用 protocol buffer 的代码之后，无疑早晚有一天你将会想要 “改进” protocol buffer 的定义。  
如果你希望你的新 buffer 向后兼容，并且你的旧 buffer 是向前兼容的（实际上你一定想要这种兼容性） - 那么你需要遵循一些规则。  
在新版本的 protocol buffer 中：
- 你不得更改任何现有字段的字段编号
- 你不得添加或删除任何 required 字段
- 你可以删除 optional 或 repeated 的字段
- 你可以添加新的 optional 或 repeated 字段，但必须使用新的标记号（即从未在此协议缓冲区中使用的编号，甚至包括那些已删除的字段的编号）

如果你遵循这些规则，旧代码将很乐意阅读新消息并简单地忽略任何新字段。对于旧代码，已删除的可选字段将只具有其默认值，删除的重复字段将为空。  
新代码也将透明地读取旧消息。但是，请记住旧的 message 中不会出现新的可选字段，因此你需要明确通过调用 has_ 方法来检查它们是否被设置，  
或者在字段编号后面使用 [default = value] 在 .proto 文件中提供合理的默认值。如果未为 optional 元素指定默认值，则使用特定于类型的默认值：  
对于字符串，默认值为空字符串。对于布尔值，默认值为 false。对于数字类型，默认值为零。另请注意，如果添加了新的 repeated 字段，  
则新代码将无法判断它是否为空（通过新代码）或从未设置（通过旧代码），因为它没有 has_ 标志。


