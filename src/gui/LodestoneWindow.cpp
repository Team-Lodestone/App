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

#include "Lodestone.App/gui/screens/MainScreen.h"

namespace lodestone::app::gui {
  LodestoneWindow::LodestoneWindow(LodestoneApp *app, QWidget* parent) : QMainWindow(
      parent) {
    this->m_screens = new QStackedWidget(this);
    this->m_mainScreen = new screens::MainScreen(app, this->m_screens);

    this->m_screens->addWidget(this->m_mainScreen);

    this->m_screens->setCurrentIndex(0);
    setCentralWidget(this->m_screens);
  }
}