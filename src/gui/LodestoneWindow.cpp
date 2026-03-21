/** @file LodestoneWindow.cpp
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#include "Lodestone.App/gui/LodestoneWindow.h"
#include "Lodestone.App/gui/LodestoneWindow.h"

#include "Lodestone.App/LodestoneApp.h"
#include "Lodestone.App/gui/screen/screens/AboutScreen.h"
#include "Lodestone.App/gui/screen/screens/MainScreen.h"
#include "Lodestone.App/gui/screen/screens/OptionsScreen.h"

namespace lodestone::app::gui {
    LodestoneWindow::LodestoneWindow(LodestoneApp *app, QWidget *parent) : QMainWindow(parent), m_app(app) {
        this->m_tabs = new QTabWidget(this);
        this->m_tabs->setTabsClosable(true);
        this->m_tabs->connect(this->m_tabs, &QTabWidget::tabCloseRequested, this, [this](const int idx) {
            if (idx == 0) { //never close the main tab
                return;
            }

            this->m_tabs->removeTab(idx);
        });

        this->mainScreen = new screen::screens::MainScreen(app);
        this->aboutScreen = new screen::screens::AboutScreen(app);

        this->addTab(mainScreen);
        this->setCentralWidget(this->m_tabs);
    }

    // TODO create wrapper class for Screen * to hold tab attributes
    int LodestoneWindow::addTab(screen::Screen *screen, const bool switchTo) const {
        const int t = this->m_tabs->addTab(screen, screen->getTitle());

        const std::optional<QIcon> icon = screen->getIcon();
        if (icon.has_value() && !icon.value().isNull()) {
            this->m_tabs->setTabIcon(t, icon.value());
        }

        if (switchTo) {
            this->switchTab(t);
        }

        return t;
    }
}