#include "./test/test.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "Hello, World!" << std::endl;
    yzn::test();


//    std::string s_0("Hello");
//    s_0 += '\0';
//    s_0 += "World";
//    const char *s_1 = "Hello\0World";
//    std::cout << strlen(s_1) << std::endl;


    //    // 转换构造
    //    std::string s0 = "Replaces the contents with a copy of str. If *this and str are the same object, this function has no effect.";
    //    std::cout << "s0: " << (void *) s0.data() << "\t" << std::quoted(s0) << std::endl
    //              << std::endl;
    //
    //    // 拷贝构造
    //    std::string s1 = s0;
    //    std::cout << "s0: " << (void *) s0.data() << "\t" << std::quoted(s0) << std::endl
    //              << "s1: " << (void *) s1.data() << "\t" << std::quoted(s1) << std::endl
    //              << std::endl;
    //
    //    // 移动构造
    //    std::string s2 = std::move(s0);
    //    std::cout << "s0: " << (void *) s0.data() << "\t" << std::quoted(s0) << std::endl
    //              << "s2: " << (void *) s2.data() << "\t" << std::quoted(s2) << std::endl
    //              << std::endl;
    //
    //    std::string s3;
    //    std::string &&s4 = std::move(s1);
    //    s3 = std::move(s4);
    //    std::cout << "s1: " << (void *) s1.data() << "\t" << std::quoted(s1) << std::endl
    //              << "s4: " << (void *) s4.data() << "\t" << std::quoted(s4) << std::endl
    //              << "s3: " << (void *) s3.data() << "\t" << std::quoted(s3) << std::endl
    //              << std::endl;

    return 0;
}
