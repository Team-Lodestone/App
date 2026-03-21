/** @file LodestoneWindow.h
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#ifndef LODESTONE_LODESTONEWINDOW_H
#define LODESTONE_LODESTONEWINDOW_H
#include "Lodestone.App/gui/screen/Screen.h"
#include "Lodestone.App/gui/screen/screens/OptionsScreen.h"

#include <qtmetamacros.h>
#include <QMainWindow>
#include <QStackedWidget>
#include <stack>


namespace lodestone::app {
    class LodestoneApp;
}

namespace lodestone::app::gui {
    namespace screen::screens {
        class AboutScreen;
        class OptionsScreen;
        class MainScreen;
    }

    class LodestoneWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit LodestoneWindow(LodestoneApp *app, QWidget *parent = nullptr);

        [[nodiscard]] screen::Screen *currentTabElement() const {
            return static_cast<screen::Screen *>(this->m_tabs->currentWidget());
        }

        [[nodiscard]] int currentTab() const {
            return this->m_tabs->currentIndex();
        }

        void switchTab(const int idx) const {
            this->m_tabs->setCurrentIndex(idx);
        }

        int addTab(screen::Screen *screen, bool switchTo = false) const;

        screen::screens::MainScreen *mainScreen;
        screen::screens::AboutScreen *aboutScreen;
    private:
        LodestoneApp *m_app;

        QTabWidget *m_tabs;
    };
}

#endif // LODESTONE_LODESTONEWINDOW_H