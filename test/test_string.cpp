#include "str.h"

#include <iostream>
#include <stdexcept>
#include <cassert>

using namespace pm;

void ctor_novalue()
{
    Str s;
    assert(s.empty() == true);
    assert(s[s.size()] == '\0');
    std::cout<<"1_OK"<<std::endl;
}

void ctor_value_char()
{
    Str s{10,'s'};
    assert(s.size() == 10);
    for(unsigned int i = 0; i < s.size(); i++)
        assert(s[i] == 's');
    //assert(s[s.size()] == '\0');
    std::cout<<"2_OK"<<std::endl;
}

void ctor_string()
{
    char test[] = "test text\0";
    Str s{test};
    assert(s.size() == 9);
    for(unsigned int i = 0; i < s.size(); i++){
            assert(s[i] == test[i]);
    }
    assert(s[s.size()] == '\0');
    std::cout<<"3_OK"<<std::endl;
}

void ctor_value_string()
{
    char test[] = "test text";
    Str s{test,5};
    assert(s.size() == 5);
    for(unsigned int i = 0; i < s.size(); i++){
            assert(s[i] == test[i]);
    }
    //assert(s[s.size()] == '\0');
    std::cout<<"4_OK"<<std::endl;
}

void ctor_copy()
{
    Str s{"text"};
    Str s_c{s};
    assert(s_c.size() == s.size());
    for(unsigned int i = 0; i < s.size(); i++){
            assert(s_c[i] == s[i]);
    }
    assert(s_c[s_c.size()] == '\0');
    std::cout<<"5_OK"<<std::endl;
}

void ctor_move()
{
    Str s{"test"};
    Str k = s;
    Str s_c{std::move(s)};
    assert(s_c.size() == k.size());
    for(unsigned int i = 0; i < k.size(); i++){
            assert(s_c[i] == k[i]);
    }
    assert(s_c[s_c.size()] == '\0');
    assert(s.size() == 0);
    assert(*(s.data()) == '\0');
    std::cout<<"6_OK"<<std::endl;
}

void oper_copy_equal()
{
    Str s{"text"};
    Str s_c = s;
    assert(s_c.size() == s.size());
    for(unsigned int i = 0; i < s.size(); i++){
            assert(s_c[i] == s[i]);
    }
    assert(s_c[s_c.size()] == '\0');
    std::cout<<"7_OK"<<std::endl;
}

void oper_move_equal()
{
    Str s{"test"};
    Str k = s;
    Str s_c = std::move(s);
    assert(s_c.size() == k.size());
    for(unsigned int i = 0; i < k.size(); i++){
            assert(s_c[i] == k[i]);
    }
    assert(s_c[s_c.size()] == '\0');
    assert(s.size() == 0);
    assert(*(s.data()) == '\0');
    std::cout<<"8_OK"<<std::endl;
}

void front()
{
    Str s{"testing"};
    assert(s.front() == 't');
    std::cout<<"9_OK"<<std::endl;
}

void back()
{
    Str s{"tests"};
    assert(s.back() == 's');
    std::cout<<"10_OK"<<std::endl;
}

void date()
{
    Str s{"true"};
    char test[] = "true";
    for(unsigned int i = 0; i < s.size(); i++){
            assert(*(s.data()+i) == test[i]);
    }
    assert(*(s.data()) == 't');
    std::cout<<"11_OK"<<std::endl;
}

void empty()
{
    Str s;
    assert(s.empty() == true);
    std::cout<<"12_OK"<<std::endl;
}

void size()
{
    Str s;
    Str k{"text full"};
    assert(s.size() == 0);
    assert(k.size() == 9);
    std::cout<<"13_OK"<<std::endl;
}

void capacity()
{
    Str s{"hello"};
    Str k{"hello world"};
    assert(s.capacity() == 5);
    assert(k.capacity() == 11);
    std::cout<<"14_OK"<<std::endl;
}

void clear()
{
    Str k{"text hello"};
    k.clear();
    assert(k.size() == 0);
    assert(*(k.data()) == '\0');
    std::cout<<"15_OK"<<std::endl;
}

void push_back_char()
{
    Str s{"hello"};
    char test[] = "world";
    char test1[] = "helloworld";
    unsigned int k =s.size();
    for(unsigned int i = 0; i < k; i++){
            s.push_back(test[i]);
    }
    for(unsigned int i = 0; i < s.size(); i++){
            assert(s[i] == test1[i]);
    }
    assert(s.size() == 10);
    assert(s[s.size()] == '\0');
    std::cout<<"16_OK"<<std::endl;
}

void push_back_string()
{
    Str s{"hello"};
    char test[] = "world";
    char test1[] = "helloworld";
    s.push_back(test);
    for(unsigned int i = 0; i < s.size(); i++){
            assert(s[i] == test1[i]);
    }
    assert(s.size() == 10);
    assert(s[s.size()] == '\0');
    std::cout<<"17_OK"<<std::endl;
}

void pop_back()
{
    Str s{"hello world"};
    char test[] = "hello";
    unsigned int k = s.size()-5;
    for(unsigned int i = 0; i < k; i++){
            s.pop_back();
    }
    for(unsigned int i = 0; i < k; i++){
            assert(s[i] == test[i]);
    }
    assert(s.size() == 5);
    assert(s[s.size()] == '\0');
    std::cout<<"18_OK"<<std::endl;
}

void oper_plus_equal_char()
{
    Str s{"green"};
    s += 's';
    assert(s[5] == 's');
    assert(s.size() == 6);
    assert(s[s.size()] == '\0');
    std::cout<<"19_OK"<<std::endl;
}

