#include "HealRule.hpp"
#include <iostream>
namespace AMB
{
    namespace Modules
    {
        namespace Heal
        {
            bool HealRule::passed( size_t characterHp, size_t characterMana ) const
            {
                std::cout<<"Checking rule: " << minHp << " <= "<<characterHp <<" <= "<<maxHp<<"\n";
                std::cout<<"Checking rule: " << minMana << " <= "<<characterMana <<" <= "<<maxMana<<"\n";
                return minHp <= characterHp && characterHp <= maxHp
                    && minMana <= characterMana && characterMana <= maxMana;
            }
        }
    }
}
