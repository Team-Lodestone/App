/** @file OptionsScreen.cpp
 *
 * @author DexrnZacAttack
 * @date 3/18/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.App/gui/screen/screens/OptionsScreen.h"

#include "Lodestone.App/LodestoneApp.h"

#include <QLabel>

namespace lodestone::app::gui::screen::screens {
    OptionsScreen::OptionsScreen(LodestoneApp *app, QWidget *parent) : Screen(app, parent) {
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        // LAYOUT INIT
        this->m_layout = new QVBoxLayout();
        this->m_layout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
        this->m_layout->setSpacing(10);

        //CHILDREN INIT
        std::ranges::for_each(app->options().guiOptions().registeredOptions(), [this](const auto &p) {
            auto &[id, option] = p;

            this->m_layout->addWidget(option->getWidget());
        });

        this->setLayout(this->m_layout);
    }

    QString OptionsScreen::getTitle() {
        return "Options";
    }

    std::optional<QIcon> OptionsScreen::getIcon() {
        return QIcon::fromTheme("configure");
    }
}