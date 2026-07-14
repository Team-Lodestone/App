/** @file QtNativeExtensionLoader.h
*
 * @author Zero_DSRS_VX
 * @date 7/12/26
 *
 * @device PC
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */

#ifndef QT_NATIVE_EXTENSION_LOADER_H
#define QT_NATIVE_EXTENSION_LOADER_H

#include <QPluginLoader>
#include <Lodestone.Core/loader/NativeExtensionLoader.h>
#include <LodestoneCoreExt/plugin/LodestoneAppExtension.h>

#include "Lodestone.App/LodestoneApp.h"

class QtNativeExtensionLoader : public lodestone::core::loader::NativeExtensionLoader {
    lodestone::app::LodestoneApp* m_app;

public:
    using PluginEntry = std::pair<std::unique_ptr<QPluginLoader>, LodestoneAppExtension *>;

    map_t<QString, PluginEntry> m_extensions;

    QtNativeExtensionLoader(lodestone::app::LodestoneApp* app, const std::filesystem::path &extensionsDirectory, lodestone::core::Lodestone *core)
        : NativeExtensionLoader(extensionsDirectory, core) {
        this->m_app = app;
    }

    void load() override;
};

#endif //QT_NATIVE_EXTENSION_LOADER_H
