//
// Created by yzn on 2022/6/23.
//

#include "TestJsonGenerator.h"

namespace yzn {
    static int total_test_num = 0;
    static int passed_test_num = 0;


    static void Test_Generator_Literals(){
        TEST_GENERATOR_BY_STRING("null");
        TEST_GENERATOR_BY_STRING("true");
        TEST_GENERATOR_BY_STRING("false");
    }

    static void Test_Generator_Numbers(){
        TEST_GENERATOR_BY_STRING("0");
        TEST_GENERATOR_BY_STRING("-0");
        TEST_GENERATOR_BY_STRING("1");
        TEST_GENERATOR_BY_STRING("-1");
        TEST_GENERATOR_BY_STRING("1.5");
        TEST_GENERATOR_BY_STRING("-1.5");
        TEST_GENERATOR_BY_STRING("3.25");
        TEST_GENERATOR_BY_STRING("1e+20");
        TEST_GENERATOR_BY_STRING("1.234e+20");
        TEST_GENERATOR_BY_STRING("1.234e-20");

        TEST_GENERATOR_BY_STRING("1.0000000000000002"); /* the smallest number > 1 */
        TEST_GENERATOR_BY_STRING("4.9406564584124654e-324"); /* minimum denormal */
        TEST_GENERATOR_BY_STRING("-4.9406564584124654e-324");
        TEST_GENERATOR_BY_STRING("2.2250738585072009e-308");  /* Max subnormal double */
        TEST_GENERATOR_BY_STRING("-2.2250738585072009e-308");
        TEST_GENERATOR_BY_STRING("2.2250738585072014e-308");  /* Min normal positive double */
        TEST_GENERATOR_BY_STRING("-2.2250738585072014e-308");
        TEST_GENERATOR_BY_STRING("1.7976931348623157e+308");  /* Max double */
        TEST_GENERATOR_BY_STRING("-1.7976931348623157e+308");
    }

    static void Test_Generator_String(){
        TEST_GENERATOR_BY_STRING("\"\"");
        TEST_GENERATOR_BY_STRING("\"Hello\"");
        TEST_GENERATOR_BY_STRING("\"Hello\\nWorld\"");
        TEST_GENERATOR_BY_STRING("\"\\\" \\\\ / \\b \\f \\n \\r \\t\"");
        TEST_GENERATOR_BY_STRING("\"Hello\\u0000World\"");
    }

    static void Test_Generator_Array(){
        TEST_GENERATOR_BY_STRING("[]");
        TEST_GENERATOR_BY_STRING("[null,false,true,123,\"abc\",[1,2,3]]");
    }

    static void Test_Generator_Object(){
        TEST_GENERATOR_BY_STRING("{}");
        TEST_GENERATOR_BY_STRING("{\"n\":null,\"f\":false,\"t\":true,\"i\":123,\"s\":\"abc\",\"a\":[1,2,3],\"o\":{\"1\":1,\"2\":2,\"3\":3}}");
    }



    void TestJsonGenerator::test() {
        std::cout << "----------------------------------[ test JsonGenerator ]----------------------------------" << std::endl;

        Test_Generator_Literals();
        Test_Generator_Numbers();
        Test_Generator_String();
        Test_Generator_Array();
        //Test_Generator_Object();

        std::cout << std::endl
                  << "-------------------------------------------------------------------------------------" << std::endl
                  << passed_test_num << "/" << total_test_num << " ("
                  << 100 * ((float) passed_test_num / (float) total_test_num)
                  << " %) passed." << std::endl;
        std::cout << "----------------------------------[   Finished.   ]----------------------------------" << std::endl;
    }
}// namespace yzn