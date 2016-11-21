#pragma once

#include <iostream>
#include <fstream>

namespace details
{
    struct S
    {
        static std::ostream& getFile()
        {
            static std::ofstream file("log.txt");
            return file;
        }
    };
}

#define LOG(x) std::cout<<x<<"\n"

#define LOG_FILE(x) LOG(x)
//#define LOG_FILE(x) details::S::getFile() << x<<"\n"
