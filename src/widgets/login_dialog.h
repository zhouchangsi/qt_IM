#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include "main_window.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog {
  Q_OBJECT

 public:
  explicit LoginDialog(QWidget* parent = 0);
  ~LoginDialog();

 private slots:
  void on_login_push_button_clicked();
  void show_wechat_window();

 private:
  Ui::LoginDialog* ui_;
  MainWindow* wechat_window_;
};


#endif  // LOGINDIALOG_H