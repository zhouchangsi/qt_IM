#pragma once

#include <QGridLayout>
#include <QWidget>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget {
  Q_OBJECT

 public:
  explicit LoginForm(QWidget* parent = 0);
  ~LoginForm();

 protected:
 private slots:
  /**
   * @brief 登录按钮点击
   */
  void on_login_push_button_clicked();

 private:
  Ui::LoginForm* ui_;
};
