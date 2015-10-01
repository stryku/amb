#pragma once

#include <Windows.h>

namespace AMB
{
    namespace Memory
    {
        struct Addresses
        {
            DWORD XOR;

            struct
            {
                DWORD hp;
                DWORD hpMax;
                DWORD mana;
                DWORD manaMax;
            } character;
        };
    }
}