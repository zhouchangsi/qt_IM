#include "login_dialog.h"
#include "ui_login_dialog.h"

LoginDialog::LoginDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::LoginDialog) {
  ui->setupUi(this);
  ui->pwdLineEdit->setFocus();
  QPixmap pixmap("./resources/login.jpg");
  ui->label->setPixmap(pixmap);
  ui->label->setScaledContents(true);
}

LoginDialog::~LoginDialog() {
  delete ui;
}

void LoginDialog::on_loginPushButton_clicked() {
  showWeiChatWindow();
}

void LoginDialog::showWeiChatWindow() {
  bool exist = false;
  QString username = "user1";
  QString password = "123456";

  // auto clear = [&]() {
  //   ui->usrLineEdit->clear();
  //   ui->pwdLineEdit->clear();
  //   ui->usrLineEdit->setFocus();
  // };

  if (username != ui->usrLineEdit->text()) {
    QMessageBox::warning(0, QObject::tr("提示"), "此用户不存在！请重新输入。");
    // clear();
    return;
  }

  if (password != ui->pwdLineEdit->text()) {
    QMessageBox::warning(0, QObject::tr("提示"), "口令错！请重新输入。");
    // clear();
    return;
  }

  weiChatWindow = new MainWindow(0);
  weiChatWindow->setWindowTitle(ui->usrLineEdit->text());
  weiChatWindow->show();
  this->destroy();
}
