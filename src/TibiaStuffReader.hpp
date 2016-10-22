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

            int readWithXor( DWORD ptr ) const;

        public:
            TibiaStuffReader( DWORD pid );
            TibiaStuffReader()
            {
                int a = 0;
                a ++;
                ++a;

            }
            ~TibiaStuffReader()
            {}

            int hp() const;
            int mana() const;

            void attachNewProcess( DWORD pid );
        };
    }
}
