#pragma once

#include "Addresses.hpp"
#include "ProcessMemoryReader.hpp"

namespace AMB
{
    namespace Memory
    {
        class TibiaStuffReader
        {
        private:
            ProcessMemoryReader memReader;
            Addresses addresses;

        public:
            TibiaStuffReader( DWORD pid ) :
                memReader( pid )
            {}
            ~TibiaStuffReader()
            {}

            size_t hp() const
            {
                auto notXoredHp = memReader.read<int32_t>( reinterpret_cast<LPCVOID>( addresses.character.hp ) );
                auto xorVal = memReader.read<int32_t>( reinterpret_cast<LPCVOID>( addresses.XOR ) );

                return notXoredHp ^ xorVal;
            }

            size_t mana() const
            {
                auto notXoredMana = memReader.read<int32_t>( reinterpret_cast<LPCVOID>( addresses.character.mana ) );
                auto xorVal = memReader.read<int32_t>( reinterpret_cast<LPCVOID>( addresses.XOR ) );

                return notXoredMana ^ xorVal;
            }
        };
    }
}