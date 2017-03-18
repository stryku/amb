#include "ui/updaters/details/TibiaNickHider.hpp"

namespace Amb
{
    namespace Ui
    {
        namespace Updaters
        {
            namespace details
            {
                TibiaNickHider::TibiaNickHider(const std::string& str)
                    : title{ str }
                {}

                void TibiaNickHider::set(const std::string& str)
                {
                    title = str;
                }

                std::string TibiaNickHider::getNormal() const
                {
                    return title;
                }

                std::string TibiaNickHider::getHiden() const
                {
                    const auto pos = title.find("Tibia - ");

                    if (pos != 0)
                        return title;

                    auto ret = title.substr(0, std::size("Tibia - ") - 1);

                    ret += "****";

                    return ret;
                }

                bool TibiaNickHider::operator==(const TibiaNickHider& rhs) const
                {
                    return title == rhs.title;
                }
            }
        }
    }
}
