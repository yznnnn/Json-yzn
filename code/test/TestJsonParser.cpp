//
// Created by yzn on 2022/6/14.
//

#include "TestJsonParser.h"

namespace yzn {
    static int total_test_num = 0;
    static int passed_test_num = 0;

    static void Test_Parse_NULL() {
        TEST_LITERAL(JsonNodeType::TYPE_NULL, "null");
        TEST_LITERAL(JsonNodeType::TYPE_NULL, "    \t       null");
        TEST_LITERAL(JsonNodeType::TYPE_NULL, "null     \n    ");
        TEST_LITERAL(JsonNodeType::TYPE_NULL, "  \t     null    \r   ");
    }

    static void Test_Parse_TRUE() {
        TEST_LITERAL(JsonNodeType::TYPE_TRUE, "true");
        TEST_LITERAL(JsonNodeType::TYPE_TRUE, "    \t       true");
        TEST_LITERAL(JsonNodeType::TYPE_TRUE, "true     \n    ");
        TEST_LITERAL(JsonNodeType::TYPE_TRUE, "  \t     true    \r   ");
    }

    static void Test_Parse_FALSE() {
        TEST_LITERAL(JsonNodeType::TYPE_FALSE, "false");
        TEST_LITERAL(JsonNodeType::TYPE_FALSE, "    \t       false");
        TEST_LITERAL(JsonNodeType::TYPE_FALSE, "false     \n    ");
        TEST_LITERAL(JsonNodeType::TYPE_FALSE, "  \t     false    \r   ");
    }


    void TestJsonParser::test() {
        std::cout << "----------------------------------[ test JsonNode ]----------------------------------" << std::endl;

        Test_Parse_NULL();
        Test_Parse_TRUE();
        Test_Parse_FALSE();

        std::cout << std::endl
                  << "-------------------------------------------------------------------------------------" << std::endl
                  << passed_test_num << "/" << total_test_num << " ("
                  << 100 * ((float) passed_test_num / (float) total_test_num)
                  << " %) passed." << std::endl;
        std::cout << "----------------------------------[   Finished.   ]----------------------------------" << std::endl;
    }
}// namespace yzn