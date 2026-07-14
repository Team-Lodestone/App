/** @file QtNativeExtensionLoader.cpp
*
 * @author Zero_DSRS_VX
 * @date 7/12/26
 *
 * @device PC
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */

#include "Lodestone.App/loader/QtNativeExtensionLoader.h"

#include <QDir>
#include <QPluginLoader>

#include "LodestoneCoreExt/plugin/LodestoneAppExtension.h"

void QtNativeExtensionLoader::load() {
    NativeExtensionLoader::load();

    // Load statically linked plugins
    for (const QStaticPlugin &plugin : QPluginLoader::staticPlugins()) {
        QObject *instance = plugin.instance();

        if (auto *extension = qobject_cast<LodestoneAppExtension *>(instance)) {
            QJsonObject metadata = plugin.metaData().value("MetaData").toObject();
            QString pluginId = metadata.value("Id").toString();

            if (this->m_extensions.contains(pluginId)) {
                throw std::runtime_error("Tried to register plugin with id that already exists.");
            }

            this->m_extensions.emplace(
                pluginId,
                std::make_pair(std::move(nullptr), extension)
            );

            emit this->m_app->notifyPluginInitialized(extension);
        }
    }

    // Load dynamically linked plugins
    // TODO: Refactor to settings
    const QDir pluginsDir = this->m_app->applicationDirPath() + "/plugins/";

    const auto entryList = pluginsDir.entryList(QDir::Files);

    for (const QString &fileName: entryList) {
        const auto filePath = pluginsDir.absoluteFilePath(fileName);

        auto pluginLoader = std::make_unique<QPluginLoader>(filePath);
        if (const auto instance = pluginLoader->instance()) {
            if (auto *extension = qobject_cast<LodestoneAppExtension *>(instance); extension) {
                QJsonObject metadata = pluginLoader->metaData().value("MetaData").toObject();
                QString pluginId = metadata.value("Id").toString();

                if (this->m_extensions.contains(pluginId)) {
                    throw std::runtime_error("Tried to register plugin with id that already exists.");
                }

                this->m_extensions.emplace(
                    pluginId,
                    std::make_pair(std::move(pluginLoader), extension)
                );

                emit this->m_app->notifyPluginInitialized(extension);
            }
        } else {
            qDebug() << pluginLoader->errorString();
        }
    }
}
