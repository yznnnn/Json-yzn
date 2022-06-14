//
// Created by yzn on 2022/6/14.
//

#ifndef JSON_DEMO_JSONNODE_H
#define JSON_DEMO_JSONNODE_H
#include <iostream>

namespace yzn {

    enum class JsonNodeType {
        TYPE_UNKNOWN,
        TYPE_NULL,
        TYPE_TRUE,
        TYPE_FALSE,
        TYPE_NUMBER,
        TYPE_STRING,
        TYPE_ARRAY,
        TYPE_OBJECT
    };
    std::ostream &operator<<(std::ostream &os, const yzn::JsonNodeType &node_type);


    class JsonNode {
    public:
        virtual JsonNodeType getType() { return JsonNodeType::TYPE_UNKNOWN; }

        virtual const void *getValue() const { return nullptr; }

        virtual ~JsonNode() = default;
    };


}// namespace yzn

#endif//JSON_DEMO_JSONNODE_H
