#include "str.h"

#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <cstring>
#include <ostream>

using namespace pm;

Str::value_type npos = '\0';

Str::Str()
    :str(&npos)
    ,len(0){}

Str::Str(size_type count, value_type ch)
    :str(new value_type[count+1])
    ,len(count)
{
    std::fill_n(str,count,ch);
}

Str::Str(const_pointer s)
    :len(strlen(s))
    ,str(new value_type[len+1])
{
    strcpy(str,s);
}

Str::Str(const_pointer s, size_type count)
    :str(new value_type[count+1])
    ,len(count)
{
    strncpy(str,s,count);
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
    if(str != &npos){
        delete[]str;
    }
}

Str& Str::operator=(const Str& other)
{
    Str tmp(other);
    swap(tmp);
    return *this;
}

Str& Str::operator=(Str&& other) noexcept
{
    if(str != &npos){
        delete[]str;
    }
    str = other.str;
    len = other.len;
    other.str = &npos;
    other.len = 0;
    return *this;
}

Str::reference Str::operator[](size_type idx) noexcept
{
    return str[idx];
}

Str::const_reference Str::operator[](size_type idx) const noexcept
{
    return str[idx];
}

Str::reference Str::at(size_type idx)
{
    if(idx >= len){
        throw std::out_of_range("out of range");
    }
    return str[idx];
}

Str::const_reference Str::at(size_type idx) const
{
    if(idx >= len){
        throw std::out_of_range("out of range");
    }
    return str[idx];
}

Str::reference Str::front() noexcept
{
    return str[0];
}

Str::const_reference Str::front() const noexcept
{
    return str[0];
}

Str::reference Str::back() noexcept
{
    return str[len-1];
}

Str::const_reference Str::back() const noexcept
{
    return str[len-1];
}

Str::pointer Str::data() noexcept
{
    return str;
}

Str::const_pointer Str::data() const noexcept
{
    return str;
}

bool Str::empty() const noexcept
{
    return len == 0;
}

Str::size_type Str::size() const noexcept
{
    return len;
}

Str::size_type Str::capacity() const noexcept
{
    return len;
}

void Str::clear()
{
    if(str != &npos){
        delete[]str;
    }
    len = 0;
    str = &npos;
}

void Str::push_back(value_type ch)
{
    len++;
    pointer buf = new value_type[len + 1];
    strcpy(buf,str);
    buf[len - 1] = ch;
    buf[len] = npos;
    if(str != &npos){
        delete[]str;
    }
    str = buf;
}

void Str::push_back(const char* s)
{
    len += strlen(s);
    pointer buf = new value_type[len+1];
    strcpy(buf,str);
    strcat(buf,s);
    if(str != &npos){
        delete[]str;
    }
    str = buf;
}

void Str::pop_back()
{
    if(len){
        len--;
        pointer buf = new value_type[len + 1];
        for(size_type i = 0; i < len; i++){
            buf[i] = str[i];
        }
        buf[len] = npos;
        if(str != &npos){
            delete[]str;
        }
        str = buf;
    }
    else{
        throw std::invalid_argument("len == 0");
    }
}

Str& Str::operator+=(value_type ch)
{
    push_back(ch);
    return *this;
}

Str& Str::operator+=(const char* s)
{
    push_back(s);
    return *this;
}

Str& Str::operator+=(const Str& other)
{
    push_back(other.str);
    return *this;
}

void Str::swap(Str& other) noexcept
{
    std::swap(str,other.str);
    std::swap(len,other.len);
}

Str::size_type Str::find(const char* st, size_type pos) const noexcept
{
     for(size_type i = pos; i < len; i++){
            size_type k = 0;
            if(str[i] == st[k]){
                size_type j = i;
                while (st[k] != npos){
                    if(str[j] != st[k]){
                        break;
                    }
                    j++;
                    k++;
                }
                if(st[k] == npos){
                    return j-k;
                }
                i += j-i;
            }
    }
    return npos;
}

Str::size_type Str::find(const Str& st, size_type pos) const noexcept
{
    return find(st.str,pos);
}

Str::size_type Str::find(value_type ch, size_type pos) const noexcept
{
    for(size_type i = pos; i < len; i++){
            if(str[i] == ch){
                return i;
            }
    }
    return npos;
}

Str pm::operator+(const Str& lhs, const Str& rhs)
{
    return Str(lhs) += rhs;
}

bool pm::operator==(const Str& lhs, const Str& rhs)
{
    if(lhs.size() == rhs.size()){
            Str::size_type i = 0;
            for(; lhs[i] == rhs[i] && i < lhs.size() ; i++);
            return (i == lhs.size()) ? true : false;
    }
    return false;
}

bool pm::operator!=(const Str& lhs, const Str& rhs)
{
    return !(lhs == rhs);
}

bool pm::operator<(const Str& lhs, const Str& rhs)
{
    return (strcmp(lhs.data(), rhs.data()) < 0) ? true : false;
}

bool pm::operator>(const Str& lhs, const Str& rhs)
{
    return !(lhs < rhs);
}

bool pm::operator<=(const Str& lhs, const Str& rhs)
{
    return (lhs == rhs)||(lhs < rhs);
}

bool pm::operator>=(const Str& lhs, const Str& rhs)
{
    return (lhs == rhs)||(lhs > rhs);
}

std::ostream& pm::operator<<(std::ostream& stream, const Str& rhs)
{
    stream<<rhs.data()<<' ';
    return stream;
}

