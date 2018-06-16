#ifndef KEYGEN_NO_STRING_VIEW_H_
#define KEYGEN_NO_STRING_VIEW_H_

#if KeyGen_COMPILER_CXX_STD_17
#else
#include <iostream>

inline void TestStringView()
{
    std::cout << "string_view disabled; C++17 support is off line!\n";
}
#endif // KeyGen_COMPILER_CXX_STD_17

#endif // KEYGEN_NO_STRING_VIEW_H_