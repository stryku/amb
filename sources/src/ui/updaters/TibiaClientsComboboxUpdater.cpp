#include "ui/updaters/TibiaClientsComboboxUpdater.hpp"
#include "TibiaFinder.hpp"
#include "utils.hpp"
#include "ui/updaters/details/TibiaNickHider.hpp"

#include <boost/assert.hpp>

namespace Amb
{
    namespace Ui
    {
        namespace Updaters
        {
            void TibiaClientsComboboxUpdater::setCombobox(QComboBox* combobox)
            {
                cb = combobox;
            }

            void TibiaClientsComboboxUpdater::update(bool hideNick)
            {
                BOOST_ASSERT_MSG(cb,
                                 "TibiaClientsComboboxUpdater cb pointer is null");

                BOOST_ASSERT_MSG(cb->count() == entries.size(),
                                 "combobox entries should be same as TibiaClientsComboboxUpdater class entries");

                const auto lastSelectedIndex = cb->currentIndex();
                const auto lastSelected = (lastSelectedIndex != -1) ? entries[lastSelectedIndex] : details::TibiaNickHider{};
                const auto newEntries = getNewEntries();
                const auto lastSelectedIt = std::find(std::cbegin(newEntries),
                                                      std::cend(newEntries),
                                                      lastSelected);
                int newSelectedIndex{ 0 };

                if (lastSelectedIt != std::cend(newEntries))
                    newSelectedIndex = std::distance(std::cbegin(newEntries), lastSelectedIt);

                cb->clear();

                for (const auto& hider : newEntries)
                {
                    const auto title = hideNick ? hider.getHiden() : hider.getNormal();
                    cb->addItem(QString::fromStdString(title));
                }

                cb->setCurrentIndex(newSelectedIndex);
                entries = newEntries;
            }

            std::vector<details::TibiaNickHider> TibiaClientsComboboxUpdater::getNewEntries() const
            {
                std::vector<details::TibiaNickHider> ret;

                ret.push_back(details::TibiaNickHider{ "Select client" });
                ret.push_back(details::TibiaNickHider{ "-------------" });

                const auto clientsTitles = Amb::Utils::TibiaFinder::findAllClientsTitles();

                for (const auto &clientTitle : clientsTitles)
                    ret.push_back(details::TibiaNickHider{ Utils::wstringToString(clientTitle) });

                return ret;
            }

            std::string TibiaClientsComboboxUpdater::getCurrent(bool hideNick) const
            {
                BOOST_ASSERT_MSG(cb,
                                 "TibiaClientsComboboxUpdater cb pointer is null");

                BOOST_ASSERT_MSG(cb->count() == entries.size(),
                                 "combobox entries should be same as TibiaClientsComboboxUpdater class entries");

                const auto selectedIndex = cb->currentIndex();

                return hideNick ? entries[selectedIndex].getHiden() : entries[selectedIndex].getNormal();
            }
        }
    }
}
