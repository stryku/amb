#pragma once

#include "utils.hpp"

#include <Windows.h>

namespace AMB
{
    namespace Memory
    {
        class ProcessMemoryReader
        {
        private:
            HANDLE processHandle = NULL;

        public:
            ProcessMemoryReader( DWORD pid )
            {
                attachNewProcess( pid );
            }
            ProcessMemoryReader()
            {}
            ~ProcessMemoryReader()
            {
                Utils::safeCloseAndNullHandle( processHandle );
            }

            ProcessMemoryReader( ProcessMemoryReader &&rval ) = delete;
            ProcessMemoryReader& operator=( ProcessMemoryReader &&rval ) = delete;
            ProcessMemoryReader( const ProcessMemoryReader& ) = delete;
            ProcessMemoryReader& operator=( const ProcessMemoryReader& ) = delete;

            template <typename T>
            T read( LPCVOID ptrInProcess ) const
            {
                T value;
                SIZE_T bytesRead;

                if( processHandle == NULL )
                    return T();

                bytesRead = ReadProcessMemory( processHandle,
                                   ptrInProcess,
                                   &value,
                                   sizeof( T ),
                                   NULL );

                auto er = GetLastError();

                return value;
            }

            void attachNewProcess( DWORD pid )
            {
                Utils::safeCloseAndNullHandle( processHandle );

                processHandle = OpenProcess( PROCESS_ALL_ACCESS,
                                             TRUE,
                                             pid );
            }
        };
    }
}
