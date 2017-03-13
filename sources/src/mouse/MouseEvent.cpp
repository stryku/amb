#include "mouse/MouseEvent.hpp"
#include "log/log.hpp"

#include <boost/assert.hpp>

namespace Amb
{
    namespace Mouse
    {

        std::string MouseEvent::toString() const
        {
            LOG_DEBUG("MouseEvent::toString: {}", value);

            const auto enumVal = static_cast<KnownMouseEvents>(value);

            switch (enumVal)
            {
                case KnownMouseEvents::LEFT_UP: return "LEFT_UP";
                case KnownMouseEvents::LEFT_DOWN: return "LEFT_DOWN";
                case KnownMouseEvents::RIGHT_UP: return "RIGHT_UP";
                case KnownMouseEvents::RIGHT_DOWN: return "RIGHT_DOWN";
                case KnownMouseEvents::WHEEL: return "WHEEL";
                case KnownMouseEvents::X1_UP: return "X1_UP";
                case KnownMouseEvents::X1_DOWN: return "X1_DOWN";
                case KnownMouseEvents::X2_UP: return "X2_UP";
                case KnownMouseEvents::X2_DOWN: return "X2_DOWN";

                default:
                    return std::to_string(value);
            }
        }

        MouseEvent MouseEvent::fromString(const std::string& str)
        {
            MouseEvent ret;
            LOG_DEBUG("MouseEvent::fromString: {}", str);

            if (str == "LEFT_UP")
                ret.value = static_cast<size_t>(KnownMouseEvents::LEFT_UP);
            else if (str == "LEFT_DOWN")
                ret.value = static_cast<size_t>(KnownMouseEvents::LEFT_DOWN);
            else if (str == "RIGHT_UP")
                ret.value = static_cast<size_t>(KnownMouseEvents::RIGHT_UP);
            else if (str == "RIGHT_DOWN")
                ret.value = static_cast<size_t>(KnownMouseEvents::RIGHT_DOWN);
            else if (str == "WHEEL")
                ret.value = static_cast<size_t>(KnownMouseEvents::WHEEL);
            else if (str == "X1_UP")
                ret.value = static_cast<size_t>(KnownMouseEvents::X1_UP);
            else if (str == "X1_DOWN")
                ret.value = static_cast<size_t>(KnownMouseEvents::X1_DOWN);
            else if (str == "X2_UP")
                ret.value = static_cast<size_t>(KnownMouseEvents::X2_UP);
            else if (str == "X2_DOWN")
                ret.value = static_cast<size_t>(KnownMouseEvents::X2_DOWN);
            else
            {
                try
                {
                    ret.value = static_cast<size_t>(std::stoul(str));
                }
                catch (std::exception& e)
                {
                    LOG_DEBUG("MouseEvent::fromPrettyString stoul throw: {}", e.what());
                    BOOST_ASSERT(false);
                }
            }

            return ret;
        }


        std::string MouseEvent::toPrettyString() const
        {
            LOG_DEBUG("MouseEvent::mouseEventToPrettyString: {}", value);

            const auto enumVal = static_cast<KnownMouseEvents>(value);

            switch (enumVal)
            {
                case KnownMouseEvents::LEFT_UP: return "Left button";
                case KnownMouseEvents::LEFT_DOWN: return "Left button down";
                case KnownMouseEvents::RIGHT_UP: return "Right button";
                case KnownMouseEvents::RIGHT_DOWN: return "Right button down";
                case KnownMouseEvents::WHEEL: return "Wheel";
                case KnownMouseEvents::X1_UP: return "X1 button";
                case KnownMouseEvents::X1_DOWN: return "X1 button down";
                case KnownMouseEvents::X2_UP: return "X2 button";
                case KnownMouseEvents::X2_DOWN: return "X2 button down";

                default:
                    return std::to_string(value);
            }
        }

        MouseEvent MouseEvent::fromPrettyString(const std::string& str)
        {
            MouseEvent ret;
            LOG_DEBUG("MouseEvent::fromPrettyString: {}", str);

            if (str == "Left button")
                ret.value = static_cast<size_t>(KnownMouseEvents::LEFT_UP);
            else if (str == "Left button down") 
                ret.value = static_cast<size_t>(KnownMouseEvents::LEFT_DOWN);
            else if (str == "Right button") 
                ret.value = static_cast<size_t>(KnownMouseEvents::RIGHT_UP);
            else if (str == "Right button down") 
                ret.value = static_cast<size_t>(KnownMouseEvents::RIGHT_DOWN);
            else if (str == "Wheel") 
                ret.value = static_cast<size_t>(KnownMouseEvents::WHEEL);
            else if (str == "X1 button") 
                ret.value = static_cast<size_t>(KnownMouseEvents::X1_UP);
            else if (str == "X1 button down") 
                ret.value = static_cast<size_t>(KnownMouseEvents::X1_DOWN);
            else if (str == "X2 button") 
                ret.value = static_cast<size_t>(KnownMouseEvents::X2_UP);
            else if (str == "X2 button down") 
                ret.value = static_cast<size_t>(KnownMouseEvents::X2_DOWN);
            else
            {
                try
                {
                    ret.value = static_cast<size_t>(std::stoul(str));
                }
                catch (std::exception& e)
                {
                    LOG_DEBUG("MouseEvent::fromPrettyString stoul throw: {}", e.what());
                    BOOST_ASSERT(false);
                }
            }

            return ret;
        }
    }
}
