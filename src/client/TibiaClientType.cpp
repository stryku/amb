#include "client/TibiaClientType.hpp"

namespace Amb
{
    namespace Client
    {
        TibiaClientType fromSize_t(size_t val)
        {
            switch (val)
            {
                case 0: return TibiaClientType::Tibia10;
                case 1: return TibiaClientType::Tibia11;
                case 2: return TibiaClientType::Flash;
            }
        }

        size_t toSize_t(TibiaClientType type)
        {
            switch (type)
            {
                case TibiaClientType::Tibia10: return 0;
                case TibiaClientType::Tibia11: return 1;
                case TibiaClientType::Flash: return 2;

                default:
                    assert(false);
            }
        }

        void toPropertyTreeBuilder(AMB::Utils::PropertyTreeBuilder &builder, TibiaClientType type, const std::string &path)
        {
            std::string str;

            switch (type)
            {
                case TibiaClientType::Tibia10: str = "Tibia10"; break;
                case TibiaClientType::Tibia11: str = "Tibia11"; break;
                case TibiaClientType::Flash: str = "Flash"; break;

                default:
                    assert(false);
            }

            const auto elements =
            {
                AMB::Utils::PtreeElement<>{ path + ".client_type", str }
            };

            builder.addElements(elements);
        }

        TibiaClientType fromPtree(boost::property_tree::ptree &tree)
        {
            const auto str = tree.get<std::string>("client_type");

            if (str == "Tibia10") return TibiaClientType::Tibia10;
            else if (str == "Tibia11") return TibiaClientType::Tibia11;
            else if (str == "Flash") return TibiaClientType::Flash;
        }
    }
}
