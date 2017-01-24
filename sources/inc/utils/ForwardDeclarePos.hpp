#pragma once

namespace Amb
{
    namespace details
    {
        template <typename T>
        struct PosImpl;
    }
    
    using Pos = details::PosImpl<int>;
    using Offset = details::PosImpl<size_t>;
}
