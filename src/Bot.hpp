#pragma once

#include "Simulator.hpp"
#include "TibiaStuffReader.hpp"
#include "ModulesManager.hpp"

#include <vector>

namespace AMB
{
    class Bot
    {
    private:
        Simulate::Simulator simulator;
        Memory::TibiaStuffReader reader;
        Modules::ModulesManager modulesManager;
    };
}