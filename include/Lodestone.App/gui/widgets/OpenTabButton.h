/** @file TabOpenButton.h
 *
 * @author DexrnZacAttack
 * @date 3/20/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_TABOPENBUTTON_H
#define LODESTONE_TABOPENBUTTON_H
#include "Lodestone.App/gui/LodestoneWindow.h"
#include "Lodestone.App/gui/widgets/builder/BuildableQPushButton.h"

#include <QPushButton>

namespace lodestone::app::gui::widgets {
    class OpenTabButton : public builder::BuildableQPushButton {
        Q_OBJECT

    public:
        OpenTabButton(LodestoneWindow *window, const std::function<screen::Screen *()> &ctor, QWidget *parent = nullptr);

        void mousePressEvent(QMouseEvent *event) override;

    private:
        LodestoneWindow *m_window;
        std::function<screen::Screen *()> m_screenCtor;
    };
}

#endif // LODESTONE_TABOPENBUTTON_H