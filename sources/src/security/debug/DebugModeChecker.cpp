#include "security/debug/DebugModeChecker.hpp"
#include "log/log.hpp"

#include <Windows.h>
#include <Winternl.h>

namespace Amb
{
    namespace Security
    {
        namespace Debug
        {
            DebugModeChecker::DebugModeChecker(CallbackType debugModeDetectedCallback)
            {
                auto loop = [this, debugModeDetectedCallback]
                {
                    if (isDebugged())
                        debugModeDetectedCallback();
                };

                threadWorker.start(loop, delayDuration);
            }

            DebugModeChecker::~DebugModeChecker()
            {
                threadWorker.stop();
            }

            bool DebugModeChecker::isDebugged() const
            {
                return
                    checkIsDebuggerPresent() ||
                    checkIsDebugged() ||
                    checkNtGlobalFlags() ||
                    //checkHeapFlags() ||
                    checkNtQueryInformationProcess() ||
                    checkCheckRemoteDebuggerPresent();
            }

            bool DebugModeChecker::checkIsDebuggerPresent() const
            {
                if (IsDebuggerPresent())
                {
                    LOG_DEBUG("IsDebuggerPresent success");
                    return true;
                }

                return false;
            }

            bool DebugModeChecker::checkIsDebugged() const
            {
                bool ret{ false };

                __asm
                {
                    push eax
                    push ebx

                    jmp doStuff

                raiseDebuggedError:
                    mov ret, 1
                    jmp end

                doStuff:
                    mov eax, fs : [30h]
                    mov ebx, 0
                    mov bl, BYTE PTR[eax + 2]
                    cmp bl, 0
                    jne raiseDebuggedError

                end:
                    pop ebx
                    pop eax
                }

                if (ret)
                {
                    LOG_DEBUG("checkIsDebugged success");
                }
                return ret;
            }

            bool DebugModeChecker::checkNtGlobalFlags() const
            {
                bool ret{ false };

                __asm
                {
                    push eax
                    push ebx

                    jmp doStuff

                raiseDebuggedError:
                    mov ret, 1
                    jmp end

                doStuff:
                    mov eax, fs:[30h]
                    mov ebx, 0
                    mov bl, BYTE PTR[eax + 2]
                    cmp bl, 0
                    jne raiseDebuggedError

                end:
                    pop ebx
                    pop eax
                }

                if (ret)
                {
                    LOG_DEBUG("checkNtGlobalFlags success");
                }

                return ret;
            }

            bool DebugModeChecker::checkHeapFlags() const
            {
                bool ret{ false };

                __asm
                {
                    push eax
                    push ebx

                    jmp doStuff

                raiseDebuggedError :
                    mov ret, 1
                    jmp end

                doStuff:
                    mov eax, fs : [30h]
                    mov eax, [eax + 18h]; process heap
                    mov eax, [eax + 10h]; heap flags
                    test eax, eax
                    jne raiseDebuggedError

                end:
                    pop ebx
                    pop eax
                }

                if (ret)
                {
                    LOG_DEBUG("checkHeapFlags success");
                }

                return ret;
            }

            bool DebugModeChecker::checkVista() const
            {
                bool ret{ false };

                __asm
                {
                    push eax
                    push ebx

                    jmp doStuff

                raiseDebuggedError :
                    mov ret, 1
                    jmp end

                doStuff :
                    call GetVersion

                    cmp al, 6
                    jne end; this is not a Vista

                    ; push offset _seh

                    mov ebx, fs:[0]
                    push ebx

                    mov fs : [0], esp
                    mov eax, fs : [18h]; teb
                    add eax, 0BFCh
                    mov ebx, [eax]; pointer to a unicode string
                    test ebx, ebx; (ntdll.dll, gdi32.dll, ...)
                    je end; debugger not found

                    sub ebx, eax; the unicode string follows the
                    sub ebx, 4; pointer
                    jne end; debugger not found

                    ; debugger detected if it reaches this point
                    jmp raiseDebuggedError

                end:
                    pop ebx
                    pop eax
                }

                if (ret)
                {
                    LOG_DEBUG("checkVista success");
                }

                return ret;
            }

            bool DebugModeChecker::checkNtQueryInformationProcess() const
            {
                DWORD pBasicInfo;

                NtQueryInformationProcess(HANDLE(-1), PROCESSINFOCLASS(7), &pBasicInfo, 4, 0);

                if (pBasicInfo == 1)
                {
                    LOG_DEBUG("checkNtQueryInformationProcess success");
                    return true;
                }

                return false;
            }

            bool DebugModeChecker::checkCheckRemoteDebuggerPresent() const
            {
                BOOL isDebugged;
                CheckRemoteDebuggerPresent(HANDLE(-1), &isDebugged);

                if (isDebugged == 1)
                {
                    LOG_DEBUG("checkCheckRemoteDebuggerPresent success");
                    return true;
                }

                return false;
            }
        }
    }
}