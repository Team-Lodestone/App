/** @file MainScreen.cpp
 *
 * @author DexrnZacAttack
 * @date 3/17/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.App/gui/screen/screens/MainScreen.h"

#include <QLabel>
#include <QPushButton>

#include "Lodestone.App/LodestoneApp.h"
#include "Lodestone.App/gui/screen/screens/AboutScreen.h"
#include "Lodestone.App/gui/widgets/OpenTabButton.h"
#include "Lodestone.App/gui/widgets/TitleWidget.h"

#include <qicon.h>

namespace lodestone::app::gui::screen::screens {
    MainScreen::MainScreen(LodestoneApp *app, QWidget *parent) : Screen(app, parent) {
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
        QPushButton *aboutButton = (new widgets::OpenTabButton(
            &this->m_app->window(),
            [this] {
                return this->m_app->window().aboutScreen;
            },
        this
        ))->withIcon(aboutIcon)->withIconSize({24, 24})->withTooltip("About")->withFixedSize({36, 36});

        const QIcon optionsIcon = QIcon::fromTheme("configure");
        QPushButton *optionsButton = (new widgets::OpenTabButton(
            &this->m_app->window(),
            [this] {
                return new OptionsScreen(this->m_app);
            },
        this
        ))->withIcon(optionsIcon)->withIconSize({24, 24})->withTooltip("Options")->withFixedSize({36, 36});

        this->m_toolbar->addWidget(versionLabel);
        this->m_toolbar->addWidget(optionsButton);
        this->m_toolbar->addWidget(aboutButton);

        // OUTER OBJECTS INIT
        this->m_layout->addStretch();

        this->m_layout->addLayout(this->m_toolbar);
    }

    QString MainScreen::getTitle() {
        return "Lodestone";
    }
}