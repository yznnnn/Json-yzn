//
// Created by yzn on 2022/6/14.
//

#ifndef JSON_DEMO_JSONNUMBERNODE_H
#define JSON_DEMO_JSONNUMBERNODE_H
#include "JsonNode.h"
namespace yzn {

    class JsonNumberNode : public JsonNode {
    private:
        double value;

    public:
        JsonNumberNode() : value(0) {}
        explicit JsonNumberNode(double input_value) : value(input_value) {}

        JsonNodeType getType() override { return JsonNodeType::TYPE_NUMBER; }
        const void *getValue() const override { return &this->value; }
    };

}// namespace yzn

#endif//JSON_DEMO_JSONNUMBERNODE_H
