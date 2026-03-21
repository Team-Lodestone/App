/** @file Screen.cpp
 *
 * @author DexrnZacAttack
 * @date 3/18/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.App/gui/screen/Screen.h"

namespace lodestone::app::gui::screen {
    Screen::Screen(LodestoneApp *app, QWidget *parent) : QWidget(parent), m_app(app) {}

    std::optional<QIcon> Screen::getIcon() {
        return std::nullopt;
    }
}