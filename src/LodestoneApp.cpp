/** @file LodestoneApp.cpp
*
 * @author DexrnZacAttack
 * @date 3/11/26
 *
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#include "Lodestone.App/LodestoneApp.h"
#include <print>
#include <string>

#include <BinaryIO/Exports.h>
#include "Lodestone.Core/loader/NativeExtensionLoader.h"
#include "Lodestone.Core/loader/ExtensionLoader.h"
#include "Lodestone.Common/LodestoneCommon.h"
#include "Lodestone.Common/event/Cancellable.h"

namespace lodestone::app {
  LodestoneApp::LodestoneApp(int argc, char *argv[], core::Lodestone* core) : m_core(core),
    m_application(argc, argv), m_window(this) {
  }

  void LodestoneApp::initialize() {
    std::print("Lodestone.App v{}\n", std::string(VERSION));

    std::print("== Libraries ==\n");
    std::print("{}\n", lodestone::common::lodestone_get_library_string());
    std::print("{}\n", bio::bio_get_library_string());

    std::print("== Loading extensions ==\n");

    lodestone::core::loader::NativeExtensionLoader l(this->m_core);
    l.extensionLoadingEvent += [](common::event::Cancellable &/*cancellable*/, const std::filesystem::path &p) {
      std::print("Initializing extension '{}'\n", p.c_str());
    };

    l.extensionLoadedEvent += [this](const core::LodestoneExtension *ext) {
      std::print("Initialized extension '{}' v{}\n", ext->getIdentifier(), ext->getVersion().toString());
      emit this->extensionInitialized(ext);
    };

    l.load();

    std::print("Loaded {} extensions", this->m_core->getExtensions().size());
  }

  void LodestoneApp::run() {
    this->m_window.setFixedSize(800, 600);
    this->m_window.show();

    this->m_application.exec();
  }

  void LodestoneApp::stop() const {
    this->m_application.quit();
  }
} // app

int main(const int argc, char *argv[]) {
  lodestone::app::LodestoneApp app(argc, argv, lodestone::core::Lodestone::getInstance());
  app.initialize();
  app.run();

  return 0;
}