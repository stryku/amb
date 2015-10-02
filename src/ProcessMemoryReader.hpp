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
            HANDLE processHandle;

            void attachNewProcess( DWORD pid )
            {
                processHandle = OpenProcess( PROCESS_ALL_ACCESS,
                                             TRUE,
                                             pid );
            }
            

        public:
            ProcessMemoryReader( DWORD pid )
            {
                attachNewProcess( pid );
            }
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

                ReadProcessMemory( processHandle,
                                   ptrInProcess,
                                   &value,
                                   sizeof( T ),
                                   NULL );


                return value;
            }
        };
    }
}