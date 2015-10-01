#pragma once

#include "utils.hpp"

#include <Windows.h>

namespace Memory
{
    class ProcessMemoryReader
    {
    private:
        HANDLE processHandle = NULL;

    public:
        ProcessMemoryReader()
        {}
        ProcessMemoryReader( DWORD pid )
        {
            processHandle = OpenProcess( READ_CONTROL,
                                         TRUE,
                                         pid );
        }
        ~ProcessMemoryReader()
        {
            Utils::safeCloseAndNullHandle( processHandle );
        }

        ProcessMemoryReader( ProcessMemoryReader &&rval ) :
            processHandle( rval.processHandle )
        {
            rval.processHandle = NULL;
        }
        ProcessMemoryReader& operator=( ProcessMemoryReader &&rval )
        {
            processHandle = rval.processHandle;

            rval.processHandle = NULL;
        }
        ProcessMemoryReader( const ProcessMemoryReader& ) = delete;
        ProcessMemoryReader& operator=( const ProcessMemoryReader& ) = delete;

    };
}