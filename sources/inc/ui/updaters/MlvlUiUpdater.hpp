#pragma once

namespace Amb
{
    namespace Configs
    {
        struct Mlvl;
    }

    namespace Ui
    {
        namespace Controls
        {
            struct Mlvl;
        }

        namespace Updaters
        {
            class Mlvl
            {
            public:
                void update(const Configs::Mlvl &configs, const Controls::Mlvl &controls) const;
            };
        }
    }
}
