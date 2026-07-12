//
// Created by zero on 7/12/26.
//

#ifndef QT_NATIVE_EXTENSION_LOADER_H
#define QT_NATIVE_EXTENSION_LOADER_H

#include <qguiapplication.h>
#include <QPluginLoader>
#include <Lodestone.Core/loader/NativeExtensionLoader.h>
#include <LodestoneCoreExt/plugin/LodestoneAppExtension.h>

class QtNativeExtensionLoader : public lodestone::core::loader::NativeExtensionLoader {
    QGuiApplication* m_app;

public:
    using PluginEntry = std::pair<std::unique_ptr<QPluginLoader>, LodestoneAppExtension *>;

    map_t<QString, PluginEntry> m_extensions;

    QtNativeExtensionLoader(QGuiApplication* app, const std::filesystem::path &extensionsDirectory, lodestone::core::Lodestone *core)
        : NativeExtensionLoader(extensionsDirectory, core) {
        this->m_app = app;
    }

    void load() override;
};

#endif //QT_NATIVE_EXTENSION_LOADER_H
