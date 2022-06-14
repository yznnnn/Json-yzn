//
// Created by yzn on 2022/6/14.
//

#ifndef JSON_DEMO_JSONPARSER_H
#define JSON_DEMO_JSONPARSER_H
#include "../JsonNode/JsonNode.h"
#include <iostream>

namespace yzn {

    enum class JsonParserStateCode {
        OK// 解析成功
    };
    std::ostream &operator<<(std::ostream &os, const yzn::JsonParserStateCode &state_code);

    class JsonParser {
    private:
        char *cur_char = nullptr;

        JsonParserStateCode parseWhitespace();
        JsonParserStateCode parseValue();
        JsonParserStateCode parseLiterals();
        JsonParserStateCode parseNumber();
        JsonParserStateCode parseString();

    public:
        JsonParserStateCode parse(JsonNode **node_pp,
                                  const char *json_text);
    };

}// namespace yzn

#endif//JSON_DEMO_JSONPARSER_H
