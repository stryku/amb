#pragma once

namespace Amb
{
    namespace Configs
    {
        struct Looter;
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
                void update(const Configs::Looter &configs, const Controls::Looter &controls) const;
            };
        }
    }
}
