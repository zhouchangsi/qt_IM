#ifndef MOVEABLE_FRAMELESS_WINDOW_H
#define MOVEABLE_FRAMELESS_WINDOW_H

#include <QGridLayout>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QObject>
#include <QPoint>
#include <QRect>
#include <QWidget>

/**
 * @brief 无边框窗体
 */
class MoveableFramelessWindow : public QWidget {
  Q_OBJECT
 public:
  explicit MoveableFramelessWindow(QWidget* parent);

 protected:
  /**
   * @brief 鼠标按下，准备拖动窗体
   * @param event
   */
  void mousePressEvent(QMouseEvent* event) override;

  /**
   * @brief 鼠标移动，处理窗体拖动
   * @param event
   */
  void mouseMoveEvent(QMouseEvent* event) override;

  /**
   * @brief 释放鼠标
   * @param event
   */
  void mouseReleaseEvent(QMouseEvent* event) override;

  /**
   * @brief 获取可拖动控件，必须由子类指定
   * @return
   */
  virtual QWidget* get_draggable_widget() = 0;

  /**
   * @brief 判断鼠标点击的位置是否进入可拖动区域
   * @param widget 可拖动控件位置
   * @param point  鼠标点击位置
   * @return
   */
  bool is_point_in_draggable_widget(const QWidget* widget, const QPoint& point);

  /**
   * @brief 标志是否移动窗体
   */
  bool is_moving_;

  /**
   * @brief 鼠标按下去的点
   */
  QPoint pressed_point_;
 protected slots:
  // 主题改变
  virtual void on_theme_color_change(QString colorStr) {}
 signals:

 public slots:
};

#endif  // MOVEABLE_FRAMELESS_WINDOW_H
