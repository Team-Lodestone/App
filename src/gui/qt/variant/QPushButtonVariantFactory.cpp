/** @file QPushButtonVariantFactory.cpp
 *
 * @author DexrnZacAttack
 * @date 3/17/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.App/gui/qt/variant/QPushButtonVariantFactory.h"

namespace lodestone::app::gui::qt::variant {
  QPushButton* QPushButtonVariantFactory::createWithIcon(const QIcon& icon, const QSize &size, const QString &tooltip, QWidget *parent) {
    const auto btn = new QPushButton(parent);

    if (!icon.isNull()) {
      btn->setIcon(icon);
      btn->setIconSize(size);
      btn->setToolTip(tooltip);
    } else {
      btn->setText(tooltip);
    }

    return btn;
  }
}