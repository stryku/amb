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

            size_t readWithXor( DWORD ptr ) const
            {
                auto notXored = memReader.read<int32_t>( reinterpret_cast<LPCVOID>( ptr ) );
                auto xorVal = memReader.read<int32_t>( reinterpret_cast<LPCVOID>( addresses.base + addresses.XOR ) );

                return notXored ^ xorVal;
            }

        public:
            TibiaStuffReader( DWORD pid ) :
                memReader( pid ),
                addresses( pid )
            {}
            TibiaStuffReader()
            {}
            ~TibiaStuffReader()
            {}

            size_t hp() const
            {
                return readWithXor( addresses.base + addresses.character.hp );
            }

            size_t mana() const
            {
                return readWithXor( addresses.base + addresses.character.mana );
            }

            void attachNewProcess( DWORD pid )
            {
                memReader.attachNewProcess( pid );
                addresses.attachNewProcess( pid );
            }
        };
    }
}