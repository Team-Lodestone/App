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

        enum class ScreenIndex : int {
            MAIN_SCREEN,
            ABOUT_SCREEN,
            OPTIONS_SCREEN
        };

        [[nodiscard]] screen::Screen *currentScreenElement() const {
            return static_cast<screen::Screen *>(this->m_screens->currentWidget());
        }

        [[nodiscard]] ScreenIndex currentScreen() const {
            return static_cast<ScreenIndex>(this->m_screens->currentIndex());
        }

        void switchScreen(const ScreenIndex idx) {
            if (this->currentScreenElement() != nullptr)
                m_previousScreens.push(this->currentScreenElement());

            if (idx == ScreenIndex::OPTIONS_SCREEN) {
                // TODO TODO TODO VERY TEMPORARY
                // we will switch to tabbed interface, and then handle screen instances there.
                // this is for testing and development of the options stuffs
                this->m_optionsScreen = new screen::screens::OptionsScreen(this->m_app, this);
                this->m_screens->insertWidget(static_cast<int>(ScreenIndex::OPTIONS_SCREEN), this->m_optionsScreen);
            }

            this->m_screens->setCurrentIndex(static_cast<int>(idx));
        }

        void switchToPreviousScreen() {
            if (this->m_previousScreens.empty())
                return;

            QWidget *s = this->m_previousScreens.top();
            this->m_previousScreens.pop();

            //dont want to switch to some invalid screen
            //this can cause issues especially when we'll want to have dynamically instanced screens
            if (s == nullptr) {
                this->switchToPreviousScreen();
                return;
            }

            this->m_screens->setCurrentWidget(s);
        }

    private:
        LodestoneApp *m_app;

        screen::screens::MainScreen *m_mainScreen;
        screen::screens::AboutScreen *m_aboutScreen;
        screen::screens::OptionsScreen *m_optionsScreen;

        std::stack<screen::Screen *> m_previousScreens;

        QStackedWidget *m_screens;
    };
}

#endif // LODESTONE_LODESTONEWINDOW_H