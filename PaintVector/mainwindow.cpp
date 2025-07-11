#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    scene=new paintScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    connect(ui->actionAddBall,&QAction::triggered,this,&MainWindow::on_AddBall_triggered);
}

MainWindow::~MainWindow(){ delete ui; }

void MainWindow::showEvent(QShowEvent *event){
    QMainWindow::showEvent(event);
    scene->setSceneRect(0,0,ui->graphicsView->width()-20,ui->graphicsView->height()-20);
}

void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
    scene->setSceneRect(0,0,ui->graphicsView->width()-20,ui->graphicsView->height()-20);
}

void MainWindow::on_actionRed_triggered(){
    scene->setPenColor(Qt::red); scene->setDrawMode(paintScene::ModeDraw);
}
void MainWindow::on_actionGreen_triggered(){
    scene->setPenColor(Qt::green); scene->setDrawMode(paintScene::ModeDraw);
}
void MainWindow::on_actionBlue_triggered(){
    scene->setPenColor(Qt::blue); scene->setDrawMode(paintScene::ModeDraw);
}
void MainWindow::on_actionClear_triggered(){
    scene->clear();
}
void MainWindow::on_actionCustomColor_triggered(){
    QColor c=QColorDialog::getColor(Qt::white,this); if(c.isValid())scene->setPenColor(c);
}
void MainWindow::on_actionSquare_triggered(){
    scene->setTypeFigure(paintScene::SquareType); scene->setDrawMode(paintScene::ModeFigure);
}
void MainWindow::on_actionRomb_triggered(){
    scene->setTypeFigure(paintScene::RombType); scene->setDrawMode(paintScene::ModeFigure);
}
void MainWindow::on_actionTriangle_triggered(){
    scene->setTypeFigure(paintScene::TriangleType); scene->setDrawMode(paintScene::ModeFigure);
}
void MainWindow::on_actionSave_triggered(){
    QString f=QFileDialog::getSaveFileName(this,"Save","","*.txt"); if(!f.isEmpty())scene->saveToFile(f);
}
void MainWindow::on_actionLoad_triggered(){
    QFileDialog dialog(this);
    dialog.setWindowTitle(tr("Load"));
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);
    dialog.setDirectory(QDir::currentPath());
    dialog.setDirectory(dialog.directory());
    if (dialog.exec() == QDialog::Accepted) {
        QString f = dialog.selectedFiles().first();
        if (!f.isEmpty()) {
            scene->loadFromFile(f);
        }
    }
}
void MainWindow::on_AddBall_triggered(){
    scene->addBall();
}
