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

#include "Lodestone.App/options/manager/NativeOptionsManager.h"
#include "Lodestone.App/util/Environment.h"

#include <print>
#include <string>

#include <BinaryIO/Exports.h>
#include "Lodestone.Core/loader/NativeExtensionLoader.h"
#include "Lodestone.Core/loader/ExtensionLoader.h"
#include "Lodestone.Common/LodestoneCommon.h"
#include "Lodestone.Common/event/Cancellable.h"

#include <QStandardPaths>
#include <fstream>

namespace lodestone::app {
    LodestoneApp::LodestoneApp(int argc, char *argv[], core::Lodestone *core) : m_core(core),
                                                                                m_application(argc, argv), m_window(this) {
    }

    void LodestoneApp::initialize() {
        std::println("Lodestone.App {}", std::string(VERSION));

        QCoreApplication::setOrganizationName("Team Lodestone");
        QCoreApplication::setApplicationName("Project Lodestone");
        QCoreApplication::setApplicationVersion(QString::fromUtf8(LodestoneApp::VERSION.toVersionString()));
        QGuiApplication::setWindowIcon(QIcon(":/assets/icons/icon.ico"));
        QGuiApplication::setDesktopFileName("Lodestone");

        //init filesystem garbage
        std::array<std::filesystem::path, 2> requiredDirectories = {{
            util::Environment::getConfigDirectory(),
            util::Environment::getStorageDirectory()
        }};

        std::ranges::for_each(requiredDirectories, [](const std::filesystem::path &p) {
            if (!std::filesystem::exists(p)) {
                std::filesystem::create_directories(p);
            }
        });

        this->m_optionsManager = new options::manager::NativeOptionsManager();
        this->m_optionsManager->optionsLoadedEvent.subscribe([] {
           std::println("Loaded options");
        });

        this->m_optionsManager->optionsSavedEvent.subscribe([] {
           std::println("Saved options");
        });

        this->m_optionsManager->backup();
        this->m_optionsManager->load();

        this->m_optionsManager->save();

        std::println("== Libraries ==");
        std::println("{}", lodestone::common::lodestone_get_library_string());
        std::println("{}", bio::bio_get_library_string());

        this->loadExtensions();
    }

    void LodestoneApp::run() {
        this->m_window.setFixedSize(800, 600);
        this->m_window.show();

        this->m_application.exec();

        this->stop();
    }

    void LodestoneApp::loadExtensions() {
        std::print("== Loading extensions ==\n");

        lodestone::core::loader::NativeExtensionLoader l(this->options().extensionsPath, this->m_core);
        l.extensionLoadingEvent += [](common::event::Cancellable &/*cancellable*/, const std::filesystem::path &p) {
            std::println("Initializing extension '{}'", p.generic_string());
        };

        l.extensionLoadedEvent += [this](const core::LodestoneExtension *ext) {
            std::println("Initialized extension '{}' {}", ext->getIdentifier(), ext->getVersion().toString());
            emit this->extensionInitialized(ext);
        };

        l.load();

        std::println("Loaded {} extensions", this->m_core->getExtensions().size());
    }

    void LodestoneApp::stop() {
        this->m_optionsManager->save();

        this->m_application.quit();
    }

    std::filesystem::path LodestoneApp::getOptionsPath() {
        return util::Environment::getConfigDirectory() / "options.json";
    }

    Options & LodestoneApp::options() const {
        return this->m_optionsManager->options();
    }
} // app

int main(const int argc, char *argv[]) {
    lodestone::app::LodestoneApp app(argc, argv, lodestone::core::Lodestone::getInstance());
    app.initialize();
    app.run();

    return 0;
}