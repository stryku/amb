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

            DWORD XOR = 0x944FD8 - 0x400000;

            struct Character
            {
                DWORD hp = 0xAE2000 - 0x400000;
                DWORD hpMax = 0xAE2048 - 0x400000;
                DWORD mana = 0x94500C - 0x400000;
                DWORD manaMax = 0x944FDC - 0x400000;

                Character(){}
            } character;

            Addresses()
            {}
            Addresses( DWORD pid );

            void attachNewProcess( DWORD pid );
        };
    }
}
