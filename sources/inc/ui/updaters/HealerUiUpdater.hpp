#pragma once

namespace Amb
{
    namespace Config
    {
        namespace Module
        {
            struct HealerConfig;
        }
    }

    namespace Ui
    {
        namespace Controls
        {
            struct Healer;
        }

        namespace Updaters
        {
            class Healer
            {
            public:
                void update(const Config::Module::HealerConfig &healerConfigs,
                            const Controls::Healer &healerControls) const;
            };
        }
    }
}
