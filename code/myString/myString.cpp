//
// Created by yzn on 2022/6/12.
//

#include "myString.h"

namespace yzn {
    float myString::rate = 0.2;

    void myString::showInfo() const {
        std::cout << "\t   <&ob>"
                  << "\t           <&str>"
                  << "\t    [memLow"
                  << "\t memUse"
                  << "\t memMax]"
                  << "\t<String>"
                  << std::endl;
        std::cout << std::setfill('_')
                  << '\t' << std::setw(18) << (void *) (this)
                  << '\t' << std::setw(18) << (void *) (this->str)
                  << "\t   " << this->getMemLow()
                  << "\t   " << this->getMemUse()
                  << "\t   " << this->getMemMax()
                  << "\t    \"" << this->getStr() << '\"'
                  << std::endl
                  << std::endl;
    }

    void myString::memUpdate(size_t expect_len) {
        size_t mem_max = this->getMemMax();
        size_t mem_low = this->getMemLow();
        size_t mem_need = expect_len + 1;
        if (mem_need <= mem_low || mem_need >= mem_max) {
            this->str = (char *) realloc(this->str, (mem_need * (1 + rate)) * sizeof(char));
        }
    }

    myString::myString(const char *input_str) {
        this->str_len = strlen(input_str);
        this->memUpdate(this->str_len);
        memcpy(this->str, input_str, this->str_len * sizeof(char));
        this->str[this->str_len] = '\0';
    }
    myString::myString(const myString &ob) {
        this->str_len = ob.str_len;
        this->memUpdate(this->str_len);
        memcpy(this->str, ob.str, this->str_len * sizeof(char));
        this->str[this->str_len] = '\0';
    }

    myString &myString::operator=(char input_char) {
        this->str_len = 1;
        this->memUpdate(this->str_len);
        this->str[0] = input_char;
        this->str[this->str_len] = '\0';

        return *this;
    }
    myString &myString::operator=(const char *input_str) {
        this->str_len = strlen(input_str);
        this->memUpdate(this->str_len);
        memcpy(this->str, input_str, this->str_len * sizeof(char));
        this->str[this->str_len] = '\0';

        return *this;
    }
    myString &myString::operator=(const myString &ob) {
        if (this == &ob) { return *this; }

        this->str_len = ob.str_len;
        this->memUpdate(this->str_len);
        memcpy(this->str, ob.str, this->str_len * sizeof(char));
        this->str[this->str_len] = '\0';

        return *this;
    }

    myString &myString::operator+=(char input_char) {
        this->memUpdate(this->str_len + 1);
        this->str[this->str_len] = input_char;
        this->str_len++;
        this->str[this->str_len] = '\0';

        return *this;
    }
    myString &myString::operator+=(const char *input_str) {
        size_t input_len = strlen(input_str);
        this->memUpdate(this->str_len + input_len);
        memcpy(this->str + this->str_len * sizeof(char),
               input_str, input_len * sizeof(char));
        this->str_len += input_len;
        this->str[this->str_len] = '\0';

        return *this;
    }
    myString &myString::operator+=(const myString &ob) {
        this->memUpdate(this->str_len + ob.str_len);
        memcpy(this->str + this->str_len * sizeof(char),
               ob.str, ob.str_len * sizeof(char));
        this->str_len += ob.str_len;
        this->str[this->str_len] = '\0';

        return *this;
    }

    bool myString::operator==(const char *input_str) {
        size_t input_len = strlen(input_str);
        if (this->str_len != input_len) { return false; }
        if (memcmp(this->str, input_str, this->str_len) != 0) { return false; }
        return true;
    }
    bool myString::operator==(const myString &ob) {
        if (this->str_len != ob.str_len) { return false; }
        if (memcmp(this->str, ob.str, this->str_len) != 0) { return false; }
        return true;
    }


    std::ostream &operator<<(std::ostream &os, const yzn::myString &str) {
        return os << str.getStr();
    }

    void test_myString() {
        std::cout << "----------------------------------[ test myString ]----------------------------------" << std::endl;


        yzn::myString s0;
        std::cout << "s0\t";
        s0.showInfo();

        yzn::myString s1("hello,world!");
        std::cout << "s1\t";
        s1.showInfo();

        auto *s2_ptr = new yzn::myString("apple");
        std::cout << "s2\t";
        s2_ptr->showInfo();
        //delete s2_ptr;

        yzn::myString s3(s0);
        std::cout << "s3\t";
        s3.showInfo();

        s3 = s1;
        std::cout << "s3\t";
        s3.showInfo();

        s3 = *s2_ptr;
        std::cout << "s3\t";
        s3.showInfo();

        s3 = "appl";
        std::cout << "s3\t";
        s3.showInfo();

        s3 = "lppa";
        std::cout << "s3\t";
        s3.showInfo();

        s3 = "我能吞下玻璃而不伤身体";
        std::cout << "s3\t";
        s3.showInfo();

        s3 = 'j';
        std::cout << "s3\t";
        s3.showInfo();

        s3 += 'p';
        std::cout << "s3\t";
        s3.showInfo();

        s3 += 'a';
        std::cout << "s3\t";
        s3.showInfo();

        s3 += 'b';
        std::cout << "s3\t";
        s3.showInfo();

        s3 += 'c';
        std::cout << "s3\t";
        s3.showInfo();

        yzn::myString s4(s1);
        std::cout << "s4\t";
        s4.showInfo();

        s4 += "x";
        std::cout << "s4\t";
        s4.showInfo();

        s4 += s3;
        std::cout << "s4\t";
        s4.showInfo();

        yzn::myString s5("Three days to see.");
        std::cout << "s5\t";
        s5.showInfo();

        std::cout << (s5 == "Three days to see." ? "true" : "false") << std::endl;
        std::cout << (s5 == "Three days to see" ? "true" : "false") << std::endl;

        std::cout << (s5 == myString("Three days to see.") ? "true" : "false") << std::endl;
        std::cout << (s5 == myString("Three days to see") ? "true" : "false") << std::endl;

        delete s2_ptr;
        s2_ptr = nullptr;
    }

}// namespace yzn