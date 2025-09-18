#include <QtTest/QtTest>
#include "mainwindow.h"

class TestAddressBook : public QObject
{
    Q_OBJECT

private slots:
    void testWindowTitle();
    void testAddContact();
};

void TestAddressBook::testWindowTitle()
{
    MainWindow w;
    w.show();
    QCOMPARE(w.windowTitle(), QString("Address Book"));
}

void TestAddressBook::testAddContact()
{
    MainWindow w;
    w.show();

    // simulate clicking "Add Contact" button
    QPushButton *addButton = w.findChild<QPushButton*>("addButton");
    QVERIFY(addButton);  // check button exists

    QTest::mouseClick(addButton, Qt::LeftButton);

    // simulate filling the dialog
    QDialog *dialog = w.findChild<QDialog*>();
    QVERIFY(dialog);

    QLineEdit *nameEdit = dialog->findChild<QLineEdit*>("nameLineEdit");
    QLineEdit *addressEdit = dialog->findChild<QLineEdit*>("addressTextEdit");

    QTest::keyClicks(nameEdit, "John Doe");
    QTest::keyClicks(addressEdit, "123 Main St");

    QPushButton *okButton = dialog->findChild<QPushButton*>("okButton");
    QTest::mouseClick(okButton, Qt::LeftButton);

    // verify contact was added
    QCOMPARE(w.contactCount(), 1);
}

QTEST_MAIN(TestAddressBook)
#include "testaddressbook.moc"
