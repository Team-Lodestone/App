/** @file AboutScreen.cpp
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#include "Lodestone.App/gui/screens/AboutScreen.h"
#include "Lodestone.App/gui/screens/AboutScreen.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include <ranges>
#include <print>

#include "Lodestone.App/LodestoneApp.h"
#include "Lodestone.App/gui/widgets/TitleWidget.h"
#include "Lodestone.Common/LodestoneCommon.h"

namespace lodestone::app::gui::screens {
  AboutScreen::AboutScreen(LodestoneApp* app, QWidget* parent) : QWidget(parent), m_app(app) {
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *outer = new QVBoxLayout(this);

    // LAYOUT INIT
    this->m_layout = new QVBoxLayout();
    this->m_layout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    this->m_layout->setContentsMargins(0, 0, 0, 0);
    this->m_layout->setSpacing(0);

    outer->addLayout(this->m_layout);

    //CHILDREN INIT
    //add title
    this->m_layout->addWidget(new widgets::TitleWidget());

    //REGISTERED EXTENSIONS INIT
    this->m_registeredExtensions = new QVBoxLayout();
    connect(app, &LodestoneApp::extensionInitialized, this, &AboutScreen::onExtensionRegistered);

    QGroupBox *registeredExtensionsContainer = new QGroupBox("Registered Extensions", this);
    registeredExtensionsContainer->setLayout(this->m_registeredExtensions);

    this->m_layout->addWidget(registeredExtensionsContainer);

    //OUTER INIT

    QIcon backIcon = QApplication::style()->standardIcon(QStyle::SP_ArrowLeft);

    QPushButton *backButton = new QPushButton(this);

    if (!backIcon.isNull()) {
      backButton->setIcon(backIcon);
      backButton->setIconSize({24, 24});
    } else {
      backButton->setText("Go back");
    }

    backButton->connect(backButton, &QPushButton::clicked, this, &AboutScreen::onBackButtonClicked);
    backButton->show();
    backButton->move(5, 5);

    QLabel *libVersionLabel = new QLabel("libLodestone v" + QString::fromUtf8(lodestone::common::lodestone_get_version_string()));
    outer->addWidget(libVersionLabel, 0, Qt::AlignLeft | Qt::AlignBottom);
  }

  void AboutScreen::onExtensionRegistered(const core::LodestoneExtension* ext) const {
      this->m_registeredExtensions->addWidget(
        new QLabel(
          QString::fromStdString(
            std::format("{} v{}", ext->getIdentifier(), ext->getVersion().toString())
          )
        )
      );
  }

  void AboutScreen::onBackButtonClicked() {
    this->m_app->window().switchToPreviousScreen();
  }
}