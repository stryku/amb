#pragma once

#include <Windows.h>

namespace AMB
{
    namespace Memory
    {
        struct Addresses
        {
            DWORD XOR = 0x933658;

            struct
            {
                DWORD hp = 0xAD1030;
                DWORD hpMax = 0xAD1024;
                DWORD mana = 0x933688;
                DWORD manaMax = 0x93365C;
            } character;
        };
    }
}