/** @file LodestoneScreen.h
 *
 * @author DexrnZacAttack
 * @date 3/18/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_LODESTONESCREEN_H
#define LODESTONE_LODESTONESCREEN_H

#include <QWidget>

namespace lodestone::app {
    class LodestoneApp;
}

namespace lodestone::app::gui::screen {
    class Screen : public QWidget {
        Q_OBJECT

    protected:
        explicit Screen(LodestoneApp *app, QWidget *parent = nullptr);

        LodestoneApp *m_app;
    };
}

#endif // LODESTONE_LODESTONESCREEN_H