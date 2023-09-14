#include "main_window.h"
#include "file_client_dialog.h"
#include "file_server_dialog.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  init_main_window();
}

MainWindow::~MainWindow() {
  delete ui_;
}

void MainWindow::init_main_window() {
  udp_socket_ = new QUdpSocket(this);
  udp_port_ = 23232;
  udp_socket_->bind(udp_port_,
                    QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
  connect(udp_socket_, SIGNAL(readyRead()), this,
          SLOT(receive_and_process_udp_message()));
  file_server_dialog_ = new FileServerDialog(this);
  connect(file_server_dialog_, SIGNAL(sent_filename(QString)), this,
          SLOT(get_filename(QString)));
}

void MainWindow::broadcast_udp_message(MessageType message_type,
                                       QString username) {
  QByteArray byte_array;
  QDataStream write(&byte_array, QIODevice::WriteOnly);
  QString ip = get_local_host_ip();
  QString message = get_local_chat_message();
  write << message_type << username_;
  switch (message_type) {
    case ChatMessage:
      write << ip << message;
      break;
    case OnLine:
      write << ip;
      break;
    case OffLine:
      break;
    case Filename:
      write << ip << username << filename_;
      break;
    case RefuseFile:
      write << ip << username;  // ?
      break;
  }
  udp_socket_->writeDatagram(byte_array, byte_array.length(),
                             QHostAddress::Broadcast, udp_port_);
}

void MainWindow::closeEvent(QCloseEvent* event) {
  broadcast_udp_message(OffLine);
}

void MainWindow::get_filename(QString fname) {
  filename_ = fname;
  int row = ui_->userListTableWidget->currentRow();
  QString username = ui_->userListTableWidget->item(row, 0)->text();
  broadcast_udp_message(Filename, username);
}

QString MainWindow::get_local_host_ip() {
  QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
  foreach (QHostAddress address, addresses) {
    if (address.protocol() == QAbstractSocket::IPv4Protocol)
      return address.toString();
  }
  return 0;
}

QString MainWindow::get_local_chat_message() {
  QString chat_message = ui_->chatTextEdit->toHtml();
  ui_->chatTextEdit->clear();
  ui_->chatTextEdit->setFocus();
  return chat_message;
}

void MainWindow::handle_offline(QString name, QString time) {
  int row = ui_->userListTableWidget->findItems(name, Qt::MatchExactly)
                .first()
                ->row();
  ui_->userListTableWidget->removeRow(row);
  ui_->chatTextBrowser->setTextColor(Qt::gray);
  ui_->chatTextBrowser->setCurrentFont(QFont("Times New Roman", 12));
  ui_->chatTextBrowser->append(tr("%1 %2 离线！").arg(time).arg(name));
}

void MainWindow::handle_online(QString name, QString time) {
  bool notExist =
      ui_->userListTableWidget->findItems(name, Qt::MatchExactly).isEmpty();
  if (notExist) {
    QTableWidgetItem* newuser = new QTableWidgetItem(name);
    ui_->userListTableWidget->insertRow(0);
    ui_->userListTableWidget->setItem(0, 0, newuser);
    ui_->chatTextBrowser->setTextColor(Qt::gray);
    ui_->chatTextBrowser->setCurrentFont(QFont("Times New Roman", 12));
    ui_->chatTextBrowser->append(tr("%1 %2 上线！").arg(time).arg(name));
    broadcast_udp_message(OnLine);
  }
}

void MainWindow::on_search_push_button_clicked() {
  username_ = this->windowTitle();
  ui_->userLabel->setText(username_);
  broadcast_udp_message(OnLine);
}

void MainWindow::on_send_push_button_clicked() {
  broadcast_udp_message(ChatMessage);
}

void MainWindow::on_transmission_push_button_clicked() {
  if (ui_->userListTableWidget->selectedItems().isEmpty()) {
    QMessageBox::warning(0, tr("选择好友"), tr("请先选择文件接收方！"),
                         QMessageBox::Ok);
    return;
  }
  file_server_dialog_->show();
}

void MainWindow::receive_filename(QString name,
                                  QString ip,
                                  QString username,
                                  QString filename) {
  if (username_ == username) {
    int result = QMessageBox::information(
        this, tr("收到文件"),
        tr("好友 %1 给您发文件：\r\n%2，是否接收？").arg(name).arg(filename),
        QMessageBox::Yes, QMessageBox::No);
    if (result == QMessageBox::Yes) {
      QString _filename =
          QFileDialog::getSaveFileName(0, tr("保 存"), filename);
      if (!_filename.isEmpty()) {
        FileClientDialog* file_client_dialog = new FileClientDialog(this);
        file_client_dialog->set_file(_filename);
        file_client_dialog->set_server_address(QHostAddress(ip));
        file_client_dialog->show();
      }
    } else {
      broadcast_udp_message(RefuseFile, name);
    }
  }
}

void MainWindow::receive_and_process_udp_message() {
  while (udp_socket_->hasPendingDatagrams()) {
    QByteArray byte_array;
    byte_array.resize(udp_socket_->pendingDatagramSize());
    udp_socket_->readDatagram(byte_array.data(), byte_array.size());
    QDataStream read(&byte_array, QIODevice::ReadOnly);
    int message_type;
    read >> message_type;
    QString name, ip, chat_message, remote_name, file_name;
    QString current_time =
        QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    switch (message_type) {
      case ChatMessage: {
        read >> name >> ip >> chat_message;
        ui_->chatTextBrowser->setTextColor(Qt::darkGreen);
        ui_->chatTextBrowser->setCurrentFont(QFont("Times New Roman", 14));
        ui_->chatTextBrowser->append("【" + name + "】" + current_time);
        ui_->chatTextBrowser->append(chat_message);
        break;
      }
      case OnLine:
        read >> name >> ip;
        handle_online(name, current_time);
        break;
      case OffLine:
        read >> name;
        handle_offline(name, current_time);
        break;
      case Filename:
        read >> name >> ip >> remote_name >> file_name;
        receive_filename(name, ip, remote_name, file_name);
        break;
      case RefuseFile:
        read >> name >> ip >> remote_name;
        if (username_ == remote_name)
          file_server_dialog_->handle_client_refused();
        break;
    }
  }
}
