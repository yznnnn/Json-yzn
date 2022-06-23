//
// Created by yzn on 2022/6/23.
//

#ifndef JSON_DEMO_JSONGENERATOR_H
#define JSON_DEMO_JSONGENERATOR_H
#include "../JsonNode/JsonNode.h"
#include <string>

namespace yzn {
    enum class JsonGeneratorStateCode {
        OK = 0// 生成成功
    };


    class JsonGenerator {
    private:
        std::string json_text;
        void clean() { this->json_text = ""; }

    public:
        JsonGeneratorStateCode stringify(JsonNode *node_ptr);

        const std::string &getJsonText() const { return this->json_text; }
    };

}// namespace yzn

#endif//JSON_DEMO_JSONGENERATOR_H
