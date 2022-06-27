//
// Created by yzn on 2022/6/23.
//

#include "JsonGenerator.h"

namespace yzn {
    std::ostream &operator<<(std::ostream &os, const yzn::JsonGeneratorStateCode &state_code) {
        os << "Generator ";
        switch (state_code) {
            case JsonGeneratorStateCode::OK:
                return os << "State Code: OK";
            case JsonGeneratorStateCode::FAILED:
                return os << "State Code: FAILED";
        }
        return os;
    }

    JsonGeneratorStateCode JsonGenerator::stringify(const JsonNode *cur_node_ptr) {
        assert(cur_node_ptr != nullptr);
        this->clean();
        this->stringifyValue(cur_node_ptr);

        return JsonGeneratorStateCode::OK;
    }

    JsonGeneratorStateCode JsonGenerator::stringifyValue(const JsonNode *cur_node_ptr) {
        switch (cur_node_ptr->getType()) {
            case JsonNodeType::TYPE_NULL:
            case JsonNodeType::TYPE_TRUE:
            case JsonNodeType::TYPE_FALSE:
                return this->stringifyLiterals(cur_node_ptr);
            case JsonNodeType::TYPE_NUMBER:
                return this->stringifyNumber(cur_node_ptr);
            case JsonNodeType::TYPE_STRING:
                return this->stringifyString(cur_node_ptr);
            case JsonNodeType::TYPE_ARRAY:
                break;
            case JsonNodeType::TYPE_OBJECT:
                break;
            default:
                break;
        }
        return JsonGeneratorStateCode::FAILED;
    }

    JsonGeneratorStateCode JsonGenerator::stringifyLiterals(const JsonNode *cur_node_ptr) {
        switch (cur_node_ptr->getType()) {
            case JsonNodeType::TYPE_NULL:
                this->json_text += "null";
                break;
            case JsonNodeType::TYPE_TRUE:
                this->json_text += "true";
                break;
            case JsonNodeType::TYPE_FALSE:
                this->json_text += "false";
                break;
            default:
                break;
        }
        return JsonGeneratorStateCode::OK;
    }

    JsonGeneratorStateCode JsonGenerator::stringifyNumber(const JsonNode *cur_node_ptr) {
        assert(cur_node_ptr->getType() == JsonNodeType::TYPE_NUMBER);
        double temp_double = *((double *) cur_node_ptr->getValue());
        char buffer[32];
        sprintf(buffer, "%.17g", temp_double);
        this->json_text += buffer;

        return JsonGeneratorStateCode::OK;
    }
    JsonGeneratorStateCode JsonGenerator::stringifyString(const JsonNode *cur_node_ptr) {
        static const char hex_digits[] = {'0', '1', '2', '3', '4',
                                          '5', '6', '7', '8', '9',
                                          'A', 'B', 'C', 'D', 'E', 'F'};

        assert(cur_node_ptr->getType() == JsonNodeType::TYPE_STRING);
        this->json_text += '\"';

        const std::string &str_read = *(std::string *) cur_node_ptr->getValue();
        for (auto &ch: str_read) {
            switch (ch) {
                case '\"':
                    this->json_text += '\\';
                    this->json_text += '\"';
                    break;
                case '\\':
                    this->json_text += '\\';
                    this->json_text += '\\';
                    break;
                case '\b':
                    this->json_text += '\\';
                    this->json_text += 'b';
                    break;
                case '\f':
                    this->json_text += '\\';
                    this->json_text += 'f';
                    break;
                case '\n':
                    this->json_text += '\\';
                    this->json_text += 'n';
                    break;
                case '\r':
                    this->json_text += '\\';
                    this->json_text += 'r';
                    break;
                case '\t':
                    this->json_text += '\\';
                    this->json_text += 't';
                    break;
                default:
                    if (ch < 0x20) {
                        this->json_text += '\\';
                        this->json_text += 'u';
                        this->json_text += '0';
                        this->json_text += '0';
                        this->json_text += hex_digits[ch >> 4];
                        this->json_text += hex_digits[ch & 15];
                    } else {
                        this->json_text += ch;
                    }
            }
        }
        this->json_text += '\"';
        return JsonGeneratorStateCode::OK;
    }


}// namespace yzn