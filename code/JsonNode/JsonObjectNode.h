//
// Created by yzn on 2022/6/17.
//

#ifndef JSON_DEMO_JSONOBJECTNODE_H
#define JSON_DEMO_JSONOBJECTNODE_H
#include "JsonDict.h"
#include "JsonNode.h"
#include <vector>
namespace yzn {
    class JsonObjectNode : public JsonNode {
    private:
        std::vector<JsonDict *> value{};
        void free() {
            if (!this->value.empty()) {
                for (auto &e: this->value) {
                    delete e;
                    e = nullptr;
                }
            }
        }

    public:
        JsonObjectNode() = default;
        explicit JsonObjectNode(const std::vector<JsonDict *> &input_vector_ob) : value(input_vector_ob) {}
        explicit JsonObjectNode(std::vector<JsonDict *> &&input_vector_ob) : value(std::move(input_vector_ob)) {}

        ~JsonObjectNode() override { this->free(); }

        JsonNodeType getType() const override { return JsonNodeType::TYPE_OBJECT; }
        const void *getValue() const override {
            if (this->value.empty()) { return nullptr; }
            return &this->value;
        }


        void print() const override {
            std::cout << "{";
            if (!this->value.empty()) {
                size_t i;
                for (i = 0; i < this->value.size() - 1; i++) {
                    std::cout << "\n\t";
                    this->value[i]->print();
                    std::cout << ",";
                }
                std::cout << "\n\t";
                this->value[i]->print();
                std::cout << "\n";
            }
            std::cout << "}";
        }
    };

}// namespace yzn

#endif//JSON_DEMO_JSONOBJECTNODE_H
