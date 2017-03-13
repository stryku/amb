#pragma once

#include "ui/controls/Table.hpp"

namespace Amb
{
    namespace Module
    {
        namespace Modules
        {
            namespace MouseHotkeys
            {
                struct MouseHotkey;
            }
        }
    }

    namespace Ui
    {
        namespace Modules
        {
            namespace MouseHotkeys
            {
                const size_t NumberOfTableColumns = 3;
                class MouseHotkeysTable : public Amb::Ui::Controls::Table<NumberOfTableColumns>
                {
                private:
                    using ItemType = ::Amb::Module::Modules::MouseHotkeys::MouseHotkey;
                    using Table = Amb::Ui::Controls::Table<NumberOfTableColumns>;

                public:
                    MouseHotkeysTable(QTableView *view);

                    std::vector<ItemType> getItems() const;
                    ItemType get(const size_t row) const;
                    ItemType getSelectedForEdit() const;

                    bool isSelectedEditable() const;

                    void add(const ItemType &item);
                    void add(const std::string& mouseEvName, size_t hot, bool onlyIfTop);

                    void set(const ItemType &item, size_t row);

                    bool itemExists(const std::string& prettyName) const;
                };
            }
        }
    }
}
