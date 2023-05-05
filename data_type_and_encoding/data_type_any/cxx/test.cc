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
    t1.mutable_any()->PackFrom(st1);  //field_number = 21, wire_type = 2 (Lenth-Delimited)
    //std::cout << t1.any().type_url() << std::endl;
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
