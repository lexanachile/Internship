#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , M1(new COMP<comp>())
    , M2(new COMP<comp>())
    , M3(new COMP<comp>())
    , M7(new COMP<comp>())
    , K1(new COMP<bag>())
    , K2(new COMP<bag>())
    , K3(new COMP<bag>())
    , K7(new COMP<bag>())
    , MM1(new MyModel1())
    , MM2(new MyModel1())
    , MM3(new MyModel1())
    , MM7(new MyModel1())
    , MK1(new MyModel2())
    , MK2(new MyModel2())
    , MK3(new MyModel2())
    , MK7(new MyModel2())
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete M1, M2, M3, M7, K1, K2, K3, K7;
    delete MM1, MM2, MM3, MM7, MK1, MK2, MK3, MK7;
}

void MainWindow::on_button_1_clicked()
{
    QFile f1("comp1.txt");
    QFile f2("comp2.txt");
    if(!iscomp){
        ui->field3->setModel(new QStandardItemModel(0, 0, this));
        iscomp = true;
    }
    f1.open(QIODevice::ReadOnly);
    f2.open(QIODevice::ReadOnly);
    QTextStream p1(&f1);
    QTextStream p2(&f2);
    p1 >> *M1;
    p2 >> *M2;
    f1.close();
    f2.close();
    MM1->setModel(M1);
    MM2->setModel(M2);
    ui->field1->setModel(MM1);
    ui->field1->resizeColumnsToContents();
    ui->field2->setModel(MM2);
    ui->field2->resizeColumnsToContents();
}

void MainWindow::on_button_2_clicked()
{
    QFile f1("bag1.txt");
    QFile f2("bag2.txt");
    if(iscomp){
        ui->field3->setModel(new QStandardItemModel(0, 0, this));
        iscomp = false;
    }
    f1.open(QIODevice::ReadOnly);
    f2.open(QIODevice::ReadOnly);
    QTextStream p1(&f1);
    QTextStream p2(&f2);
    p1 >> *K1;
    p2 >> *K2;
    f1.close();
    f2.close();
    MK1->setModel(K1);
    MK2->setModel(K2);
    ui->field1->setModel(MK1);
    ui->field1->resizeColumnsToContents();
    ui->field2->setModel(MK2);
    ui->field2->resizeColumnsToContents();
}

void MainWindow::on_button_3_clicked()
{
    if(iscomp){
        *M3 = *M1 + *M2;
        MM3->setModel(M3);
        ui->field3->setModel(MM3);
        ui->field3->resizeColumnsToContents();
    }
    else{
        *K3 = *K1 + *K2;
        MK3->setModel(K3);
        ui->field3->setModel(MK3);
        ui->field3->resizeColumnsToContents();
    }
}

void MainWindow::on_button_5_clicked()
{
    if(iscomp){
        *M7 = *M3;
        M7->reverse_sort();
        MM7->setModel(M7);
        ui->field7->setModel(MM7);
        ui->field7->resizeColumnsToContents();
    }
    else{
        *K7 = *K3;
        K7->reverse_sort();
        MK7->setModel(K7);
        ui->field7->setModel(MK7);
        ui->field7->resizeColumnsToContents();
    }
}

void MainWindow::on_button_6_clicked()
{
    if(iscomp){
        *M7 = *M3;
        M7->sect_sort();
        MM7->setModel(M7);
        ui->field7->setModel(MM7);
        ui->field7->resizeColumnsToContents();
    }
    else{
        *K7 = *K3;
        K7->sect_sort();
        MK7->setModel(K7);
        ui->field7->setModel(MK7);
        ui->field7->resizeColumnsToContents();
    }
}

void MainWindow::on_button_7_clicked()
{
    if(iscomp){
        M3->sort();
        MM3->setModel(M3);
    }
    else{
        K3->sort();
        MK3->setModel(K3);
    }
}

void MainWindow::on_button_8_clicked()
{
    QString what = ui->lineEdit->text();

    if (iscomp) {
        *M7 = M3->findItem(what);
        MM7->setModel(M7);
        ui->field7->setModel(MM7);
        ui->field7->resizeColumnsToContents();
    } else {
        *K7 = K3->findItem(what);
        MK7->setModel(K7);
        ui->field7->setModel(MK7);
        ui->field7->resizeColumnsToContents();
    }
}
