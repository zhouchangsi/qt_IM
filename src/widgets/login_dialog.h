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
  void on_loginPushButton_clicked();
  void showWeiChatWindow();

 private:
  Ui::LoginDialog* ui;
  MainWindow* weiChatWindow;
};


#endif  // LOGINDIALOG_H