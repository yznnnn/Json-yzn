//
// Created by yzn on 2022/6/17.
//

#ifndef JSON_DEMO_JSONDICT_H
#define JSON_DEMO_JSONDICT_H
#include "./JsonNode.h"
#include <iomanip>// std::quoted()
#include <iostream>
#include <string>
#include <utility>


namespace yzn {

    class JsonDict {
    private:
        std::string key;
        JsonNode *value_ptr;
        void free() {
            delete this->value_ptr;
            this->value_ptr = nullptr;
        }

    public:
        JsonDict() : value_ptr(nullptr) {}
        JsonDict(const char *input_str, JsonNode *node_ptr)
            : key(input_str),
              value_ptr(node_ptr) {}
        JsonDict(const std::string &input_string_ob, JsonNode *node_ptr)
            : key(input_string_ob),
              value_ptr(node_ptr) {}
        JsonDict(std::string &&input_string_ob, JsonNode *node_ptr)
            : key(std::move(input_string_ob)),
              value_ptr(node_ptr) {}

        void print() const {
            std::cout << std::quoted(this->key) << " : ";
            if (this->value_ptr != nullptr) { this->value_ptr->print(); }
        }


        ~JsonDict() { this->free(); }
    };

}// namespace yzn

#endif//JSON_DEMO_JSONDICT_H
