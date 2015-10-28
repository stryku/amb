#include "TibiaStuffReader.hpp"

namespace AMB
{
    namespace Memory
    {
        size_t TibiaStuffReader::readWithXor( DWORD ptr ) const
        {
            auto notXored = memReader.read<int32_t>( reinterpret_cast<LPCVOID>( ptr ) );
            auto xorVal = memReader.read<int32_t>( reinterpret_cast<LPCVOID>( addresses.base + addresses.XOR ) );

            return notXored ^ xorVal;
        }

        TibiaStuffReader::TibiaStuffReader( DWORD pid ) :
            memReader( pid ),
            addresses( pid )
        {}

        size_t TibiaStuffReader::hp() const
        {
            return readWithXor( addresses.base + addresses.character.hp );
        }

        size_t TibiaStuffReader::mana() const
        {
            return readWithXor( addresses.base + addresses.character.mana );
        }

        void TibiaStuffReader::attachNewProcess( DWORD pid )
        {
            memReader.attachNewProcess( pid );
            addresses.attachNewProcess( pid );
        }
    }
}
