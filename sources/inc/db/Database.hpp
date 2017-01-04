#pragma once

#include "db/Items.hpp"
#include "db/Containers.hpp"

namespace Amb
{
    namespace Db
    {
        struct Database
        {
            Items items;
            Containers containers;
        };
    }
}
