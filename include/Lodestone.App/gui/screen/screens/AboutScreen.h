/** @file AboutScreen.h
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#ifndef LODESTONE_ABOUTSCREEN_H
#define LODESTONE_ABOUTSCREEN_H
#include "Lodestone.App/gui/screen/Screen.h"

#include <QVBoxLayout>
#include <QWidget>

#include <Lodestone.Core/Lodestone.h>
#include <LodestoneCoreExt/plugin/LodestoneAppExtension.h>

namespace lodestone::app {
class LodestoneApp;
}

namespace lodestone::app::gui::screen::screens {
  class AboutScreen : public screen::Screen {
  public:
      explicit AboutScreen(LodestoneApp *app, QWidget *parent = nullptr);

      QString getTitle() override;
      std::optional<QIcon> getIcon() override;

  public slots:
    void onExtensionRegistered(const lodestone::core::LodestoneExtension *ext) const;
    void onPluginRegistered(const LodestoneAppExtension *plugin) const;

  private:
    QVBoxLayout *m_layout;
    QVBoxLayout *m_registeredExtensions;
    QVBoxLayout *m_registeredPlugins;
  };
}

#endif // LODESTONE_ABOUTSCREEN_H