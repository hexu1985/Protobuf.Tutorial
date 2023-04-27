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
    t1.set_i32(1);  //field_number = 1, wire_type = 0 (varint)
    t1.set_i64(2);  //field_number = 2, wire_type = 0 (varint)
    t1.set_u32(1);  //field_number = 3, wire_type = 0 (varint)
    t1.set_u64(2);  //field_number = 4, wire_type = 0 (varint)
    t1.set_si32(1); //field_number = 5, wire_type = 0 (varint)
    t1.set_si64(2); //field_number = 6, wire_type = 0 (varint)
    std::string buf;
    t1.SerializeToString(&buf);
    dump_hexstring("==== test_1 ====", buf);
}

static void test_2() {
    mytest::Test t2;
    t2.set_i32(-1);  //field_number = 1, wire_type = 0 (varint)
    t2.set_i64(-2);  //field_number = 2, wire_type = 0 (varint)
    t2.set_u32(-1);  //field_number = 3, wire_type = 0 (varint)
    t2.set_u64(-2);  //field_number = 4, wire_type = 0 (varint)
    t2.set_si32(-1); //field_number = 5, wire_type = 0 (varint)
    t2.set_si64(-2); //field_number = 6, wire_type = 0 (varint)
    std::string buf;
    t2.SerializeToString(&buf);
    dump_hexstring("==== test_2 ====", buf);
}

int main() {
    test_1();
    test_2();
    return 0;
}
