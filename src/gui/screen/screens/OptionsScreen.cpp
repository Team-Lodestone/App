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

        this->m_layout->setContentsMargins(0, 0, 0, 0);
        this->m_layout->setSpacing(0);

        //CHILDREN INIT
        // TODO this should be DYNAMIC
        // or we should be able to properly sync with app->options()
        std::ranges::for_each(app->options().guiOptions().registeredOptions(), [this](const auto &p) {
            auto &[id, option] = p;

            this->m_layout->addWidget(new QLabel(QString::fromStdString(id.getString())));
            this->m_layout->addWidget(new QLabel(QString::fromStdString(option->displayName())));
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