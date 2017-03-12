#include "utils/ToString.hpp"

namespace utils // todo Amb::Utils
{
    std::string toString(bool value)
    {
        return value ? "true" : "false";
    }
}
