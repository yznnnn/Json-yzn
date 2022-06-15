//
// Created by yzn on 2022/6/14.
//

#ifndef JSON_DEMO_TESTJSONPARSER_H
#define JSON_DEMO_TESTJSONPARSER_H
#include "../JsonNode/JsonNode.h"
#include "../JsonParser/JsonParser.h"
#include <cmath>
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
        JsonParser parser{};                                                 \
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


/**
 * 测试 number 类型的 parse
 */
#define TEST_NUMBER(expect_value, json_text)                                     \
    do {                                                                         \
        JsonNode *node_ptr = nullptr;                                            \
        JsonParser parser{};                                                     \
        JsonParserStateCode state_code = parser.parse(&node_ptr, json_text);     \
        EQUAL_NUMBER(JsonParserStateCode::OK, state_code);                       \
        if (node_ptr != nullptr) {                                               \
            EQUAL_NUMBER(JsonNodeType::TYPE_NUMBER, node_ptr->getType());        \
            EQUAL_NUMBER(expect_value, *((double *) node_ptr->getValue()));      \
        } else {                                                                 \
            EQUAL_NUMBER(JsonNodeType::TYPE_NUMBER, JsonNodeType::TYPE_UNKNOWN); \
            EQUAL_NUMBER(expect_value, NAN);                                     \
        }                                                                        \
        delete node_ptr;                                                         \
        node_ptr = nullptr;                                                      \
    } while (0)


    /**
     * 测试 解析出现错误时是否返回正确的状态码
     */
#define TEST_ERROR(expect_state_code, json_text)                             \
    do {                                                                     \
        JsonNode *node_ptr = nullptr;                                        \
        JsonParser parser{};                                                 \
        JsonParserStateCode state_code = parser.parse(&node_ptr, json_text); \
        EQUAL_NUMBER(expect_state_code, state_code);                         \
        delete node_ptr;                                                     \
        node_ptr = nullptr;                                                  \
    } while (0)

    class TestJsonParser {
    public:
        static void test();
    };

}// namespace yzn

#endif//JSON_DEMO_TESTJSONPARSER_H
