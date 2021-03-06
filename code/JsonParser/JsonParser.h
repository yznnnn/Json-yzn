//
// Created by yzn on 2022/6/14.
//

#ifndef JSON_DEMO_JSONPARSER_H
#define JSON_DEMO_JSONPARSER_H
#include "../JsonNode/JsonArrayNode.h"
#include "../JsonNode/JsonFalseNode.h"
#include "../JsonNode/JsonNode.h"
#include "../JsonNode/JsonNullNode.h"
#include "../JsonNode/JsonNumberNode.h"
#include "../JsonNode/JsonObjectNode.h"
#include "../JsonNode/JsonStringNode.h"
#include "../JsonNode/JsonTrueNode.h"
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>

namespace yzn {

    enum class JsonParserStateCode {
        OK = 0,                      // 解析成功
        ONLY_WS,                     // json-text 中，只有 ws
        INVALID_VALUE,               // json-text 中，value 包含非法字符
        SURPLUS,                     // json-text 中，ws value ws 之后还有多余字符
        OUT_OF_RANGE,                // json-text 中，number的值超过存储范围
        MISS_QUOTATION_MARK,         // json-text 中，string 缺少一个 '"'
        INVALID_STRING_ESCAPE,       // json-text 中，string 含有错误的转义字符
        INVALID_STRING_CHAR,         // json-text 中，string 含有非法字符
        INVALID_UNICODE_HEX,         // json-text 中，string 含有非法UNICODE字符
        INVALID_UNICODE_SURROGATE,   // json-text 中，string 含有非法高代理UNICODE字符
        MISS_COMMA_OR_SQUARE_BRACKET,// json-text 中，array 含有非法字符
        MISS_KEY,                    // json-text 中，object 找不到 key
        MISS_COLON,                  // json-text 中，object 找不到 :
        MISS_COMMA_OR_CURLY_BRACKET
    };
    std::ostream &operator<<(std::ostream &os, const yzn::JsonParserStateCode &state_code);

    class JsonParser {
    private:
        const char *cur_char;

        static void deleteJsonNode(JsonNode **node_pp) {
            delete *node_pp;
            *node_pp = nullptr;// 避免野指针
        }

        static void deleteNodePtrVector(std::vector<JsonNode *> &vec) {
            if (!vec.empty()) {
                for (auto &e: vec) {
                    delete e;
                    e = nullptr;
                }
            }
        }

        static void deleteDictPtrVector(std::vector<JsonDict *> &vec) {
            if (!vec.empty()) {
                for (auto &e: vec) {
                    delete e;
                    e = nullptr;
                }
            }
        }

        void parseWhitespace();
        JsonParserStateCode parseValue(JsonNode **node_pp);
        JsonParserStateCode parseLiterals(JsonNode **node_pp,
                                          const char *expect_literals,
                                          JsonNodeType expect_type);
        JsonParserStateCode parseNumber(JsonNode **node_pp);
        JsonParserStateCode parseString_raw(std::string &temp_string);
        JsonParserStateCode parseString(JsonNode **node_pp);
        JsonParserStateCode parseArray(JsonNode **node_pp);
        JsonParserStateCode parseObject(JsonNode **node_pp);

        static const char *parseHEX4(const char *p, unsigned int *u);
        static void encodeUTF8(std::string &temp_string, unsigned int u);

    public:
        JsonParserStateCode parse(JsonNode **node_pp,
                                  const char *json_text);
    };

}// namespace yzn

#endif//JSON_DEMO_JSONPARSER_H
