//
// Created by yzn on 2022/6/14.
//

#include "JsonNode.h"

namespace yzn {

    std::ostream &operator<<(std::ostream &os, const yzn::JsonNodeType &node_type) {
        switch (node_type) {
            case JsonNodeType::TYPE_UNKNOWN:
                return os << "Type: UNKNOWN";
            case JsonNodeType::TYPE_NULL:
                return os << "Type: NULL";
            case JsonNodeType::TYPE_TRUE:
                return os << "Type: TRUE";
            case JsonNodeType::TYPE_FALSE:
                return os << "Type: FALSE";
            case JsonNodeType::TYPE_NUMBER:
                return os << "Type: NUMBER";
            case JsonNodeType::TYPE_STRING:
                return os << "Type: STRING";
            case JsonNodeType::TYPE_ARRAY:
                return os << "Type: ARRAY";
            case JsonNodeType::TYPE_OBJECT:
                return os << "Type: OBJECT";
        }
    }



}// namespace yzn