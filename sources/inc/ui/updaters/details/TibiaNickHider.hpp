#pragma once

#include <string>

namespace Amb
{
    namespace Ui
    {
        namespace Updaters
        {
            namespace details
            {
                class TibiaNickHider
                {
                public:
                    TibiaNickHider() = default;
                    TibiaNickHider(const std::string& str);
                    TibiaNickHider(const TibiaNickHider& rhs) = default;
                    TibiaNickHider& operator=(const TibiaNickHider& rhs) = default;

                    void set(const std::string& str);
                    std::string getNormal() const;
                    std::string getHiden() const;

                    bool operator==(const TibiaNickHider& rhs) const;
                    
                private:
                    std::string title;
                };
            }
        }
    }
}
