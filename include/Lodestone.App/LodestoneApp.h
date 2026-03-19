/** @file LodestoneApp.h
 *
 * @author DexrnZacAttack
 * @date 3/11/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#ifndef PROJECT_LODESTONE_LODESTONEAPP_H
#define PROJECT_LODESTONE_LODESTONEAPP_H
#include "Lodestone.App/Options.h"

#include <Lodestone.Common/util/Semver.h>
#include <Lodestone.Core/Lodestone.h>
#include <QApplication>

#include "Lodestone.App/gui/LodestoneWindow.h"
#include "Lodestone.App/options/manager/OptionsManager.h"

#include <filesystem>

#ifdef LODESTONE_APP_MAJOR_VERSION
#define MAJOR LODESTONE_APP_MAJOR_VERSION
#else
#define MAJOR 0
#endif

#ifdef LODESTONE_APP_MINOR_VERSION
#define MINOR LODESTONE_APP_MINOR_VERSION
#else
#define MINOR 0
#endif

#ifdef LODESTONE_APP_PATCH_VERSION
#define PATCH LODESTONE_APP_PATCH_VERSION
#else
#define PATCH 0
#endif

#ifdef LODESTONE_APP_DEV_VERSION
#define DEV LODESTONE_APP_DEV_VERSION
#else
#define DEV common::util::Semver::NONE
#endif

namespace lodestone::app {
    class LodestoneApp : public QObject {
        Q_OBJECT

    public:
        static constexpr common::util::Semver VERSION{MAJOR, MINOR, PATCH, DEV};

        LodestoneApp(int argc, char *argv[], core::Lodestone *core);

        void initialize();

        void run();

        void stop();

        void loadExtensions();

        core::Lodestone *core() const {
            return this->m_core;
        }

        gui::LodestoneWindow &window() {
            return this->m_window;
        }

        static std::filesystem::path getOptionsPath();

        Options &options() const;

    signals:
        void extensionInitialized(const core::LodestoneExtension *extension);

    private:
        core::Lodestone *m_core;
        options::manager::OptionsManager *m_optionsManager;

        QApplication m_application;
        gui::LodestoneWindow m_window;
    };
} // app
// lodestone

#endif // PROJECT_LODESTONE_LODESTONEAPP_H