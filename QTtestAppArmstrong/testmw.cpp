#include "testmw.h"
#include "ui_mainwindow.h"

void TestMW::init()
{
    mw.ui->num1->clear();
    mw.ui->num2->clear();
    mw.ui->answer->clear();
    mw.ui->options->setCurrentIndex(0);
    mw.ui->num2->show();
}

void TestMW::testUiDynamics()
{
    mw.ui->num2->show();
    //QVERIFY(mw.ui->num2->isVisible());
    mw.ui->options->setCurrentIndex(2);

    QVERIFY(!mw.ui->num2->isVisible());

    mw.ui->options->setCurrentIndex(0);

    //(mw.ui->num2->isVisible());
}


void TestMW::testCalculations_data()
{
    QTest::addColumn<int>("optionIndex");
    QTest::addColumn<QString>("num1");
    QTest::addColumn<QString>("num2");
    QTest::addColumn<QString>("expected");

    QTest::newRow("NOD_normal")       << 0 << "54" << "24" << "6";
    QTest::newRow("NOD_num1_empty")   << 0 << ""   << "24" << "Error";
    QTest::newRow("NOD_num2_empty")   << 0 << "54" << ""   << "Error";

    QTest::newRow("NOK_normal")       << 1 << "21" << "6" << "42";
    QTest::newRow("NOK_num2_empty")   << 1 << "21" << ""  << "Error";

    QTest::newRow("IsPrime_true")     << 2 << "13" << "" << "True";
    QTest::newRow("IsPrime_false")    << 2 << "12" << "" << "False";
    QTest::newRow("IsPrime_one")      << 2 << "1"  << "" << "False";

    QTest::newRow("IsArmstrong_true") << 3 << "153" << "" << "True";
    QTest::newRow("IsArmstrong_false")<< 3 << "154" << "" << "False";
    QTest::newRow("IsArmstrong_zero") << 3 << "0"   << "" << "True";

    QTest::newRow("Digits_normal")    << 4 << "12345" << "" << "5";
    QTest::newRow("Digits_zero")      << 4 << "0"     << "" << "1";
}
void TestMW::testCalculations()
{
    QFETCH(int, optionIndex);
    QFETCH(QString, num1);
    QFETCH(QString, num2);
    QFETCH(QString, expected);

    mw.ui->options->setCurrentIndex(optionIndex);
    QTest::keyClicks(mw.ui->num1, num1);
    QTest::keyClicks(mw.ui->num2, num2);

    QTest::mouseClick(mw.ui->solve, Qt::LeftButton);

    QCOMPARE(mw.ui->answer->text(), expected);
}


QTEST_MAIN(TestMW)

