#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Armstrong.h"
#include <QMainWindow>
//#include "testmw.cpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class TestMW;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_options_currentIndexChanged(int index);

    void on_solve_clicked();

    void on_num1_editingFinished();

    void on_num2_editingFinished();

private:
    Ui::MainWindow *ui;
    Numbers num;
};
#endif // MAINWINDOW_H
