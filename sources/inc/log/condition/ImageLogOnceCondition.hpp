#pragma once

#include "log/condition/LoggerCondition.hpp"

#include <cexpr/crypto.hpp>

namespace Amb
{
    namespace Graphics
    {
        struct Image;
    }

    namespace Log
    {
        namespace Condition
        {
            class ImageLogOnceCondition : public LoggerCondition<ImageLogOnceCondition, Graphics::Image>
            {
            public:
                bool shouldLogDerived(const Graphics::Image&) const;
                void willLogThis(const Graphics::Image&) override;

            private:
                bool alreadyLogged{ false };
            };
        }
    }
}
