#include "ModulesManager.hpp"

#include <iostream>

AMB::Utils::Hotkey size_tToHot( size_t v )
{
    switch( v )
    {
        case 1: return AMB::Utils::Hotkey::F1;
        case 2: return AMB::Utils::Hotkey::F2;
        case 3: return AMB::Utils::Hotkey::F3;
        case 4: return AMB::Utils::Hotkey::F4;
        case 5: return AMB::Utils::Hotkey::F5;
        case 6: return AMB::Utils::Hotkey::F6;
        case 7: return AMB::Utils::Hotkey::F7;
        case 8: return AMB::Utils::Hotkey::F8;
        case 9: return AMB::Utils::Hotkey::F9;
        case 10: return AMB::Utils::Hotkey::F10;
        case 11: return AMB::Utils::Hotkey::F11;
        case 12: return AMB::Utils::Hotkey::F12;
    }
}

AMB::Configs::GlobalConfig toGlobalConfig()
{
    AMB::Configs::GlobalConfig config;
    AMB::Modules::Heal::HealRule healerRule;
    size_t rulesCount;

    std::cout << "Type pid: ";
    std::cin >> config.pid;

    std::cout << "How many rules: ";
    std::cin >> rulesCount;

    while( rulesCount-- )
    {
        size_t hot;

        std::cout << "New rule\n";
        std::cout << "\tMin hp: ";
        std::cin >> healerRule.minHp;
        std::cout << "\tMax hp: ";
        std::cin >> healerRule.maxHp;
        std::cout << "\tMin mana: ";
        std::cin >> healerRule.minMana;
        std::cout << "\tMax mana: ";
        std::cin >> healerRule.maxMana;

        std::cout << "\tHotkey: ";
        std::cin >> hot;

        healerRule.hotkey = size_tToHot( hot );

        config.healerConfig.rules.push_back( healerRule );
    }

    return config;
}

int main()
{
    while( 1 )
    {
        int tmp;
        auto config = toGlobalConfig();
        AMB::Modules::ModulesManager manager( config );

        std::cout << "Type to run healer\n";
        std::cin >> tmp;

        std::cout << "Starting healer... ";
        manager.run( AMB::Modules::ModuleId::MOD_HEALER );
        std::cout << "started\nType to stop.\n";

        std::cin >> tmp;
        manager.stop( AMB::Modules::ModuleId::MOD_HEALER );

        std::cout << "healer stoped";
        std::cin >> tmp;
    }

    return 0;
}