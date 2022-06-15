//
// Created by yzn on 2022/6/14.
//

#include "JsonParser.h"

namespace yzn {

    std::ostream &operator<<(std::ostream &os, const yzn::JsonParserStateCode &state_code) {
        switch (state_code) {
            case JsonParserStateCode::OK:
                return os << "State Code: OK";
            case JsonParserStateCode::ONLY_WS:
                return os << "State Code: ONLY_WS";
            case JsonParserStateCode::INVALID_VALUE:
                return os << "State Code: INVALID_VALUE";
            case JsonParserStateCode::SURPLUS:
                return os << "State Code: SURPLUS";
            case JsonParserStateCode::OUT_OF_RANGE:
                return os << "State Code: OUT_OF_RANGE";
            case JsonParserStateCode::MISS_QUOTATION_MARK:
                return os << "State Code: MISS_QUOTATION_MARK";
            case JsonParserStateCode::INVALID_STRING_ESCAPE:
                return os << "State Code: INVALID_STRING_ESCAPE";
            case JsonParserStateCode::INVALID_STRING_CHAR:
                return os << "State Code: INVALID_STRING_CHAR";
            case JsonParserStateCode::INVALID_UNICODE_HEX:
                return os << "State Code: INVALID_UNICODE_HEX";
            case JsonParserStateCode::INVALID_UNICODE_SURROGATE:
                return os << "State Code: INVALID_UNICODE_SURROGATE";
            case JsonParserStateCode::MISS_COMMA_OR_SQUARE_BRACKET:
                return os << "State Code: MISS_COMMA_OR_SQUARE_BRACKET";
        }
    }


    JsonParserStateCode JsonParser::parse(JsonNode **node_pp, const char *json_text) {
        assert(*node_pp == nullptr && json_text != nullptr);
        this->cur_char = json_text;

        this->parseWhitespace();

        JsonParserStateCode state_code = this->parseValue(node_pp);
        if (state_code == JsonParserStateCode::OK) {
            this->parseWhitespace();// 解析最后一个 ws
            if (*(this->cur_char) != '\0') {
                JsonParser::deleteJsonNode(node_pp);
                return JsonParserStateCode::SURPLUS;
            }
        }

        return state_code;
    }


    void JsonParser::parseWhitespace() {
        while (*(this->cur_char) == ' ' || *(this->cur_char) == '\t' ||
               *(this->cur_char) == '\n' || *(this->cur_char) == '\r') {
            this->cur_char++;
        }
    }

    JsonParserStateCode JsonParser::parseValue(JsonNode **node_pp) {
        switch (*this->cur_char) {
            case 'n':
                return this->parseLiterals(node_pp, "null", JsonNodeType::TYPE_NULL);
            case 't':
                return this->parseLiterals(node_pp, "true", JsonNodeType::TYPE_TRUE);
            case 'f':
                return this->parseLiterals(node_pp, "false", JsonNodeType::TYPE_FALSE);
            case '\0':
                return JsonParserStateCode::ONLY_WS;
            default:
                return this->parseNumber(node_pp);
        }
    }

    JsonParserStateCode JsonParser::parseLiterals(JsonNode **node_pp,
                                                  const char *expect_literals,
                                                  JsonNodeType expect_type) {
        assert(*(this->cur_char) == expect_literals[0]);// 检验开头字符

        /* 解析后续字符 */
        size_t i;
        for (i = 1; i < strlen(expect_literals); i++) {
            if (this->cur_char[i] != expect_literals[i]) {
                return JsonParserStateCode::INVALID_VALUE;
            }
        }

        /* 解析成功，生成具体的对象 */
        switch (expect_type) {
            case JsonNodeType::TYPE_NULL:
                *node_pp = new JsonNullNode();
                break;
            case JsonNodeType::TYPE_TRUE:
                *node_pp = new JsonTrueNode();
                break;
            case JsonNodeType::TYPE_FALSE:
                *node_pp = new JsonFalseNode();
                break;
            default:
                break;
        }

        this->cur_char = this->cur_char + i;// 令解析指针指向 value 之后的第一个字符
        return JsonParserStateCode::OK;
    }

    JsonParserStateCode JsonParser::parseNumber(JsonNode **node_pp) {
        const char *p = this->cur_char;

        // 解析负号
        if (*p == '-') { p++; }

        // 解析整数
        if (*p == '0') {
            p++;
        } else {
            if ('1' <= *p && *p <= '9') {
                p++;
                while ('0' <= *p && *p <= '9') {
                    p++;
                }
            } else {
                return JsonParserStateCode::INVALID_VALUE;
            }
        }

        // 解析小数
        if (*p == '.') {
            p++;
            if (!('0' <= *p && *p <= '9')) {
                return JsonParserStateCode::INVALID_VALUE;
            }
            while ('0' <= *p && *p <= '9') {
                p++;
            }
        }

        // 解析指数
        if (*p == 'e' || *p == 'E') {
            p++;
            if (*p == '+' || *p == '-') {
                p++;
            }
            if (!('0' <= *p && *p <= '9')) {
                return JsonParserStateCode::INVALID_VALUE;
            }
            while ('0' <= *p && *p <= '9') {
                p++;
            }
        }

        // 计算结果
        errno = 0;
        double value = strtod(this->cur_char, nullptr);
        if (errno == ERANGE && (value == HUGE_VAL || value == -HUGE_VAL)) {
            return JsonParserStateCode::OUT_OF_RANGE;
        }

        *node_pp = new JsonNumberNode(value);
        this->cur_char = p;
        return JsonParserStateCode::OK;
    }


}// namespace yzn