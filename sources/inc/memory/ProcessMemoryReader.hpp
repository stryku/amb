#pragma once

#include <Windows.h>
#include <Psapi.h>

namespace Amb
{
    namespace Memory
    {
        class ProcessMemoryReader
        {
        public:
            ProcessMemoryReader(DWORD pid);
            ~ProcessMemoryReader();

            ProcessMemoryReader(ProcessMemoryReader &&rval) = delete;
            ProcessMemoryReader& operator=(ProcessMemoryReader &&rval) = delete;
            ProcessMemoryReader(const ProcessMemoryReader&) = delete;
            ProcessMemoryReader& operator=(const ProcessMemoryReader&) = delete;

            template <typename T>
            T read(DWORD dwordAddress) const
            {
                return read<T>(reinterpret_cast<LPCVOID>(dwordAddress + baseAddress));
            }

            template <typename T>
            T read(LPCVOID addressInProcess) const
            {
                T value;

                if (processHandle == NULL)
                    return T{};

                ReadProcessMemory(processHandle,
                                  addressInProcess,
                                  &value,
                                  sizeof(T),
                                  NULL);
                return value;
            }

            void attachNewProcess(DWORD pid);

        private:
            DWORD getModuleBase(DWORD pid, const char *sModuleName = "Tibia.exe");
            void closeAndNullHandle(HANDLE &handle);
            void safeCloseAndNullHandle(HANDLE &handle);

        private:
            HANDLE processHandle{ NULL };
            DWORD baseAddress;
        };
    }
}
