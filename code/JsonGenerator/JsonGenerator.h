//
// Created by yzn on 2022/6/23.
//

#ifndef JSON_DEMO_JSONGENERATOR_H
#define JSON_DEMO_JSONGENERATOR_H
#include "../JsonNode/JsonNode.h"
#include "../JsonNode/JsonDict.h"
#include <cassert>
#include <string>
#include <vector>
namespace yzn {
    enum class JsonGeneratorStateCode {
        OK = 0,// 生成成功
        FAILED // 生成失败
    };
    std::ostream &operator<<(std::ostream &os, const yzn::JsonGeneratorStateCode &state_code);

    class JsonGenerator {
    private:
        std::string json_text;

        void clean() { this->json_text = ""; }
        JsonGeneratorStateCode stringifyValue(const JsonNode *cur_node_ptr);
        JsonGeneratorStateCode stringifyLiterals(const JsonNode *cur_node_ptr);
        JsonGeneratorStateCode stringifyNumber(const JsonNode *cur_node_ptr);
        JsonGeneratorStateCode stringifyString(const JsonNode *cur_node_ptr);
        JsonGeneratorStateCode stringifyStringRaw(const std::string &str_read);
        JsonGeneratorStateCode stringifyArray(const JsonNode *cur_node_ptr);
        JsonGeneratorStateCode stringifyObject(const JsonNode *cur_node_ptr);

    public:
        JsonGeneratorStateCode stringify(const JsonNode *cur_node_ptr);

        const std::string &getJsonText() { return this->json_text; }
    };

}// namespace yzn

#endif//JSON_DEMO_JSONGENERATOR_H
