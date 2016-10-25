#pragma once

#include <cstddef>
#include <ostream>

namespace pm{

class Str {
public:
    //====================
    // Member types
    //====================
    
    using value_type = char;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    
    //=====================
    // Member functions
    //=====================
    // Creates null terminated empty string
    Str();

    // Create string with length equal to count filled with ch characters
    Str(size_type count, value_type ch);

    // Create copy of null terminated c style string
    Str(const char* s);

    // Create copy of first count characters from c style string
    Str(const char* s, size_type count);

    // Copy constructor
    Str(const Str& other);

    // Move constructor
    Str(Str&& other) noexcept;
    
    // Dectructor
    ~Str();

    // Copy assignment
    Str& operator=(const Str& other);

    // Move assignment
    Str& operator=(Str&& other) noexcept;

    //=====================
    // Element access
    //=====================

    // access specified character
    reference operator[](size_type idx) noexcept;

    const_reference operator[](size_type idx) const noexcept;

    // access specified character with bounds checking
    reference at(size_type idx);

    const_reference at(size_type idx) const;

    // access the first character
    reference front() noexcept;

    const_reference front() const noexcept;

    // access the last character
    reference back() noexcept;

    const_reference back() const noexcept;

    // returns a pointer to the first character of a string
    pointer data() noexcept;

    const_pointer data() const noexcept;

    //=====================
    // Capacity
    //=====================

    bool empty() const noexcept;

    size_type size() const noexcept;

    size_type capacity() const noexcept;


    //=====================
    // Operations
    //=====================
    
    void soother();

    void clear();

    // appends character to the end
    void push_back(value_type ch);

    // removes the last character
    void pop_back();

    // appends character to the end
    Str& operator+=(value_type ch);

    Str& operator+=(const char* s);

    Str& operator+=(const Str& other);

    // swaps the contents
    void swap(Str& other) noexcept;

    //=====================
    // Search
    //=====================

    //  Finds the first substring equal to str. Search begins at pos
    size_type find(const Str& st, size_type pos = 0) const noexcept;

    size_type find(const char* st, size_type pos = 0) const noexcept;

    size_type find(value_type ch, size_type pos = 0) const noexcept;

private:
    size_type len;
    size_type memory;
    pointer str;

};

//=====================
// Non-member functions
//=====================

// Concatenates two strings
Str operator+(const Str& lhs, const Str& rhs);

// Lexicographically compares two strings
bool operator==(const Str& lhs, const Str& rhs);

bool operator!=(const Str& lhs, const Str& rhs);

bool operator<(const Str& lhs, const Str& rhs);

bool operator>(const Str& lhs, const Str& rhs);

bool operator<=(const Str& lhs, const Str& rhs);

bool operator>=(const Str& lhs, const Str& rhs);

// Performs stream output on Str
std::ostream& operator<<(std::ostream& stream, const Str& rhs);

}
