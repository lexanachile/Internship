#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "paintscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent=nullptr);
    ~MainWindow() override;
protected:
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_actionRed_triggered();
    void on_actionGreen_triggered();
    void on_actionBlue_triggered();
    void on_actionClear_triggered();
    void on_actionCustomColor_triggered();
    void on_actionSquare_triggered();
    void on_actionRomb_triggered();
    void on_actionTriangle_triggered();
    void on_actionSave_triggered();
    void on_actionLoad_triggered();
    void on_AddBall_triggered();
private:
    Ui::MainWindow *ui;
    paintScene *scene;
};

#endif // MAINWINDOW_H
