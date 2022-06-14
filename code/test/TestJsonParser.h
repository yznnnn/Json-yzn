//
// Created by yzn on 2022/6/14.
//

#ifndef JSON_DEMO_TESTJSONPARSER_H
#define JSON_DEMO_TESTJSONPARSER_H
#include "../JsonNode/JsonNode.h"
#include "../JsonParser/JsonParser.h"
#include <iostream>

namespace yzn {

    /**
     * 测试样例统计
     */
#define EQUAL_STATISTICS(expect_value, actual_value, equality)           \
    do {                                                                 \
        total_test_num++;                                                \
        if (equality) {                                                  \
            passed_test_num++;                                           \
        } else {                                                         \
            std::cout << "<Line " << __LINE__ << "> "                    \
                      << __FILE__ << std::endl;                          \
            std::cout << "\t expect -> " << (expect_value) << std::endl; \
            std::cout << "\t actual -> " << (actual_value) << std::endl  \
                      << std::endl;                                      \
        }                                                                \
    } while (0)

    /**
     * 比较数字类型的结果
     */
#define EQUAL_NUMBER(expect_number, actual_number) \
    EQUAL_STATISTICS(expect_number, actual_number, \
                     (expect_number) == (actual_number))

    /**
     * 测试 literal(null \ true \ false) 类型的 parse
     */
#define TEST_LITERAL(expect_type, json_text)                                 \
    do {                                                                     \
        JsonNode *node_ptr = nullptr;                                        \
        JsonParser parser;                                                   \
        JsonParserStateCode state_code = parser.parse(&node_ptr, json_text); \
        EQUAL_NUMBER(JsonParserStateCode::OK, state_code);                   \
        if (node_ptr != nullptr) {                                           \
            EQUAL_NUMBER(expect_type, node_ptr->getType());                  \
        } else {                                                             \
            EQUAL_NUMBER(expect_type, JsonNodeType::TYPE_UNKNOWN);           \
        }                                                                    \
        delete node_ptr;                                                     \
        node_ptr = nullptr;                                                  \
    } while (0)


    class TestJsonParser {
    public:
        static void test();
    };

}// namespace yzn

#endif//JSON_DEMO_TESTJSONPARSER_H
