/** @file BuildableQPushButton.h
 *
 * @author DexrnZacAttack
 * @date 3/20/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_BUILDABLEQPUSHBUTTON_H
#define LODESTONE_BUILDABLEQPUSHBUTTON_H
#include <QPushButton>

namespace lodestone::app::gui::widgets::builder {
    // TODO still kind of messy
    class BuildableQPushButton : public QPushButton {
    public:
        explicit BuildableQPushButton(QWidget *parent = nullptr);

        BuildableQPushButton *withIcon(const QIcon &icon);
        BuildableQPushButton *withIconSize(QSize size);

        BuildableQPushButton *withTooltip(const QString &tooltip);
        BuildableQPushButton *withText(const QString &text);

        BuildableQPushButton *withFixedSize(QSize size);
    };
}

#endif // LODESTONE_BUILDABLEQPUSHBUTTON_H