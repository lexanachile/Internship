#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_options_currentIndexChanged(ui->options->currentIndex());
    ui->num2->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_options_currentIndexChanged(int index)
{
    ui->answer->setText("");
    if(index >= 2) ui->num2->hide();
    else ui->num2->show();
}


void MainWindow::on_solve_clicked()
{
    QString str = ui->num1->text();
    if(str == "") {
        ui->answer->setText("Error");
            return;
    }
    num.set(str.toInt());

    str = ui->num2->text();
    int y = str.toInt();
    switch (ui->options->currentIndex()) {
    case 0:{
        if(str == "") {
            ui->answer->setText("Error");
            return;
        }
        ui->answer->setText(QString::number(num.nod(y)));
        return;
    }
    case 1:{
        if(str == "") {
            ui->answer->setText("Error");
            return;
        }
        ui->answer->setText(QString::number(num.nok(y)));
        return;
    }
    case 2:{
        if(num.isPrime()) ui->answer->setText("True");
        else ui->answer->setText("False");
        return;
    }
    case 3:{
        if(num.isArmstrong()) ui->answer->setText("True");
        else ui->answer->setText("False");
        return;
    }
    case 4:{
        ui->answer->setText(QString::number(num.countDigits()));
        return;
    }
    default:
        return;
    }
}


void MainWindow::on_num1_editingFinished()
{
    ui->answer->setText("");
}


void MainWindow::on_num2_editingFinished()
{
    ui->answer->setText("");
}

