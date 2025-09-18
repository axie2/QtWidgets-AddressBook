#include <QtTest/QtTest>
#include <QAction>
#include <QPushButton>
#include <QLineEdit>
#include <QDialog>
#include <QTableView>
#include <QSignalSpy>
#include "../mainwindow.h"


class TestAddressBook : public QObject {
    Q_OBJECT

    private slots:
        void testAddContact();
        void testRemoveContact();
};

// ---------------- Add Contact Test ----------------
void TestAddressBook::testAddContact()
{
    MainWindow w;
    w.show();

    // Access Add QAction
    QAction *addAction = w.getAddAction();
    QVERIFY(addAction);

    // Spy on the selectionChanged signal
    QSignalSpy spy(w.getAddressWidget(), &AddressWidget::selectionChanged);

    // Trigger Add Entry action
    addAction->trigger();

    // Interact with Add Contact dialog
    QDialog *dialog = w.findChild<QDialog*>();
    QVERIFY(dialog);

    QLineEdit *nameEdit = dialog->findChild<QLineEdit*>("nameLineEdit");
    QLineEdit *addressEdit = dialog->findChild<QLineEdit*>("addressTextEdit");
    QVERIFY(nameEdit);
    QVERIFY(addressEdit);

    QTest::keyClicks(nameEdit, "John Doe");
    QTest::keyClicks(addressEdit, "123 Main St");

    QPushButton *okButton = dialog->findChild<QPushButton*>("okButton");
    QVERIFY(okButton);
    QTest::mouseClick(okButton, Qt::LeftButton);

    // Check that selectionChanged was emitted
    QVERIFY(spy.count() > 0);
}

// ---------------- Remove Contact Test ----------------
void TestAddressBook::testRemoveContact()
{
    MainWindow w;
    w.show();

    AddressWidget *aw = w.getAddressWidget();
    QVERIFY(aw);

    // Add a contact via Add Entry dialog (or directly if allowed)
    QAction *addAction = w.getAddAction();
    addAction->trigger();
    QDialog *dialog = w.findChild<QDialog*>();
    QVERIFY(dialog);

    QLineEdit *nameEdit = dialog->findChild<QLineEdit*>("nameLineEdit");
    QLineEdit *addressEdit = dialog->findChild<QLineEdit*>("addressTextEdit");
    QTest::keyClicks(nameEdit, "Alice");
    QTest::keyClicks(addressEdit, "111 First St");

    QPushButton *okButton = dialog->findChild<QPushButton*>("okButton");
    QTest::mouseClick(okButton, Qt::LeftButton);

    // Select the contact in the table (simulate user clicking first row)
    QTableView *table = aw->findChild<QTableView*>();
    QVERIFY(table);
    table->selectRow(0);

    // Spy on selectionChanged
    QSignalSpy spy(aw, &AddressWidget::selectionChanged);

    // Trigger Remove action
    QAction *removeAction = w.getRemoveAction();
    QVERIFY(removeAction);
    removeAction->trigger();

    // Verify that selectionChanged signal was emitted
    QVERIFY(spy.count() > 0);
}


// Generates main() automatically for Qt Test
QTEST_MAIN(TestAddressBook)
#include "test_addressbook.moc"
