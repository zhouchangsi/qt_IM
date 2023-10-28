#include "moveable_frameless_window.h"

MoveableFramelessWindow::MoveableFramelessWindow(QWidget* parent)
    : QWidget(parent), is_moving_(false) {
  // 设置窗体为无边框
  this->setWindowFlags(Qt::FramelessWindowHint);
  // 设置底层背景透明
  this->setAttribute(Qt::WA_TranslucentBackground);
}

void MoveableFramelessWindow::mousePressEvent(QMouseEvent* event) {
  // 判断位置
  bool should_move =
      is_point_in_draggable_widget(get_draggable_widget(), event->pos());
  if (should_move) {
    pressed_point_ = event->pos();
    is_moving_ = true;
  }
  event->ignore();
}

void MoveableFramelessWindow::mouseMoveEvent(QMouseEvent* event) {
  if ((event->buttons() == Qt::LeftButton) && is_moving_ == true) {
    QPoint current_point = this->pos();
    current_point.setX(current_point.x() + event->x() - pressed_point_.x());
    current_point.setY(current_point.y() + event->y() - pressed_point_.y());
    this->move(current_point);
  }
}

void MoveableFramelessWindow::mouseReleaseEvent(QMouseEvent* event) {
  is_moving_ = false;
}

bool MoveableFramelessWindow::is_point_in_draggable_widget(
    const QWidget* widget,
    const QPoint& point) {
  // 判断位置
  QRect rect = widget->rect();
  bool is_in_ = point.x() >= rect.left() && point.x() <= rect.right() &&
                point.y() >= rect.top() && point.y() <= rect.bottom();
  return is_in_;
}
