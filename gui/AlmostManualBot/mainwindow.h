#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <TibiaFinder.hpp>
#include <HealerRulesTable.hpp>

#include <QMainWindow>

#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnRefreshClientsComboBox_clicked();

    void on_btnHealerAddRule_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<HealerRulesTable> healerRulesTable;


    void updateTibiaClientsComboBox();
};

#endif // MAINWINDOW_H
