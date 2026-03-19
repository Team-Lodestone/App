/** @file NativeOptionsManager.cpp
 *
 * @author DexrnZacAttack
 * @date 3/18/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.App/options/manager/NativeOptionsManager.h"

#include "Lodestone.App/LodestoneApp.h"
#include "Lodestone.App/util/Environment.h"

#include <fstream>
#include <system_error>

namespace lodestone::app::options::manager {
    NativeOptionsManager::NativeOptionsManager() {
        this->m_optionsDirectory = util::Environment::getConfigDirectory();
        this->m_optionsFilePath = LodestoneApp::getOptionsPath();
    }

    void NativeOptionsManager::load() {
        std::ifstream f(this->m_optionsFilePath);
        f.exceptions(std::ios::failbit | std::ios::badbit);

        this->m_options = Options::fromJson(f);

        this->optionsLoadedEvent.notify();
    }

    void NativeOptionsManager::save() {
        std::ofstream f(this->m_optionsFilePath, std::ios::trunc);
        f.exceptions(std::ios::failbit | std::ios::badbit);

        f << this->m_options.toJson().dump();

        this->optionsSavedEvent.notify();
    }

    void NativeOptionsManager::backup() {
        if (std::filesystem::exists(this->m_optionsFilePath)) {
            std::filesystem::path backupPath = this->m_optionsFilePath;
            backupPath.replace_extension(".json.bak");

            std::filesystem::copy_file(this->m_optionsFilePath, backupPath, std::filesystem::copy_options::overwrite_existing);
        }
    }
}