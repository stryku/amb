#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

#include <TibiaFinder.hpp>

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
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    void updateTibiaClientsComboBox();
};

#endif // MAINWINDOW_H
