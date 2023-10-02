#pragma once

#include <string>
#include <sstream>

// TO_STRING
//
// For some reason to have to_string work I have to define it as a template here.
// Either it is not supported by Windows or the Problem is with Visual Studio.
template <typename T>
std::string to_string(T value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}