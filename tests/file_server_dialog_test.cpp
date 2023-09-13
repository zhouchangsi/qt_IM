// #include "file_server_dialog.h"
// #include <QApplication>
// #include <QtTest>

// class FileServerDialogTest : public QObject {
//   Q_OBJECT

//  private:
//   bool myCondition() { return true; }

//  private slots:
//   void initTestCase() {
//     qDebug("Called before everything else.");
//     int argc = 0;
//     char* argv[] = {nullptr};
//     QApplication a(argc, argv);
//     FileServerDialog* dialog;
//     dialog->show();
//     a.exec();
//   }

//   void myFirstTest() {
//     QVERIFY(true);   // check that a condition is satisfied
//     QCOMPARE(1, 1);  // compare two values
//   }

//   void mySecondTest() {
//     QVERIFY(myCondition());
//     QVERIFY(1 != 2);
//   }

//   void cleanupTestCase() {
//     qDebug("Called after myFirstTest and mySecondTest.");
//   }
// };

// QTEST_MAIN(FileServerDialogTest)

// #include "file_server_dialog_test.moc"

#include <QApplication>
#include "file_server_dialog.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  FileServerDialog* dialog;
  dialog->show();
  return a.exec();
}