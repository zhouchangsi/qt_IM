#include "file_client_dialog.h"
#include "ui_file_client_dialog.h"

FileClientDialog::FileClientDialog(QWidget* parent)
    : QDialog(parent), ui_(new Ui::FileClientDialog) {
  ui_->setupUi(this);
  client_socket_ = new QTcpSocket(this);
  server_port_ = 5555;
  connect(client_socket_, SIGNAL(readyRead()), this, SLOT(read_chat_message()));
  filesize_ = 0;
  total_bytes_ = 0;
  received_bytes_ = 0;
}

FileClientDialog::~FileClientDialog() {
  delete ui_;
}

void FileClientDialog::set_file(QString path) {
  file_ = new QFile(path);
}

void FileClientDialog::set_server_address(QHostAddress server_address) {
  server_address_ = server_address;
  connect_to_server();
}

void FileClientDialog::connect_to_server() {
  block_size_ = 0;
  client_socket_->abort();
  client_socket_->connectToHost(server_address_, server_port_);
  time_.start();
}

void FileClientDialog::read_chat_message() {
  QDataStream in(client_socket_);
  in.setVersion(QDataStream::Qt_5_11);
  float used_time = time_.elapsed();
  if (received_bytes_ <= sizeof(qint64) * 2) {
    if ((client_socket_->bytesAvailable() >= sizeof(qint64) * 2) &&
        (filesize_ == 0)) {
      in >> total_bytes_ >> filesize_;
      received_bytes_ += sizeof(qint64) * 2;
    }
    if ((client_socket_->bytesAvailable() >= filesize_) && (filesize_ != 0)) {
      in >> filename_;
      received_bytes_ += filesize_;
      file_->open(QFile::WriteOnly);
      ui_->file_name_line_edit->setText(filename_);
    } else {
      return;
    }
  }
  if (received_bytes_ < total_bytes_) {
    received_bytes_ += client_socket_->bytesAvailable();
    transmission_block_ = client_socket_->readAll();
    file_->write(transmission_block_);
    transmission_block_.resize(0);
  }
  ui_->receive_progress_bar->setMaximum(total_bytes_);
  ui_->receive_progress_bar->setValue(received_bytes_);
  double transmission_speed = received_bytes_ / used_time;
  ui_->file_size_line_edit->setText(tr("%1").arg(total_bytes_ / (1024 * 1024)) +
                                    " MB");
  ui_->receive_size_line_edit->setText(
      tr("%1").arg(received_bytes_ / (1024 * 1024)) + " MB");
  ui_->rate_label->setText(
      tr("%1").arg(transmission_speed * 1000 / (1024 * 1024), 0, 'f', 2) +
      " MB/秒");
  if (received_bytes_ == total_bytes_) {
    file_->close();
    client_socket_->close();
    ui_->rate_label->setText("接收完毕！");
  }
}

void FileClientDialog::on_client_close_push_button_clicked() {
  client_socket_->abort();
  file_->close();
  close();
}

void FileClientDialog::closeEvent(QCloseEvent*) {
  on_client_close_push_button_clicked();
}
