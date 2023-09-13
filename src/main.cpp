#include "login_dialog.h"

#include <QApplication>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  // MainWindow w;
  // w.show();
  // return a.exec();
  LoginDialog login_dialog;
  login_dialog.show();
  return a.exec();
}
