#ifndef TESTMW_H
#define TESTMW_H


#include "mainwindow.h"
#include <QObject>
#include <QtTest>

class QLineEdit;
class QPushButton;
class QLabel;

class TestMW : public QObject
{
    Q_OBJECT

public:
    TestMW() = default;
    ~TestMW() = default;

private slots:
    void init();

    void testUiDynamics();

    void testCalculations_data();
    void testCalculations();
private:
    MainWindow mw;
};

#endif // TESTMW_H
