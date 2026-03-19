/** @file Environment.cpp
 *
 * @author DexrnZacAttack
 * @date 3/18/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.App/util/Environment.h"

#include <QStandardPaths>
#include <qcoreapplication.h>

namespace lodestone::app::util {
    std::filesystem::path Environment::getStorageDirectory() {
        return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).toStdString();
    }

    std::filesystem::path Environment::getConfigDirectory() {
        return QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation).toStdString();
    }

    std::filesystem::path Environment::getCurrentDirectory() {
        return QCoreApplication::applicationDirPath().toStdString();
    }
}