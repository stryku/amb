#pragma once

#include "utils.hpp"

#include <Windows.h>

namespace Memory
{
    class ProcessMemoryReader
    {
    private:
        HANDLE processHandle = NULL;

        void _attachNewProcess( DWORD pid )
        {
            Utils::safeCloseAndNullHandle( processHandle );

            processHandle = OpenProcess( READ_CONTROL,
                                         TRUE,
                                         pid );
        }

    public:
        ProcessMemoryReader()
        {}
        ProcessMemoryReader( DWORD pid )
        {
            _attachNewProcess( pid );
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

        void attachNewProcess( DWORD pid )
        {
            _attachNewProcess( pid );
        }

        template <typename T>
        T read( LPCVOID ptrInProcess ) const
        {
            T value;
            SIZE_T bytesRead;

            if( processHandle == NULL )
                return T();

            ReadProcessMemory( processHandle, 
                               ptrInProcess,
                               &value,
                               sizeof( T ), 
                               &bytesRead );

            if( bytesRead != sizeof( T ) )
                return T();

            return value;
        }
    };
}