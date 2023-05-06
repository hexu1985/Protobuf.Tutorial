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
