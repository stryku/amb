#pragma once

#include "ui/updaters/details/TibiaNickHider.hpp"

#include <QComboBox>

#include <vector>
#include <string>

namespace Amb
{
    namespace Ui
    {
        namespace Updaters
        {
            class TibiaClientsComboboxUpdater
            {
            public:
                void update(bool hideNick);
                void setCombobox(QComboBox* cb);
                std::string getCurrent(bool hideNick = false) const;

            private:
                std::vector<details::TibiaNickHider> getNewEntries() const;

                std::vector<details::TibiaNickHider> entries;
                QComboBox* cb{ nullptr };
            };
        }
    }
}
