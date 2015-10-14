#pragma once

#include "Simulator.hpp"
#include "TibiaStuffReader.hpp"

namespace AMB
{
    class Bot
    {
    private:
        Simulate::Simulator simulator;
        Memory::TibiaStuffReader reader;
    };
}