//
// Created by yzn on 2022/6/14.
//

#ifndef JSON_DEMO_JSONTRUENODE_H
#define JSON_DEMO_JSONTRUENODE_H
#include "JsonNode.h"
namespace yzn {

    class JsonTrueNode : public JsonNode {
    public:
        JsonNodeType getType() override { return JsonNodeType::TYPE_TRUE; }
    };

}// namespace yzn

#endif//JSON_DEMO_JSONTRUENODE_H
