#include "file_server_dialog.h"
#include "ui_file_server_dialog.h"

FileServerDialog::FileServerDialog(QWidget* parent)
    : QDialog(parent), ui_(new Ui::FileServerDialog) {
  ui_->setupUi(this);
  tcp_server_ = new QTcpServer(this);
  server_port_ = 5555;
  connect(tcp_server_, SIGNAL(newConnection()), this,
          SLOT(send_chat_message()));
  tcp_server_->close();
  file_total_bytes_ = 0;
  sent_bytes_ = 0;
  remaining_bytes_ = 0;
  payload_capacity_ = 64 * 1024;
  ui_->send_progress_bar->reset();
  ui_->open_file_push_button->setEnabled(true);
  ui_->send_file_push_button->setEnabled(false);
}

FileServerDialog::~FileServerDialog() {
  delete ui_;
}

void FileServerDialog::send_chat_message() {
  ui_->send_file_push_button->setEnabled(false);
  server_socket_ = tcp_server_->nextPendingConnection();
  connect(server_socket_, SIGNAL(bytesWritten(qint64)), this,
          SLOT(refresh_progress(qint64)));
  file_ = new QFile(filepath_);
  file_->open((QFile::ReadOnly));
  file_total_bytes_ = file_->size();
  QDataStream send_stream(&cache_data_of_1_transmission_, QIODevice::WriteOnly);
  send_stream.setVersion(QDataStream::Qt_5_11);
  time_.start();  // 开始计时
  QString current_file =
      filepath_.right(filepath_.size() - filepath_.lastIndexOf('/') - 1);
  send_stream << qint64(0) << qint64(0) << current_file;
  file_total_bytes_ += cache_data_of_1_transmission_.size();
  send_stream.device()->seek(0);
  send_stream << file_total_bytes_
              << qint64((cache_data_of_1_transmission_.size() -
                         sizeof(qint64) * 2));
  remaining_bytes_ =
      file_total_bytes_ - server_socket_->write(cache_data_of_1_transmission_);
  cache_data_of_1_transmission_.resize(0);
}

void FileServerDialog::refresh_progress(qint64 byte_count) {
  qApp->processEvents();
  sent_bytes_ += (int)byte_count;
  if (remaining_bytes_ > 0) {
    cache_data_of_1_transmission_ =
        file_->read(qMin(remaining_bytes_, payload_capacity_));
    remaining_bytes_ -=
        (int)server_socket_->write(cache_data_of_1_transmission_);
    cache_data_of_1_transmission_.resize(0);
  } else {
    file_->close();
  }
  ui_->send_progress_bar->setMaximum(file_total_bytes_);
  ui_->send_progress_bar->setValue(sent_bytes_);
  ui_->file_size_line_edit->setText(
      tr("%1").arg(file_total_bytes_ / (1024 * 1024)) + " MB");
  ui_->sent_size_line_edit->setText(tr("%1").arg(sent_bytes_ / (1024 * 1024)) +
                                 " MB");
  if (sent_bytes_ == file_total_bytes_) {
    file_->close();
    tcp_server_->close();
    QMessageBox::information(0, QObject::tr("完毕"), "文件传输完成！");
  }
}

void FileServerDialog::on_open_file_push_button_clicked() {
  filepath_ = QFileDialog::getOpenFileName(this);
  if (!filepath_.isEmpty()) {
    filename_ =
        filepath_.right(filepath_.size() - filepath_.lastIndexOf('/') - 1);
    ui_->file_name_line_edit->setText(tr("%1").arg(filename_));
    ui_->send_file_push_button->setEnabled(true);
    ui_->open_file_push_button->setEnabled(false);
  }
}

void FileServerDialog::on_send_file_push_button_clicked() {
  if (!tcp_server_->listen(QHostAddress::Any, server_port_))  // 开始监听
  {
    QMessageBox::warning(0, QObject::tr("异常"),
                         "打开TCP端口出错,请检查网络连接！");
    close();
    return;
  }
  emit sent_file_name(filename_);
}

void FileServerDialog::on_stop_push_button_clicked() {
  if (tcp_server_->isListening()) {
    tcp_server_->close();
    file_->close();
    server_socket_->abort();
  }
  close();
}

void FileServerDialog::on_client_refused() {
  tcp_server_->close();
  QMessageBox::warning(0, QObject::tr("提示"), "对方拒绝接收！");
}

void FileServerDialog::closeEvent(QCloseEvent*) {
  on_stop_push_button_clicked();
}
