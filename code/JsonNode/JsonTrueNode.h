//
// Created by yzn on 2022/6/14.
//

#ifndef JSON_DEMO_JSONTRUENODE_H
#define JSON_DEMO_JSONTRUENODE_H
#include "JsonNode.h"
namespace yzn {

    class JsonTrueNode : public JsonNode {
    public:
        JsonNodeType getType() const override { return JsonNodeType::TYPE_TRUE; }

        void print() const override { std::cout << "true"; }
    };

}// namespace yzn

#endif//JSON_DEMO_JSONTRUENODE_H
