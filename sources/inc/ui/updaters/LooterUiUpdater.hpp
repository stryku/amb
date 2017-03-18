#pragma once

namespace Amb
{
    namespace Config
    {
        namespace Module
        {
            struct LooterConfig;
        }
    }

    namespace Ui
    {
        namespace Controls
        {
            struct Looter;
        }

        namespace Updaters
        {
            class Looter
            {
            public:
                void update(const Config::Module::LooterConfig &configs, const Controls::Looter &controls) const;
            };
        }
    }
}
