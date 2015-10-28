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

            size_t readWithXor( DWORD ptr ) const;

        public:
            TibiaStuffReader( DWORD pid );
            TibiaStuffReader()
            {}
            ~TibiaStuffReader()
            {}

            size_t hp() const;
            size_t mana() const;

            void attachNewProcess( DWORD pid );
        };
    }
}
