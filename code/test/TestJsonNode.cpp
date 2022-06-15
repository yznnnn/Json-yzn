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

        JsonStringNode node_0;
        std::cout << node_0.getType()
                  << "\t" << std::quoted(*((std::string *) node_0.getValue())) << std::endl
                  << std::endl;

        JsonStringNode node_1("hello");
        std::cout << node_1.getType()
                  << "\t" << std::quoted(*((std::string *) node_1.getValue())) << std::endl
                  << std::endl;

        std::string str_0("apple");
        JsonStringNode node_2(str_0);
        std::cout << node_2.getType()
                  << "\t" << std::quoted(*((std::string *) node_2.getValue())) << std::endl;
        std::cout << "str_0  : " << (void *) str_0.data() << "\t" << std::quoted(str_0) << std::endl
                  << "node_2 : " << (void *) (*((std::string *) node_2.getValue())).data() << "\t" << std::quoted(*((std::string *) node_2.getValue())) << std::endl
                  << std::endl;


        // 移动语义测试
        std::string str_1("Replaces the contents with a copy of str. If *this and str are the same object, this function has no effect.");
        std::cout << "str_1  : " << (void *) str_1.data() << "\t" << std::quoted(str_1) << std::endl;

        JsonNode *node_3_ptr = new JsonStringNode(str_1);
        std::cout << node_3_ptr->getType()
                  << "\t" << std::quoted(*((std::string *) node_3_ptr->getValue())) << std::endl;
        std::cout << "str_1  : " << (void *) str_1.data() << "\t" << std::quoted(str_1) << std::endl
                  << "node_3 : " << (void *) (*((std::string *) node_3_ptr->getValue())).data() << "\t" << std::quoted(*((std::string *) node_3_ptr->getValue())) << std::endl
                  << std::endl;

        JsonNode *node_4_ptr = new JsonStringNode(std::move(str_1));
        std::cout << node_4_ptr->getType()
                  << "\t" << std::quoted(*((std::string *) node_4_ptr->getValue())) << std::endl;
        std::cout << "str_1  : " << (void *) str_1.data() << "\t" << std::quoted(str_1) << std::endl
                  << "node_4 : " << (void *) (*((std::string *) node_4_ptr->getValue())).data() << "\t" << std::quoted(*((std::string *) node_4_ptr->getValue())) << std::endl
                  << std::endl;
    }


    void TestJsonNode::test() {
        std::cout << "----------------------------------[ test JsonNode ]----------------------------------" << std::endl;
        test_JsonNode();
        test_JsonNullNode();
        test_JsonTrueNode();
        test_JsonFalseNode();
        test_JsonNumberNode();
        test_JsonStringNode();
    }
}// namespace yzn