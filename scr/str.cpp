#include <iostream>
#include "str.h"
#include <stdexcept>
#include <cstddef>
#include <cstring>
#include <ostream>

using value_type = char;
using size_type = std::size_t;
using difference_type = std::ptrdiff_t;
using reference = value_type&;
using const_reference = const value_type&;
using pointer = value_type*;
using const_pointer = const value_type*;
char npos = '\0';


Str::Str()
    :str(&npos)
    ,len(0){}

Str::Str(size_type count, value_type ch)
    :str(new value_type[count+1])
    ,len(count)
{
    for(size_type i = 0; i < len; i++){
        str[i] = ch;
    }
}

Str::Str(const_pointer s)
    :str(new value_type[strlen(s)+1])
    ,len(strlen(s))
{
    strcpy(str,s);
}

Str::Str(const_pointer s, size_type count)
    :str(new value_type[count+1])
    ,len(count)
{
    for(size_type i = 0; i < count; i++){
        str[i] = s[i];
    }
}

Str::Str(const Str& other)
    :str(new value_type[other.len+1])
    ,len(other.len)
{
    strcpy(str,other.str);
}

Str::Str(Str&& other) noexcept
    :str(other.str)
    ,len(other.len)
{
    other.str = &npos;
    other.len = 0;
}

Str::~Str()
{
    delete[]str;
}

Str& Str::operator=(const Str& other)
{
    Str tmp(other);
    swap(tmp);
    return *this;
}

Str& Str::operator=(Str&& other) noexcept
{
    delete[]str;
    str = other.str;
    len = other.len;
    other.str = &npos;
    other.len = 0;
    return *this;
}

reference Str::operator[](size_type idx) noexcept
{
    return str[idx];
}

const_reference Str::operator[](size_type idx) const noexcept
{
    return str[idx];
}

reference Str::at(size_type idx)
{
    if(idx >= len){
        throw std::out_of_range("out of range");
    }
    return str[idx];
}

const_reference Str::at(size_type idx) const
{
    if(idx >= len){
        throw std::out_of_range("out of range");
    }
    return str[idx];
}

reference Str::front() noexcept
{
    return str[0];
}

const_reference Str::front() const noexcept
{
    return str[0];
}

reference Str::back() noexcept
{
    return str[len-1];
}

const_reference Str::back() const noexcept
{
    return str[len-1];
}

pointer Str::data() noexcept
{
    return str;
}

const_pointer Str::data() const noexcept
{
    return str;
}

bool Str::empty() const noexcept
{
    return(!len) ? true : false;
}

size_type Str::size() const noexcept
{
    return len;
}

size_type Str::capacity() const noexcept
{
    return sizeof(str)+len;
}

void Str::clear()
{
    delete[]str;
    len = 0;
    str = &npos;
}

void Str::push_back(value_type ch)
{
    len++;
    pointer ptr = new value_type[len + 1];
    for(size_type i = 0; i < len-1; i++){
        ptr[i] = str[i];
    }
    delete[]str;
    ptr[len-1] = ch;
    ptr[len] = npos;
    str = new value_type[len + 1];
    for(size_type i = 0; i < len; i++){
        str[i] = ptr[i];
    }
    str[len] = npos;
    delete[]ptr;
}

void Str::pop_back()
{
    if(len){
        len--;
        pointer ptr = new value_type[len+1];
        for(size_type i = 0; i < len; i++){
                ptr[i] = str[i];
        }
        ptr[len] = npos;
        delete[]str;
        str = new value_type[len+1];
        for(size_type i = 0; i < len; i++){
                str[i] = ptr[i];
        }
        str[len] = npos;
        delete[]ptr;
    }
    else{
        str = &npos;
    }
}

Str& Str::operator+=(value_type ch)
{
    push_back(ch);
    return *this;
}

Str& Str::operator+=(const char* s)
{
    for(size_type i = 0; i < strlen(s); i++){
            push_back(s[i]);
    }
    return *this;
}

Str& Str::operator+=(const Str& other)
{
    for(size_type i = 0; i < other.size(); i++){
            push_back(other[i]);
    }
    return *this;
}

void Str::swap(Str& other) noexcept
{
    std::swap(str,other.str);
    std::swap(len,other.len);
}

size_type Str::find(const Str& st, size_type pos) const noexcept
{
    for(size_type i = pos; i < len; i++){
            if(str[i] == *(st.data())){
                size_type j = i;
                size_type k = 0;
                while (*(st.data()+k)){
                    if(str[j] != *(st.data()+k)){
                        break;
                    }
                    j++;
                    k++;
                }
                if(*(st.data()+k) == npos){
                    return j-k;
                }
                i += j-i;
            }
    }
    return npos;
}

size_type Str::find(const char* st, size_type pos) const noexcept
{
    Str stroka(st);
    return find(stroka,pos);

}

size_type Str::find(value_type ch, size_type pos) const noexcept
{
    for(size_type i = pos; i < len; i++){
            if(str[i] == ch){
                return i;
            }
    }
    return npos;
}

Str operator+(const Str& lhs, const Str& rhs)
{
    return Str(lhs) += rhs;
}

bool operator==(const Str& lhs, const Str& rhs)
{
    size_type i = 0;
    for(; *(lhs.data()+i) == *(rhs.data()+i) && i < lhs.size(); i++);
    return (i == lhs.size()) ? true : false;
}

bool operator!=(const Str& lhs, const Str& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Str& lhs, const Str& rhs)
{
    return (lhs.size() < rhs.size());
}

bool operator>(const Str& lhs, const Str& rhs)
{
    return !(lhs < rhs);
}

bool operator<=(const Str& lhs, const Str& rhs)
{
    return (lhs == rhs)||(lhs < rhs);
}

bool operator>=(const Str& lhs, const Str& rhs)
{
    return (lhs == rhs)||(lhs > rhs);
}

std::ostream& operator<<(std::ostream& stream, const Str& rhs)
{
    stream<<rhs.data()<<' ';
    return stream;
}
