//
// Created by yzn on 2022/6/14.
//

#include "JsonParser.h"

namespace yzn {

    std::ostream &operator<<(std::ostream &os, const yzn::JsonParserStateCode &state_code) {
        switch (state_code) {
            case JsonParserStateCode::OK:
                return os << "State Code: OK";
        }
    }


    JsonParserStateCode JsonParser::parse(JsonNode **node_pp, const char *json_text) {
        return JsonParserStateCode::OK;
    }

}// namespace yzn