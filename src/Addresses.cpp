#include "Addresses.hpp"

namespace AMB
{
    namespace Memory
    {
        Addresses::Addresses( DWORD pid )
        {
            attachNewProcess( pid );
        }

        void Addresses::attachNewProcess( DWORD pid )
        {
            base = Utils::getModuleBase( pid, "Tibia.exe" );
        }
    }
}
