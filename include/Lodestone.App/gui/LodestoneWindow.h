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

#include "Lodestone.App/gui/screens/MainScreen.h"

namespace lodestone::app {
class LodestoneApp;
}

namespace lodestone::app::gui {
  class LodestoneWindow : public QMainWindow {
    Q_OBJECT

  public:
    LodestoneWindow(LodestoneApp *app, QWidget *parent = nullptr);

    QWidget *currentScreen() const {
      return this->m_screens->currentWidget();
    }

  private:
    screens::MainScreen *m_mainScreen;

    QStackedWidget *m_screens;
  };
}

#endif // LODESTONE_LODESTONEWINDOW_H