void oper_plus_equal_string()
{
    Str s{"test"};
    char test[] = " work";
    char test1[] = "test work";
    s += test;
    for(unsigned int i = 0; i < 9; i++){
            assert(s[i] == test1[i]);
    }
    assert(s.size() == 9);
    std::cout<<"20_OK"<<std::endl;
}

void oper_plus_equal_class()
{
    Str s{"test"};
    Str test{" work"};
    char test1[] = "test work";
    s += test;
    for(unsigned int i = 0; i < 9; i++){
            assert(s[i] == test1[i]);
    }
    assert(s.size() == 9);
    std::cout<<"21_OK"<<std::endl;
}

void swop()
{
    Str s;
    Str s1{"text"};
    Str tmp(s1);
    s.swap(tmp);
    for(unsigned int i = 0; i < s.size(); i++){
            assert(s[i] == s1[i]);
    }
    assert(s.size() == 4);
    std::cout<<"22_OK"<<std::endl;
}

void find_class()
{
    Str s{"hello mr freeman"};
    Str s1{"free"};
    Str s2{"r"};
    Str s3{"zero"};
    auto k1 = s.find(s1);
    auto k2 = s.find(s2,3);
    auto k3 = s.find(s2,9);
    auto k4 = s.find(s3);
    assert(k1 == 9);
    assert(k2 == 7);
    assert(k3 == 10);
    assert(k4 == '\0');
    std::cout<<"23_OK"<<std::endl;
}

void find_string()
{
    Str s{"good job friend !"};
    char s1[] = "!";
    char s2[] = "job";
    char s3[] = "o";
    char s4[] = "z";
    auto k1 = s.find(s1,12);
    auto k2 = s.find(s2);
    auto k3 = s.find(s3);
    auto k4 = s.find(s4);
    assert(k1 == 16);
    assert(k2 == 5);
    assert(k3 == 1);
    assert(k4 == '\0');
    std::cout<<"24_OK"<<std::endl;
}

void find_char()
{
    Str s{"my job is find char in string"};
    char c1 = 's';
    char c2 = '4';
    char c3 = 'f';
    char c4 = 'j';
    auto k1 = s.find(c1);
    auto k2 = s.find(c2,4);
    auto k3 = s.find(c3,3);
    auto k4 = s.find(c4,10);
    assert(k1 == 8);
    assert(k2 == '\0');
    assert(k3 == 10);
    assert(k4 == '\0');
    std::cout<<"25_OK"<<std::endl;
}

void oper_plus_class()
{
    Str s{"wrong"};
    Str s1{" way!"};
    Str s2 = s + s1;
    for(unsigned int  i = 0; i < s.size(); i++){
            assert(s2[i] == s[i]);
            assert(s2[i+s.size()] == s1[i]);
    }
    assert(s2[s2.size()] == '\0');
    std::cout<<"26_OK"<<std::endl;
}

void oper_equal()
{
    Str s{"warning"};
    Str s1{"this is wrong"};
    Str s2{s};
    bool b1 = (s == s1);
    bool b2 = (s == s2);
    assert(b1 == false);
    assert(b2 == true);
    std::cout<<"27_OK"<<std::endl;
}

void oper_not_equal()
{
    Str s{"warning"};
    Str s1{"this is wrong"};
    Str s2{s};
    bool b1 = (s != s1);
    bool b2 = (s != s2);
    assert(b1 == true);
    assert(b2 == false);
    std::cout<<"28_OK"<<std::endl;
}

void oper_less()
{
    Str s{"2"};
    Str s1{"3"};
    Str s2{s};
    Str s3{"1"};
    bool b1 = (s < s1);
    bool b2 = (s < s2);
    bool b3 = (s < s3);
    assert(b1 == true);
    assert(b2 == false);
    assert(b3 == false);
    std::cout<<"29_OK"<<std::endl;
}

void oper_more()
{
    Str s{"1"};
    Str s1{"2"};
    Str s2{"0"};
    bool b1 = (s > s1);
    bool b2 = (s > s2);
    assert(b1 == false);
    assert(b2 == true);
    std::cout<<"30_OK"<<std::endl;
}

void oper_less_equal()
{
    Str s{"1"};
    Str s1{"3"};
    Str s2{"2"};
    Str s3{"0"};
    bool b1 = (s <= s1);
    bool b2 = (s <= s2);
    bool b3 = (s <= s3);
    assert(b1 == true);
    assert(b2 == true);
    assert(b3 == false);
    std::cout<<"31_OK"<<std::endl;
}

void oper_large_equal()
{
    Str s{"1"};
    Str s1{"2"};
    Str s2{"3"};
    Str s3{"0"};
    bool b1 = (s >= s1);
    bool b2 = (s >= s2);
    bool b3 = (s >= s3);
    assert(b1 == false);
    assert(b2 == false);
    assert(b3 == true);
    std::cout<<"32_OK"<<std::endl;
}

int main()
{

try
{

ctor_novalue();
ctor_value_char();
ctor_string();
ctor_value_string();
ctor_copy();
ctor_move();
oper_copy_equal();
oper_move_equal();
front();
back();
date();
empty();
size();
capacity();
clear();
push_back_char();
push_back_string();
pop_back();
oper_plus_equal_char();
oper_plus_equal_string();
oper_plus_equal_class();
swop();
find_class();
find_string();
find_char();
oper_plus_class();
oper_equal();
oper_not_equal();
oper_less();
oper_more();
oper_less_equal();
oper_large_equal();

}

catch(std::invalid_argument& oop)
{
    std::cout<<"exception:"<<oop.what()<<std::endl;
}

catch(std::bad_alloc& oop)
{
    std::cout<<"exception:"<<oop.what()<<std::endl;
}

catch(std::out_of_range& oop)
{
    std::cout<<"exception:"<<oop.what()<<std::endl;
}

    return 0;
}
