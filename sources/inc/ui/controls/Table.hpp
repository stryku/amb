#pragma once

#include "utils/string/toString.hpp"
#include "cexpr/template.hpp"

#include <QTableView>
#include <QStandardItemModel>
#include <QList>
#include <QHeaderView>

#include <array>
#include <unordered_set>

namespace Amb
{
    namespace Ui
    {
        namespace Controls
        {
            template <size_t ColumnCount>
            class Table
            {
            public:
                Table(QTableView *view, const std::vector<std::string> &columnHeaders)
                    : view{ view }
                    , columnHeaders{ columnHeaders }
                {
                    createModel();
                    view->setSelectionBehavior(QAbstractItemView::SelectRows);
                    view->horizontalHeader()->setDragEnabled(true);
                    view->horizontalHeader()->setDragDropMode(QAbstractItemView::InternalMove);
                }

                void clear()
                {
                    model->clear();
                    createHeaders();
                }

                std::vector<size_t> selectedRows() const
                {
                    std::vector<size_t> ret;
                    std::unordered_set<size_t> set;

                    auto indexes = view->selectionModel()->selection().indexes();

                    for (const auto &idx : indexes)
                        set.insert(idx.row());

                    ret.resize(set.size());

                    std::copy(std::cbegin(set), std::cend(set), std::begin(ret));

                    return ret;
                }

                template <typename ...Args>
                void set(const size_t row, const Args&... args)
                {
                    const std::array<std::string,
                                     cexpr::TemplateArgs<Args...>::count> items = utils::toStringArray(args...);

                    for (size_t i = 0; i < items.size(); ++i)
                    {
                        model->setItem(row,
                                       i,
                                       new QStandardItem(QString::fromStdString(items[i])));
                    }

                    view->resizeColumnsToContents();
                }

                template <typename ...Args>
                void add(const Args&... args)
                {
                    set(model->rowCount(), args...);
                }

                template <typename Type>
                Type getItem(const size_t row) const
                {
                    return getItemImpl<Type>(row, std::make_index_sequence<ColumnCount>());
                }

                template <typename Type>
                Type getAndRemoveItem(const size_t row) const
                {
                    const auto item = getItem<Type>(row);
                    model->removeRow(row);
                    return item;
                }

                template <typename Type>
                std::vector<Type> getAll() const
                {
                    size_t rowCount = static_cast<size_t>(model->rowCount());
                    std::vector<Type> ret;

                    for (size_t i = 0; i < rowCount; ++i)
                        ret.push_back(getItem<Type>(i));

                    return ret;
                }

                void moveSelectedRowByOffset(int offset)
                {
                    const auto selected = selectedRows();

                    if (selected.size() == 1)
                    {
                        const auto row = selected.front();
                        int newRow = row + offset;
                        
                        if (newRow >= 0 && newRow < model->rowCount())
                        {
                            const auto rowItem = model->takeRow(row);
                            if (static_cast<int>(row) < newRow - offset)
                                ++newRow;

                            model->insertRow(newRow, rowItem);
                            view->selectRow(newRow);
                        }
                    }
                }

            private:
                template <typename Type, size_t ...Columns>
                Type getItemImpl(const size_t row, std::index_sequence<Columns...>) const
                {
                    return 
                    {
                        { model->item(row, Columns)->data(0).toString().toStdString() }...
                    };
                }

                void createModel()
                {
                    model = new QStandardItemModel(0, 0);
                    view->setModel(model);
                    createHeaders();
                }

                void createHeaders()
                {
                    auto rowCount = model->rowCount();

                    for (size_t i = 0; i < columnHeaders.size(); ++i)
                    {
                        model->setHorizontalHeaderItem(i,
                                                       new QStandardItem(QString::fromStdString(columnHeaders[i])));
                    }

                    view->resizeColumnsToContents();
                }

                QTableView *view;
                QStandardItemModel *model;
                std::vector<std::string> columnHeaders;
            };
        }
    }
}
