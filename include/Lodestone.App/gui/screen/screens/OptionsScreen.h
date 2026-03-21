/** @file OptionsScreen.h
 *
 * @author DexrnZacAttack
 * @date 3/18/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_OPTIONSSCREEN_H
#define LODESTONE_OPTIONSSCREEN_H
#include "Lodestone.App/Options.h"
#include "Lodestone.App/gui/screen/Screen.h"

#include <QVBoxLayout>

namespace lodestone::app::gui::screen::screens {
    class OptionsScreen : public screen::Screen {
    public:
        explicit OptionsScreen(LodestoneApp *app, QWidget *parent = nullptr);

        QString getTitle() override;
        std::optional<QIcon> getIcon() override;

    private:
        QVBoxLayout *m_layout;
    };
}

#endif // LODESTONE_OPTIONSSCREEN_H