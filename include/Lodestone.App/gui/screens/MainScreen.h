/** @file MainScreen.h
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#ifndef LODESTONE_MAINSCREEN_H
#define LODESTONE_MAINSCREEN_H
#include <QVBoxLayout>
#include <QWidget>

#include "Lodestone.Core/Lodestone.h"

namespace lodestone::app {
class LodestoneApp;
}

namespace lodestone::app::gui::screens {
  class MainScreen : public QWidget {
    Q_OBJECT

  public:
    MainScreen(LodestoneApp *app, QWidget *parent = nullptr);

  public slots:
    void onExtensionRegistered(const core::LodestoneExtension *ext) const;

  private:
    LodestoneApp *m_app;

    QVBoxLayout *m_layout;
  };
}

#endif // LODESTONE_MAINSCREEN_H