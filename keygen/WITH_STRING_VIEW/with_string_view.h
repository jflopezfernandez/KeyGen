#ifndef KEYGEN_WITH_STRING_VIEW_H_
#define KEYGEN_WITH_STRING_VIEW_H_

#if KeyGen_COMPILER_CXX_STD_17
#include <iostream>

inline void TestStringView()
{
    std::cout << "string_view enabled; C++17 support is on line!\n";
}
#endif // KeyGen_COMPILER_CXX_STD_17

#endif // KEYGEN_WITH_STRING_VIEW_H_
