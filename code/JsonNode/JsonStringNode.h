//
// Created by yzn on 2022/6/14.
//

#ifndef JSON_DEMO_JSONSTRINGNODE_H
#define JSON_DEMO_JSONSTRINGNODE_H
#include "JsonNode.h"
#include <iomanip>// std::quoted()
#include <string>
#include <utility>
namespace yzn {

    class JsonStringNode : public JsonNode {
    private:
        std::string value;

    public:
        JsonStringNode() = default;

        explicit JsonStringNode(const char *input_str) : value(input_str) {}

        explicit JsonStringNode(const std::string &input_string_ob) : value(input_string_ob) {}

        explicit JsonStringNode(std::string &&input_string_ob) : value(std::move(input_string_ob)) {}


        JsonNodeType getType() override { return JsonNodeType::TYPE_STRING; }
        const void *getValue() const override { return &this->value; }
    };

}// namespace yzn

#endif//JSON_DEMO_JSONSTRINGNODE_H
