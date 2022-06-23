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

    static void Test_Parse_NUMBER() {
        TEST_NUMBER(0.0, "0");
        TEST_NUMBER(0.0, "-0");
        TEST_NUMBER(0.0, "-0.0");
        TEST_NUMBER(1.0, "1");
        TEST_NUMBER(-1.0, "-1");
        TEST_NUMBER(1.5, "1.5");
        TEST_NUMBER(-1.5, "-1.5");
        TEST_NUMBER(3.1416, "3.1416");
        TEST_NUMBER(1E10, "1E10");
        TEST_NUMBER(1e10, "1e10");
        TEST_NUMBER(1E+10, "1E+10");
        TEST_NUMBER(1E-10, "1E-10");
        TEST_NUMBER(-1E10, "-1E10");
        TEST_NUMBER(-1e10, "-1e10");
        TEST_NUMBER(-1E+10, "-1E+10");
        TEST_NUMBER(-1E-10, "-1E-10");
        TEST_NUMBER(1.234E+10, "1.234E+10");
        TEST_NUMBER(1.234E-10, "1.234E-10");
        TEST_NUMBER(0.0, "1e-10000"); /* must underflow */

        TEST_NUMBER(1.0000000000000002,
                    "1.0000000000000002"); /* the smallest number > 1 */
        TEST_NUMBER(4.9406564584124654e-324,
                    "4.9406564584124654e-324"); /* minimum denormal */
        TEST_NUMBER(-4.9406564584124654e-324, "-4.9406564584124654e-324");
        TEST_NUMBER(2.2250738585072009e-308,
                    "2.2250738585072009e-308"); /* Max subnormal double */
        TEST_NUMBER(-2.2250738585072009e-308, "-2.2250738585072009e-308");
        TEST_NUMBER(2.2250738585072014e-308,
                    "2.2250738585072014e-308"); /* Min normal positive double */
        TEST_NUMBER(-2.2250738585072014e-308, "-2.2250738585072014e-308");
        TEST_NUMBER(1.7976931348623157e+308,
                    "1.7976931348623157e+308"); /* Max double */
        TEST_NUMBER(-1.7976931348623157e+308, "-1.7976931348623157e+308");
    }


    static void Test_Parse_STRING() {
        TEST_STRING("",
                    "\"\"");
        TEST_STRING("Hello",
                    "\"Hello\"");
        TEST_STRING("Hello\nWorld",
                    "\"Hello\\nWorld\"");
        TEST_STRING("\" \\ / \b \f \n \r \t",
                    "\"\\\" \\\\ \\/ \\b \\f \\n \\r \\t\"");


        TEST_STRING(std::string("Hello") + '\0' + "World",// 这里直接用 C-style string 会吞到 '\0'
                    "\"Hello\\u0000World\"");
        TEST_STRING("\x24",
                    "\"\\u0024\""); /* Dollar sign U+0024 */
        TEST_STRING("\xC2\xA2",
                    "\"\\u00A2\""); /* Cents sign U+00A2 */
        TEST_STRING("\xE2\x82\xAC",
                    "\"\\u20AC\""); /* Euro sign U+20AC */
        TEST_STRING("\xF0\x9D\x84\x9E",
                    "\"\\uD834\\uDD1E\""); /* G clef sign U+1D11E */
        TEST_STRING("\xF0\x9D\x84\x9E",
                    "\"\\ud834\\udd1e\""); /* G clef sign U+1D11E */
    }

    static void Test_Parse_ARRAY() {
        JsonNode *node_ptr = nullptr;
        JsonParser parser{};
        JsonParserStateCode state_code;
        const char *json_text;
        size_t expect_element_size;

        /* 测试样例 [] */
        json_text = "[    ]";
        expect_element_size = 0;
        state_code = parser.parse(&node_ptr, json_text);
        EQUAL_NUMBER(JsonParserStateCode::OK, state_code);
        if (node_ptr != nullptr) {
            EQUAL_NUMBER(JsonNodeType::TYPE_ARRAY, node_ptr->getType());
            size_t real_size = node_ptr->getValue() ? ((std::vector<JsonNode *> *) node_ptr->getValue())->size() : 0;
            EQUAL_NUMBER(expect_element_size, real_size);
        } else {
            EQUAL_NUMBER(JsonNodeType::TYPE_ARRAY, JsonNodeType::TYPE_UNKNOWN);
        }
        delete node_ptr;
        node_ptr = nullptr;


        /* 测试样例： [ null , false , true , 123 , \"abc\" ] */
        json_text = "[null , false , true , 123 , \"abc\"]";
        expect_element_size = 5;
        state_code = parser.parse(&node_ptr, json_text);
        EQUAL_NUMBER(JsonParserStateCode::OK, state_code);
        if (node_ptr != nullptr) {
            EQUAL_NUMBER(JsonNodeType::TYPE_ARRAY, node_ptr->getType());
            size_t real_size = node_ptr->getValue() ? ((std::vector<JsonNode *> *) node_ptr->getValue())->size() : 0;
            EQUAL_NUMBER(expect_element_size, real_size);

            const auto *vec_ptr = (std::vector<JsonNode *> *) node_ptr->getValue();
            EQUAL_NUMBER(JsonNodeType::TYPE_NULL, (*vec_ptr)[0]->getType());
            EQUAL_NUMBER(JsonNodeType::TYPE_FALSE, (*vec_ptr)[1]->getType());
            EQUAL_NUMBER(JsonNodeType::TYPE_TRUE, (*vec_ptr)[2]->getType());
            EQUAL_NUMBER(JsonNodeType::TYPE_NUMBER, (*vec_ptr)[3]->getType());
            EQUAL_NUMBER(123, *((double *) (*vec_ptr)[3]->getValue()));
            EQUAL_NUMBER(JsonNodeType::TYPE_STRING, (*vec_ptr)[4]->getType());
            EQUAL_STRING("abc", *((std::string *) (*vec_ptr)[4]->getValue()));
        } else {
            EQUAL_NUMBER(JsonNodeType::TYPE_ARRAY, JsonNodeType::TYPE_UNKNOWN);
        }
        delete node_ptr;
        node_ptr = nullptr;


        /* 测试样例： [ [ ] , [ 0 ] , [ 0 , 1 ] , [ 0 , 1 , 2 ] ] */
        json_text = "[ [ ] , [ 0 ] , [ 0 , 1 ] , [ 0 , 1 , 2 ] ]";
        expect_element_size = 4;
        state_code = parser.parse(&node_ptr, json_text);
        EQUAL_NUMBER(JsonParserStateCode::OK, state_code);
        if (node_ptr != nullptr) {
            EQUAL_NUMBER(JsonNodeType::TYPE_ARRAY, node_ptr->getType());
            size_t real_size = node_ptr->getValue() ? ((std::vector<JsonNode *> *) node_ptr->getValue())->size() : 0;
            EQUAL_NUMBER(expect_element_size, real_size);

            const auto *vec_ptr = (std::vector<JsonNode *> *) node_ptr->getValue();
            for (size_t i = 0; i < expect_element_size; i++) {
                EQUAL_NUMBER(JsonNodeType::TYPE_ARRAY, (*vec_ptr)[i]->getType());
                size_t temp_real_size = (*vec_ptr)[i]->getValue() ? ((std::vector<JsonNode *> *) (*vec_ptr)[i]->getValue())->size() : 0;
                EQUAL_NUMBER(i, temp_real_size);
                const auto *temp_vec_ptr = (std::vector<JsonNode *> *) (*vec_ptr)[i]->getValue();
                for (size_t j = 0; j < i; j++) {
                    EQUAL_NUMBER(JsonNodeType::TYPE_NUMBER, (*temp_vec_ptr)[j]->getType());
                    EQUAL_NUMBER(j, *((double *) (*temp_vec_ptr)[j]->getValue()));
                }
            }
        } else {
            EQUAL_NUMBER(JsonNodeType::TYPE_ARRAY, JsonNodeType::TYPE_UNKNOWN);
        }
        delete node_ptr;
        node_ptr = nullptr;
    }

    static void Test_Parse_Object() {
        JsonNode *node_ptr = nullptr;
        JsonParser parser{};
        JsonParserStateCode state_code;
        const char *json_text;
        size_t expect_element_size;

        /* 测试样例 {} */
        json_text = "{   }";
        expect_element_size = 0;
        state_code = parser.parse(&node_ptr, json_text);
        EQUAL_NUMBER(JsonParserStateCode::OK, state_code);
        if (node_ptr != nullptr) {
            EQUAL_NUMBER(JsonNodeType::TYPE_OBJECT, node_ptr->getType());
            size_t real_size = node_ptr->getValue() ? ((std::vector<JsonDict *> *) node_ptr->getValue())->size() : 0;
            EQUAL_NUMBER(expect_element_size, real_size);
        } else {
            EQUAL_NUMBER(JsonNodeType::TYPE_OBJECT, JsonNodeType::TYPE_UNKNOWN);
        }
        delete node_ptr;
        node_ptr = nullptr;


        /* 测试样例 */
        json_text = " { "
                    "\"n\" : null , "
                    "\"f\" : false , "
                    "\"t\" : true , "
                    "\"i\" : 123 , "
                    "\"s\" : \"abc\", "
                    "\"a\" : [ 1, 2, 3 ],"
                    "\"o\" : { \"1\" : 1, \"2\" : 2, \"3\" : 3 }"
                    " } ";
        expect_element_size = 7;
        state_code = parser.parse(&node_ptr, json_text);

        EQUAL_NUMBER(JsonParserStateCode::OK, state_code);
        if (node_ptr != nullptr) {
            EQUAL_NUMBER(JsonNodeType::TYPE_OBJECT, node_ptr->getType());
            size_t real_size = node_ptr->getValue() ? ((std::vector<JsonDict *> *) node_ptr->getValue())->size() : 0;
            EQUAL_NUMBER(expect_element_size, real_size);

            const auto *vec_ptr = (std::vector<JsonDict *> *) node_ptr->getValue();

            EQUAL_STRING("n", (*vec_ptr)[0]->getKey());
            EQUAL_NUMBER(JsonNodeType::TYPE_NULL, (*vec_ptr)[0]->getValuePtr()->getType());

            EQUAL_STRING("f", (*vec_ptr)[1]->getKey());
            EQUAL_NUMBER(JsonNodeType::TYPE_FALSE, (*vec_ptr)[1]->getValuePtr()->getType());

            EQUAL_STRING("t", (*vec_ptr)[2]->getKey());
            EQUAL_NUMBER(JsonNodeType::TYPE_TRUE, (*vec_ptr)[2]->getValuePtr()->getType());

            EQUAL_STRING("i", (*vec_ptr)[3]->getKey());
            EQUAL_NUMBER(JsonNodeType::TYPE_NUMBER, (*vec_ptr)[3]->getValuePtr()->getType());
            EQUAL_NUMBER(123, *((double *) (*vec_ptr)[3]->getValuePtr()->getValue()));

            EQUAL_STRING("s", (*vec_ptr)[4]->getKey());
            EQUAL_NUMBER(JsonNodeType::TYPE_STRING, (*vec_ptr)[4]->getValuePtr()->getType());
            EQUAL_STRING("abc", *((std::string *) (*vec_ptr)[4]->getValuePtr()->getValue()));

            EQUAL_STRING("a", (*vec_ptr)[5]->getKey());
            EQUAL_NUMBER(JsonNodeType::TYPE_ARRAY, (*vec_ptr)[5]->getValuePtr()->getType());
            const JsonNode *node_cptr = (*vec_ptr)[5]->getValuePtr();
            real_size = node_cptr->getValue() ? ((std::vector<JsonNode *> *) node_cptr->getValue())->size() : 0;
            EQUAL_NUMBER(3, real_size);
            const auto temp_vec_ptr = (std::vector<JsonNode *> *) node_cptr->getValue();
            for (size_t i = 0; i < 3; i++) {
                EQUAL_NUMBER(JsonNodeType::TYPE_NUMBER, (*temp_vec_ptr)[i]->getType());
                EQUAL_NUMBER(i + 1, *((double *) (*temp_vec_ptr)[i]->getValue()));
            }

            EQUAL_STRING("o", (*vec_ptr)[6]->getKey());
            EQUAL_NUMBER(JsonNodeType::TYPE_OBJECT, (*vec_ptr)[6]->getValuePtr()->getType());
            const JsonNode *node_cptr_0 = (*vec_ptr)[6]->getValuePtr();
            real_size = node_cptr_0->getValue() ? ((std::vector<JsonNode *> *) node_cptr_0->getValue())->size() : 0;
            EQUAL_NUMBER(3, real_size);
            const auto temp_vec_ptr_0 = (std::vector<JsonDict *> *) node_cptr_0->getValue();
            for (size_t i = 0; i < 3; i++) {
                std::string temp_str;
                temp_str += (char) ('1' + i);
                EQUAL_STRING(temp_str, (*temp_vec_ptr_0)[i]->getKey());
                EQUAL_NUMBER(JsonNodeType::TYPE_NUMBER, (*temp_vec_ptr_0)[i]->getValuePtr()->getType());
                EQUAL_NUMBER(i + 1, *((double *) (*temp_vec_ptr_0)[i]->getValuePtr()->getValue()));
            }


        } else {
            EQUAL_NUMBER(JsonNodeType::TYPE_OBJECT, JsonNodeType::TYPE_UNKNOWN);
        }
        delete node_ptr;
        node_ptr = nullptr;
    }

    static void Test_Parse_Error_ONLY_WS() {
        TEST_ERROR(JsonParserStateCode::ONLY_WS, "  \n  \t  \r  ");
    }

    static void Test_Parse_Error_INVALID_VALUE() {
        TEST_ERROR(JsonParserStateCode::INVALID_VALUE, "   \n   ? \t  \r  ");

        /* Invalid Literal */
        TEST_ERROR(JsonParserStateCode::INVALID_VALUE, "   \n   nul \t  \r  ");
        TEST_ERROR(JsonParserStateCode::INVALID_VALUE, "   \n   ture \t  \r  ");
        TEST_ERROR(JsonParserStateCode::INVALID_VALUE, "   \n   fales \t  \r  ");

        /* Invalid Number */
        TEST_ERROR(JsonParserStateCode::INVALID_VALUE, "+0");
        TEST_ERROR(JsonParserStateCode::INVALID_VALUE, "+1");
        TEST_ERROR(JsonParserStateCode::INVALID_VALUE, ".123"); /* at least one digit before '.' */
        TEST_ERROR(JsonParserStateCode::INVALID_VALUE, "1.");   /* at least one digit after '.' */
        TEST_ERROR(JsonParserStateCode::INVALID_VALUE, "INF");
        TEST_ERROR(JsonParserStateCode::INVALID_VALUE, "inf");
        TEST_ERROR(JsonParserStateCode::INVALID_VALUE, "NAN");
        TEST_ERROR(JsonParserStateCode::INVALID_VALUE, "nan");

        /* invalid value in array */
        TEST_ERROR(JsonParserStateCode::INVALID_VALUE, "[1,]");
        TEST_ERROR(JsonParserStateCode::INVALID_VALUE, "[\"a\", nul]");
        TEST_ERROR(JsonParserStateCode::INVALID_VALUE, "[[1,false,3],[1, nul]]");
    }

    static void Test_Parse_Error_SURPLUS() {
        TEST_ERROR(JsonParserStateCode::SURPLUS, "   \n   null null \t  \r  ");

        /* invalid number */
        TEST_ERROR(JsonParserStateCode::SURPLUS, "0123"); /* after zero should be '.' or nothing */
        TEST_ERROR(JsonParserStateCode::SURPLUS, "0x0");
        TEST_ERROR(JsonParserStateCode::SURPLUS, "0x123");
    }

    static void Test_Parse_Error_OUT_OF_RANGE() {
        TEST_ERROR(JsonParserStateCode::OUT_OF_RANGE, "1e309");
        TEST_ERROR(JsonParserStateCode::OUT_OF_RANGE, "-1e309");
    }

    static void Test_Parse_Error_MISS_QUOTATION_MARK() {
        TEST_ERROR(JsonParserStateCode::MISS_QUOTATION_MARK, "\"");
        TEST_ERROR(JsonParserStateCode::MISS_QUOTATION_MARK, "\"abc");
    }

    static void Test_Parse_Error_INVALID_STRING_ESCAPE() {
        TEST_ERROR(JsonParserStateCode::INVALID_STRING_ESCAPE, "\"\\v\"");
        TEST_ERROR(JsonParserStateCode::INVALID_STRING_ESCAPE, "\"\\'\"");
        TEST_ERROR(JsonParserStateCode::INVALID_STRING_ESCAPE, "\"\\0\"");
        TEST_ERROR(JsonParserStateCode::INVALID_STRING_ESCAPE, "\"\\x12\"");
    }

    static void Test_Parse_Error_INVALID_STRING_CHAR() {
        TEST_ERROR(JsonParserStateCode::INVALID_STRING_CHAR, "\"\x01\"");
        TEST_ERROR(JsonParserStateCode::INVALID_STRING_CHAR, "\"\x1F\"");
    }

    static void Test_Parse_Error_INVALID_UNICODE_HEX() {
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_HEX, "\"\\u\"");
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_HEX, "\"\\u0\"");
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_HEX, "\"\\u01\"");
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_HEX, "\"\\u012\"");
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_HEX, "\"\\u/000\"");
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_HEX, "\"\\uG000\"");
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_HEX, "\"\\u0/00\"");
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_HEX, "\"\\u0G00\"");
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_HEX, "\"\\u00/0\"");
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_HEX, "\"\\u00G0\"");
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_HEX, "\"\\u000/\"");
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_HEX, "\"\\u000G\"");
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_HEX, "\"\\u 123\"");
    }

    static void Test_Parse_Error_INVALID_UNICODE_SURROGATE() {
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_SURROGATE, "\"\\uD800\"");
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_SURROGATE, "\"\\uDBFF\"");
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_SURROGATE, "\"\\uD800\\\\\"");
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_SURROGATE, "\"\\uD800\\uDBFF\"");
        TEST_ERROR(JsonParserStateCode::INVALID_UNICODE_SURROGATE, "\"\\uD800\\uE000\"");
    }


    static void Test_Parse_Error_MISS_COMMA_OR_SQUARE_BRACKET() {
        TEST_ERROR(JsonParserStateCode::MISS_COMMA_OR_SQUARE_BRACKET, "[1");
        TEST_ERROR(JsonParserStateCode::MISS_COMMA_OR_SQUARE_BRACKET, "[1}");
        TEST_ERROR(JsonParserStateCode::MISS_COMMA_OR_SQUARE_BRACKET, "[1 2");
        TEST_ERROR(JsonParserStateCode::MISS_COMMA_OR_SQUARE_BRACKET, "[[]");
    }

    static void Test_Parse_Error_MISS_KEY() {
        TEST_ERROR(JsonParserStateCode::MISS_KEY, "{:1,");
        TEST_ERROR(JsonParserStateCode::MISS_KEY, "{1:1,");
        TEST_ERROR(JsonParserStateCode::MISS_KEY, "{true:1,");
        TEST_ERROR(JsonParserStateCode::MISS_KEY, "{false:1,");
        TEST_ERROR(JsonParserStateCode::MISS_KEY, "{null:1,");
        TEST_ERROR(JsonParserStateCode::MISS_KEY, "{[]:1,");
        TEST_ERROR(JsonParserStateCode::MISS_KEY, "{{}:1,");
        TEST_ERROR(JsonParserStateCode::MISS_KEY, "{\"a\":1,");
    }

    static void Test_Parse_Error_MISS_COLON() {
        TEST_ERROR(JsonParserStateCode::MISS_COLON, "{\"a\"}");
        TEST_ERROR(JsonParserStateCode::MISS_COLON, "{\"a\",\"b\"}");
    }

    static void Test_Parse_Error_MISS_COMMA_OR_CURLY_BRACKET() {
        TEST_ERROR(JsonParserStateCode::MISS_COMMA_OR_CURLY_BRACKET, "{\"a\":1");
        TEST_ERROR(JsonParserStateCode::MISS_COMMA_OR_CURLY_BRACKET, "{\"a\":1]");
        TEST_ERROR(JsonParserStateCode::MISS_COMMA_OR_CURLY_BRACKET, "{\"a\":1 \"b\"");
        TEST_ERROR(JsonParserStateCode::MISS_COMMA_OR_CURLY_BRACKET, "{\"a\":{}");
    }

    void TestJsonParser::test() {
        std::cout << "----------------------------------[ test JsonParser ]----------------------------------" << std::endl;

        Test_Parse_NULL();
        Test_Parse_TRUE();
        Test_Parse_FALSE();
        Test_Parse_NUMBER();
        Test_Parse_STRING();
        Test_Parse_ARRAY();
        Test_Parse_Object();


        Test_Parse_Error_ONLY_WS();
        Test_Parse_Error_INVALID_VALUE();
        Test_Parse_Error_SURPLUS();
        Test_Parse_Error_OUT_OF_RANGE();
        Test_Parse_Error_MISS_QUOTATION_MARK();
        Test_Parse_Error_INVALID_STRING_ESCAPE();
        Test_Parse_Error_INVALID_STRING_CHAR();
        Test_Parse_Error_INVALID_UNICODE_HEX();
        Test_Parse_Error_INVALID_UNICODE_SURROGATE();
        Test_Parse_Error_MISS_COMMA_OR_SQUARE_BRACKET();
        Test_Parse_Error_MISS_KEY();
        Test_Parse_Error_MISS_COLON();
        Test_Parse_Error_MISS_COMMA_OR_CURLY_BRACKET();

        std::cout << std::endl
                  << "-------------------------------------------------------------------------------------" << std::endl
                  << passed_test_num << "/" << total_test_num << " ("
                  << 100 * ((float) passed_test_num / (float) total_test_num)
                  << " %) passed." << std::endl;
        std::cout << "----------------------------------[   Finished.   ]----------------------------------" << std::endl;
    }
}// namespace yzn