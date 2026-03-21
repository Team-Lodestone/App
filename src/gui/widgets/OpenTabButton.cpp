/** @file TabOpenButton.cpp
 *
 * @author DexrnZacAttack
 * @date 3/20/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.App/gui/widgets/OpenTabButton.h"

#include <QMouseEvent>

namespace lodestone::app::gui::widgets {
    OpenTabButton::OpenTabButton(LodestoneWindow *window, const std::function<screen::Screen *()> &ctor, QWidget *parent) : BuildableQPushButton(parent), m_window(window), m_screenCtor(ctor) {}

    void OpenTabButton::mousePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::MiddleButton || event->button() == Qt::LeftButton) {
            this->m_window->addTab(this->m_screenCtor(), event->button() == Qt::LeftButton);
            return;
        }

        QPushButton::mousePressEvent(event);
    }
}