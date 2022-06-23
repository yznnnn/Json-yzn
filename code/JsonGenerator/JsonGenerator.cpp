//
// Created by yzn on 2022/6/23.
//

#include "JsonGenerator.h"

namespace yzn {
    JsonGeneratorStateCode JsonGenerator::stringify(JsonNode *node_ptr) {
        this->clean();


        return JsonGeneratorStateCode::OK;
    }
}// namespace yzn