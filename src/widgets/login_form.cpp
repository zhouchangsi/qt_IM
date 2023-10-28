#include "login_form.h"
#include "ui_login_form.h"

LoginForm::LoginForm(QWidget* parent) : ui_(new Ui::LoginForm) {
  ui_->setupUi(this);
  connect(ui_->login_push_button, SIGNAL(clicked()), this,
          SLOT(on_login_push_button_clicked()));

  connect(ui_->find_password_label, SIGNAL(clicked()), this,
          SLOT([]() { qDebug() << "find password"; }));
}

LoginForm::~LoginForm() {
  delete ui_;
}

void LoginForm::on_login_push_button_clicked() {
  // this->hide();
}
