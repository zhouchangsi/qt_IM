#ifndef FILESRVDLG_H
#define FILESRVDLG_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>

class QFile;
class QTcpServer;
class QTcpSocket;

namespace Ui {
class FileServerDialog;
}

class FileServerDialog : public QDialog {
  Q_OBJECT

 public:
  explicit FileServerDialog(QWidget* parent = 0);
  ~FileServerDialog();
  void on_client_refused();

 protected:
  void closeEvent(QCloseEvent*);

 private slots:
  void send_chat_message();

  void refresh_progress(qint64 bynum);

  void on_open_file_push_button_clicked();

  void on_send_file_push_button_clicked();

  void on_stop_push_button_clicked();

 private:
  Ui::FileServerDialog* ui_;
  QTcpServer* tcp_server_;
  QTcpSocket* server_socket_;
  qint16 server_port_;

  QFile* file_;
  QString filepath_;  // absolute path
  QString filename_;

  qint64 file_total_bytes_;
  qint64 sent_bytes_;
  qint64 remaining_bytes_;
  qint64 payload_capacity_;
  QByteArray cache_data_of_1_transmission_;
  QTime time_;
 signals:
  void sent_file_name(QString name);
};

#endif  // FILESRVDLG_H
