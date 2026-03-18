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
#include <qtmetamacros.h>
#include <QMainWindow>
#include <QStackedWidget>
#include <stack>

#include "Lodestone.App/gui/screens/AboutScreen.h"

namespace lodestone::app {
class LodestoneApp;
}

namespace lodestone::app::gui {
namespace screens {
class MainScreen;
}

class LodestoneWindow : public QMainWindow {
    Q_OBJECT

  public:
    LodestoneWindow(LodestoneApp *app, QWidget *parent = nullptr);

    enum class ScreenIndex : int {
      MAIN_SCREEN,
      ABOUT_SCREEN
    };

    [[nodiscard]] QWidget *currentScreenElement() const {
      return this->m_screens->currentWidget();
    }

    [[nodiscard]] ScreenIndex currentScreen() const {
      return static_cast<ScreenIndex>(this->m_screens->currentIndex());
    }

    void switchScreen(const ScreenIndex idx) {
      if (this->currentScreenElement() != nullptr)
        m_previousScreens.push(this->currentScreenElement());

      this->m_screens->setCurrentIndex(static_cast<int>(idx));
    }

    void switchToPreviousScreen() {
      QWidget *s = this->m_previousScreens.top();
      this->m_previousScreens.pop();

      this->m_screens->setCurrentWidget(s);
    }

  private:
    screens::MainScreen *m_mainScreen;
    screens::AboutScreen *m_aboutScreen;

    std::stack<QWidget *> m_previousScreens;

    QStackedWidget *m_screens;
  };
}

#endif // LODESTONE_LODESTONEWINDOW_H