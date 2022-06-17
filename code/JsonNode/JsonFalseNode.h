//
// Created by yzn on 2022/6/14.
//

#ifndef JSON_DEMO_JSONFALSENODE_H
#define JSON_DEMO_JSONFALSENODE_H
#include "JsonNode.h"
namespace yzn {

    class JsonFalseNode : public JsonNode {
    public:
        JsonNodeType getType() const override { return JsonNodeType::TYPE_FALSE; }
        void print() const override { std::cout << "false"; }
    };

}// namespace yzn

#endif//JSON_DEMO_JSONFALSENODE_H
