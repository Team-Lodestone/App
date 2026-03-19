/** @file NativeOptionsManager.h
 *
 * @author DexrnZacAttack
 * @date 3/18/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_NATIVEOPTIONSMANAGER_H
#define LODESTONE_NATIVEOPTIONSMANAGER_H
#include "Lodestone.App/options/manager/OptionsManager.h"

namespace lodestone::app::options::manager {
    class NativeOptionsManager : public OptionsManager {
    public:
        NativeOptionsManager();

        void load() override;
        void save() override;
        void backup() override;
    private:
        std::filesystem::path m_optionsDirectory;
        std::filesystem::path m_optionsFilePath;
    };
}

#endif // LODESTONE_NATIVEOPTIONSMANAGER_H