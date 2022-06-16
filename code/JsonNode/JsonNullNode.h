//
// Created by yzn on 2022/6/14.
//

#ifndef JSON_DEMO_JSONNULLNODE_H
#define JSON_DEMO_JSONNULLNODE_H
#include "JsonNode.h"
#include <iostream>


namespace yzn {

    class JsonNullNode : public JsonNode {
    public:
        JsonNodeType getType() override { return JsonNodeType::TYPE_NULL; }

        void print() const override { std::cout << "null"; }
    };

}// namespace yzn

#endif//JSON_DEMO_JSONNULLNODE_H
