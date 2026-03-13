/** @file MainScreen.cpp
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#include "Lodestone.App/gui/screens/MainScreen.h"
#include <QVBoxLayout>
#include <QLabel>
#include <ranges>
#include <print>

#include "Lodestone.App/LodestoneApp.h"

namespace lodestone::app::gui::screens {
  MainScreen::MainScreen(LodestoneApp* app, QWidget* parent) : QWidget(parent), m_app(app) {
    this->m_layout = new QVBoxLayout(this);
    this->m_layout->setSizeConstraint(QLayout::SetMaximumSize);

    connect(app, &LodestoneApp::extensionInitialized, this, &MainScreen::onExtensionRegistered);
  }

  void MainScreen::onExtensionRegistered(const core::LodestoneExtension* ext) const {
      this->m_layout->addWidget(
        new QLabel(
          QString::fromStdString(
            std::format("{} v{}", ext->getIdentifier(), ext->getVersion().toString())
          )
        )
      );
  }
}