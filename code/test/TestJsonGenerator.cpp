//
// Created by yzn on 2022/6/23.
//

#include "TestJsonGenerator.h"

namespace yzn {
    static int total_test_num = 0;
    static int passed_test_num = 0;


    static void Test_Generator_Literals(){
        TEST_GENERATOR_BY_STRING("null");
    }


    void TestJsonGenerator::test() {
        std::cout << "----------------------------------[ test JsonGenerator ]----------------------------------" << std::endl;

        Test_Generator_Literals();

        std::cout << std::endl
                  << "-------------------------------------------------------------------------------------" << std::endl
                  << passed_test_num << "/" << total_test_num << " ("
                  << 100 * ((float) passed_test_num / (float) total_test_num)
                  << " %) passed." << std::endl;
        std::cout << "----------------------------------[   Finished.   ]----------------------------------" << std::endl;
    }
}// namespace yzn