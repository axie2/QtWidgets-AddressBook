#include <QtTest/QTest>
#include <QAction>
#include <QPushButton>
#include <QLineEdit>
#include <QDialog>
#include <QTableView>
#include <QSignalSpy>
#include <QTextEdit>
#include <QTimer>

#include "../mainwindow.h"
#include "../addresswidget.h"
#include "../adddialog.h"
// #include "../tablemodel.h"

class TestAddressBook : public QObject {
    Q_OBJECT

private:
    MainWindow *mainWin = nullptr;
    AddressWidget *aw = nullptr;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testAddContact();
};

void TestAddressBook::initTestCase() {
    mainWin = new MainWindow();
    mainWin->show();
    QVERIFY(QTest::qWaitForWindowExposed(mainWin));

    aw = mainWin->getAddressWidget();
    QVERIFY(aw);
}

void TestAddressBook::cleanupTestCase() {
    delete mainWin;
    mainWin = nullptr;
    aw = nullptr;
}


// ---------------- Add Contact Test ----------------
void TestAddressBook::testAddContact()
{
    // MainWindow w;
    // w.show();
    // QVERIFY(QTest::qWaitForWindowExposed(&w));

    // AddressWidget *aw = w.getAddressWidget();
    // QVERIFY(aw);


    // Spy on the selectionChanged signal
    QSignalSpy spy(aw, &AddressWidget::selectionChanged);

    // Wait for the Add Entry dialog to appear
    // There might be an easier way to do this?
    // I can't use findChild here because AddressWidget::editEntry(),
    // creates a local AddDialog object on the stack.
    // Because it’s local, there’s no persistent pointer in the object tree for findChild() to see.
    QTimer::singleShot(150, [&]() {
        QDialog *dialog = qobject_cast<QDialog*>(QApplication::activeModalWidget());
        QVERIFY(dialog);
        QVERIFY(QTest::qWaitForWindowExposed(dialog));

        QLineEdit *nameEdit = dialog->findChild<QLineEdit*>("nameLineEdit");
        QVERIFY(nameEdit);
        QTextEdit *addressEdit = dialog->findChild<QTextEdit*>("addressTextEdit");
        QVERIFY(addressEdit);

        QTest::keyClicks(nameEdit, "John Doe");
        QTest::keyClicks(addressEdit, "123 Main St");

        QPushButton *okButton = dialog->findChild<QPushButton*>("okButton");
        QVERIFY(okButton);
        QTest::mouseClick(okButton, Qt::LeftButton);
    });

    // Trigger Add Entry action
    QAction *addAction = mainWin->getAddAction();
    QVERIFY(addAction);
    addAction->trigger();
    spy.wait(500);

    // Switch to the "JKL" tab before checking the table
    bool foundJKL = false;
    for (int i = 0; i < aw->count(); ++i) {
        if (aw->tabText(i) == "JKL") {
            aw->setCurrentIndex(i);
            foundJKL = true;
            break;
        }
    }
    QVERIFY(foundJKL);

    // Verify table contents
    QTableView *table = qobject_cast<QTableView*>(aw->currentWidget());
    QVERIFY(table);
    QAbstractItemModel *model = table->model();
    QCOMPARE(model->rowCount(), 1);
    QString name = table->model()->index(0, 0).data().toString();
    QCOMPARE(model->data(model->index(0, 0)).toString(), QString("John Doe"));
    QCOMPARE(model->data(model->index(0, 1)).toString(), QString("123 Main St"));
}





// Generates main() automatically for Qt Test
QTEST_MAIN(TestAddressBook)
#include "test_addressbook.moc"
