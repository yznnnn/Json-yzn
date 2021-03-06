//
// Created by yzn on 2022/6/14.
//

#include "JsonParser.h"

namespace yzn {

    std::ostream &operator<<(std::ostream &os, const yzn::JsonParserStateCode &state_code) {
        os << "Parser ";

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
            case JsonParserStateCode::MISS_KEY:
                return os << "State Code: MISS_KEY";
            case JsonParserStateCode::MISS_COLON:
                return os << "State Code: MISS_COLON";
            case JsonParserStateCode::MISS_COMMA_OR_CURLY_BRACKET:
                return os << "State Code: MISS_COMMA_OR_CURLY_BRACKET";
        }
        return os;
    }


    JsonParserStateCode JsonParser::parse(JsonNode **node_pp, const char *json_text) {
        assert(*node_pp == nullptr && json_text != nullptr);
        this->cur_char = json_text;

        this->parseWhitespace();

        JsonParserStateCode state_code = this->parseValue(node_pp);
        if (state_code == JsonParserStateCode::OK) {
            this->parseWhitespace();// ?????????????????? ws
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
            case '\"':
                return this->parseString(node_pp);
            case '\0':
                return JsonParserStateCode::ONLY_WS;
            case '[':
                return this->parseArray(node_pp);
            case '{':
                return this->parseObject(node_pp);
            default:
                return this->parseNumber(node_pp);
        }
    }

    JsonParserStateCode JsonParser::parseLiterals(JsonNode **node_pp,
                                                  const char *expect_literals,
                                                  JsonNodeType expect_type) {
        assert(*(this->cur_char) == expect_literals[0]);// ??????????????????

        /* ?????????????????? */
        size_t i;
        for (i = 1; i < strlen(expect_literals); i++) {
            if (this->cur_char[i] != expect_literals[i]) {
                return JsonParserStateCode::INVALID_VALUE;
            }
        }

        /* ???????????????????????????????????? */
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

        this->cur_char = this->cur_char + i;// ????????????????????? value ????????????????????????
        return JsonParserStateCode::OK;
    }

    JsonParserStateCode JsonParser::parseNumber(JsonNode **node_pp) {
        const char *p = this->cur_char;

        // ????????????
        if (*p == '-') { p++; }

        // ????????????
        if (*p == '0') {
            p++;
        } else {
            if ('1' <= *p && *p <= '9') {
                p++;
                while ('0' <= *p && *p <= '9') { p++; }
            } else {
                return JsonParserStateCode::INVALID_VALUE;
            }
        }

        // ????????????
        if (*p == '.') {
            p++;
            if (!('0' <= *p && *p <= '9')) { return JsonParserStateCode::INVALID_VALUE; }
            while ('0' <= *p && *p <= '9') { p++; }
        }

        // ????????????
        if (*p == 'e' || *p == 'E') {
            p++;
            if (*p == '+' || *p == '-') { p++; }
            if (!('0' <= *p && *p <= '9')) { return JsonParserStateCode::INVALID_VALUE; }
            while ('0' <= *p && *p <= '9') { p++; }
        }

        // ????????????
        errno = 0;
        double value = strtod(this->cur_char, nullptr);
        if (errno == ERANGE && (value == HUGE_VAL || value == -HUGE_VAL)) {
            return JsonParserStateCode::OUT_OF_RANGE;
        }

        *node_pp = new JsonNumberNode(value);
        this->cur_char = p;
        return JsonParserStateCode::OK;
    }

    JsonParserStateCode JsonParser::parseString(JsonNode **node_pp) {
        std::string temp_string;
        JsonParserStateCode state_code = this->parseString_raw(temp_string);
        if (state_code == JsonParserStateCode::OK) {
            *node_pp = new JsonStringNode(std::move(temp_string));
        }
        return state_code;
    }

    const char *JsonParser::parseHEX4(const char *p, unsigned int *u) {
        int i;
        *u = 0;
        for (i = 0; i < 4; i++) {
            char ch = *p++;
            *u <<= 4;
            if (ch >= '0' && ch <= '9') {
                *u |= ch - '0';
            } else if (ch >= 'A' && ch <= 'F') {
                *u |= ch - ('A' - 10);
            } else if (ch >= 'a' && ch <= 'f') {
                *u |= ch - ('a' - 10);
            } else {
                return nullptr;
            }
        }
        return p;
    }

    void JsonParser::encodeUTF8(std::string &temp_string, unsigned int u) {
        if (u <= 0x7F) {
            temp_string += (char) (u & 0xFF);
        } else if (u <= 0x7FF) {
            temp_string += (char) (0xC0 | ((u >> 6) & 0xFF));
            temp_string += (char) (0x80 | (u & 0x3F));
        } else if (u <= 0xFFFF) {
            temp_string += (char) (0xE0 | ((u >> 12) & 0xFF));
            temp_string += (char) (0x80 | ((u >> 6) & 0x3F));
            temp_string += (char) (0x80 | (u & 0x3F));
        } else {
            assert(u <= 0x10FFFF);
            temp_string += (char) (0xF0 | ((u >> 18) & 0xFF));
            temp_string += (char) (0x80 | ((u >> 12) & 0x3F));
            temp_string += (char) (0x80 | ((u >> 6) & 0x3F));
            temp_string += (char) (0x80 | (u & 0x3F));
        }
    }

    JsonParserStateCode JsonParser::parseArray(JsonNode **node_pp) {
        assert(*(this->cur_char) == '[');// ????????????????????????
        this->cur_char++;
        JsonParserStateCode state_code;

        // ?????? ws
        this->parseWhitespace();

        // ?????? ???array
        if (*(this->cur_char) == ']') {
            *node_pp = new JsonArrayNode();// ??????????????? array
            this->cur_char++;
            return JsonParserStateCode::OK;
        }

        // ?????? array ??????
        std::vector<JsonNode *> temp_vec;
        size_t num = 0;
        while (true) {
            JsonNode *temp_node_ptr = nullptr;
            state_code = this->parseValue(&temp_node_ptr);

            // ????????????????????????
            if (state_code != JsonParserStateCode::OK) {
                JsonParser::deleteNodePtrVector(temp_vec);
                return state_code;
            }

            // ????????????????????????????????? temp_vec
            num++;
            temp_vec.push_back(temp_node_ptr);

            // ?????? ws
            this->parseWhitespace();

            // ??????????????????
            if (*(this->cur_char) == ',')// ??????????????????
            {
                this->cur_char++;
                this->parseWhitespace();
            } else if (*(this->cur_char) == ']')// ????????????????????????????????????
            {
                this->cur_char++;
                *node_pp = new JsonArrayNode(std::move(temp_vec));// ????????????
                return JsonParserStateCode::OK;
            } else {
                return JsonParserStateCode::MISS_COMMA_OR_SQUARE_BRACKET;
            }
        }
    }

    JsonParserStateCode JsonParser::parseString_raw(std::string &temp_string) {
        assert(*(this->cur_char) == '\"');// ????????????????????????
        this->cur_char++;
        const char *p = this->cur_char;
        unsigned H, L;

        while (true) {
            char ch = *p++;
            switch (ch) {
                case '\"':
                    this->cur_char = p;
                    return JsonParserStateCode::OK;
                case '\0':
                    return JsonParserStateCode::MISS_QUOTATION_MARK;
                case '\\':
                    switch (*p++) {
                        case '\"':
                            temp_string += '\"';
                            break;
                        case '\\':
                            temp_string += '\\';
                            break;
                        case '/':
                            temp_string += '/';
                            break;
                        case 'b':
                            temp_string += '\b';
                            break;
                        case 'f':
                            temp_string += '\f';
                            break;
                        case 'n':
                            temp_string += '\n';
                            break;
                        case 'r':
                            temp_string += '\r';
                            break;
                        case 't':
                            temp_string += '\t';
                            break;
                        case 'u':
                            if (!(p = JsonParser::parseHEX4(p, &H))) { return JsonParserStateCode::INVALID_UNICODE_HEX; }
                            if (H >= 0xD800 && H <= 0xDBFF) /* ???????????????????????????????????? \u ?????? */
                            {
                                if (*p++ != '\\') { return JsonParserStateCode::INVALID_UNICODE_SURROGATE; }
                                if (*p++ != 'u') { return JsonParserStateCode::INVALID_UNICODE_SURROGATE; }
                                if (!(p = JsonParser::parseHEX4(p, &L))) { return JsonParserStateCode::INVALID_UNICODE_HEX; }
                                if (L < 0xDC00 || L > 0xDFFF) { return JsonParserStateCode::INVALID_UNICODE_SURROGATE; }
                                H = (((H - 0xD800) << 10) | (L - 0xDC00)) + 0x10000;
                            }
                            JsonParser::encodeUTF8(temp_string, H);
                            break;
                        default:
                            return JsonParserStateCode::INVALID_STRING_ESCAPE;
                    }
                    break;
                default:
                    if ((unsigned char) ch < 0x20) { return JsonParserStateCode::INVALID_STRING_CHAR; }
                    temp_string += ch;
            }
        }
    }

    JsonParserStateCode JsonParser::parseObject(JsonNode **node_pp) {
        assert(*(this->cur_char) == '{');// ????????????????????????
        this->cur_char++;
        JsonParserStateCode state_code;

        // ?????? ws
        this->parseWhitespace();

        // ?????? ???array
        if (*(this->cur_char) == '}') {
            *node_pp = new JsonObjectNode;// ??????????????? array
            this->cur_char++;
            return JsonParserStateCode::OK;
        }

        // ?????? object ??????
        std::vector<JsonDict *> temp_vec;
        size_t num = 0;
        while (true) {
            // ?????? key
            if (*(this->cur_char) != '\"') { return JsonParserStateCode::MISS_KEY; }
            std::string temp_key_string;
            state_code = this->parseString_raw(temp_key_string);
            if (state_code != JsonParserStateCode::OK) { return state_code; }

            // ?????? :
            this->parseWhitespace();
            if (*(this->cur_char) != ':') { return JsonParserStateCode::MISS_COLON; }
            this->cur_char++;

            // ?????? ???
            this->parseWhitespace();
            JsonNode *temp_node_ptr = nullptr;
            state_code = this->parseValue(&temp_node_ptr);

            // ????????????????????????
            if (state_code != JsonParserStateCode::OK) {
                JsonParser::deleteDictPtrVector(temp_vec);
                return state_code;
            }

            // ????????????????????? temp_vec
            num++;
            temp_vec.push_back(new JsonDict(std::move(temp_key_string), temp_node_ptr));

            // ?????? ws
            this->parseWhitespace();

            // ??????????????????
            if (*(this->cur_char) == ',')// ??????????????????
            {
                this->cur_char++;
                this->parseWhitespace();
            } else if (*(this->cur_char) == '}')// ????????????????????????????????????
            {
                this->cur_char++;
                *node_pp = new JsonObjectNode(std::move(temp_vec));// ????????????
                return JsonParserStateCode::OK;
            } else {
                return JsonParserStateCode::MISS_COMMA_OR_CURLY_BRACKET;
            }
        }
    }


}// namespace yzn