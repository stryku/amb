#pragma once

#include "utils/ToString.hpp"
#include "cexpr/template.hpp"

#include <QTableView>
#include <QStandardItemModel>
#include <QList>

#include <array>

namespace AMB
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
                }

                void clear()
                {
                    model->clear();
                    createHeaders();
                }

                template <typename ...Args>
                void add(const Args&... args)
                {
                    const std::array<std::string, 
                                     cexpr::TemplateArgs<Args...>::count> items = 
                        utils::toStringArray(args...);
                    const auto rowCount = model->rowCount();

                    for(size_t i = 0; i < items.size(); ++i)
                    {
                        model->setItem(rowCount,
                                       i,
                                       new QStandardItem(QString::fromStdString(items[i])));
                    }

                    view->resizeColumnsToContents();
                }

                template <typename Type>
                Type getItem(const size_t row) const
                {
                    return getItemImpl<Type>(row, std::make_index_sequence<ColumnCount>());
                }

                template <typename Type>
                std::vector<Type> getItems() const
                {
                    int rowCount = model->rowCount();
                    std::vector<Type> ret;

                    for (size_t i = 0; i < rowCount; ++i)
                        ret.push_back(getItem<Type>(i));

                    return ret;
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

                    model->appendRow(new QStandardItem());

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
