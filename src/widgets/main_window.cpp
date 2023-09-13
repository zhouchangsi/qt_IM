#include "main_window.h"

#include "ui_main_window.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QLabel* label = new QLabel("Hello, world!");
  ui->vertical_layout->addWidget(label);
  ui->vertical_layout->setAlignment(
      Qt::AlignCenter);  // set alignment to center
  ui->central_widget->setLayout(
      ui->vertical_layout);  // set the layout to central widget
}

MainWindow::~MainWindow() {
  delete ui;
}
