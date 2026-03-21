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
#include "Lodestone.App/gui/screen/screens/AboutScreen.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include <ranges>
#include <print>

#include "Lodestone.App/LodestoneApp.h"
#include "Lodestone.App/gui/widgets/TitleWidget.h"
#include "Lodestone.Common/LodestoneCommon.h"

namespace lodestone::app::gui::screen::screens {
    AboutScreen::AboutScreen(LodestoneApp *app, QWidget *parent) : Screen(app, parent) {
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        const auto outer = new QVBoxLayout(this);

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

        const auto registeredExtensionsContainer = new QGroupBox("Registered Extensions", this);
        registeredExtensionsContainer->setLayout(this->m_registeredExtensions);

        this->m_layout->addWidget(registeredExtensionsContainer);

        //OUTER INIT
        const auto libVersionLabel = new QLabel("libLodestone v" + QString::fromUtf8(lodestone::common::lodestone_get_version_string()));
        outer->addWidget(libVersionLabel, 0, Qt::AlignLeft | Qt::AlignBottom);
    }

    QString AboutScreen::getTitle() {
        return "About";
    }

    std::optional<QIcon> AboutScreen::getIcon() {
        return QIcon::fromTheme("help-about");
    }

    void AboutScreen::onExtensionRegistered(const core::LodestoneExtension *ext) const {
        this->m_registeredExtensions->addWidget(
            new QLabel(
                QString::fromStdString(
                    std::format("{} {}", ext->getIdentifier(), ext->getVersion().toString())
                    )
                )
            );
    }
}