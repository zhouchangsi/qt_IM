#include "login_dialog.h"
#include "ui_login_dialog.h"

LoginDialog::LoginDialog(QWidget* parent)
    : QDialog(parent), ui_(new Ui::LoginDialog) {
  ui_->setupUi(this);
  ui_->password_line_edit->setFocus();
  QPixmap pixmap("./resources/images/login.jpg");
  ui_->label->setPixmap(pixmap);
  ui_->label->setScaledContents(true);
}

LoginDialog::~LoginDialog() {
  delete ui_;
}

void LoginDialog::on_login_push_button_clicked() {
  show_wechat_window();
}

void LoginDialog::show_wechat_window() {
  bool exist = false;
  QString username = "user1";
  QString password = "123456";

  // auto clear = [&]() {
  //   ui_->user_line_edit->clear();
  //   ui_->password_line_edit->clear();
  //   ui_->user_line_edit->setFocus();
  // };

  // if (username != ui_->user_line_edit->text()) {
  //   QMessageBox::warning(0, QObject::tr("提示"), "此用户不存在！请重新输入。");
  //   // clear();
  //   return;
  // }

  // if (password != ui_->password_line_edit->text()) {
  //   QMessageBox::warning(0, QObject::tr("提示"), "口令错！请重新输入。");
  //   // clear();
  //   return;
  // }

  wechat_window_ = new MainWindow(0);
  wechat_window_->setWindowTitle(ui_->user_line_edit->text());
  wechat_window_->show();
  // this->destroy();
}
