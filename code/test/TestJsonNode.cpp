//
// Created by yzn on 2022/6/14.
//

#include "TestJsonNode.h"

namespace yzn {

    static void test_JsonNode() {
        std::cout << std::endl;

        std::cout << JsonNodeType::TYPE_UNKNOWN << std::endl;
        std::cout << JsonNodeType::TYPE_NULL << std::endl;
        std::cout << JsonNodeType::TYPE_TRUE << std::endl;
        std::cout << JsonNodeType::TYPE_FALSE << std::endl;
        std::cout << JsonNodeType::TYPE_NUMBER << std::endl;
        std::cout << JsonNodeType::TYPE_STRING << std::endl;
        std::cout << JsonNodeType::TYPE_ARRAY << std::endl;
        std::cout << JsonNodeType::TYPE_OBJECT << std::endl;

        JsonNode node;
        std::cout << node.getType() << std::endl;
    }

    static void test_JsonNullNode() {
        std::cout << std::endl;

        JsonNullNode node;
        std::cout << node.getType() << std::endl;
    }

    static void test_JsonTrueNode() {
        std::cout << std::endl;

        JsonTrueNode node;
        std::cout << node.getType() << std::endl;
    }

    static void test_JsonFalseNode() {
        std::cout << std::endl;

        JsonFalseNode node;
        std::cout << node.getType() << std::endl;
    }

    static void test_JsonNumberNode() {
        std::cout << std::endl;

        JsonNumberNode node;
        std::cout << node.getType()
                  << "\t" << *((double *) node.getValue()) << std::endl;

        JsonNumberNode node_1(3.14);
        std::cout << node_1.getType()
                  << "\t" << *((double *) node_1.getValue()) << std::endl;
    }

    static void test_JsonStringNode() {
        std::cout << std::endl;

        JsonStringNode node;
        std::cout << node.getType()
                  << "\t\"" << *((myString *) node.getValue()) << '\"' << std::endl
                  << std::endl;

        JsonStringNode node_1("hello");
        std::cout << node_1.getType()
                  << "\t\"" << *((myString *) node_1.getValue()) << '\"' << std::endl
                  << std::endl;

        myString str_0("apple");
        JsonStringNode node_2(str_0);
        std::cout << node_2.getType()
                  << "\t\"" << *((myString *) node_2.getValue()) << '\"' << std::endl
                  << std::endl;

        myString str_1("break");
        JsonNode *node_ptr = new JsonStringNode(str_1);
        std::cout << node_ptr->getType()
                  << "\t\"" << *((myString *) node_ptr->getValue()) << '\"' << std::endl
                  << std::endl;
        delete node_ptr;
    }


    void TestJsonNode::test() {
        test_JsonNode();
        test_JsonNullNode();
        test_JsonTrueNode();
        test_JsonFalseNode();
        test_JsonNumberNode();
        test_JsonStringNode();
    }
}// namespace yzn