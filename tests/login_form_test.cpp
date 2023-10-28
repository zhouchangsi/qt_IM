#include "login_form.h"
#include <QApplication>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  LoginForm loginForm;
  loginForm.show();
  return app.exec();
}