/** @file MainScreen.h
 *
 * @author DexrnZacAttack
 * @date 3/17/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_MAINSCREEN_H
#define LODESTONE_MAINSCREEN_H
#include "Lodestone.App/gui/screen/Screen.h"

#include <QVBoxLayout>
#include <QWidget>

namespace lodestone::app {
    class LodestoneApp;
}

namespace lodestone::app::gui::screen::screens {
    class MainScreen : public screen::Screen {
    public:
        explicit MainScreen(LodestoneApp *app, QWidget *parent = nullptr);

        QString getTitle() override;

    private:
        QVBoxLayout *m_layout;
        QHBoxLayout *m_toolbar;
    };
}

#endif // LODESTONE_MAINSCREEN_H