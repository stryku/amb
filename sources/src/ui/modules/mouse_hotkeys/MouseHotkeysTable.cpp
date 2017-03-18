#include "ui/modules/mouse_hotkeys/MouseHotkeysTable.hpp"

#include "module/modules/mouse_hotkeys/MouseHotkey.hpp"

namespace Amb
{
    namespace Ui
    {
        namespace Modules
        {
            namespace MouseHotkeys
            {
                MouseHotkeysTable::MouseHotkeysTable(QTableView *view)
                    : Table(view, { "Mouse", "Hotkey", "Only when top" })
                {}

                std::vector<MouseHotkeysTable::ItemType> MouseHotkeysTable::getItems() const
                {
                    return getAll<typename ItemType>();
                }

                MouseHotkeysTable::ItemType MouseHotkeysTable::get(const size_t row) const
                {
                    return getItem<ItemType>(row);
                }

                bool MouseHotkeysTable::isSelectedEditable() const
                {
                    return selectedRows().size() == 1;
                }

                MouseHotkeysTable::ItemType MouseHotkeysTable::getSelectedForEdit() const
                {
                    const auto rows = selectedRows();

                    if (rows.empty())
                        return{};

                    return getAndRemoveItem<ItemType>(rows[0]);
                }

                void MouseHotkeysTable::add(const ItemType &item)
                {
                    Table::add(item.mouseEvent.toPrettyString(), 
                               Client::hotkeyToStdString(item.hotkey),
                               utils::toString(item.onlyWhenTibiaOnTop));
                }

                void MouseHotkeysTable::set(const ItemType &item, size_t row)
                {
                    Table::set(row,
                               item.mouseEvent.toPrettyString(),
                               Client::hotkeyToStdString(item.hotkey),
                               utils::toString(item.onlyWhenTibiaOnTop));
                }

                bool MouseHotkeysTable::itemExists(const std::string& prettyName) const
                {
                    const auto items = getItems();

                    return std::find_if(std::cbegin(items), std::cend(items),
                                        [&prettyName](const auto &item)
                                        {
                                            return item.mouseEvent.toPrettyString() == prettyName;
                                        }) != std::cend(items);
                }

                void MouseHotkeysTable::add(const std::string& mouseEvName, 
                                            size_t hot, 
                                            bool onlyIfTop)
                {
                    ItemType mouseHot;

                    mouseHot.hotkey = Client::size_tToHotkey(hot);
                    mouseHot.onlyWhenTibiaOnTop = onlyIfTop;
                    mouseHot.mouseEvent = Amb::Mouse::MouseEvent::fromPrettyString(mouseEvName);

                    add(mouseHot);
                }

            }
        }
    }
}
