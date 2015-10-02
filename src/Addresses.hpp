#pragma once

#include "utils.hpp"

#include <Windows.h>



namespace AMB
{
    namespace Memory
    {
        struct Addresses
        {
            DWORD base;

            DWORD XOR = 0x933658 - 0x400000;

            struct
            {
                DWORD hp = 0xAD1030 - 0x400000;
                DWORD hpMax = 0xAD1024;
                DWORD mana = 0x933688 - 0x400000;
                DWORD manaMax = 0x53365C;
            } character;

            Addresses( DWORD pid )
            {
                base = Utils::getModuleBase( pid, "Tibia.exe" );
            }
        };
    }
}