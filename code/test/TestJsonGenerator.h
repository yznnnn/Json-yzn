//
// Created by yzn on 2022/6/23.
//

#ifndef JSON_DEMO_TESTJSONGENERATOR_H
#define JSON_DEMO_TESTJSONGENERATOR_H
#include "../JsonGenerator/JsonGenerator.h"
#include "../JsonNode/JsonDict.h"
#include "../JsonNode/JsonNode.h"
#include "../JsonParser/JsonParser.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

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
 * 比较字符串类型的结果
 */
#define EQUAL_STRING(expect_string, actual_string) \
    EQUAL_STATISTICS(expect_string, actual_string, \
                     (expect_string) == (actual_string))



/**
 * 比较生成器生成的结果
 */
#define TEST_GENERATOR_BY_STRING(json_text)                                   \
    do {                                                                      \
        JsonNode *node_ptr = nullptr;                                         \
        JsonParser parser{};                                                  \
        JsonGenerator generator{};                                            \
        JsonParserStateCode state_code = parser.parse(&node_ptr, json_text);  \
        EQUAL_NUMBER(JsonParserStateCode::OK, state_code);                    \
        if (node_ptr != nullptr) {                                            \
            generator.stringify(node_ptr);                                    \
            const std::string &generator_json_text = generator.getJsonText(); \
            EQUAL_STRING(json_text, generator_json_text);                     \
        }                                                                     \
    } while (0)


    class TestJsonGenerator {
    public:
        static void test();
    };

}// namespace yzn

#endif//JSON_DEMO_TESTJSONGENERATOR_H
