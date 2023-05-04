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
