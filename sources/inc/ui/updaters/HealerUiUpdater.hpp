#pragma once

namespace Amb
{
    namespace Configs
    {
        struct HealerConfig;
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
                void update(const Configs::HealerConfig &healerConfigs, 
                            const Controls::Healer &healerControls) const;
            };
        }
    }
}
