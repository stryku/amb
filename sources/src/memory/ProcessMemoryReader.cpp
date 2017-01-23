#include "memory/ProcessMemoryReader.hpp"

namespace Amb
{
    namespace Memory
    {
        ProcessMemoryReader::ProcessMemoryReader(DWORD pid)
        {
            attachNewProcess(pid);
        }

        ProcessMemoryReader::~ProcessMemoryReader()
        {
            safeCloseAndNullHandle(processHandle);
        }

        void ProcessMemoryReader::attachNewProcess(DWORD pid)
        {
            if (pid != NULL)
            {
                safeCloseAndNullHandle(processHandle);

                processHandle = OpenProcess(PROCESS_ALL_ACCESS,
                                            TRUE,
                                            pid);

                baseAddress = getModuleBase(pid);
            }
        }

        DWORD ProcessMemoryReader::getModuleBase(DWORD pid, const char *sModuleName)
        {
            auto hProc = OpenProcess(PROCESS_ALL_ACCESS,
                                     TRUE,
                                     pid);

            HMODULE *hModules = nullptr;
            char szBuf[50];
            DWORD cModules;
            DWORD dwBase = -1;

            EnumProcessModules(hProc, hModules, 0, &cModules);
            hModules = new HMODULE[cModules / sizeof(HMODULE)];

            if (EnumProcessModules(hProc, hModules, cModules / sizeof(HMODULE), &cModules))
            {
                for (DWORD i = 0; i < cModules / sizeof(HMODULE); ++i)
                {
                    if (GetModuleBaseNameA(hProc, hModules[i], szBuf, sizeof(szBuf)))
                    {
                        if (_strcmpi(szBuf, sModuleName) == 0)
                        {
                            dwBase = (DWORD)hModules[i];
                            break;
                        }
                    }
                }
            }

            delete[] hModules;

            CloseHandle(hProc);

            return dwBase;
        }

        void ProcessMemoryReader::closeAndNullHandle(HANDLE &handle)
        {
            CloseHandle(handle);
            handle = NULL;
        }

        void ProcessMemoryReader::safeCloseAndNullHandle(HANDLE &handle)
        {
            if (handle != NULL)
                closeAndNullHandle(handle);
        }

    }
}
