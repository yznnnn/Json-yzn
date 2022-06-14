//
// Created by yzn on 2022/6/14.
//

#ifndef JSON_DEMO_JSONSTRINGNODE_H
#define JSON_DEMO_JSONSTRINGNODE_H
#include "../myString/myString.h"
#include "JsonNode.h"
namespace yzn {

    class JsonStringNode : public JsonNode {
    private:
        myString value;

    public:
        JsonStringNode() = default;

        explicit JsonStringNode(const char *input_str) {
            this->value = input_str;
        }

        explicit JsonStringNode(const myString &input_myString_ob) {
            this->value = input_myString_ob;// 深拷贝
            // TODO 考虑移动语义
        }

        JsonNodeType getType() override { return JsonNodeType::TYPE_STRING; }
        const void *getValue() const override { return &this->value; }
    };

}// namespace yzn

#endif//JSON_DEMO_JSONSTRINGNODE_H
