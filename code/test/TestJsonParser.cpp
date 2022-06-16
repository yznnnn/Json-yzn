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
    void TestJsonParser::test() {
        std::cout << "----------------------------------[ test JsonNode ]----------------------------------" << std::endl;

        Test_Parse_NULL();
        Test_Parse_TRUE();
        Test_Parse_FALSE();
        Test_Parse_NUMBER();
        Test_Parse_STRING();


        Test_Parse_Error_ONLY_WS();
        Test_Parse_Error_INVALID_VALUE();
        Test_Parse_Error_SURPLUS();
        Test_Parse_Error_OUT_OF_RANGE();
        Test_Parse_Error_MISS_QUOTATION_MARK();
        Test_Parse_Error_INVALID_STRING_ESCAPE();
        Test_Parse_Error_INVALID_STRING_CHAR();
        Test_Parse_Error_INVALID_UNICODE_HEX();
        Test_Parse_Error_INVALID_UNICODE_SURROGATE();

        std::cout << std::endl
                  << "-------------------------------------------------------------------------------------" << std::endl
                  << passed_test_num << "/" << total_test_num << " ("
                  << 100 * ((float) passed_test_num / (float) total_test_num)
                  << " %) passed." << std::endl;
        std::cout << "----------------------------------[   Finished.   ]----------------------------------" << std::endl;
    }
}// namespace yzn