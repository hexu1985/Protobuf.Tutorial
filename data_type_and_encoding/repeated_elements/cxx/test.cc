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
    t1.add_vec(1);  //field_number = 16, wire_type = 2 (Length-Delimited)
    t1.add_vec(2);  //field_number = 16, wire_type = 2 (Length-Delimited)
    std::string buf;
    t1.SerializeToString(&buf);
    dump_hexstring("==== test_1 ====", buf);
}

static void test_2() {
    mytest::Test t2;
    t2.add_test_vec()->set_i32(1);//field_number = 22, wire_type = 2 (Length-Delimited)
    t2.add_test_vec()->set_i32(2);//field_number = 22, wire_type = 2 (Length-Delimited)
    std::string buf;
    t2.SerializeToString(&buf);
    dump_hexstring("==== test_2 ====", buf);
}

int main() {
    test_1();
    test_2();
    return 0;
}
