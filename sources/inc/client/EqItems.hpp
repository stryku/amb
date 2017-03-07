#pragma once

namespace Amb
{
    namespace Client
    {
        struct EqItems
        {
            size_t amulet;
            size_t head;
            size_t backpack;
            size_t shield;
            size_t weapon;
            size_t armor;
            size_t legs;
            size_t boots;
            size_t ring;
            struct
            {
                size_t id;
                size_t amount;
            } amunition;
        };
    }
}
