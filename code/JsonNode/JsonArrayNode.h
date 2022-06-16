//
// Created by yzn on 2022/6/16.
//

#ifndef JSON_DEMO_JSONARRAYNODE_H
#define JSON_DEMO_JSONARRAYNODE_H
#include "JsonNode.h"
#include <vector>
namespace yzn {

    class JsonArrayNode : public JsonNode {
    private:
        std::vector<JsonNode *> value{};

        void free() {
            if (!this->value.empty()) {
                for (auto &e: this->value) {
                    delete e;
                    e = nullptr;
                }
            }
        }

    public:
        JsonArrayNode() = default;
        JsonArrayNode(const std::vector<JsonNode *> &input_vector_ob) : value(input_vector_ob) {}
        JsonArrayNode(std::vector<JsonNode *> &&input_vector_ob) : value(std::move(input_vector_ob)) {}

        ~JsonArrayNode() override { this->free(); }

        JsonNodeType getType() override { return JsonNodeType::TYPE_ARRAY; }
        const void *getValue() const override {
            if (this->value.empty()) { return nullptr; }
            return &this->value;
        }

        void print() const override {
            std::cout << "[";
            if (!this->value.empty()) {
                size_t i;
                for (i = 0; i < this->value.size() - 1; i++) {
                    this->value[i]->print();
                    std::cout << ", ";
                }
                this->value[i]->print();
            }
            std::cout << "]";
        }
    };

}// namespace yzn

#endif//JSON_DEMO_JSONARRAYNODE_H
