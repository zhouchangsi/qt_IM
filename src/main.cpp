#include <QApplication>
#include "login_dialog.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  LoginDialog login_dialog;
  login_dialog.show();
  return a.exec();
}
