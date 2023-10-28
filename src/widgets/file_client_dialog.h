#ifndef FILECNTDLG_H
#define FILECNTDLG_H

#include <QDialog>
#include <QFile>
#include <QHostAddress>
#include <QTcpSocket>
#include <QTime>

class QTcpSocket;

namespace Ui {
class FileClientDialog;
}

class FileClientDialog : public QDialog {
  Q_OBJECT

 public:
  explicit FileClientDialog(QWidget* parent = 0);
  ~FileClientDialog();
  void set_server_address(QHostAddress saddr);
  void set_file(QString path);

 protected:
  void closeEvent(QCloseEvent*);

 private slots:
  void connect_to_server();

  void read_chat_message();

  void on_client_close_push_button_clicked();

 private:
  Ui::FileClientDialog* ui_;
  QTcpSocket* client_socket_;
  QHostAddress server_address_;
  qint16 server_port_;

  qint64 total_bytes_;
  qint64 received_bytes_;
  QByteArray transmission_block_;
  quint16 block_size_;

  QFile* file_;
  QString filename_;
  qint64 filesize_;

  QTime time_;
};

#endif  // FILECNTDLG_H