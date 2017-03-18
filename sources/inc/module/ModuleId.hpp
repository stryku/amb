#pragma once

namespace Amb
{
    namespace Module
    {
        enum class ModuleId
        {
            MOD_HEALER,

#ifdef AMB_PRO_COMPILATION
            MOD_LOOTER,
            MOD_MLVL,
            MOD_MOUSE_HOTKEYS,
#endif

            DUMMY
        };
    }
}
