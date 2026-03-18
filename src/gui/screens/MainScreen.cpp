/** @file MainScreen.cpp
 *
 * @author DexrnZacAttack
 * @date 3/17/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.App/gui/screens/MainScreen.h"

#include <QLabel>
#include <QPushButton>

#include "Lodestone.App/LodestoneApp.h"
#include "Lodestone.App/gui/qt/variant/QPushButtonVariantFactory.h"
#include "Lodestone.App/gui/widgets/TitleWidget.h"

namespace lodestone::app::gui::screens {
  MainScreen::MainScreen(LodestoneApp* app, QWidget* parent) : m_app(app) {
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // MAIN LAYOUT INIT
    this->m_layout = new QVBoxLayout(this);
    this->m_layout->setAlignment(Qt::AlignTop);

    //INNER LAYOUT INIT
    auto innerLayout = new QVBoxLayout();
    innerLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    this->m_layout->addLayout(innerLayout);

    //INNER OBJECTS INIT
    innerLayout->addWidget(new widgets::TitleWidget());

    // TOOLBAR INIT
    this->m_toolbar = new QHBoxLayout(this);

    //TOOLBAR OBJECTS INIT
    QLabel *versionLabel = new QLabel(QString::fromStdString(LodestoneApp::VERSION.toString()));
    versionLabel->setAlignment(Qt::AlignBottom | Qt::AlignLeft);

    const QIcon aboutIcon = QIcon::fromTheme("help-about");
    QPushButton *aboutButton = qt::variant::QPushButtonVariantFactory::createWithIcon(aboutIcon, {24, 24}, "About", this);
    aboutButton->setFixedSize(36, 36);

    QPushButton::connect(aboutButton, &QPushButton::clicked, this, &MainScreen::onAboutButtonClicked);

    this->m_toolbar->addWidget(versionLabel);
    this->m_toolbar->addWidget(aboutButton);

    // OUTER OBJECTS INIT
    this->m_layout->addStretch();

    this->m_layout->addLayout(this->m_toolbar);
  }

  void MainScreen::onAboutButtonClicked() {
    this->m_app->window().switchScreen(LodestoneWindow::ScreenIndex::ABOUT_SCREEN);
  }
}