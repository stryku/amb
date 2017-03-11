#pragma once

namespace Amb
{
    namespace Config
    {
        namespace Module
        {
            struct MlvlConfig;
        }
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
                void update(const Config::Module::MlvlConfig& configs, const Controls::Mlvl &controls) const;
            };
        }
    }
}
