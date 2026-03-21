/** @file BuildableQPushButton.cpp
 *
 * @author DexrnZacAttack
 * @date 3/20/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.App/gui/widgets/builder/BuildableQPushButton.h"

namespace lodestone::app::gui::widgets::builder {
    BuildableQPushButton::BuildableQPushButton(QWidget *parent) : QPushButton(parent) {
    }

    BuildableQPushButton * BuildableQPushButton::withIcon(const QIcon &icon) {
        this->setIcon(icon);

        return this;
    }

    BuildableQPushButton * BuildableQPushButton::withIconSize(const QSize size) {
        this->setIconSize(size);

        return this;
    }

    BuildableQPushButton * BuildableQPushButton::withTooltip(const QString &tooltip) {
        this->setToolTip(tooltip);

        return this;
    }

    BuildableQPushButton * BuildableQPushButton::withText(const QString &text) {
        this->setText(text);

        return this;
    }

    BuildableQPushButton * BuildableQPushButton::withFixedSize(const QSize size) {
        this->setFixedSize(size);

        return this;
    }
}