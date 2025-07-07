#ifndef MYTEST_H
#define MYTEST_H

#include <QtTest>
#include "Armstrong.h"

// add necessary includes here

class myTest : public QObject
{
    Q_OBJECT

public:
    void init();
    myTest();
    ~myTest();

private slots:
    void digitsNum_data();
    void digitsNum();
    void Prime_data();
    void Prime();
    void Armstrong_data();
    void Armstrong();
    void nod_data();
    void nod();
    void nok_data();
    void nok();
private:
    int n;
    Numbers num;
};


#endif // MYTEST_H
