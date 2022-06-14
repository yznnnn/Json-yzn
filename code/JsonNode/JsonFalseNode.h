//
// Created by yzn on 2022/6/14.
//

#ifndef JSON_DEMO_JSONFALSENODE_H
#define JSON_DEMO_JSONFALSENODE_H
#include "JsonNode.h"
namespace yzn {

    class JsonFalseNode : public JsonNode {
    public:
        JsonNodeType getType() override { return JsonNodeType::TYPE_FALSE; }
    };

}// namespace yzn

#endif//JSON_DEMO_JSONFALSENODE_H
