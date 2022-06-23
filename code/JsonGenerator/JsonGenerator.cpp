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
                break;
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


}// namespace yzn