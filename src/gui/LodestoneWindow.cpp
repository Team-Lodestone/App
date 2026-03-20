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
  LodestoneWindow::LodestoneWindow(LodestoneApp* app, QWidget* parent) : QMainWindow(parent), m_app(app) {
    this->m_screens = new QStackedWidget(this);

    this->m_mainScreen = new screen::screens::MainScreen(app, this->m_screens);
    this->m_aboutScreen = new screen::screens::AboutScreen(app, this->m_screens);
    this->m_optionsScreen = nullptr;

    this->m_screens->insertWidget(static_cast<int>(ScreenIndex::MAIN_SCREEN), this->m_mainScreen);
    this->m_screens->insertWidget(static_cast<int>(ScreenIndex::ABOUT_SCREEN), this->m_aboutScreen);

    this->switchScreen(ScreenIndex::MAIN_SCREEN);
    this->setCentralWidget(this->m_screens);
  }
}