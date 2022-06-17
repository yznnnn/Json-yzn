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

        JsonNode *node_ptr = new JsonNullNode();
        std::cout << node_ptr->getType() << "\t-> ";
        node_ptr->print();
        std::cout << std::endl;
    }

    static void test_JsonTrueNode() {
        std::cout << std::endl;

        JsonNode *node_ptr = new JsonTrueNode();
        std::cout << node_ptr->getType() << "\t-> ";
        node_ptr->print();
        std::cout << std::endl;
    }

    static void test_JsonFalseNode() {
        std::cout << std::endl;

        JsonNode *node_ptr = new JsonFalseNode();
        std::cout << node_ptr->getType() << "\t-> ";
        node_ptr->print();
        std::cout << std::endl;
    }

    static void test_JsonNumberNode() {
        std::cout << std::endl;

        JsonNumberNode node;
        std::cout << node.getType()
                  << "\t-> " << *((double *) node.getValue()) << std::endl;

        JsonNode *node_ptr = new JsonNumberNode(3.1415926);
        std::cout << node_ptr->getType() << "\t-> ";
        node_ptr->print();
        std::cout << std::endl;
    }

    static void test_JsonStringNode() {
        std::cout << std::endl;

        JsonStringNode node_0;
        std::cout << node_0.getType()
                  << "\t" << std::quoted(*((std::string *) node_0.getValue())) << std::endl
                  << std::endl;


        JsonStringNode node_1("hello");
        std::cout << node_1.getType() << "\t-> ";
        node_1.print();
        std::cout << std::endl
                  << std::endl;


        std::string str_0("apple");
        JsonStringNode node_2(str_0);
        std::cout << node_2.getType() << "\t-> ";
        node_2.print();
        std::cout << std::endl
                  << "str_0  : " << (void *) str_0.data() << "\t" << std::quoted(str_0) << std::endl
                  << "node_2 : " << (void *) (*((std::string *) node_2.getValue())).data() << "\t" << std::quoted(*((std::string *) node_2.getValue())) << std::endl
                  << std::endl;


        // 移动语义测试
        std::string str_1("Replaces the contents with a copy of str. If *this and str are the same object, this function has no effect.");
        std::cout << "str_1  : " << (void *) str_1.data() << "\t" << std::quoted(str_1) << std::endl
                  << std::endl;

        JsonNode *node_3_ptr = new JsonStringNode(str_1);
        std::cout << node_3_ptr->getType() << "\t-> ";
        node_3_ptr->print();
        std::cout << std::endl
                  << "str_1  : " << (void *) str_1.data() << "\t" << std::quoted(str_1) << std::endl
                  << "node_3 : " << (void *) (*((std::string *) node_3_ptr->getValue())).data() << "\t" << std::quoted(*((std::string *) node_3_ptr->getValue())) << std::endl
                  << std::endl;


        JsonNode *node_4_ptr = new JsonStringNode(std::move(str_1));
        std::cout << node_4_ptr->getType() << "\t-> ";
        node_4_ptr->print();
        std::cout << std::endl
                  << "str_1  : " << (void *) str_1.data() << "\t" << std::quoted(str_1) << std::endl
                  << "node_4 : " << (void *) (*((std::string *) node_4_ptr->getValue())).data() << "\t" << std::quoted(*((std::string *) node_4_ptr->getValue())) << std::endl
                  << std::endl;
    }

    static void test_JsonArrayNode() {
        std::cout << std::endl;

        JsonArrayNode node_0;
        std::cout << node_0.getType() << "\t-> ";
        node_0.print();
        std::cout << std::endl
                  << std::endl;


        // 移动语义测试
        std::vector<JsonNode *> temp;
        JsonNode *node_ptr;

        node_ptr = new JsonNumberNode(1.2);
        std::cout << node_ptr << "\t" << node_ptr->getType() << std::endl;
        temp.push_back(node_ptr);

        node_ptr = new JsonStringNode("道可道");
        std::cout << node_ptr << "\t" << node_ptr->getType() << std::endl;
        temp.push_back(node_ptr);

        node_ptr = new JsonStringNode("apple");
        std::cout << node_ptr << "\t" << node_ptr->getType() << std::endl;
        temp.push_back(node_ptr);

        node_ptr = new JsonNullNode();
        std::cout << node_ptr << "\t" << node_ptr->getType() << std::endl;
        temp.push_back(node_ptr);

        node_ptr = new JsonFalseNode();
        std::cout << node_ptr << "\t" << node_ptr->getType() << std::endl;
        temp.push_back(node_ptr);

        node_ptr = new JsonTrueNode();
        std::cout << node_ptr << "\t" << node_ptr->getType() << std::endl;
        temp.push_back(node_ptr);

        std::cout << std::endl;

        std::cout << "temp data: " << (void *) temp.data() << std::endl;
        for (const auto e: temp) {
            std::cout << e << "\t" << e->getType() << std::endl;
        }

        std::cout << std::endl;

        JsonNode *node_1_ptr = new JsonArrayNode(temp);
        std::cout << "temp data: " << (void *) temp.data() << std::endl;
        std::cout << node_1_ptr->getType() << "\t" << (void *) (*((std::vector<JsonNode *> *) node_1_ptr->getValue())).data() << "\t-> ";
        node_1_ptr->print();
        std::cout << std::endl
                  << std::endl;

        //delete node_1_ptr;

        JsonNode *node_2_ptr = new JsonArrayNode(std::move(temp));
        std::cout << "temp data: " << (void *) temp.data() << std::endl;
        std::cout << node_2_ptr->getType() << "\t" << (void *) (*((std::vector<JsonNode *> *) node_2_ptr->getValue())).data() << "\t-> ";
        node_1_ptr->print();


        std::cout << std::endl;
    }


    static void test_Dict() {
        std::cout << std::endl;

        JsonDict dict_0;
        dict_0.print();
        std::cout << std::endl;

        JsonDict dict_1("name",new JsonStringNode("Bob"));
        dict_1.print();
        std::cout << std::endl;

        JsonDict dict_2("age",new JsonNumberNode(12));
        dict_2.print();
        std::cout << std::endl;

        std::vector<JsonNode *> temp;
        JsonNode *node_ptr;

        node_ptr = new JsonNumberNode(1.2);
        temp.push_back(node_ptr);

        node_ptr = new JsonStringNode("道可道");
        temp.push_back(node_ptr);

        node_ptr = new JsonStringNode("apple");
        temp.push_back(node_ptr);

        node_ptr = new JsonNullNode();
        temp.push_back(node_ptr);

        node_ptr = new JsonFalseNode();
        temp.push_back(node_ptr);

        node_ptr = new JsonTrueNode();
        temp.push_back(node_ptr);

        JsonDict dict_3("array",new JsonArrayNode(std::move(temp)));
        dict_3.print();
        std::cout << std::endl;
    }


    void TestJsonNode::test() {
        std::cout << "----------------------------------[ test JsonNode ]----------------------------------" << std::endl;
//        //test_JsonNode();
//        test_JsonNullNode();
//        test_JsonTrueNode();
//        test_JsonFalseNode();
//        test_JsonNumberNode();
//        test_JsonStringNode();
//
//        test_JsonArrayNode();

        test_Dict();
    }
}// namespace yzn