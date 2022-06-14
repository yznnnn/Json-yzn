//
// Created by yzn on 2022/6/12.
//

#ifndef BASIC_DATA_STRUCTURE_MYSTRING_H
#define BASIC_DATA_STRUCTURE_MYSTRING_H
#include <cstring>
#include <iomanip>
#include <iostream>

namespace yzn {

    class myString {
    private:
        char *str = nullptr;
        size_t str_len;// 字符串的长度
        static float rate;

        size_t getMemUse() const {// 获得实际使用的内存块的数量，块大小为 sizeof(char)
            if (this->str == nullptr) { return 0; }
            return (this->str_len + 1);
        }

        size_t getMemMax() const {// 获得实际分配的内存块的数量，块大小为 sizeof(char)
            if (this->str == nullptr) { return 0; }
            return _msize(this->str) / sizeof(char);
        }

        size_t getMemLow() const {// 获得检测范围的下界
            if (this->str == nullptr) { return 0; }
            return ((1 - rate) / (1 + rate)) * this->getMemMax();
        }

        void memUpdate(size_t expect_len);

        void freeSelf() {
            free(this->str);
            this->str = nullptr;
            this->str_len = 0;
        }


    public:
        /* 构造函数 */
        myString() {
            this->str_len = 0;
            this->memUpdate(this->str_len);
            this->str[this->str_len] = '\0';
        }

        explicit myString(const char *input_str);
        myString(const myString &ob);

        ~myString() { this->freeSelf(); }


        /* 运算符 */
        myString &operator=(char input_char);// 拷贝赋值
        myString &operator=(const char *input_str);
        myString &operator=(const myString &ob);

        myString &operator+=(char input_char);
        myString &operator+=(const char *input_str);
        myString &operator+=(const myString &ob);

        bool operator==(const char *input_str);
        bool operator==(const myString &ob);


        /* const 函数*/
        const char *getStr() const { return this->str; }

        size_t getLength() const { return this->str_len; }

        void showInfo() const;
    };


    std::ostream &operator<<(std::ostream &os, const yzn::myString &str);

    void test_myString();
}// namespace yzn

#endif//BASIC_DATA_STRUCTURE_MYSTRING_H
