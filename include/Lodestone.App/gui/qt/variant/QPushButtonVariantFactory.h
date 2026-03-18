/** @file QPushButtonVariantFactory.h
 *
 * @author DexrnZacAttack
 * @date 3/17/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_QPUSHBUTTONVARIANTFACTORY_H
#define LODESTONE_QPUSHBUTTONVARIANTFACTORY_H
#include <QLabel>
#include <QPushButton>

namespace lodestone::app::gui::qt::variant {
  //I hate the boilerplate required just to create certain buttons
  //Maybe I should create a bunch of builder style classes
  class QPushButtonVariantFactory {
  public:
    [[nodiscard]] static QPushButton *createWithIcon(const QIcon& icon, const QSize &size, const QString &tooltip, QWidget *parent = nullptr);
  };
}

#endif // LODESTONE_QPUSHBUTTONVARIANTFACTORY_H