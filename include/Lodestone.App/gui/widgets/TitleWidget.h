/** @file TitleWidget.h
 *
 * @author DexrnZacAttack
 * @date 3/17/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_TITLEWIDGET_H
#define LODESTONE_TITLEWIDGET_H
#include <QWidget>

namespace lodestone::app::gui::widgets {
  class TitleWidget : public QWidget {
    Q_OBJECT
  public:
    explicit TitleWidget(QWidget *parent = nullptr);
  };
}

#endif // LODESTONE_TITLEWIDGET_H