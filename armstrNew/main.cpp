#include <QCoreApplication>
#include "mytest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}


myTest::myTest() {}

myTest::~myTest() {}

void myTest::init()
{
    num.set(n);
}

void myTest::digitsNum_data() {
    QTest::addColumn<int>("x");
    QTest::addColumn<int>("result");

    QTest::newRow("3 digits") << 123 << 3;
    QTest::newRow("Zero") << 0 << 1;
    QTest::newRow("1 digit") << 4<< 1;
    QTest::newRow("5 digits") << 21313 << 5;
    QTest::newRow("Negative") << -12 << 2;
}
void myTest::digitsNum() {
    QFETCH(int, x);
    QFETCH(int, result);

    num.set(x);

    QCOMPARE(num.countDigits(), result);
}



void myTest::Prime_data(){
    QTest::addColumn<int>("x");
    QTest::addColumn<bool>("result");

    QTest::newRow("Zero") << 0 << false;
    QTest::newRow("One") << 1 << false;
    QTest::newRow("Two") << 2 << true;
    QTest::newRow("Thirdteen") << 13 << true;
    QTest::newRow("one hundred") << 100 << false;
}
void myTest::Prime(){
    QFETCH(int, x);
    QFETCH(bool, result);

    num.set(x);

    QCOMPARE(num.isPrime(), result);
}



void myTest::Armstrong_data(){
    QTest::addColumn<int>("x");
    QTest::addColumn<bool>("result");

    QTest::newRow("0") << 0 << true;
    QTest::newRow("1") << 1 << true;
    QTest::newRow("153") << 153 << true;
    QTest::newRow("8") << 8 << true;
    QTest::newRow("23") << 23 << false;
    QTest::newRow("42") << 42 << false;
    QTest::newRow("52") << 52 << false;
    QTest::newRow("213") << 213 << false;
}
void myTest::Armstrong(){
    QFETCH(int, x);
    QFETCH(bool, result);

    num.set(x);

    QCOMPARE(num.isArmstrong(), result);
}



void myTest::nod_data(){
    QTest::addColumn<int>("x");
    QTest::addColumn<int>("y");
    QTest::addColumn<int>("result");

    QTest::newRow("226 and 76") << 226 <<	76 << 2;
    QTest::newRow("193 and 238") << 193 << 238 << 1;
    QTest::newRow("278 and 166") << 278 << 166 << 2;
    QTest::newRow("2000000 and 100") << 2000000 << 100 << 100;
    QTest::newRow("29 and 153") << 29 << 153 << 1;
}
void myTest::nod(){
    QFETCH(int, x);
    QFETCH(int, y);
    QFETCH(int, result);

    num.set(x);

    QCOMPARE(num.nod(y), result);
}



void myTest::nok_data(){
    QTest::addColumn<int>("x");
    QTest::addColumn<int>("y");
    QTest::addColumn<int>("result");

    QTest::newRow("226 and 76") << 226 <<	76 << 8588;
    QTest::newRow("193 and 238") << 193 << 238 << 45934;
    QTest::newRow("278 and 166") << 278 << 166 << 23074;
    QTest::newRow("2000000 and 100") << 2000000 << 100 << 2000000;
    QTest::newRow("29 and 153") << 29 << 153 << 4437;
}
void myTest::nok(){
    QFETCH(int, x);
    QFETCH(int, y);
    QFETCH(int, result);

    num.set(x);

    QCOMPARE(num.nok(y), result);
}


//QTEST_APPLESS_MAIN(myTest)

//#include "myTest.moc"
