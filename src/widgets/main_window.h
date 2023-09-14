#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QUdpSocket>

class FileServerDialog;

namespace Ui {
class MainWindow;
}

enum MessageType {
  ChatMessage,
  OnLine,
  OffLine,
  Filename,
  RefuseFile
};  // 消息类型
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();
  void init_main_window();
  void handle_online(QString name, QString time);   // 处理新用户加入
  void handle_offline(QString name, QString time);  // 处理用户离开
  void broadcast_udp_message(MessageType message_type, QString username = "");
  QString get_local_host_ip();
  QString get_local_chat_message();  // 获取本端聊天信息内容
  void receive_filename(QString name,
                        QString ip,
                        QString username,
                        QString filename);

 protected:
  /**
   * @brief closeEvent 重写关闭窗口方法以便发送通知离开消息
   */
  void closeEvent(QCloseEvent* event) override;

 private slots:
  void on_send_push_button_clicked();

  void receive_and_process_udp_message();

  /**
   * 搜索所有在线用户
   */
  void on_search_push_button_clicked();

  void get_filename(QString);

  void on_transmission_push_button_clicked();

 private:
  Ui::MainWindow* ui_;
  QString username_ = "";
  QUdpSocket* udp_socket_;
  qint16 udp_port_;
  QString filename_;
  FileServerDialog* file_server_dialog_;
};

#endif  // MAINWINDOW_H