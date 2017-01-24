#include "client/window/finder/DeadCreatureWindowFinderFactory.hpp"
#include "client/window/finder/DeadCreatureWindowFinder.hpp"
#include "capture/ConstPixels.hpp"
#include "log/log.hpp"

namespace Amb
{
    namespace Client
    {
        namespace Window
        {
            namespace Finder
            {
                DeadCreatureWindowFinder DeadCreatureWindowFinderFactory::create(TibiaClientType clientType) const
                {
                    switch (clientType)
                    {
                    case Amb::Client::TibiaClientType::Tibia10:
                        return DeadCreatureWindowFinder{ ConstPixels::Slain, ConstPixels::Dead, ConstPixels::Dead };

                    case Amb::Client::TibiaClientType::Tibia11:
                        return DeadCreatureWindowFinder{ ConstPixels::Slain_11, ConstPixels::Dead_11, ConstPixels::Remains_11 };

                    case Amb::Client::TibiaClientType::Flash:
                    default:
                        LOG_DEBUG("unsupported client type in switch");
                        BOOST_ASSERT_MSG(false, "unsupported client type in switch");
                        break;
                    }
                }
            }
        }
    }
}
